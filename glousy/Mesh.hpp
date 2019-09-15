#pragma once

#include "Texture.hpp"
#include "Shader.h"
#include "Drawable.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace GLousy {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class Mesh : public Drawable {
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void draw(Shader &shader) const;

	private:
		unsigned int VAO, VBO, EBO;
	};

}

