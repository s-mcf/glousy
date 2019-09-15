#pragma once
#include <glm/glm.hpp>

namespace GLousy::constants {
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	constexpr int rendersurface_render_width = 1000;
	constexpr int rendersurface_render_height = 1000;
	constexpr float rendersurface_render_aspect =
		static_cast<float>(rendersurface_render_width) / static_cast<float>(rendersurface_render_height);
	constexpr int rendersurface_render_fov = 90;
}
