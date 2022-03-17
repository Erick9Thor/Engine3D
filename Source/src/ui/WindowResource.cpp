#include "core/hepch.h"
#include "WindowResource.h"
#include "events/Event.h"
#include "modules/ModuleResources.h"
#include "modules/ModuleEvent.h"

Hachiko::WindowResource::WindowResource() : 
    Window("Resources", true)
{
}

void Hachiko::WindowResource::Update()
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin((std::string(ICON_FA_IMAGES " ") + name).c_str(), &active))
    {
        ImGui::End();
        return;
    }
    std::filesystem::path library_path("./library");

    if (current_directory != library_path)
    {
        if (ImGui::Button(ICON_FA_FOLDER_MINUS))
        {
            current_directory = current_directory.parent_path();
        }
    }

    for (auto& directory_entry : std::filesystem::directory_iterator(current_directory))
    {
        const auto& path = directory_entry.path();
        auto relative_path = relative(path, library_path);
        std::string filename = relative_path.filename().string();

        if (directory_entry.is_directory())
        {
            if (ImGui::Button(filename.c_str()))
            {
                current_directory /= path.filename();
            }
        }
        else
        {
            auto selection = ImGui::Selectable(filename.c_str(), ImGuiSelectableFlags_AllowDoubleClick);
            if (ImGui::IsMouseDoubleClicked(selection) && ImGui::IsItemHovered())
            {
                filename.insert(0, "\\");
                filename.insert(0, current_directory.string().c_str());
                LoadResource(filename);
            }
        }
    }

    ImGui::End();
}

void Hachiko::WindowResource::LoadResource(const std::string& path)
{
    App->resources->LoadResourceIntoScene(path.c_str());
}
