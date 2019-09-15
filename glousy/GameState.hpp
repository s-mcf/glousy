#pragma once

#include "Camera.hpp"

/* GLFW does not allow you to attach context (parameters) to callbacks.
 * It only allows you to attach a single pointer to the window object which callbacks have access to.
 * Thus, we can use a pointer to an instance of this struct to give callbacks the context they need.
 * TODO get rid of GLFW so we can have better callbacks.
 */
struct GameState {
	int *screen_width, *screen_height;
	GLousy::Camera* camera;
};
