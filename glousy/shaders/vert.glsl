#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coords;

out vec3 frag_pos;
out vec3 normal;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	frag_pos = vec3(model * vec4(aPos, 1.0));
	normal = mat3(transpose(inverse(model))) * in_normal; // multiple by normal matrix so scaling doesn't break normals
	tex_coords = in_tex_coords;
}
