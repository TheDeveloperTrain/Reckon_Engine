#pragma once
#include "SceneObject.h"
#include "SceneSettings.h"
#include <ReckonCore.h>
class RCK_API Scene
{
public:
    Scene();
    std::shared_ptr<SceneObject> CreateGameObject();
    SceneSettings settings;
    std::string name;

    std::shared_ptr<SceneObject> root;
};