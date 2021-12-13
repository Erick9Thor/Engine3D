#pragma once

#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"
#include "GameObject.h"

#include "ImGuiComponents/AppLog.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor() :fps_log(100), ms_log(100) {};
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Draw();

	void showMenu();

	void DrawHierarchyTree(GameObject* root);
	void RecursiveDraw(GameObject* go);
	
	void showFPSGraph();
	void AddFPS(float fps, float ms);

	void showAbaoutInfo();

private:
	std::vector<float> ms_log;
	std::vector<float> fps_log;

	bool show_hirarchy = true;
	bool show_inspector_window = true;
	bool show_abaout = false;
	bool show_camera_window = false;
	bool show_fps_counter = false;
};
