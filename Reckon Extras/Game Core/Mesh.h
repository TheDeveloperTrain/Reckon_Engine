#pragma once
#include <vector>
class Mesh
{
public:
	Mesh(std::vector<float> _vertices, std::vector<unsigned int> _indices);
	Mesh();
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
};

