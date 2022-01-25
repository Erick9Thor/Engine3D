#pragma once
#include "Window.h"

#include "../Utils/PathNode.h"

#include <vector>

using namespace std;

class WindowProject : public Window
{
public:
	WindowProject();
	void Init() override;
	void Update() override;

private:
	void DetailsGUI();
	void DoFilter();
	void CreateBreadCrumps();
	void Thumbnail(PathNode& node, float size, bool selected);

	void ChangeDir(const char* folder_name);

	void ShowDir(PathNode& node);
	void ShowFilesOnFolder();

	void GetAssets();

private:
	char m_filter[128];
	float m_left_column_width = 120;

	float m_thumbnail_size = 1.f;

	PathNode all_assets;
	
};
