#include "core/hepch.h"
#include "GeometryBatch.h"

#include "../Components/ComponentMesh.h"

Hachiko::GeometryBatch::GeometryBatch(ResourceMesh::Layout batch_layout) {
    batch = new ResourceMesh(0);
    batch->layout = batch_layout;
}

Hachiko::GeometryBatch::~GeometryBatch() {
    RELEASE(batch);
}

void Hachiko::GeometryBatch::AddMesh(const ComponentMesh* mesh)
{
    components.push_back(mesh);

    const ResourceMesh* resource = mesh->GetResource();
    auto it = resources.find(resource);

    if (it == resources.end())
    {
        // It will be formatted when generating batches
        resources[resource] = new DrawCommand();
    }
}

void Hachiko::GeometryBatch::GenerateBatch() {
    unsigned resource_index = 0;

    static const int buffer_types[] = {
        static_cast<int>(ResourceMesh::Buffers::INDICES), 
        static_cast<int>(ResourceMesh::Buffers::VERTICES), 
        static_cast<int>(ResourceMesh::Buffers::NORMALS), 
        static_cast<int>(ResourceMesh::Buffers::TEX_COORDS)};

    // Index all resources and compute total size to generate batch buffers;
    for (auto& resource : resources)
    {
        const ResourceMesh* r = resource.first;
                
        for (int buffer_type : buffer_types)
        {
            batch->buffer_sizes[buffer_type] += r->buffer_sizes[buffer_type];
        }
            
    }
    
    batch->indices = new unsigned[batch->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::INDICES)]];
    batch->vertices = new float[batch->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::VERTICES)]];
    batch->normals = new float[batch->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::NORMALS)]];
    batch->tex_coords = new float[batch->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::TEX_COORDS)]];

    unsigned indices_offset = 0;
    unsigned vertices_offset = 0;
    unsigned normals_offset = 0;
    unsigned tex_coords_offset = 0;

    for (auto& resource : resources)
    {
        const ResourceMesh* r = resource.first;
        DrawCommand* command = resource.second;

        command->count = r->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::INDICES)];
        command->first_index = indices_offset;
        command->base_vertex = static_cast<int>(vertices_offset / 3);

        unsigned size = r->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::INDICES)];        
        unsigned size_bytes = sizeof(unsigned) * size;
        memcpy(&batch->indices[indices_offset], r->indices, size_bytes);
        indices_offset += size;

        size = r->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::VERTICES)];
        size_bytes = sizeof(float) * size;
        memcpy(&batch->vertices[vertices_offset], r->vertices, size_bytes);
        vertices_offset += size;

        size = r->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::NORMALS)];
        size_bytes = sizeof(float) * size;
        memcpy(&batch->normals[normals_offset], r->normals, size_bytes);
        normals_offset += size;

        size = r->buffer_sizes[static_cast<int>(ResourceMesh::Buffers::TEX_COORDS)];
        size_bytes = sizeof(float) * size;
        memcpy(&batch->tex_coords[tex_coords_offset], r->tex_coords, size_bytes);
        tex_coords_offset += size;        
    }


    GenerateCommands();
}

void Hachiko::GeometryBatch::GenerateBuffers() {
    batch->GenerateBuffers();
}

void Hachiko::GeometryBatch::GenerateCommands() {
    commands.reserve(components.size());
    
    unsigned instance = 0;
    for (const ComponentMesh* component : components)
    {
        const ResourceMesh* r = component->GetResource();
        DrawCommand command = (*resources[r]);
        command.base_instance = instance;
        commands.emplace_back(command);
        ++instance;
    }
}
