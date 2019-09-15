#pragma once

#include <string>
#include <array>
#include <memory>

namespace GLousy {
	enum class TextureType {
		Diffuse,
		Specular,
		Height,
		Ambient,
	};
	
	enum class TextureFormat {
		R,
		RGB,
		RGBA
	};

	class Texture {
	public:
		Texture(TextureType type);
		Texture(TextureType type, int width, int height);
		~Texture();

		unsigned int id() const {
			return id_;
		}

		TextureType type() const {
			return type_;
		}

	private:
		unsigned int id_;
		TextureType type_;
	protected:
		void setup(TextureFormat format, int width, int height, unsigned char* data);
	};

	class ImageTexture : public Texture {
	public:
		ImageTexture(std::string path, TextureType type);
		
		std::string path() {
			return path_;
		}
	private:
		std::string path_;
	};

	class CubemapTexture {
	public:
		CubemapTexture(const unsigned int width, const unsigned int height);
		~CubemapTexture();

		unsigned int id() const {
			return id_;
		}
	private:
		unsigned int id_;
	};

	std::shared_ptr<CubemapTexture> load_cubemap_from_imageset(std::array<std::string, 6> faces);
}
