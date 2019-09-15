#include "Mesh.hpp"

#include <glad/glad.h>
#include <stdint.h>
#include <iostream>

GLousy::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
	// TODO DSA-ify and move VAO/VBO to its own object?
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	// normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	// UVs
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coords)));
	
	glBindVertexArray(0); // unbind
}

void GLousy::Mesh::draw(Shader &shader) const {
	unsigned int diffuse_count = 1;
	unsigned int specular_count = 1;

	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i); // GL_TEXTUREn is guaranteed to be GL_TEXTURE0 + n

		std::string number;
		std::string name;
		switch (textures[i].type()) {
		case TextureType::Diffuse:
			number = std::to_string(diffuse_count++);
			name = "diffuse";
			break;
		case TextureType::Specular:
			number = std::to_string(specular_count++);
			name = "specular";
			break;
		default:
			continue; // unsupported texture type
		}

		name = "material." + name;
		shader.set_int(name, i); // tell shader which texture to use
		shader.set_float("material.shininess", 32.0f);
		glBindTexture(GL_TEXTURE_2D, textures[i].id()); // TODO is this right?
	}
	glBindVertexArray(VAO);
	shader.use();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
