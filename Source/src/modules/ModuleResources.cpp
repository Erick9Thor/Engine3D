#include "core/hepch.h"

#include "ModuleResources.h"
#include "ModuleEvent.h"
#include "ModuleSceneManager.h"
#include "ModuleEditor.h"

#include "core/preferences/src/ResourcesPreferences.h"

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
    for (int i = 1; i < static_cast<int>(Resource::Type::COUNT); ++i)
    {
        FileSystem::CreateDir(preferences->GetLibraryPath(static_cast<Resource::Type>(i)));
        FileSystem::CreateDir(preferences->GetAssetsPath(static_cast<Resource::Type>(i)));
    }

    AssetsLibraryCheck();

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
        RELEASE(it.second);
    }

    for (auto& it : meshes)
    {
        RELEASE(it.second);
    }

    for (auto& it : materials)
    {
        RELEASE(it.second);
    }

    for (auto& it : textures)
    {
        RELEASE(it.second);
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

    size_t relative_pos = path.string().find("assets\\");
    bool file_in_asset = relative_pos != std::string::npos;
    std::filesystem::path destination;

    if (file_in_asset)
    {
        HE_LOG("Resource file in assets folder");
        destination = std::filesystem::relative(path, path.string().substr(0, relative_pos));
    }
    else
    {
        HE_LOG("Resource file outside the assets folder");
        destination = preferences->GetAssetsPath(type);
        destination.append(path.filename().c_str());
        FileSystem::Copy(path.string().c_str(), destination.string().c_str(), true);
    }

    // Import asset
    if (!importer_manager.IsImported(path.string().c_str(), type))
    {
        last_resource_path = path; // We may need this to import more assets from this path
        ImportResource(destination, type);
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

//ResourceModel* Hachiko::ModuleResources::GetModel(const std::string& name)
//{
//    auto it = models.find(name);
//    if (it != models.end())
//    {
//        return it->second;
//    }
//    // Use always .model extension for loading
//    std::filesystem::path model_path(name);
//    auto res = static_cast<ResourceModel*>( importer_manager.Load(Resource::Type::MODEL, 
//            StringUtils::Concat(model_path.parent_path().string(), "\\", model_path.filename().replace_extension(META_EXTENSION).string()).c_str()));
//
//    // TODO: This is a hack. We need to implement our own assert with message
//    assert(res != nullptr && "Unable to return a valid model resource");
//    models.emplace(name, res);
//
//    return res;
//}
//
//ResourceMesh* Hachiko::ModuleResources::GetMesh(const UID uid, const std::string& model_path, int mesh_index)
//{
//    // 1 - Find locally
//    auto it = meshes.find(uid);
//    if (it != meshes.end())
//    {
//        return it->second;
//    }
//
//    // 2 - Import from disk
//    std::string mesh_path = preferences->GetLibraryPath(Resource::Type::MESH) + std::to_string(uid);
//    auto res = static_cast<ResourceMesh*>(importer_manager.Load(Resource::Type::MESH, mesh_path.c_str()));
//    
//    // 3 - Cherry Import
//    if (res == nullptr && !model_path.empty() && mesh_index > -1)
//    {
//        ModelImporter* mod_importer = static_cast<ModelImporter*>(importer_manager.GetImporter(Resource::Type::MODEL));
//        res = static_cast<ResourceMesh*>(mod_importer->CherryImport(mesh_index, uid, model_path.c_str()));
//    }
//
//    // TODO: This is a hack. We need to implement our own assert with message
//    assert(res != nullptr && "Unable to return a valid mesh resource");
//    meshes.emplace(uid, res);
//    
//    return res;
//}
//
//ResourceMaterial* Hachiko::ModuleResources::GetMaterial(const std::string& material_name)
//{
//    auto it = materials.find(material_name);
//    if (it != materials.end())
//    {
//        return it->second;
//    }
//    std::string material_path = App->preferences->GetResourcesPreference()->GetAssetsPath(Resource::Type::MATERIAL) + material_name;
//    auto res = static_cast<ResourceMaterial*>(importer_manager.Load(Resource::Type::MATERIAL, material_path.c_str()));
//    
//    // TODO: This is a hack. We need to implement our own assert with message
//    assert(res != nullptr && "Unable to return a valid material resource");
//    materials.emplace(material_name, res);
//
//    return res;
//}
//
//ResourceTexture* Hachiko::ModuleResources::GetTexture(const std::string& texture_name, const std::string& asset_path)
//{
//    if (texture_name.empty())
//    {
//        return nullptr;
//    }
//
//    auto it = textures.find(texture_name);
//    if (it != textures.end())
//    {
//        return it->second;
//    }
//
//    std::string texture_path = App->preferences->GetResourcesPreference()->GetLibraryPath(Resource::Type::TEXTURE) + texture_name;
//    auto res = static_cast<ResourceTexture*>(importer_manager.Load(Resource::Type::TEXTURE, texture_path.c_str()));
//    
//    if (res == nullptr && !asset_path.empty())
//    {
//        // TODO: Importing must be done by importer manager
//        Hachiko::TextureImporter texture_importer;
//        res = static_cast<ResourceTexture*>(texture_importer.ImportTexture(asset_path.c_str(), UUID::GenerateUID()));
//        res->GenerateBuffer();
//    }
//    
//    // TODO: This is a hack. We need to implement our own assert with message
//    assert(res != nullptr && "Unable to return a valid texture resource");
//    textures.emplace(texture_name, res);
//
//    return res;
//}

Resource* Hachiko::ModuleResources::GetResource(Resource::Type type, UID id)
{
    auto it = loaded_resources.find(id);
    if (it != loaded_resources.end())
    {
        return it->second;
    }

    auto res = importer_manager.Load(type, id);
    if (res != nullptr)
    {
        return loaded_resources.emplace(id, res).first->second;
    }

    return nullptr;
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

void Hachiko::ModuleResources::AssetsLibraryCheck()
{
    HE_LOG("Assets/Library check...");

    // TODO: use defined values, for extensions and assets
    std::vector<std::string> meta_ext { "meta" };
    PathNode assets_folder = FileSystem::GetAllFiles("assets", nullptr, &meta_ext);
    //PathNode assets_folder = FileSystem::GetAllFiles("assets", &meta_ext, nullptr); // TODO: check that all meta has its asset
    // TODO: check library folder

    //GenerateLibrary(assets_folder);

    HE_LOG("Assets/Library check finished.");
}

void Hachiko::ModuleResources::GenerateLibrary(const PathNode& folder) 
{
    for (PathNode path_node : folder.children)
    {
        if (path_node.isFile)
        {
            Resource::Type type = GetType(path_node.path);
            std::string meta_path = StringUtils::Concat(path_node.path, META_EXTENSION);

            if (FileSystem::Exists(meta_path.c_str()))
            {
                YAML::Node meta_node = YAML::LoadFile(meta_path);

                // Extract data from meta
                UID meta_uid = meta_node[GENERAL_NODE][GENERAL_ID].as<UID>();
                //node[GENERAL_NODE][GENERAL_FILE_PATH]
                //node[GENERAL_NODE][GENERAL_TYPE]
                FILETIME meta_timestamp = meta_node[GENERAL_NODE][GENERAL_LAST_WRITE_TIME].as<FILETIME>();
                
                std::string library_path = StringUtils::Concat(preferences->GetLibraryPath(type), std::to_string(meta_uid));
                bool library_file_exists = FileSystem::Exists(library_path.c_str());

                // Get the asset timestamp
                FILETIME asset_timestamp = GetFileLastWriteTime(StringUtils::StringToWString(path_node.path));

                if (CompareFileTime(&meta_timestamp, &asset_timestamp) != 0)
                {

                    if (library_file_exists)
                    {
                        importer_manager.DeleteWithMeta(type, meta_node);
                        // TODO: delete it -> should be done by the importer (to search dependent files as models with meshes)
                    }
                    // TODO: reimport + remake meta with new timestamp
                }
                else if (!library_file_exists)
                {
                    // TODO: import but with the meta -> overload, since we will need info of the meta has the uid, or in models case other things
                    continue;
                }
            }
            else
            {
                importer_manager.Import(std::filesystem::path(path_node.path), type);
            }
        }
        else
        {
            GenerateLibrary(path_node);
        }
    }
}

void ModuleResources::ImportResource(const std::filesystem::path& asset_path, const Resource::Type asset_type)
{
    importer_manager.Import(asset_path.string(), asset_type);
}