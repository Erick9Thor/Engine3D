#include "WindowScene.h"

#include "../Application.h"
#include "../GameObject.h"

#include "../Modules/ModuleInput.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleCamera.h"
#include "../Modules/ModuleRender.h"
#include "../Modules/ModuleSceneManager.h"

#include "../Components/ComponentCamera.h"
#include "../Components/ComponentTransform.h"

#include <IconsFontAwesome5.h>
#include <imgui_internal.h>

WindowScene::WindowScene()
	: Window("Scene", true)
{
	scene_timer = new Timer();
}

void WindowScene::Update()
{
	if (!App->input->GetMouseButton(SDL_BUTTON_RIGHT))
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) guizmo_operation = ImGuizmo::TRANSLATE;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) guizmo_operation = ImGuizmo::ROTATE;
		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) guizmo_operation = ImGuizmo::SCALE;
	}
	if (ImGui::Begin(ICON_FA_GLOBE "Scene", &active))
	{
		GuizmoOptionsController();
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
		ToolbarMenu();
		DrawScene();
		Controller();
		ImGui::End();
	};
}

void WindowScene::GuizmoOptionsController()
{
	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_ARROWS_ALT, guizmo_operation == ImGuizmo::TRANSLATE)) guizmo_operation = ImGuizmo::TRANSLATE;
	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_UNDO, guizmo_operation == ImGuizmo::ROTATE)) guizmo_operation = ImGuizmo::ROTATE;
	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_EXPAND_ALT, guizmo_operation == ImGuizmo::SCALE)) guizmo_operation = ImGuizmo::SCALE;

	ImGui::SameLine();
	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	ImGui::SameLine();

	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_HOME, guizmo_mode == ImGuizmo::LOCAL)) guizmo_mode = ImGuizmo::LOCAL;
	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_GLOBE, guizmo_mode == ImGuizmo::WORLD)) guizmo_mode = ImGuizmo::WORLD;
}

void WindowScene::ToolbarMenu()
{
	float w = (ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x) * 0.5f - 30 - ImGui::GetCursorPosX();
	ImGui::Dummy(ImVec2(w, ImGui::GetTextLineHeight()));

	if (scene_timer->HasGameStarted())
	{
		if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_STOP, !scene_timer->IsGameRunning()))scene_timer->StopGame();

		if (scene_timer->IsGameRunning())
			if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_PAUSE, !scene_timer->IsGameRunning())) scene_timer->PauseGame();
		else
			if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_PLAY, scene_timer->IsGameRunning())) scene_timer->ResumeGame();
	}
	else
		if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_PLAY, scene_timer->IsGameRunning())) scene_timer->StartGame();

	if (ToolbarButton(App->editor->m_big_icon_font, ICON_FA_STEP_FORWARD, scene_timer->IsGameRunning())) scene_timer->StepGame();
	ImGui::Separator();
}

void WindowScene::DrawScene()
{
	ImVec2 size = ImGui::GetContentRegionAvail();
	if (size.x != texture_size.x || size.y != texture_size.y) {
		texture_size = {
			size.x,
			size.y,
		};
		App->camera->OnResize((unsigned) texture_size.x, (unsigned) texture_size.y);
	}
	
	ComponentCamera* camera = App->camera->GetMainCamera();

	// Top left corner of the image in imgui coords, top is y = 0
	guizmo_rect_origin = ImGui::GetCursorScreenPos();
	// Bottom left corner in opengl coordinates, bottom is y = 0
	texture_position = float2(guizmo_rect_origin.x, float(App->window->GetHeight()) - guizmo_rect_origin.y - texture_size.y);
	
	ImGui::Image((void*) (intptr_t) App->renderer->GetTextureId(), size, ImVec2 {0, 1}, ImVec2 {1, 0});

	// TO AVOID Camera orbit
	if (ImGui::IsWindowFocused())
	{
		bool guizmo_enabled = !(App->input->GetMouseButton(SDL_BUTTON_RIGHT) || App->input->GetKey(SDL_SCANCODE_LALT));
		ImGuizmo::Enable(guizmo_enabled);
	}

	constexpr bool transposed = true;
	float4x4 view = camera->GetViewMatrix(transposed);

	//TODO ADD look at when manipulating cube
	ImGuizmo::ViewManipulate((float*) &view, 4, ImVec2(guizmo_rect_origin.x + texture_size.x - imguizmo_size.x, 
		guizmo_rect_origin.y + texture_size.y - imguizmo_size.x), imguizmo_size, 0x10101010);

	GameObject* selected_object = App->editor->GetSelectedGO();
	if (!selected_object) return;
	
	if (selected_object) {
		// Using GL format which means transposing them
		float4x4 projection = camera->GetProjectionMatrix(transposed);
		float4x4 model = selected_object->GetComponent<ComponentTransform>()->GetTransform().Transposed();
		float4x4 delta;

		//TODO: Fix
		ImGuizmo::SetRect(guizmo_rect_origin.x, guizmo_rect_origin.y, (float) size.x, (float) size.y);
		ImGuizmo::SetDrawlist();	

		ImGuizmo::Manipulate((float*) &view, (float*) &projection, guizmo_operation, guizmo_mode, (float*) &model, (float*) &delta);
		
		using_guizmo = ImGuizmo::IsUsing();		
		if (using_guizmo && !delta.IsIdentity())
		{
			// Transpose back again to store in our format
			model.Transpose();
			selected_object->GetComponent<ComponentTransform>()->SetGlobalTransform(model);
		}
	}
}

void WindowScene::Controller()
{
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		Scene* scene = App->scene_manager->GetActiveScene();
		GameObject* picked = SelectObject(App->camera->GetMainCamera(), scene);
		if (picked)
			App->editor->SetSelectedGO(picked);
	}
}

GameObject* WindowScene::SelectObject(ComponentCamera* camera, Scene* scene)
{
	// sdl -> (0, 0) top left, (w, h) bottom right
	// // imgui -> (0,0) botton left
	// plane -> (1,1) top right , (-1, -1) bottom left
	
	
	ImVec2 mouse = ImGui::GetMousePos();
	float2 mouse_viewport_pos = float2(mouse.x - guizmo_rect_origin.x, mouse.y - guizmo_rect_origin.y);

	// Fit in range and coordinate direction
	float x_normalized = mouse_viewport_pos.x / texture_size.x * 2.f - 1.f;
	float y_normalized = -(mouse_viewport_pos.y / texture_size.y * 2.f - 1.f);

	LineSegment line = camera->RayCast(x_normalized, y_normalized);
	GameObject* selected = scene->RayCast(line);
	
	return selected;
}

//TODO: Move to utils gui and add tooltips
bool WindowScene::ToolbarButton(ImFont* font, const char* font_icon, bool active)
{
	const ImVec4 col_active = ImGui::GetStyle().Colors[ImGuiCol_ButtonActive];
	const ImVec4 bg_color = active ? col_active : ImGui::GetStyle().Colors[ImGuiCol_Text];

	ImGui::SameLine();
	auto frame_padding = ImGui::GetStyle().FramePadding;
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_Text, bg_color);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, ImGui::GetStyle().FramePadding.y));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, frame_padding);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

	ImGui::PushFont(font);
	active = ImGui::Button(font_icon);

	ImGui::PopFont();
	ImGui::PopStyleColor(4);
	ImGui::PopStyleVar(3);

	return active;
}
