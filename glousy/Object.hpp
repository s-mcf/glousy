#pragma once

#include "Drawable.hpp"
#include "Model.hpp"

#include <glm/glm.hpp>

namespace GLousy {
	class Object : public ShaderedDrawable {
	public:
		Object(const Drawable* m, std::shared_ptr<Shader> s);
		~Object();

		void draw() const;

		void alter_relative(
			glm::vec3 translate = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(0.0f),
			glm::vec3 rotation = glm::vec3(0.0f));
		void alter_absolute(
			glm::vec3 translate = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(0.0f),
			glm::vec3 rotation = glm::vec3(0.0f));

	private:
		glm::vec3 pos_ = glm::vec3(0.0f);
		glm::vec3 scale_ = glm::vec3(1.0f);
		glm::vec3 rotation_;

		glm::mat4 transform_ = glm::mat4(1.0f);
		const Drawable* model_;

		void recalculate_transform();
	};
}
