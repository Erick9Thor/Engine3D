#pragma once

#include "Component.h"
#include "resources/ResourceMaterial.h"

#include <assimp/scene.h>

namespace Hachiko
{
    class ComponentMaterial : public Component
    {
    public:
        ComponentMaterial(GameObject* conatiner);
        ~ComponentMaterial() override;

        static Type GetType()
        {
            return Type::MATERIAL;
        }

        [[nodiscard]] const ResourceMaterial* GetMaterial() const
        {
            return material;
        }

        void DrawGui() override;

        void Import(aiMaterial* assimp_material, const std::string& model_path, const std::string& model_name);
        void Save(JsonFormatterValue j_component) const override;
        void Load(JsonFormatterValue j_component) override;

        char diffuse_filename_buffer[MAX_PATH] = "Diffuse Filename\0";
        char specular_filename_buffer[MAX_PATH] = "Specular Filename\0";

        bool use_diffuse_texture = false;
        bool use_specular_texture = false;

    private:
        ResourceMaterial* material{};
    };
}
