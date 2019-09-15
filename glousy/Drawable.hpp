#pragma once

#include "Shader.h"
#include <set>
#include <vector>

namespace GLousy {
	class Drawable {
	public:
		virtual ~Drawable() = default;

		virtual void draw(Shader &s) const = 0;

	};

	class ShaderedDrawable {
	public:
		ShaderedDrawable(std::shared_ptr<Shader> s) :
			shader_(s) {
		};

		virtual void draw() const = 0;

		std::shared_ptr<Shader> shader() const {
			return shader_;
		}
	private:
		std::shared_ptr<Shader> shader_ = nullptr;
	};

	class DrawableSet {
	public:
		// TODO wrap the vector so the user can't accidentally add an object without updating the shader cache?
		std::vector<std::shared_ptr<ShaderedDrawable>> drawables;

		void update_shader_cache();

		// TODO consult with a C++ expert and make sure that this doesn't break everything
		const std::set<std::shared_ptr<Shader>>& shader_cache() const {
			return shaders;
		}
	private:
		std::set<std::shared_ptr<Shader>> shaders;
	};
}
