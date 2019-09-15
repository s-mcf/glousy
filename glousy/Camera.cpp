#include "Camera.hpp"
#include "const.h"
#include "utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLousy {
	Camera::Camera(int fov, float aspect, float z_near, float z_far, float pitch, float yaw)
	{
		set_perspective(fov, aspect, z_near, z_far);
		set_angles(pitch, yaw);
	}

	Camera::~Camera()
	{
	}

	glm::mat4 Camera::calc_view_mat() const {
		return glm::lookAt(pos, pos + front_, up_);
	}

	void Camera::set_angles(float pitch, float yaw) {
		yaw = utils::clamp(yaw, -89.0f, 89.0f);
		this->pitch_ = pitch;
		this->yaw_ = yaw;

		std::tie(front_, right_, up_) = utils::calc_camera_vectors(pitch, yaw);
	}

	void Camera::move(float forward, float left) {
			pos += forward * front_;
			pos -= glm::normalize(glm::cross(front_, up_)) * left;
	}

	void Camera::set_perspective(int fov, float aspect, float z_near, float z_far) {
		std::tie(fov_, aspect_, z_near_, z_far_) = std::make_tuple(fov, aspect, z_near, z_far);

		projection_ = glm::perspective(glm::radians(static_cast<float>(fov)), aspect, z_near, z_far);
	}
}
