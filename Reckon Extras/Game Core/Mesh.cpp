#include "Mesh.h"

Mesh::Mesh(std::vector<float> _vertices, std::vector<unsigned int> _indices)
{
	vertices = _vertices;
	indices = _indices;
}