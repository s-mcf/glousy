#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <iterator>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "callbacks.hpp"
#include "input.hpp"
#include "Shader.h"
#include "Camera.hpp"
#include "Light.hpp"
#include "GameState.hpp"
#include "Texture.hpp"
#include "RenderSurface.hpp"
#include "Model.hpp"
#include "Object.hpp"
#include "Drawable.hpp"
#include "Renderer.hpp"
#include "Skybox.hpp"

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam) {
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
		fprintf(stderr, "%s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
}

#define DEBUG true

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// make windows
	int screen_width = 1000;
	int screen_height = 1000;
	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW windows\n";
		return 1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return 1;
	}

	// set up camera
	GLousy::Camera camera = GLousy::Camera(75, static_cast<float>(screen_width) / static_cast<float>(screen_height));
	camera.pos = glm::vec3(0.0f, 0.0f, 3.0f);
	GameState gs;
	gs.screen_height = &screen_height;
	gs.screen_width = &screen_width;
	gs.camera = &camera;

	// create lights
	std::vector<GLousy::Light> lights {
GLousy::Light(
		1.0f, 
		0.35f,
		0.44f,

		glm::vec3(0.1f),
		glm::vec3(2.0f),
		glm::vec3(2.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	),
GLousy::Light(
		1.0f, 
		0.35f,
		0.44f,

		glm::vec3(0.1f),
		glm::vec3(2.0f),
		glm::vec3(2.0f),
		glm::vec3(1.0f, 2.0f, 1.0f)
	)
	};

	// now we can start using OpenGL!
#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif // DEBUG
	glDebugMessageCallback(MessageCallback, 0);
	glViewport(0, 0, screen_width, screen_height);
	glfwSetWindowUserPointer(window, &gs);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	auto main_shader = std::make_shared<Shader>("shaders/vert.glsl", "shaders/frag.glsl");

	GLousy::DrawableSet objects;
	GLousy::Model our_model("assets/nanosuit/nanosuit.obj");
	objects.drawables = std::vector<std::shared_ptr<GLousy::ShaderedDrawable>>(3);
	objects.drawables[0] = std::make_shared<GLousy::Skybox>(std::array<std::string, 6>{ {
				"assets/lmcity/lmcity_rt.tga",
				"assets/lmcity/lmcity_lf.tga",
				"assets/lmcity/lmcity_up.tga",
				"assets/lmcity/lmcity_dn.tga",
				"assets/lmcity/lmcity_ft.tga",
				"assets/lmcity/lmcity_bk.tga"
		}});
	objects.drawables[1] = std::make_shared<GLousy::Object>(&our_model, main_shader);
	objects.drawables[2] = std::make_shared<GLousy::RenderSurface>(main_shader);
	auto nanosuit = std::static_pointer_cast<GLousy::Object> (objects.drawables[1]);
	auto surface = std::static_pointer_cast<GLousy::RenderSurface> (objects.drawables[2]);
	auto skybox = std::static_pointer_cast<GLousy::Skybox> (objects.drawables[0]);
	nanosuit->alter_relative(glm::vec3(0.0f), glm::vec3(0.15f));
	objects.update_shader_cache();


	double delta_t = 0.0f;
	double frame_t = 0.0f;

	// render loop
	while (!glfwWindowShouldClose(window)) {
		double current_frame_t = glfwGetTime();
		delta_t = current_frame_t - frame_t;
		frame_t = current_frame_t;

		processInput(window, delta_t, &camera);

		GLousy::Render::render(objects, camera, lights);
		// 2nd pass for render-to-texture
		GLousy::Render::render(objects, camera, lights, surface->framebuffer());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
