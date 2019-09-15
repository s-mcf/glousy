#include "input.hpp"
#include "GameState.hpp"
#include "utils.hpp"

float mouse_last_x = 500, mouse_last_y = 500;

void processInput(GLFWwindow* window, double delta_t, GLousy::Camera* c) {
	float camera_speed = (float)(1.5 * delta_t);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		c->move(camera_speed, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		c->move(camera_speed * -1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		c->move(0.0f, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		c->move(0.0f, camera_speed * -1.0f);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	GameState* gs = static_cast<GameState*>(glfwGetWindowUserPointer(window));

	float xoffset = (float) xpos - mouse_last_x;
	float yoffset = (float) ypos - mouse_last_y;
	mouse_last_x = (float) xpos;
	mouse_last_y = (float) ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	gs->camera->set_angles(gs->camera->pitch() + xoffset, gs->camera->yaw() - yoffset);
}