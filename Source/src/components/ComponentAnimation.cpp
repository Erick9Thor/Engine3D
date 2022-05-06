#include "core/hepch.h"

#include "Application.h"

#include "modules/ModuleEditor.h"

#include "ComponentAnimation.h"
#include "ComponentTransform.h"

#include "resources/ResourceAnimation.h"
#include "animation/AnimationController.h"
#include "importers/AnimationImporter.h"

Hachiko::ComponentAnimation::ComponentAnimation(GameObject* container) : Component(Type::ANIMATION, container)
{
    controller = new AnimationController();
}

Hachiko::ComponentAnimation::~ComponentAnimation()
{
    for (unsigned i = 0; i < animations.size(); ++i)
    {
        delete animations[i];
    }
    animations.clear();
}

void Hachiko::ComponentAnimation::Start()
{
    if (!animations.empty())
    {
        controller->Play(current_animation, true, 0);
    }
}

void Hachiko::ComponentAnimation::Stop()
{
    controller->Stop();
}

void Hachiko::ComponentAnimation::Update()
{
    if (current_animation)
    {
        controller->Update(EngineTimer::delta_time); // TODO: change for GameTimer::delta_time

        if (game_object != nullptr)
        {
            UpdatedGameObject(game_object);
        }
    }
}

void Hachiko::ComponentAnimation::UpdatedGameObject(GameObject* go)
{
    float3 position;
    Quat rotation;

    if (controller->GetTransform(controller->current, go->name.c_str(), position, rotation))
    {
        go->GetTransform()->SetLocalPosition(position);
        go->GetTransform()->SetLocalRotation(rotation);
    }

    for (GameObject* child : go->children)
    {
        UpdatedGameObject(child);
    }
}

void Hachiko::ComponentAnimation::DrawGui()
{
    ImGui::PushID(this);
    
    if (ImGuiUtils::CollapsingHeader(game_object, this, "Animation"))
    {
        for (unsigned i = 0; i < animations.size(); ++i)
        {
            char animation_name[50];
            strcpy_s(animation_name, 50, animations[i]->GetName().c_str());
            if (ImGui::Button(StringUtils::Concat(ICON_FA_PLAY, " ", animation_name).c_str()))
            {
                current_animation = animations[i];
                this->Start();
            }
        }

    }
    ImGui::PopID();
}

void Hachiko::ComponentAnimation::Save(YAML::Node& node) const {}

void Hachiko::ComponentAnimation::Load(const YAML::Node& node) {}
