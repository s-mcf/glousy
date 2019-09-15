#include "Model.hpp"
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

namespace GLousy {

	void Model::draw(Shader &shader) const {
		for (auto &mesh : meshes) {
			mesh.draw(shader);
		}
	}

	void Model::load_model(std::string path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "Assimp error!\n" << importer.GetErrorString() << "\n";
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		process_node(scene->mRootNode, scene);
	}

	void Model::process_node(aiNode *node, const aiScene *scene) {
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(process_mesh(mesh, scene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			process_node(node->mChildren[i], scene);
		}
	}

	Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
		// data to fill
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.tex_coords = vec;
			}
			else
				vertex.tex_coords = glm::vec2(0.0f, 0.0f);
			if (mesh->mTangents != nullptr && mesh->mBitangents != nullptr) {
				// tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.tangent = vector;
				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.bitangent = vector;
			}
			vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		std::vector<ImageTexture> diffuseMaps = load_material_textures(material,  TextureType::Diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<ImageTexture> specularMaps = load_material_textures(material, TextureType::Specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<ImageTexture> normalMaps = load_material_textures(material, TextureType::Height);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<ImageTexture> heightMaps = load_material_textures(material, TextureType::Ambient);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		// return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices, textures);
	}


	std::vector<ImageTexture> Model::load_material_textures(aiMaterial *mat, TextureType type) {
		std::vector<ImageTexture> textures;
		aiTextureType ai_type;
		switch (type) {
		case TextureType::Diffuse:
			ai_type = aiTextureType_DIFFUSE;
			break;
		case TextureType::Specular:
			ai_type = aiTextureType_SPECULAR;
			break;
		case TextureType::Height:
			ai_type = aiTextureType_HEIGHT;
			break;
		case TextureType::Ambient:
			ai_type = aiTextureType_AMBIENT;
			break;
		}
		for (unsigned int i = 0; i < mat->GetTextureCount(ai_type); i++) {
			aiString str;
			mat->GetTexture(ai_type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++) {
				if (std::strcmp(textures_loaded[j].path().data(), str.C_Str()) == 0) {
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {   // if texture hasn't been loaded already, load it
				ImageTexture texture = ImageTexture(directory + "/" + std::string(str.C_Str()), type);
				textures.push_back(texture);
				textures_loaded.push_back(texture); // add to loaded textures
			}
		}
		return textures;
	}
}