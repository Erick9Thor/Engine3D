#include "ComponentDirLight.h"
#include "ComponentTransform.h"
#include "../Scene.h"

#include "imgui.h"

#include <algorithm>

ComponentDirLight::ComponentDirLight(GameObject* conatiner)
	: Component(Component::Type::DirLight, conatiner)
{
	if (game_object->scene_owner)
		game_object->scene_owner->dir_lights.push_back((ComponentDirLight*) this);
}

ComponentDirLight::~ComponentDirLight()
{
	if (game_object->scene_owner)
	{
		auto lights = game_object->scene_owner->dir_lights;
		lights.erase(std::remove(lights.begin(), lights.end(), this), lights.end());
	}
}

void ComponentDirLight::DrawGui()
{
	if (ImGui::CollapsingHeader("Dir Light"))
	{
		ImGui::Checkbox("D.Active", &active);
		ImGui::InputFloat("D.Intensity", &intensity);
		ImGuiColorEditFlags flag = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoLabel;
		ImGui::ColorPicker3("Dir Color", &color[0], flag);
	}
}

float3 ComponentDirLight::GetDirection() const
{
	ComponentTransform* transform = game_object->GetComponent<ComponentTransform>();
	return transform->GetFwd();
}
