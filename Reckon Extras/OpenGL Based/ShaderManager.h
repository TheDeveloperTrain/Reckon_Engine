#pragma once

#include "ShaderProgram.h"
#include <unordered_map>
#include <memory>
#include <string>

class ShaderManager
{
public:
    // Load and compile a shader, and store it by name
    std::shared_ptr<ShaderProgram> LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

    // Retrieve a shader by name
    std::shared_ptr<ShaderProgram> GetShader(const std::string& name);

    // Check if a shader exists by name
    bool ShaderExists(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaders;
};
