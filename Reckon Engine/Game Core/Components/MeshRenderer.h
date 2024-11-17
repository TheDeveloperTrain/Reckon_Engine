#pragma once
#include "Component.h"
#include <Game Core/Mesh.h>
class MeshRenderer : public Component
{
public:
	unsigned int VBO, VAO, EBO;
	MeshRenderer();
	void Render();
	void Clean();
	Mesh mesh;
	
};

