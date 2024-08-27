#pragma once
#include <utility>
class Texture
{
public:
	static std::pair<unsigned int, unsigned char*> LoadAndCreateTexture(const char* path);
	static std::pair<unsigned int, unsigned char*> LoadAndCreateTexture_WithDefaultConfig(const char* path);
};

