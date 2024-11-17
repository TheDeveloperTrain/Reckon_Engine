#include "Transform.h"
#include <exception>
#include <stdexcept>

Transform::Transform()
{
	type = ComponentType::Transform;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::mat4(1.0f);  // Identity matrix for no rotation
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(glm::vec3 _position, glm::mat4 _rotation, glm::vec3 _scale)
{
	type = ComponentType::Transform;
	position = _position;
	rotation = _rotation;
	scale = _scale;
}

Transform Transform::operator*(const std::shared_ptr<Transform> ptr)
{
	if (!ptr)
	{
		throw std::runtime_error("deferencing a null pointer");
	}
	return *ptr;
}

void Transform::Rotate(float angle, const glm::vec3& axis)
{
	rotation = glm::rotate(rotation.GetMatrix(), glm::radians(angle), axis);
}

void Transform::RotateRelative(float angle, const glm::vec3& axis)
{
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * rotation.GetMatrix();
}

void Transform::Translate(float deltaX, float deltaY, float deltaZ)
{
	position += glm::vec3(deltaX, deltaY, deltaZ);
}

void Transform::Scale(float scaleX, float scaleY, float scaleZ)
{
	scale *= DLL_wrappers::vec3(scaleX, scaleY, scaleZ);
}

glm::mat4 Transform::GetTransformMatrix() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position.GetVector());
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale.GetVector());

	return translationMatrix * rotation.GetMatrix() * scaleMatrix;
}
