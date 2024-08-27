#pragma once
#include <ReckonCore.h>
enum class ComponentType
{
	Transform,
	Camera,
	MeshRenderer
};


class RCK_API Component
{
public:
	ComponentType type;
};

