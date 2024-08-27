#include "Scene.h"
#include <functional>

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
std::vector<SceneObject> Scene::GetSceneObjectsWithComponent(ComponentType component)
{
    std::vector<SceneObject> output;

    // Helper function to recursively check each object and its children
    std::function<void(std::shared_ptr<SceneObject>)> search = [&](std::shared_ptr<SceneObject> currentObject) {
        if (currentObject->object.GetComponent(component) != std::nullopt)
        {
            output.push_back(*currentObject);
        }

        // Recursively check children
        for (auto child : currentObject->children)
        {
            search(child);
        }
        };

    // Start the search from the root object
    search(root);

    return output;
}




//----------------Helper Functions------------------------
std::vector<SceneObject> Scene::GetAllSceneObjects(Scene scene)
{
    return RecursivelyGetAllChilds(*scene.root);
}


std::vector<SceneObject> Scene::RecursivelyGetAllChilds(SceneObject object)
{
    std::vector<SceneObject> output;

    // Recursively add all children
    for (auto child : object.children)
    {
        output.push_back(*child);  // Add the child to the output list

        // Recursively add the child's children
        auto childChildren = RecursivelyGetAllChilds(*child);
        output.insert(output.end(), childChildren.begin(), childChildren.end());
    }

    return output;
}
