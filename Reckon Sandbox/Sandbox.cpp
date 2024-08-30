#include "Sandbox.h"
#include <Game Core/Scene.h>
#include <ReckonEngine.h>

Sandbox Sandbox::instance;


Sandbox::Sandbox()
{

}

// Direction variables for each color component
bool rIncreasing;
bool gIncreasing;
bool bIncreasing;
double speed;
 
void Sandbox::Start()
{
    rIncreasing = true;
    gIncreasing = false;
    bIncreasing = true;
    speed = 5.0f;

    
}

void Sandbox::Update(float deltaTime)
{
    SceneSettings* currentSettings = &ReckonEngine::currentScene.settings;
    // Update color components with direction handling
    if (rIncreasing)
    {
        currentSettings->backgroundColor.r += 0.154f * deltaTime * speed;
        if (currentSettings->backgroundColor.r >= 0.5f) {
            currentSettings->backgroundColor.r = 0.5f;
            rIncreasing = false;
        }
    }
    else
    {
        currentSettings->backgroundColor.r -= 0.554f * deltaTime * speed;
        if (currentSettings->backgroundColor.r <= 0.0f) {
            currentSettings->backgroundColor.r = 0.0f;
            rIncreasing = true;
        }
    }

    if (gIncreasing)
    {
        currentSettings->backgroundColor.g += 0.52f * deltaTime;
        if (currentSettings->backgroundColor.g >= 1.0f) {
            currentSettings->backgroundColor.g = 1.0f;
            gIncreasing = false;
        }
    }
    else
    {
        currentSettings->backgroundColor.g -= 0.22f * deltaTime * speed;
        if (currentSettings->backgroundColor.g <= 0.0f) {
            currentSettings->backgroundColor.g = 0.0f;
            gIncreasing = true;
        }
    }

    if (bIncreasing)
    {
        currentSettings->backgroundColor.b += 0.61f * deltaTime * speed;
        if (currentSettings->backgroundColor.b >= 1.0f) {
            currentSettings->backgroundColor.b = 1.0f;
            bIncreasing = false;
        }
    }
    else
    {
        currentSettings->backgroundColor.b -= 0.298f * deltaTime;
        if (currentSettings->backgroundColor.b <= 0.0f) {
            currentSettings->backgroundColor.b = 0.0f;
            bIncreasing = true;
        }
    }

    std::cout << "R: " << ReckonEngine::currentScene.settings.backgroundColor.r
        << " G: " << ReckonEngine::currentScene.settings.backgroundColor.g
        << " B: " << ReckonEngine::currentScene.settings.backgroundColor.b << " DeltaTime: " << deltaTime << std::endl;
}
void Sandbox::FixedUpdate() 
{

}
