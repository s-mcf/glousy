#pragma once

#include "Object.hpp"
#include "Shader.h"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

namespace GLousy {
	class RenderSurface : public Object {
	public:
		RenderSurface(std::shared_ptr<Shader> s);

		~RenderSurface();

		const Framebuffer& framebuffer() {
			return f;
		}
	private:
		int width = 1000;
		int height = 1000;
		Mesh m;
		Framebuffer f;
		Renderbuffer r;
	};
}
