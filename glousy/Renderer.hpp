#pragma once

#include "Model.hpp"
#include "Light.hpp"
#include "Framebuffer.hpp"
#include "Camera.hpp"
#include "Drawable.hpp"

#include<vector>

namespace GLousy {
	namespace Render {
		void render(
			const DrawableSet &drawables,
			const Camera &camera,
			const std::vector<Light> &lights,
			const Framebuffer &f
		);
		void render(
			const DrawableSet &drawables,
			const Camera &camera,
			const std::vector<Light> &lights
		);
		void render_to_bound_target(
			const DrawableSet &drawables,
			const Camera &camera,
			const std::vector<Light> &lights
		);
	}
}
