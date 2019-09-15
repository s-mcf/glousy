#include "Renderer.hpp"

namespace GLousy {
	namespace Render {
		void render(const DrawableSet &drawables, const Camera &camera, const std::vector<Light> &lights, const Framebuffer &f) {
			glBindFramebuffer(GL_FRAMEBUFFER, f.id());
			render_to_bound_target(drawables, camera, lights);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void render(const DrawableSet &drawables, const Camera &camera, const std::vector<Light> &lights) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			render_to_bound_target(drawables, camera, lights);
		}

		void render_to_bound_target(const DrawableSet &drawables, const Camera &camera, const std::vector<Light> &lights) {
			glClear(GL_DEPTH_BUFFER_BIT);

			for (auto &shader : drawables.shader_cache()) {
				shader->set_mat("view", camera.calc_view_mat());
				shader->set_mat("projection", camera.projection());
				shader->set_vec("view_position", camera.pos);
				for (int i = 0; i < lights.size(); i++) {
					lights[i].Draw(shader, i);
				}
			}

			for (auto &x : drawables.drawables) {
				x->draw();
			}
		}
	}
}
