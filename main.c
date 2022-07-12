#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "inputs.h"
#include "buffers_gl.h"
#include "shaders_gl.h"
#include "textures_gl.h"
#include "render.h"
#include "matrix.h"

#define WINDOW_RESOLUTION_WIDTH 512
#define WINDOW_RESOLUTION_HEIGHT 512

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int elems[] = {
	0, 1, 2,
	2, 3, 0
};

scene render_scene;

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport (0, 0, width, height);
}

void init () {
	/*int i;
	mat4* mat = malloc (sizeof (mat4));
	matrix_perspective (mat, 3.14 / 4, 1.0, .2, 50);
	matrix_print4 (mat);
	for (i = 0; i < 4; i++) {
		v4* pos = newv4 (vertices[i * 8], vertices[i * 8 + 1], vertices[i * 8 + 2], 1.0);
		v4* res = malloc (sizeof (v4));
		matrix_mul4v (res, mat, pos);
		vertices[i * 8] = res->x / res->w;
		vertices[i * 8 + 1] = res->y / res->w;
		vertices[i * 8 + 2] = res->z / res->w;
		printf ("INITIAL: %f, %f, %f, %f\n", res->x, res->y, res->z, res->w);
		printf ("DIVIDED: %f, %f, %f\n", res->x / res->w, res->y / res->w, res->z / res->w);
	}*/
	textures_init ();
	render_init (&render_scene);
	render_scene.program = make_program_from_files ("vertex_shader.glsl", NULL, "frag_shader.glsl");
	glGenVertexArrays (1, &(render_scene.vao));
	glBindVertexArray (render_scene.vao);
	VBO* vertex_vbo = VBO_init (malloc (sizeof (VBO)), vertices, sizeof (vertices), GL_ARRAY_BUFFER);
	VBO* vertex_elem_vbo = VBO_init (malloc (sizeof (VBO)), elems, sizeof (elems), GL_ELEMENT_ARRAY_BUFFER);
	texture* tex1 = texture_load_from_file (malloc (sizeof (texture)), "resources/container.jpg");
	texture* tex2 = texture_load_from_file (malloc (sizeof (texture)), "resources/awesomeface.png");
	texture_enable (tex1);
	texture_enable (tex2);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray (1);
}

int main () {
	
	//Initialize GLFW
    glfwInit ();
	printf ("GLFW Initialized\n");
	
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