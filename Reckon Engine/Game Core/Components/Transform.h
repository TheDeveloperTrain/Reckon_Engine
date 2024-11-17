#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ReckonCore.h>
#include <memory>
#include "Wrappers/vectors/VectorWrappers.h"
#include "Wrappers/matrices/MatrixWrappers.h"

class RCK_API Transform : public Component
{
public:
	DLL_wrappers::vec3 position;
	DLL_wrappers::mat4 rotation;
	DLL_wrappers::vec3 scale;

	Transform(glm::vec3 _position, glm::mat4 _rotation, glm::vec3 _scale);
	Transform();

	Transform operator*(const std::shared_ptr<Transform> ptr);

	void Rotate(float angle, const glm::vec3& axis);
	void RotateRelative(float angle, const glm::vec3& axis);
	void Translate(float deltaX, float deltaY, float deltaZ);
	void Scale(float scaleX, float scaleY, float scaleZ);
	glm::mat4 GetTransformMatrix() const;
};
