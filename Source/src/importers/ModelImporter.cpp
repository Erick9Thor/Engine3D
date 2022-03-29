#include "Core/hepch.h"
#include "ModelImporter.h"
#include "MeshImporter.h"
#include "MaterialImporter.h"

#include "resources/ResourceModel.h"
#include "Modules/ModuleFileSystem.h"
#include "Core/preferences/src/ResourcesPreferences.h"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

Hachiko::ModelImporter::ModelImporter() : Importer(Importer::Type::MODEL)
{
}

void Hachiko::ModelImporter::Import(const char* path)
{
    HE_LOG("Entering ModelImporter: %s", path);
    Assimp::Importer import;
    //import.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
    const aiScene* scene = nullptr;
    const std::filesystem::path model_path(path);
    const std::string model_name = model_path.filename().replace_extension().string();
    const std::string model_library_path = GetResourcesPreferences()->GetLibraryPath(Resource::Type::MODEL) + model_name + MODEL_EXTENSION;
    scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        HE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }

    YAML::Node model_node;
    model_node[MODEL_ID] = UUID::GenerateUID();
    model_node[MODEL_FILE_PATH] = model_path.string();

    ImportModel(scene, model_node);

    App->file_sys->Save(model_library_path.c_str(), model_node);
}

void Hachiko::ModelImporter::ImportModel(const aiScene* scene, YAML::Node& node)
{
    Hachiko::MeshImporter mesh_importer;
    Hachiko::MaterialImporter material_importer;

    for (unsigned i = 0; i < scene->mNumMaterials; ++i)
    {
        aiMaterial* material = scene->mMaterials[i];
        Hachiko::UID material_id = UUID::GenerateUID();
        node[MODEL_MATERIAL_NODE][i][MATERIAL_ID] = material_id;
        node[MODEL_MATERIAL_NODE][i][MATERIAL_NAME] = scene->mMaterials[i]->GetName().C_Str();
        material_importer.Import(material, material_id);
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];
        Hachiko::UID mesh_id = UUID::GenerateUID();
        node[MODEL_MESH_NODE][i][MODEL_MESH_ID] = mesh_id;
        mesh_importer.Import(mesh, mesh_id);
    }

    // TODO: We are not considering that the root node could have a mesh or material
    ImportNode(scene->mRootNode, node);
}

void Hachiko::ModelImporter::ImportNode(const aiNode* assimp_node, YAML::Node& node)
{
    node[NODE_NAME] = assimp_node->mName.C_Str();
    node[NODE_TRANSFORM] = assimp_node->mTransformation;
    
    for (unsigned int j = 0; j < assimp_node->mNumMeshes; ++j)
    {
        node[NODE_MESH_INDEX][j] = assimp_node->mMeshes[j];
    }

    auto child_node = assimp_node->mChildren;
    for (unsigned i = 0; i < assimp_node->mNumChildren; ++i)
    {
        ImportNode(*child_node, node[NODE_CHILD][i]);
        node[NODE_CHILD][i][NODE_MATERIAL_INDEX][0] = 0; // Apply the same material for all childs
        ++child_node;
    }
}

Hachiko::Resource* Hachiko::ModelImporter::Load(const UID id)
{
    return nullptr;
}

Hachiko::Resource* Hachiko::ModelImporter::Load(const char* model_path)
{
    if (!std::filesystem::exists(model_path))
    {
        return nullptr;
    }

    YAML::Node model_node = YAML::LoadFile(model_path);
    Hachiko::ResourceModel* model_output = new ResourceModel(model_node[MODEL_ID].as<UID>());
    model_output->model_path = model_node[MODEL_FILE_PATH].as<std::string>();
    std::filesystem::path mp = model_node[MODEL_FILE_PATH].as<std::string>();
    model_output->model_name = mp.filename().replace_extension().string();
    LoadChilds(model_node[NODE_CHILD], model_node[MODEL_MESH_NODE], model_node[MODEL_MATERIAL_NODE], model_output->child_nodes);
    return model_output;
}

void Hachiko::ModelImporter::LoadChilds(YAML::Node& node, YAML::Node& meshes, YAML::Node& materials, std::vector<ResourceNode*>& childs)
{
    childs.reserve(node.size());
    for (int i = 0; i < node.size(); ++i)
    {
        ResourceNode* resource_node = new ResourceNode();
        resource_node->node_name = node[i][NODE_NAME].as<std::string>();
        resource_node->node_transform = node[i][NODE_TRANSFORM].as<float4x4>();

        // We only take the first element
        int mesh_idx = node[i][NODE_MESH_INDEX][0].as<int>();
        resource_node->material_name = materials[0][MATERIAL_NAME].as<std::string>();
        resource_node->mesh_id = meshes[mesh_idx][MODEL_MESH_ID].as<UID>();

        for (int j = 0; j < node[i][NODE_MESH_INDEX].size(); ++j)
        {
            resource_node->meshes_index.push_back(node[i][NODE_MESH_INDEX][j].as<int>());
        }
        
        if (node[i][NODE_CHILD].IsDefined())
        {
            LoadChilds(node[i][NODE_CHILD], meshes, materials, resource_node->childs);
        }

        childs.emplace_back(resource_node);
    }
}

void Hachiko::ModelImporter::Save(const Resource* resource) {}

Hachiko::Resource* Hachiko::ModelImporter::CherryImport(int mesh_index, const UID uid, const char* model_path)
{
    HE_LOG("ModelImporter::CherryImport");
    HE_LOG("Model path: %s", model_path)
    HE_LOG("UID: %ull", uid);
    HE_LOG("Mesh index: %d", mesh_index);

    const std::filesystem::path model(model_path);
  
    // 1 - Open assimp model
    Assimp::Importer import;
    const aiScene* scene = nullptr;
    scene = import.ReadFile(model.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        HE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return nullptr;
    }

    // 2 - Open model meta if exists. If not, create one
    const std::string model_name = model.filename().replace_extension().string();
    const std::string model_library_path = GetResourcesPreferences()->GetLibraryPath(Resource::Type::MODEL) + model_name + MODEL_EXTENSION;
    YAML::Node model_node;

    if (!std::filesystem::exists(model_library_path))
    {
        model_node[MODEL_ID] = UUID::GenerateUID();
        model_node[MODEL_FILE_PATH] = model.string();

        ImportNode(scene->mRootNode, model_node);
    }
    else
    {
        model_node = YAML::LoadFile(model_library_path);
    }

    model_node[MODEL_MESH_NODE][mesh_index][MODEL_MESH_ID] = uid;

    // 3 - Import Single Mesh
    MeshImporter mesh_importer;
    mesh_importer.Import(scene->mMeshes[mesh_index], uid);

    // 4- If ok, save new model data
    App->file_sys->Save(model_library_path.c_str(), model_node);

    return mesh_importer.Load(uid);
}


