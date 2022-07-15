#ifndef INPUTS_H
#define INPUTS_H

#include <GLFW/glfw3.h>

/// Registers the default input callbacks to the given window
/// @param the window to use for input callbacks
void inputs_register_callbacks (GLFWwindow* window);

/// Checks if the specified key is currently held down
/// @param glfw_key_code the key code to check for
/// @return 1 if the key is held down, 0 otherwise
int key_down (int glfw_key_code);

#endif