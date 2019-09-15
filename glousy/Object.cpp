#include "Object.hpp"

#include <glm/gtc/matrix_transform.hpp>


namespace GLousy {

	Object::Object(const Drawable* m, std::shared_ptr<Shader> s) :
		ShaderedDrawable(s),
		model_(m)
	{
		recalculate_transform();
	}

	Object::~Object() {
	}

	void Object::draw() const {
		shader()->use();
		shader()->set_mat("model", transform_);
		model_->draw(*shader());
	}

	void Object::alter_relative(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotation) {
		pos_ += translate;
		scale_ *= scale;
		rotation_ += rotation;
		recalculate_transform();
	}

	void Object::alter_absolute(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotation) {
		pos_ = translate;
		scale_ = scale;
		rotation_ = rotation;
		recalculate_transform();
	}

	void Object::recalculate_transform() {
		glm::mat4 transform = glm::mat4(1.0f);

		// TODO: quaternions
		transform = glm::translate(transform, pos_);
		transform = glm::scale(transform, scale_);
		transform_ = transform;
	}

}