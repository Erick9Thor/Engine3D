#include "core/hepch.h"

#include "ModuleResources.h"
#include "ModuleEvent.h"
#include "ModuleFileSystem.h"
#include "ModuleSceneManager.h"
#include "ModuleEditor.h"

#include "Core/preferences/src/ResourcesPreferences.h"

#include "importers/MeshImporter.h"
#include "importers/TextureImporter.h"
#include "importers/MaterialImporter.h"
#include "importers/ModelImporter.h"

#include "components/ComponentMesh.h"
#include "components/ComponentMaterial.h"
#include "resources/ResourceModel.h"
#include "resources/ResourceMaterial.h"
#include "resources/ResourceTexture.h"

using namespace Hachiko;

bool ModuleResources::Init()
{
    preferences = App->preferences->GetResourcesPreference();

    // create assets & library directory tree
    for (int i = 0; i < static_cast<int>(Resource::Type::UNKNOWN); ++i)
    {
        App->file_sys->CreateDir(preferences->GetLibraryPath(static_cast<Resource::Type>(i)));
        App->file_sys->CreateDir(preferences->GetAssetsPath(static_cast<Resource::Type>(i)));
    }

    std::function handleAddedFile = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<FileAddedEventPayload>();
        std::filesystem::path file = e.GetPath();
        HE_LOG("Handling dropped file: %s", file.string().c_str());
        HandleResource(file);
    };
    App->event->Subscribe(Event::Type::FILE_ADDED, handleAddedFile);
    return true;
}

bool ModuleResources::CleanUp()
{
    for (auto& it : models)
    {
        delete it.second;
    }

    for (auto& it : meshes)
    {
        delete it.second;
    }

    for (auto& it : materials)
    {
        delete it.second;
    }

    for (auto& it : textures)
    {
        delete it.second;
    }

    return true;
}

std::filesystem::path ModuleResources::GetLastResourceLoadedPath() const
{
    return last_resource_path.parent_path();
}

void ModuleResources::HandleResource(const std::filesystem::path& path)
{
    Resource::Type type = GetType(path);
    if (type == Resource::Type::UNKNOWN)
    {
        HE_LOG("Unknown resource type recevied, nothing to be done");
        return;
    }

    // Copy to assets if it does not exist
    std::filesystem::path destination = preferences->GetAssetsPath(type);
    // Relative asset path
    std::filesystem::path asset_path = destination.append(path.filename().c_str());
    App->file_sys->Copy(path.string().c_str(), asset_path.string().c_str(), true);


    // Attempt import from assets
    if (!importer_manager.CheckIfImported(path.string().c_str(), type))
    {
        last_resource_path = path; // We may need this to import more assets from this path
        ImportResource(asset_path, type);
        HE_LOG("File destination: %s", destination.string().c_str());
    }
}

Resource::Type ModuleResources::GetType(const std::filesystem::path& path)
{
    if (!path.has_extension())
    {
        return Resource::Type::UNKNOWN;
    }
    const std::filesystem::path extension = path.extension();

    auto isValidExtension = [&](const std::pair<Resource::Type, std::string>& element)
    {
        return element.second.size() == extension.string().size() &&
            std::equal(element.second.begin(), element.second.end(), extension.string().begin(),
                       [](auto a, auto b) { return std::tolower(a) == std::tolower(b); });
    };

    const auto it = std::find_if(supported_extensions.begin(), supported_extensions.end(), isValidExtension);
    if (it != supported_extensions.end())
    {
        return it->first;
    }
    return Resource::Type::UNKNOWN;
}

ResourceModel* Hachiko::ModuleResources::GetModel(const std::string& name)
{
    auto it = models.find(name);
    if (it != models.end())
    {
        return it->second;
    }

    auto res = static_cast<ResourceModel*>(importer_manager.Load(Resource::Type::MODEL, name.c_str()));

    // TODO: This is a hack. We need to implement our own assert with message
    assert(res != nullptr && "Unable to return a valid model resource");
    models.emplace(name, res);

    return res;
}

ResourceMesh* Hachiko::ModuleResources::GetMesh(const UID uid, const std::string& model_path, int mesh_index)
{
    // 1 - Find locally
    auto it = meshes.find(uid);
    if (it != meshes.end())
    {
        return it->second;
    }

    // 2 - Import from disk
    auto res = static_cast<ResourceMesh*>(importer_manager.Load(Resource::Type::MESH, uid));
    
    // 3 - Cherry Import
    if (res == nullptr && !model_path.empty() && mesh_index > -1)
    {
        ModelImporter* mod_importer = static_cast<ModelImporter*>(importer_manager.GetImporter(Resource::Type::MODEL));
        res = static_cast<ResourceMesh*>(mod_importer->CherryImport(mesh_index, uid, model_path.c_str()));
    }

    // TODO: This is a hack. We need to implement our own assert with message
    assert(res != nullptr && "Unable to return a valid mesh resource");
    meshes.emplace(uid, res);
    
    return res;
}

ResourceMaterial* Hachiko::ModuleResources::GetMaterial(const std::string& material_name)
{
    auto it = materials.find(material_name);
    if (it != materials.end())
    {
        return it->second;
    }
    std::string material_path = App->preferences->GetResourcesPreference()->GetAssetsPath(Resource::Type::MATERIAL) + material_name;
    auto res = static_cast<ResourceMaterial*>(importer_manager.Load(Resource::Type::MATERIAL, material_path.c_str()));
    
    // TODO: This is a hack. We need to implement our own assert with message
    assert(res != nullptr && "Unable to return a valid material resource");
    materials.emplace(material_name, res);

    return res;
}

ResourceTexture* Hachiko::ModuleResources::GetTexture(const std::string& texture_name, const std::string& asset_path)
{
    if (texture_name.empty())
    {
        return nullptr;
    }

    auto it = textures.find(texture_name);
    if (it != textures.end())
    {
        return it->second;
    }

    auto res = static_cast<ResourceTexture*>(importer_manager.Load(Resource::Type::TEXTURE, texture_name.c_str()));
    
    if (res == nullptr && !asset_path.empty())
    {
        Hachiko::TextureImporter texture_importer;
        res = static_cast<ResourceTexture*>(texture_importer.ImportTexture(asset_path.c_str()));
    }
    
    // TODO: This is a hack. We need to implement our own assert with message
    assert(res != nullptr && "Unable to return a valid texture resource");
    textures.emplace(texture_name, res);

    return res;
}

Resource* Hachiko::ModuleResources::GetResource(Resource::Type type, UID resource_id)
{
    switch (type)
    {
    case Resource::Type::MESH:
        {
            return GetMesh(resource_id); 
        }
    default:
        return nullptr;
    }
}

void Hachiko::ModuleResources::CreateResource(Resource::Type type, const std::string& name) const
{
    switch (type)
    {
    case Resource::Type::MATERIAL:
        {
            MaterialImporter material_importer;
            material_importer.CreateMaterial(name);
        }
    }
}

void ModuleResources::ImportResource(const std::filesystem::path& asset_path, const Resource::Type asset_type)
{
    importer_manager.Import(asset_path.string(), asset_type);
}