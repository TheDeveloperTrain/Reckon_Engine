#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ReckonCore.h>

class RCK_API Transform : public Component
{
public:
    glm::vec3 position;
    glm::mat4 rotation;
    glm::vec3 scale;

    Transform(glm::vec3 _position, glm::mat4 _rotation, glm::vec3 _scale);
    Transform();

    void Rotate(float angle, const glm::vec3& axis);
    void RotateRelative(float angle, const glm::vec3& axis);
    void Translate(float deltaX, float deltaY, float deltaZ);
    void Scale(float scaleX, float scaleY, float scaleZ);
    glm::mat4 GetTransformMatrix() const;
};
