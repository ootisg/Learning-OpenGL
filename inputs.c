#include "inputs.h"

#include <stdio.h>

char keys_down[GLFW_KEY_LAST];

void inputs_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (action == GLFW_PRESS) {
		keys_down[key] = 1;
	}
	if (action == GLFW_RELEASE) {
		keys_down[key] = 0;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose (window, 1);
	}
	
}

void inputs_register_callbacks (GLFWwindow* window) {
	glfwSetKeyCallback (window, inputs_key_callback);
	glfwSetCursorPosCallback (window, mouse_callback);
}

int key_down (int glfw_key_code) {
	return keys_down[glfw_key_code];
}