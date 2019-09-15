#pragma once

#include "Shader.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

#include <vector>
#include <string>
#include <assimp/scene.h>

namespace GLousy {
	class Model : public Drawable {
	public:
		Model(std::string path) {
			load_model(path);
		}
		void draw(Shader &shader) const;
	private:
		std::vector<Mesh> meshes;
		std::vector<ImageTexture> textures_loaded;
		std::string directory;

		void load_model(std::string path);
		void process_node(aiNode *node, const aiScene *scene);
		Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
		std::vector<ImageTexture> load_material_textures(aiMaterial *mat, TextureType type);
	};
}
