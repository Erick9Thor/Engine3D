#pragma once
#include "Module.h"

#include "il.h"
#include "ilu.h"

#include <string>

using namespace std;

struct Texture {
	unsigned id;
	string path;
};

class ModuleTexture : public Module
{
	public:
		ModuleTexture();
		~ModuleTexture();

		bool Init();
		bool CleanUp();

		unsigned int GetTextureData(const char* path);
		void CleanTexture(unsigned int& texture);
	
		ILuint texture_id;
};