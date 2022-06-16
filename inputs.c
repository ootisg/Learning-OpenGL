#include "inputs.h"

void inputs_key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose (window, 1);
	}
	
}

void inputs_register_callbacks (GLFWwindow* window) {
	glfwSetKeyCallback (window, inputs_key_callback);
}