#pragma once
#include "Game Core/Components/Camera.h"
#include "Game Core/Scene.h"
#include "ReckonCore.h"
#include <OpenGL Based/ShaderProgram.h>

class RCK_API ReckonEngine
{
public:
	static void Init();

	static Scene currentScene;
	static Camera activeCamera;
	static std::shared_ptr<ShaderProgram> currentShader;

private:
	static void RenderScene();
};