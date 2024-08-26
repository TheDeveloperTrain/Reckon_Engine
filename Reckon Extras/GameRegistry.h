#pragma once
#include <ReckonCore.h>
#include "ReckonBase.h"
#include <list>
class RCK_API GameRegistry
{
public:
	static void RegisterClass(ReckonBase* reckonClass);
	static void CallStart();
	static void CallUpdate(int deltaTime);
	static void CallFixedUpdate();
private:
	static std::list<ReckonBase*> registeredClasses;
};

