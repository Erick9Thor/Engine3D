#pragma once
#include "Resource.h"

class ResourceMaterial : public Resource
{
public:
	ResourceMaterial(UID id);

	void Load() override;
	void Unload() override;
};
