#ifndef INPUTS_H
#define INPUTS_H

#include <GLFW/glfw3.h>

/// Registers the default input callbacks to the given window
/// @param the window to use for input callbacks
void inputs_register_callbacks (GLFWwindow* window);

#endif