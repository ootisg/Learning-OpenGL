#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "inputs.h"
#include "buffers_gl.h"
#include "shaders_gl.h"
#include "render.h"

#define WINDOW_RESOLUTION_WIDTH 1280
#define WINDOW_RESOLUTION_HEIGHT 720

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

scene render_scene;

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport (0, 0, width, height);
}

void init () {
	render_init (&render_scene);
	render_scene.program = get_default_shader_program ();
	glGenVertexArrays (1, &(render_scene.vao));
	glBindVertexArray (render_scene.vao);
	VBO* vertex_vbo = VBO_init (malloc (sizeof (VBO)), vertices, sizeof (vertices), GL_ARRAY_BUFFER);
	VBO* element_vbo = VBO_init (malloc (sizeof (VBO)), indices, sizeof (indices), GL_ELEMENT_ARRAY_BUFFER);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

int main () {
	
	//Initialize GLFW
    glfwInit ();
	
	//Set the window hints
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Create the window
	GLFWwindow* window = glfwCreateWindow (WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT, "Window Title", NULL, NULL);
	if (window == NULL) {
		//Window failed to initialize
		printf ("Failed to create GLFW window\n");
		glfwTerminate ();
		return -1;
	}
	glfwMakeContextCurrent (window);
	
	//Init GLEW
	glewInit ();
	
	//Set the initial viewport
	glViewport (0, 0, WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT);
	
	//Set the resize callback
	glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);
	
	//Init rendering code
	init ();
	
	//Display/event loop until the window is closed
	while (!glfwWindowShouldClose (window)) {
		
		//Input detection
		inputs_register_callbacks (window);
		
		//Render
		render_frame (&render_scene);
		
		//Swap buffers and poll events
		glfwSwapBuffers (window);
		glfwPollEvents ();
		
	}
  
	//Terminate GLFW and exit
	glfwTerminate ();
    return 0;
	
}