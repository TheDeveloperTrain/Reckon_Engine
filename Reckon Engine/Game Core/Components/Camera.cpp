#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Configuration.h>

Camera::Camera()
{
	type = ComponentType::Camera;
	projectionMatrix = glm::perspective(glm::radians(fov), (float)Configuration::screenWidth / (float)Configuration::screenHeight, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}