#pragma once

#include "Shader.h"

#include <glm/glm.hpp>

namespace GLousy {
	class Light {
	public:
		Light(float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos);
		Light();
		~Light();

		void Draw(std::shared_ptr<Shader> s, const int index) const;

		glm::vec3 pos() const {
			return pos_;
		}
		void pos(glm::vec3 p) {
			pos_ = p;
		}
	private:
		glm::vec3 pos_;
		
		float constant_;
		float linear_;
		float quadratic_;

		glm::vec3 ambient_;
		glm::vec3 diffuse_;
		glm::vec3 specular_;
	};
}
