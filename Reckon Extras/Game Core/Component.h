#pragma once
#include <ReckonCore.h>
enum class ComponentType
{
	Transform
};


class RCK_API Component
{
public:
	ComponentType type;
};

