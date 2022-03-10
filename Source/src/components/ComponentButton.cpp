#include "core/hepch.h"
#include "ComponentButton.h"
#include "ComponentTransform2D.h"

#include "Program.h"


Hachiko::ComponentButton::ComponentButton(GameObject* container) 
	: Component(Type::BUTTON, container)
{
}


void Hachiko::ComponentButton::DrawGui()
{
    ImGui::PushID(this);

    if (ImGui::CollapsingHeader("Button", ImGuiTreeNodeFlags_DefaultOpen))
    {}

    ImGui::PopID();
}