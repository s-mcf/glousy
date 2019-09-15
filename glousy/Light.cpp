#include "Light.hpp"

#include <glm/glm.hpp>


namespace GLousy {
	Light::Light() {
	}

	Light::Light(float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos) {
		constant_ = constant;
		linear_ = linear;
		quadratic_ = quadratic;
		ambient_ = ambient;
		diffuse_ = diffuse;
		specular_ = specular;
		pos_ = pos;
	}


	Light::~Light() {
	}
	void Light::Draw(std::shared_ptr<Shader> s, const int index) const {
		const std::string i = std::to_string(index);
		s->set_float("point_lights[" + i + "].constant", constant_);
		s->set_float("point_lights[" + i + "].linear", linear_);
		s->set_float("point_lights[" + i + "].quadratic", quadratic_);
		
		s->set_vec("point_lights[" + i + "].ambient", ambient_);
		s->set_vec("point_lights[" + i + "].specular", specular_);
		s->set_vec("point_lights[" + i + "].diffuse", diffuse_);

		s->set_vec("point_lights[" + i + "].position", pos());
	}
}
