#include "MeshRenderer.h"
#include <iostream>
#include <glad_wrapper.h>

MeshRenderer::MeshRenderer()
{
	type = ComponentType::MeshRenderer;
	VBO = EBO = VAO = 0;
}

void MeshRenderer::Render()
{
	std::cout << "Rendering Object" << std::endl;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); // Generate EBO

	glBindVertexArray(VAO);

	// Bind and set vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

	// Bind and set index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO (optional)

	// Now render the mesh using the EBO
	glBindVertexArray(VAO); // Rebind the VAO before drawing
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0); // Use glDrawElements


}

void MeshRenderer::Clean()
{
	// Clean up (optional but recommended)
	glBindVertexArray(0); // Unbind VAO
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}