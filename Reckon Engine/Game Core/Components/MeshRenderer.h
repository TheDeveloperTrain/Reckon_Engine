#pragma once
#include "Component.h"
#include <Game Core/Mesh.h>
class MeshRenderer : public Component
{
public:
	MeshRenderer();
	Mesh mesh;
	
};

