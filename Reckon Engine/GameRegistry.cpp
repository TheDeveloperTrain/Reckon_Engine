#include "GameRegistry.h"
#include <GLFW/glfw3.h>


std::list<ReckonBase*> GameRegistry::registeredClasses;
void GameRegistry::RegisterClass(ReckonBase* reckonBase)
{
	registeredClasses.push_back(reckonBase);
}

void GameRegistry::CallStart()
{
	for (const auto& classes : registeredClasses)
	{
		classes->Start();
	}
}
void GameRegistry::CallUpdate(int deltaTime)
{
	for (const auto& classes : registeredClasses)
	{
		classes->Update(deltaTime);
	}
}

void GameRegistry::CallFixedUpdate()
{
	for (const auto& classes : registeredClasses)
	{
		classes->FixedUpdate();
	}
}