#include "callbacks.hpp"
#include "GameState.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GameState* gs = static_cast<GameState*>(glfwGetWindowUserPointer(window));

	*gs->screen_height = height;
	*gs->screen_width = width;
	gs->camera->aspect(static_cast<float>(width) / static_cast<float>(height));
	glViewport(0, 0, width, height);
}
