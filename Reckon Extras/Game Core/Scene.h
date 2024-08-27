#pragma once
#include "SceneObject.h"
#include "SceneSettings.h"
#include <ReckonCore.h>
class RCK_API Scene
{
public:
    Scene();
    std::shared_ptr<SceneObject> CreateGameObject();
    std::vector<SceneObject> GetSceneObjectsWithComponent(ComponentType component);
    std::vector<SceneObject> GetAllSceneObjects(Scene scene);
    std::vector<SceneObject> RecursivelyGetAllChilds(SceneObject object);

    SceneSettings settings;
    std::string name;

    std::shared_ptr<SceneObject> root;
};