#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

uniform vec3 view_position;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	float inner;
	float outer;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// TODO have this passed at runtime?
#define POINT_LIGHTS_MAX 2
uniform PointLight point_lights[POINT_LIGHTS_MAX];

uniform Material material;
uniform Light light;
uniform DirectionalLight dir_light;


vec3 calc_dir_light(DirectionalLight light, vec3 normal, vec3 view_dir);
vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir);

void main()
{
	vec3 norm = normalize(normal);
	vec3 view_dir = normalize(view_position - frag_pos);

	vec3 lighting = vec3(0.0);

	lighting += calc_dir_light(dir_light, norm, view_dir);

	for (int i = 0; i < POINT_LIGHTS_MAX; i++) {
		lighting += calc_point_light(point_lights[i], norm, frag_pos, view_dir);
	}

	FragColor = vec4(lighting, 1.0);
}


// lighting functions
// TODO move these to separate file?

vec3 calc_dir_light(DirectionalLight light, vec3 normal, vec3 view_dir) {
	vec3 light_dir = normalize(-light.direction);

	float diff = max(dot(normal, light_dir), 1.0);

	vec3 reflect_dir= reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, tex_coords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tex_coords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, tex_coords).rgb;

	return (ambient + diffuse + specular);
}

vec3 calc_point_light(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
	vec3 light_dir = normalize(light.position - frag_pos);

	float diff = max(dot(normal, light_dir), 1.0);

	vec3 reflect_dir= reflect(-light_dir, normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

	float distance = length(light.position - frag_pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * texture(material.diffuse, tex_coords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tex_coords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, tex_coords).rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}
