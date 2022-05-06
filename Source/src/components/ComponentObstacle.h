#pragma once

#include "components/Component.h"
#include "Globals.h"
#include "DetourTileCache/DetourTileCache.h"

namespace Hachiko
{
    class GameObject;

    class ComponentTransform2D;

    class ComponentObstacle : public Component
    {
    public:
        ComponentObstacle(GameObject* container);
        ~ComponentObstacle() override;

        void Start() override;
        void Stop() override;
        virtual void Update() override;
        virtual void OnTransformUpdated() override;

        static Type GetType()
        {
            return Type::OBSTACLE;
        }        
        
        // TODO: Add debugdraw
        void SetSize(const float3& new_size); // Reminder: Cylinder will ignore z value

        void Save(YAML::Node& node) const override;
        void Load(const YAML::Node& node) override;
        void DrawGui() override;        
    private:
        static const int update_freq = 25;
        int count_since_update = 0;
        bool dirty = true;
        void AddObstacle();
        void RemoveObstacle();
        void RefreshObstacle(); // Workaround manual refresh, If we call on each on transform updated the obstacle buffer saturates
        dtObstacleRef* obstacle = nullptr;	
        ObstacleType obstacle_type = ObstacleType::DT_OBSTACLE_CYLINDER;
        float3 size = float3::one;
    };
} // namespace Hachiko
