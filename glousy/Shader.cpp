#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path) {
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vert_shader_file;
	std::ifstream frag_shader_file;

	// enable exceptions
	vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vert_shader_file.open(vertex_path);
		frag_shader_file.open(fragment_path);

		std::stringstream vert_shader_stream, frag_shader_stream;
		vert_shader_stream << vert_shader_file.rdbuf();
		frag_shader_stream << frag_shader_file.rdbuf();
		vert_shader_file.close();
		frag_shader_file.close();

		vertex_code = vert_shader_stream.str();
		fragment_code = frag_shader_stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Shader file could not be read!\n";
	}

	const char* vertex_shader_source = vertex_code.c_str();
	const char* fragment_shader_source = fragment_code.c_str();
	
	// compile shaders
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	int success;
	char log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		std::cout << "Vertex shader compilation failed!\n" << log << "\n";
	}

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		std::cout << "Fragment shader compilation failed!\n" << log << "\n";
	}

	id_ = glCreateProgram();
	glAttachShader(id_, vertex_shader);
	glAttachShader(id_, fragment_shader);
	glLinkProgram(id_);

	glGetProgramiv(id_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id_, 512, NULL, log);
		std::cout << "Shader linking failed!\n" << log << "\n";
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::use()
{
	glUseProgram(id_);
}

// TODO optimize these to remove glGetUniformLocation?
// TODO research DSA or make these bind then unbind the shader
void Shader::set_bool(const std::string &name, bool value)
{
	glProgramUniform1i(id_, glGetUniformLocation(id_, name.c_str()), (int)value);
}
void Shader::set_int(const std::string &name, int value)
{
	glProgramUniform1i(id_, glGetUniformLocation(id_, name.c_str()), value);
}
void Shader::set_float(const std::string &name, float value)
{
	glProgramUniform1f(id_, glGetUniformLocation(id_, name.c_str()), value);
}
void Shader::set_mat(const std::string &name, glm::mat4 value)
{
	glProgramUniformMatrix4fv(id_, glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::set_vec(const std::string & name, glm::vec3 value) {
	glProgramUniform3fv(id_, glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(value));
}

Shader::~Shader()
{
	glDeleteProgram(id_);
}
