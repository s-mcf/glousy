#include "Texture.hpp"
#include "stb_image.h"

#include <glad/glad.h>
#include <iostream>

namespace GLousy {
	ImageTexture::ImageTexture(std::string path, TextureType type) : Texture(type) {
		path_ = path;

		int width, height, components;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &components, 0);
		if (data) {
			TextureFormat format;
			if (components == 1)
				format = TextureFormat::R;
			else if (components == 3)
				format = TextureFormat::RGB;
			else if (components == 4)
				format = TextureFormat::RGBA;

			setup(format, width, height, data);

			stbi_image_free(data);
		}
		else {
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
	}

	Texture::Texture(TextureType type) :
		type_(type) {
		glCreateTextures(GL_TEXTURE_2D, 1, &id_);
	}

	Texture::Texture(TextureType type, int width, int height) : Texture(type) {
		setup(TextureFormat::RGB, width, height, nullptr);
	}

	Texture::~Texture() {
		// TODO prevent copy and pass only shared_ptr to Texture
	}

	void Texture::setup(TextureFormat format, int width, int height, unsigned char* data) {

		GLenum storage_format, subimage_format;
		switch (format) {
		case TextureFormat::R:
			storage_format = GL_R8;
			subimage_format = GL_RED;
			break;
		case TextureFormat::RGB:
			storage_format = GL_RGB8;
			subimage_format = GL_RGB;
			break;
		case TextureFormat::RGBA:
			storage_format = GL_RGBA8;
			subimage_format = GL_RGBA;
			break;
		}

		glTextureStorage2D(id_, 1, storage_format, width, height);
		if(data != nullptr)
			glTextureSubImage2D(id_, 0, 0, 0, width, height, subimage_format, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(id_);
	}

	CubemapTexture::CubemapTexture(const unsigned int width, const unsigned int height) {
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &id_);
		
		glTextureStorage2D(id_, 1, GL_RGB8, width, height);

		glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(id_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	CubemapTexture::~CubemapTexture() {
		glDeleteTextures(1, &id_);
	}

	std::shared_ptr<CubemapTexture> load_cubemap_from_imageset(std::array<std::string, 6> faces) {
		std::shared_ptr<CubemapTexture> c;
		int width, height, channels;
		for (int i = 0; i < 6; i++) {
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
			if (data) {
				if(i == 0) {
					c = std::make_shared<CubemapTexture>(width, height);
				}
				glTextureSubImage3D(c->id(), 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else {
				std::cout << "Cubemap texture failed to load! " << faces[i] << "\n";
			}
			stbi_image_free(data);
		}
		return c;
	}
}
