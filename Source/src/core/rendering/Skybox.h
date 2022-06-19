#pragma once

#include "modules/ModuleTexture.h"

namespace Hachiko
{
    class ComponentCamera;

    class Skybox
    {
    public:
        Skybox();
        Skybox(TextureCube new_cube);
        ~Skybox();
        void Draw(ComponentCamera* camera) const;

        void ChangeCubeMapSide(UID texture_uid, TextureCube::Side cube_side);
        void ReleaseCubemap();

        const TextureCube& GetCube() const
        {
            return cube;
        }

        void BuildIBL();

        void DrawImGui();

        void BindImageBasedLightingUniforms(Program* program) const;

    private:
        void SelectSkyboxTexture(TextureCube::Side cube_side);
        
        void GenerateDiffuseIBL();
        void GeneratePrefilteredIBL();
        void GenerateEnvironmentBRDF();

        void CreateBuffers();
        TextureCube cube;
        unsigned vao{};
        unsigned vbo{};

        bool activate_ibl = false;
        unsigned diffuse_ibl_id = 0;
        unsigned prefiltered_ibl_id = 0;
        unsigned environment_brdf_id = 0;
        unsigned prefiltered_ibl_number_of_levels = 0;

    public:
        Skybox(const Skybox& other) = default;
        Skybox& operator=(const Skybox& other) = default;
    };
}
