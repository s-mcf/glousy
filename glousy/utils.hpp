#pragma once

#include "const.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>

namespace GLousy::utils {
	template<typename T>
	T clamp(T Value, T Min, T Max)
	{
		return (Value < Min) ? Min : (Value > Max) ? Max : Value;
	}

	std::tuple<glm::vec3, glm::vec3, glm::vec3> calc_camera_vectors(float yaw, float pitch, glm::vec3 world_up = constants::up);
}
