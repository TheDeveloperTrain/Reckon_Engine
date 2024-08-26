#include "Scene.h"

Scene::Scene()
{
    root = std::make_shared<SceneObject>(GameObject().name = "root");
}

std::shared_ptr<SceneObject> Scene::CreateGameObject()
{
    auto gameObject = GameObject();
    auto output = std::make_shared<SceneObject>(gameObject);
    output->parent = root;
    root->AddChild(output);
    return output;
}