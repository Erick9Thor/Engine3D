#pragma once
#include "Resource.h"

#include "resources/ResourceMesh.h"
#include "components/ComponentMesh.h"

#include "Recast.h"
#include "RecastDebugDraw.h"

#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourDebugDraw.h"

namespace Hachiko
{
    class ResourceNavMesh : public Resource
    {
    public:
        ResourceNavMesh() = default;
        ~ResourceNavMesh() = default;

        bool Build(const ComponentMesh* terrainMesh);    // Creates NavMesh for the scene level
        void DebugDraw();                               // Draw debug info
    private:
        void CleanUp();

        void SetupNavMeshParams();                      // Setup Params prior to nav mesh building
    private:

        dtNavMesh* navMesh;
    };
}