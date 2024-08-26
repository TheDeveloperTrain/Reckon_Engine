#include "ReckonEngine.h"
#include <glad/glad.h>
#include "internal Dependencies/glfw3.h"
#include "Input.h"
#include <GameRegistry.h>
#include <Configuration.h>
#include <iostream>
#include "Game Core/Scene.h"
#include <SerializationManager.h>

GLFWwindow* window;

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

    Scene scene = Scene();
    scene.name = "TestScene";
    std::shared_ptr<SceneObject> so = scene.CreateGameObject();
    so->object.name = "Demo object";
    so->object.transform.position = glm::vec3(0.4f, 0.6f, 0.4f);
    SerializationManager::SerializeScene(scene);

    Scene Deserializedscene = SerializationManager::DeserializeScene("TestScene.scene");
    SceneSettings currentSettings = scene.settings;

    //integrity test
    Deserializedscene.name = "Re-Serialized scene";
    SerializationManager::SerializeScene(Deserializedscene);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the initial OpenGL viewport to a smaller size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);

    glfwSetKeyCallback(window, Input::key_callback);

    GameRegistry::CallStart();
    const float durationBetweenFrames = 1.0f / Configuration::framesInFixedUpdate;
    float lastTime = glfwGetTime();
    float deltaTime = 0.0f;

    // Direction variables for each color component
    bool rIncreasing = true;
    bool gIncreasing = true;
    bool bIncreasing = true;
    float speed = 5.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        if (deltaTime > durationBetweenFrames)
        {
            deltaTime -= durationBetweenFrames;
            GameRegistry::CallFixedUpdate();
        }
        GameRegistry::CallUpdate(deltaTime);

        // Clear the viewport area
        glClearColor(currentSettings.backgroundColor.r, currentSettings.backgroundColor.g, currentSettings.backgroundColor.b, currentSettings.backgroundColor.a);

        // Update color components with direction handling
        if (rIncreasing)
        {
            currentSettings.backgroundColor.r += 0.154f * deltaTime;
            if (currentSettings.backgroundColor.r >= 1.0f) {
                currentSettings.backgroundColor.r = 1.0f;
                rIncreasing = false;
            }
        }
        else
        {
            currentSettings.backgroundColor.r -= 0.154f * deltaTime * speed * 2;
            if (currentSettings.backgroundColor.r <= 0.0f) {
                currentSettings.backgroundColor.r = 0.0f;
                rIncreasing = true;
            }
        }

        if (gIncreasing)
        {
            currentSettings.backgroundColor.g += 0.32f * deltaTime * speed;
            if (currentSettings.backgroundColor.g >= 1.0f) {
                currentSettings.backgroundColor.g = 1.0f;
                gIncreasing = false;
            }
        }
        else
        {
            currentSettings.backgroundColor.g -= 0.32f * deltaTime * speed / 2;
            if (currentSettings.backgroundColor.g <= 0.0f) {
                currentSettings.backgroundColor.g = 0.0f;
                gIncreasing = true;
            }
        }

        if (bIncreasing)
        {
            currentSettings.backgroundColor.b += 0.21f * deltaTime * speed;
            if (currentSettings.backgroundColor.b >= 1.0f) {
                currentSettings.backgroundColor.b = 1.0f;
                bIncreasing = false;
            }
        }
        else
        {
            currentSettings.backgroundColor.b -= 0.21f * deltaTime;
            if (currentSettings.backgroundColor.b <= 0.0f) {
                currentSettings.backgroundColor.b = 0.0f;
                bIncreasing = true;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

static void Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
