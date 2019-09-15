#include "utils.hpp"
		
namespace GLousy::utils {
	std::tuple<glm::vec3, glm::vec3, glm::vec3> calc_camera_vectors(float yaw, float pitch, glm::vec3 world_up) {
		glm::vec3 front = glm::normalize(glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		));
		glm::vec3 right = glm::normalize(glm::cross(front, world_up));
		glm::vec3 up = glm::normalize(glm::cross(right, front));

		return { front, right, up };
	}
}