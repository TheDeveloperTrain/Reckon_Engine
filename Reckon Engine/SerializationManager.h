#pragma once
#include "Game Core/Scene.h"
#include <ReckonCore.h>

static RCK_API class SerializationManager
{
public:
	static void SerializeScene(Scene scene, std::string relpath = "");
	static Scene DeserializeScene(std::string relpath);
	static void SerializeSceneObject(std::ofstream& outFile, std::shared_ptr<SceneObject> object);
};

