#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GLousy {
	class Camera
	{
	public:
		Camera(int fov, float aspect, float z_near = 0.1f, float z_far = 100.0f, float pitch = 0.0f, float yaw = 0.0f);
		~Camera();

		glm::mat4 calc_view_mat() const;

		void set_angles(float pitch, float yaw);

		glm::vec3 pos = glm::vec3(0.0f);

		void move(float forward, float left);
		
		void set_perspective(int fov, float aspect, float z_near, float z_far);

		// ----- getters -------
		glm::mat4 projection() const {
			return projection_;
		}

		glm::vec3 front() const {
			return front_;
		}

		float yaw() const {
			return yaw_;
		}
		
		float pitch() const {
			return pitch_;
		}

		void aspect(float a) {
			aspect_ = a;
			set_perspective(fov_, aspect_, z_near_, z_far_);
		}
	private:
		glm::mat4 projection_ = glm::mat4(1.0f);
		glm::vec3 right_ = glm::vec3();
		glm::vec3 up_ = glm::vec3();
		glm::vec3 front_ = glm::vec3();
		
		float yaw_ = 90.0f;
		float pitch_ = 0.0f;

		int fov_ = 90;
		float aspect_ = 1.0f;

		float z_near_ = 0.1f;
		float z_far_ = 100.0f;
	};
}
