#pragma once
#include "ReckonCore.h"
#include "Game Core/Scene.h"

class RCK_API ReckonEngine
{
public:
	static void Init();
	
	static Scene currentScene;
private:
	static void RenderScene();
};