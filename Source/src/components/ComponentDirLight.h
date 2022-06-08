#pragma once

#include "components/Component.h"

namespace Hachiko
{
    class ComponentDirLight : public Component
    {
    public:
        ComponentDirLight(GameObject* conatiner);
        ~ComponentDirLight() override;

        void DebugDraw() override;
        
        [[nodiscard]] float3 GetDirection() const;

        void Save(YAML::Node& node) const override;
        void Load(const YAML::Node& node) override;

        void DrawGui() override;

        float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
        float intensity = 1.0f;

    private:
        bool d_active = true;
        bool draw_direction = false;
    };
}
