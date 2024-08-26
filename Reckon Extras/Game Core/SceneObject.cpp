#include "SceneObject.h"

int SceneObject::idCounter = 0;

SceneObject::SceneObject(const GameObject& _object)
{
    object = _object;
    id = idCounter++;
}

SceneObject::SceneObject()
{
    object = GameObject();
    id = idCounter++;
}

void SceneObject::AddChild(std::shared_ptr<SceneObject> child)
{
    child->parent = shared_from_this();
    children.push_back(child);
}

void SceneObject::RemoveChild(std::shared_ptr<SceneObject> child)
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end())
    {
        (*it)->parent.reset();
        children.erase(it);
    }
}

glm::mat4 SceneObject::GetWorldTransform() const
{
    if (auto parentPtr = parent.lock())
    {
        return parentPtr->GetWorldTransform() * object.transform.GetTransformMatrix();
    }
    else
    {
        return object.transform.GetTransformMatrix();
    }
}
