#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"

#include <iostream>

class Init
{
public:
    Init();
    ~Init();

    GLFWwindow* InitWindow(int width, int height, const char* title);


    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    
};