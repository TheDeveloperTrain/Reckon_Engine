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
Scene ReckonEngine::currentScene;

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
    so->object.transform.position = glm::vec3(0.4f, 0.6f, 0.6f);
    SerializationManager::SerializeScene(scene);

    Scene Deserializedscene = SerializationManager::DeserializeScene("TestScene.scene");
    currentScene = Deserializedscene;
    SceneSettings currentSettings = Deserializedscene.settings;

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
    float lastFrame = glfwGetTime();
    float deltaTime = 0.0f;
    float lastFixedUpdate = glfwGetTime();
    float speed = 5.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        if (glfwGetTime() - lastFixedUpdate > durationBetweenFrames)
        {
            GameRegistry::CallFixedUpdate();
            lastFixedUpdate = glfwGetTime();
        }
        GameRegistry::CallUpdate(deltaTime);

        // Clear the viewport area
        glClearColor(currentScene.settings.backgroundColor.r, currentScene.settings.backgroundColor.g, currentScene.settings.backgroundColor.b, currentScene.settings.backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
void ReckonEngine::RenderScene()
{

}

static void Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
