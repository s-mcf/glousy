#pragma once

#include "Texture.hpp"
#include "Drawable.hpp"

namespace GLousy {

	class Skybox : public ShaderedDrawable {
	public:
		Skybox(std::array<std::string, 6> paths);
		~Skybox();

		void draw() const;

	private:
		std::shared_ptr<CubemapTexture> cubemap_;
		unsigned int VAO, VBO;
	};

}
