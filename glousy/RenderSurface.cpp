#include "RenderSurface.hpp"
#include "const.h"

#include <iostream>

namespace GLousy {

	// TODO allow rendersurface to use any mesh
	RenderSurface::RenderSurface(std::shared_ptr<Shader> s) :
		m(
			std::vector<Vertex> {
		Vertex{
			glm::vec3(1.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 0.0f)
		}, Vertex{
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
		}, Vertex{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		}, Vertex{
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
		}
	},
			std::vector<unsigned int> {
			3, 2, 1, 3, 1, 0
		},
			std::vector<Texture> {
				Texture(TextureType::Diffuse, constants::rendersurface_render_width, constants::rendersurface_render_height),
				Texture(TextureType::Specular, 1, 1)
			}
			),
		Object(&m, s),
				r(constants::rendersurface_render_width, constants::rendersurface_render_height) {
		
		f.attach_texture(m.textures[0]);
		f.attach_renderbuffer(r);
		if (!f.is_complete()) {
			std::cerr << "Framebuffer not complete!\n";
		}
	}

			RenderSurface::~RenderSurface() {
			}
}
