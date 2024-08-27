#include "Sandbox.h"
#include <Game Core/Scene.h>
#include <ReckonEngine.h>

Sandbox Sandbox::instance;


Sandbox::Sandbox()
{

}

void Sandbox::Start()
{

}

void Sandbox::Update(float deltaTime)
{
	ReckonEngine::currentScene.settings.backgroundColor.g += 0.001f;
	std::cout << ReckonEngine::currentScene.settings.backgroundColor.g << "   " << deltaTime << std::endl;
}
void Sandbox::FixedUpdate() 
{

}
