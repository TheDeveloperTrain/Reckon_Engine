#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "ImGuiStateManager.h"
#include <fstream>
#include "ReckonEditor.h"
#include "ReckonConfig.h"
#include <vector>

GLFWwindow* window;

// Vertex Shader source
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

// Fragment Shader source
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

// Function to compile a shader and check for errors
unsigned int CompileShader(unsigned int type, const char* source)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, ' ');
        glGetShaderInfoLog(shader, length, &length, &message[0]);
        std::cerr << "Failed to compile shader: " << message << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

// Function to create a shader program
unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Check for linking errors
    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, ' ');
        glGetProgramInfoLog(program, length, &length, &message[0]);
        std::cerr << "Failed to link program: " << message << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "Reckon Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    ReckonEditor::InitWorkingDirectories();
    ReckonEditor::LoadLayoutPathFile();

    glViewport(0, 0, 1920, 1080);

    // Load and compile shaders
    unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Set up vertex data
    float vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create Framebuffer
    unsigned int framebuffer, texture, rbo;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create texture to render to
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1920, 1080, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // Create renderbuffer for depth and stencil
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Check framebuffer status
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer is not complete!" << std::endl;
        return -1;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGuiStateManager::showSaveLayoutManager = false;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Bind the framebuffer to render to
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glViewport(0, 0, 1920, 1080);
        glClearColor(0.0f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Unbind the framebuffer and display the texture in ImGui
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create a menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    // Handle Open
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                    // Handle Save
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Cut", "Ctrl+X"))
                {
                    // Handle Cut
                }
                if (ImGui::MenuItem("Copy", "Ctrl+C"))
                {
                    // Handle Copy
                }
                if (ImGui::MenuItem("Paste", "Ctrl+V"))
                {
                    // Handle Paste
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Test")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Layout"))
            {
                if (ImGui::MenuItem("Save Layout"))
                {
                    ImGuiStateManager::showSaveLayoutManager = true;
                }
                if (ImGui::MenuItem("Load Layout"))
                {
                    ImGuiStateManager::showLoadLayoutManager = true;
                }
                if (ImGui::MenuItem("Clear Layouts"))
                {
                    ReckonEditor::ClearLayoutData();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        if (ImGuiStateManager::showSaveLayoutManager)
        {
            ImGui::OpenPopup("Save Layout");
        }
        if (ImGuiStateManager::showLoadLayoutManager)
        {
            ImGui::OpenPopup("Load Layout");
        }

        if (ImGui::BeginPopupModal("Save Layout", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char input[64] = "";
            if (ImGui::InputText("Layout Name", input, 64))
            {

            }
            if (ImGui::Button("Save Layout"))
            {
                ReckonEditor::SaveLayoutWithName(input);
                ImGui::CloseCurrentPopup();
                ImGuiStateManager::showSaveLayoutManager = false;
            }
            
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                ImGuiStateManager::showSaveLayoutManager = false;
            }
            ImGui::EndPopup();
        }
        if (ImGui::BeginPopupModal("Load Layout", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static int selectedLayoutIndex = -1;  // Track the selected layout index

            if (!ReckonConfig::layoutFilePaths.empty())
            {
                // Display a combo box with all saved layout names
                if (ImGui::Combo("Select Layout", &selectedLayoutIndex,
                    [](void* data, int idx, const char** out_text) {
                        const std::vector<std::string>* layouts = static_cast<std::vector<std::string>*>(data);
                        *out_text = layouts->at(idx).c_str();
                        return true;
                    },
                    &ReckonConfig::layoutNames,
                    ReckonConfig::layoutNames.size()))
                {
                    // Layout selected, nothing to do here as index is updated automatically
                }
            }
            else
            {
                ImGui::Text("No saved layouts available.");
            }

            // Only enable the Load button if a valid layout is selected
            if (selectedLayoutIndex >= 0 && selectedLayoutIndex < ReckonConfig::layoutFilePaths.size())
            {
                if (ImGui::Button("Load Layout"))
                {
                    try
                    {
                        ReckonEditor::LoadLayoutWithName(ReckonConfig::layoutFilePaths[selectedLayoutIndex]);
                        ImGui::CloseCurrentPopup();
                        ImGuiStateManager::showLoadLayoutManager = false;
                    }
                    catch (const std::runtime_error& e)
                    {
                        std::cerr << e.what() << std::endl;
                        // Optionally, display an error message in the UI
                    }
                }
            }
            else
            {
                ImGui::BeginDisabled(); // Disable Load button if no layout is selected
                ImGui::Button("Load Layout");
                ImGui::EndDisabled();
            }

            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                ImGuiStateManager::showLoadLayoutManager = false;
            }
            ImGui::EndPopup();
        }


        // Create a docking space
        ImGui::DockSpaceOverViewport();

        // Create additional docking windows
        ImGui::Begin("Hierarchy");
        ImGui::Text("Hierarchy Window");
        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::Text("Inspector Window");
        ImGui::End();

        // Create the Scene window where OpenGL content will be rendered
        ImGui::Begin("Scene");
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)(intptr_t)texture, viewportSize, ImVec2(0, 1), ImVec2(1, 0)); // Use the texture rendered by OpenGL
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteProgram(shaderProgram);
    ReckonEditor::SaveLayoutPathFile();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
