#include "Texture.h"
#include <glad/glad.h>
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

/*
Return format: (texture id, data)
Extra Details:
the default wrap settings are set to repeat and the default filtering settings are set to linear
the mipmap is generated
*/
std::pair<unsigned int, unsigned char*> Texture::LoadAndCreateTexture_WithDefaultConfig(const char* path)
{
    std::pair<unsigned int, unsigned char*> BaseTexture = LoadAndCreateTexture(path);

    // If the texture was loaded successfully, set parameters
    if (BaseTexture.first != 0)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
        
    }

    return BaseTexture;
}

std::pair<unsigned int, unsigned char*> Texture::LoadAndCreateTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Failed to load texture from: " << path << std::endl;
        glDeleteTextures(1, &textureID);  // Clean up the generated texture
        textureID = 0; // Mark as invalid texture ID
    }

    stbi_image_free(data);
    return std::make_pair(textureID, data);
}
