#include <glad_wrapper.h>
#include "Game Core/Scene.h"
#include "Input.h"
#include "ReckonEngine.h"
#include <Configuration.h>
#include <Game Core/Components/MeshRenderer.h>
#include <GameRegistry.h>
#include <iostream>
#include <OpenGL Based/ShaderManager.h>
#include <OpenGL Based/ShaderProgram.h>
#include <SerializationManager.h>
#include <GLFW/glfw3.h>


GLFWwindow* window;
Scene ReckonEngine::currentScene;
Camera ReckonEngine::activeCamera;
std::shared_ptr<ShaderProgram> ReckonEngine::currentShader;

std::vector<float> groundVertices = {
	// positions         // texture coords
	-5.0f, 0.0f, -5.0f, 0.0f, 0.0f,
	 5.0f, 0.0f, -5.0f, 1.0f, 0.0f,
	 5.0f, 0.0f,  5.0f, 1.0f, 1.0f,
	-5.0f, 0.0f,  5.0f, 0.0f, 1.0f
};

std::vector<unsigned int> groundIndices = {
	0, 1, 2, // First triangle
	0, 2, 3  // Second triangle
};

std::vector<float> cubeVertices =
{
	// Positions          // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Back face
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // Front face
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Left face
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Right face
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom face
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // Top face
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f

};
std::vector<unsigned int> cubeIndices
{
	// Back face
	0, 1, 2,
	0, 2, 3,

	// Front face
	4, 5, 6,
	4, 6, 7,

	// Left face
	8, 9, 10,
	8, 10, 11,

	// Right face
	12, 13, 14,
	12, 14, 15,

	// Bottom face
	16, 17, 18,
	16, 18, 19,

	// Top face
	20, 21, 22,
	20, 22, 23,
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (ReckonEngine::activeCamera.firstMouse)
	{
		ReckonEngine::activeCamera.lastX = xpos;
		ReckonEngine::activeCamera.lastY = ypos;
		ReckonEngine::activeCamera.firstMouse = false;
	}

	float xoffset = xpos - ReckonEngine::activeCamera.lastX;
	float yoffset = ReckonEngine::activeCamera.lastY - ypos; // reversed since y-coordinates go from bottom to top
	ReckonEngine::activeCamera.lastX = xpos;
	ReckonEngine::activeCamera.lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	ReckonEngine::activeCamera.yaw += xoffset;
	ReckonEngine::activeCamera.pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (ReckonEngine::activeCamera.pitch > 89.0f)
	{
		ReckonEngine::activeCamera.pitch = 89.0f;
	}
	if (ReckonEngine::activeCamera.pitch < -89.0f)
	{
		ReckonEngine::activeCamera.pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(ReckonEngine::activeCamera.yaw)) * cos(glm::radians(ReckonEngine::activeCamera.pitch));
	front.y = sin(glm::radians(ReckonEngine::activeCamera.pitch));
	front.z = sin(glm::radians(ReckonEngine::activeCamera.yaw)) * cos(glm::radians(ReckonEngine::activeCamera.pitch));
	ReckonEngine::activeCamera.cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ReckonEngine::activeCamera.fov -= (float)yoffset;
	if (ReckonEngine::activeCamera.fov < 1.0f)
	{
		ReckonEngine::activeCamera.fov = 1.0f;
	}
	if (ReckonEngine::activeCamera.fov > 45.0f)
	{
		ReckonEngine::activeCamera.fov = 45.0f;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Set the OpenGL viewport to the window size
	glViewport(0, 0, width, height);
}

void ReckonEngine::Init()
{
	if (!glfwInit())
	{
		// Initialization failed
		return;
	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1176, 840, "Reckon Engine", NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Failed to initialize GLAD
		glfwTerminate();
		return;
	}
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set the initial OpenGL viewport to a smaller size
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);

	glfwSetKeyCallback(window, Input::key_callback);

	ShaderManager shadermanager;
	currentShader = shadermanager.LoadShader("ActiveShader", "OpenGL Based/Basic Shaders/BasicUnlitVertexShader.txt", "OpenGL Based/Basic Shaders/BasicUnlitFragmentShader.txt");
	activeCamera.projectionMatrix = glm::perspective(glm::radians(activeCamera.fov),
		(float)Configuration::screenWidth / (float)Configuration::screenHeight,
		0.1f, 100.0f);
	activeCamera.viewMatrix = glm::lookAt(activeCamera.cameraPos, activeCamera.cameraPos + activeCamera.cameraFront, activeCamera.cameraUp);


	Mesh groundMesh(groundVertices, groundIndices);
	auto groundRenderer = std::make_shared<MeshRenderer>();
	groundRenderer->mesh = groundMesh;

	// Create a SceneObject for the ground
	auto groundObject = currentScene.CreateGameObject();
	groundObject->object->name = "Ground";
	groundObject->object->AddComponent(std::move(groundRenderer));
	if (groundObject->object->transform != nullptr)
	{
		groundObject->object->transform->position = glm::vec3(0.0f, 0.0f, 0.0f); // Centered
	}
	else
	{
		std::cerr << "Fuck you, ground object transform is null" << std::endl;
	}

	// Create a cube
	Mesh cubeMesh(cubeVertices, cubeIndices);
	auto cubeRenderer = std::make_shared<MeshRenderer>();
	cubeRenderer->mesh = cubeMesh;

	auto cubeObject = currentScene.CreateGameObject();
	cubeObject->object->name = "Cube";
	cubeObject->object->AddComponent(std::move(cubeRenderer));
	if (cubeObject->object->transform != nullptr)
	{
		cubeObject->object->transform->position = glm::vec3(0.0f, 0.5f, 0.0f); // Positioned above the ground
	}
	else
	{
		std::cerr << "Fuck you, cube Object transform is null" << std::endl;
	}

	// Configure the camera
	activeCamera.cameraPos = glm::vec3(0.0f, 1.0f, 5.0f); // Start back a bit from the ground
	activeCamera.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Look forward
	activeCamera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Up is positive Y

	GameRegistry::CallStart();
	const float durationBetweenFrames = 1.0f / Configuration::framesInFixedUpdate;
	double lastFrame = glfwGetTime();
	double deltaTime = 0.0f;
	float lastFixedUpdate = glfwGetTime();
	float speed = 5.0f;

	while (!glfwWindowShouldClose(window))
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		float cameraSpeed = static_cast<float>(Configuration::cameraSpeed * deltaTime);
		if (Input::GetKeyDown(KeyCode::W))
		{
			activeCamera.cameraPos += cameraSpeed * activeCamera.cameraFront;
		}

		if (Input::GetKeyDown(KeyCode::S))
		{
			activeCamera.cameraPos -= cameraSpeed * activeCamera.cameraFront;
		}
		if (Input::GetKeyDown(KeyCode::A))
		{
			activeCamera.cameraPos -= glm::normalize(glm::cross(activeCamera.cameraFront, activeCamera.cameraUp)) * cameraSpeed;
		}
		if (Input::GetKeyDown(KeyCode::D))
		{
			activeCamera.cameraPos += glm::normalize(glm::cross(activeCamera.cameraFront, activeCamera.cameraUp)) * cameraSpeed;
		}

		RenderScene();

		GameRegistry::CallUpdate(deltaTime);

		glfwSwapBuffers(window);

	}

	for (auto& object : currentScene.GetAllSceneObjects(currentScene))
	{
		auto meshRendererOfObject = object.object->GetComponent(ComponentType::MeshRenderer);
		if (meshRendererOfObject != std::nullopt)
		{
			MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(meshRendererOfObject.value());

			if (renderer)
			{
				renderer->Clean();
			}
			else
			{
				std::cerr << "Failed to cast component to MeshRenderer." << std::endl;
			}
		}

	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
void ReckonEngine::RenderScene()
{

	currentShader->use();
	currentShader->setMat4("view", activeCamera.viewMatrix);
	currentShader->setMat4("projection", activeCamera.projectionMatrix);

	for (auto& object : currentScene.GetAllSceneObjects(currentScene))
	{
		auto transform = *object.object->transform;
		std::cout << "Rendering Object Details: " << std::endl;
		std::cout << "Name: " << object.object->name << std::endl;
		std::cout << "Position: " << transform.position.ToString() << std::endl;
		std::cout << "Scale: " << transform.scale.ToString() << std::endl;


		glm::mat4 model = transform.GetTransformMatrix();

		currentShader->setMat4("model", model);

		// Render object (this is typically a draw call, e.g., glDrawArrays or glDrawElements)
		auto meshRendererOfObject = object.object->GetComponent(ComponentType::MeshRenderer);
		if (meshRendererOfObject != std::nullopt)
		{
			MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(meshRendererOfObject.value());

			if (renderer)
			{
				renderer->Render();
			}
			else
			{
				std::cerr << "Failed to cast component to MeshRenderer." << std::endl;
			}
		}

	}


	// Clear the viewport area
	glClearColor(currentScene.settings.backgroundColor.r, currentScene.settings.backgroundColor.g, currentScene.settings.backgroundColor.b, currentScene.settings.backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void Destroy()
{

	glfwDestroyWindow(window);
	glfwTerminate();
}
