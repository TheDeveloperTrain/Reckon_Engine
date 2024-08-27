#include "ShaderManager.h"

std::shared_ptr<ShaderProgram> ShaderManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    // Check if shader is already loaded
    if (ShaderExists(name)) {
        return shaders[name];
    }

    // Load, compile, and link shader
    auto shader = std::make_shared<ShaderProgram>(vertexPath.c_str(), fragmentPath.c_str());

    // Cache the shader for future use
    shaders[name] = shader;

    return shader;
}

std::shared_ptr<ShaderProgram> ShaderManager::GetShader(const std::string& name) {
    // Retrieve the shader from the cache
    if (ShaderExists(name)) {
        return shaders[name];
    }

    // Shader not found
    std::cerr << "ERROR::SHADER_MANAGER::SHADER_NOT_FOUND: " << name << std::endl;
    return nullptr;
}

bool ShaderManager::ShaderExists(const std::string& name) const {
    return shaders.find(name) != shaders.end();
}
