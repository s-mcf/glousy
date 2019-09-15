#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.hpp"

void processInput(GLFWwindow* window, double delta_t, GLousy::Camera* c);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);