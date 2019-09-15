#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:

	Shader(const GLchar* vertex_path, const GLchar* fragment_path);

	void use();

	void set_bool(const std::string &name, bool value);
	void set_int(const std::string &name, int value);
	void set_float(const std::string &name, float value);
	void set_mat(const std::string &name, glm::mat4 value);
	void set_vec(const std::string &name, glm::vec3 value);
	~Shader();
	
	unsigned int id() const {
		return id_;
	}
private:
	unsigned int id_;
};

