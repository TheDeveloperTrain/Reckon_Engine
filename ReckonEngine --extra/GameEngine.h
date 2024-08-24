#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

#include "Camera.h"


class Engine {
public:
    Engine(int width, int height, const char* title);
    ~Engine();
    void Run();
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Camera camera;


private:
    void InitGLFW();
    void InitGLAD();
    void SetupBuffers();
    void Render();

    GLFWwindow* window;


    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow* window);


    unsigned int VBO, VAO, EBO;
    unsigned int texture1;
    unsigned int texture2;
    
    Shader* shaderProgram;


    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float lastX, lastY;

    float fov;

    bool firstMouse;
  
};

