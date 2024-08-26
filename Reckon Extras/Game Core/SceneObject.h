#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <ReckonCore.h>

class RCK_API SceneObject : public std::enable_shared_from_this<SceneObject>
{
public:
    SceneObject(const GameObject& _object);
    SceneObject();

    void AddChild(std::shared_ptr<SceneObject> child);
    void RemoveChild(std::shared_ptr<SceneObject> child);

    glm::mat4 GetWorldTransform() const;

    GameObject object;
    int id;
    static int idCounter;
    std::weak_ptr<SceneObject> parent;
    std::vector<std::shared_ptr<SceneObject>> children;
};
