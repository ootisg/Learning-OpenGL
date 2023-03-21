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
#include "scene.h"

#define WINDOW_RESOLUTION_WIDTH 1280
#define WINDOW_RESOLUTION_HEIGHT 720

float obj_vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float light_vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

float* teapot_mesh;
int teapot_size;

scene render_scene;

void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
	glViewport (0, 0, width, height);
}

import_teapog () {
	
	scenee* sc = malloc (sizeof (scenee));
	import_scene (sc, "resources/models/teapot/teapot.obj");
	model* top = sc->objects;
	printf ("%d\n", top->root_node->children->num_meshes);
	
	mesh* curr = top->root_node->children->meshes[0];
	int numVertices = curr->num_vertices;
	float* vertices = curr->vertex_positions;
	float* normals = curr->vertex_normals;
	teapot_size = numVertices;
	teapot_mesh = malloc (numVertices * 8 * sizeof (float));
	int j = 0;
	for (j = 0; j < numVertices; j++) {
		float* currPos = &(vertices[j * 3]);
		float* currNorm = &(normals[j * 3]);
		teapot_mesh[j * 8] = *currPos;
		teapot_mesh[j * 8 + 1] = *(currPos + 1);
		teapot_mesh[j * 8 + 2] = *(currPos + 2);
		teapot_mesh[j * 8 + 3] = *currNorm;
		teapot_mesh[j * 8 + 4] = *(currNorm + 1);
		teapot_mesh[j * 8 + 5] = *(currNorm + 2);
		teapot_mesh[j * 8 + 6] = 0;
		teapot_mesh[j * 8 + 7] = 0;
	}
	
}

void init () {
	
	init_scene (&render_scene);
	textures_init ();
	render_init (&render_scene);
	
	import_teapog ();
	
	//Object 0 (cube)
	render_scene.programs[0] = make_program_from_files ("obj_vertex_shader.glsl", NULL, "obj_frag_shader.glsl");
	glGenVertexArrays (1, &(render_scene.vaos[0]));
	glBindVertexArray (render_scene.vaos[0]);
	VBO* vertex_vbo = VBO_init (malloc (sizeof (VBO)), teapot_mesh, teapot_size * 8 * sizeof (float), GL_ARRAY_BUFFER);
	render_scene.model_sizes[0] = teapot_size;
	texture* tex1 = texture_load_from_file (malloc (sizeof (texture)), "resources/container2.png");
	texture* tex2 = texture_load_from_file (malloc (sizeof (texture)), "resources/container2_specular.png");
	texture_enable (tex1);
	texture_enable (tex2);  
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof (float)));
	glEnableVertexAttribArray (2);
	matrix_scale4 (&(render_scene.models[0]), 0.25, 0.25, 0.25);
	
	//Object 1 (teapot)
	render_scene.programs[1] = make_program_from_files ("obj_vertex_shader.glsl", NULL, "obj_frag_shader.glsl");
	glGenVertexArrays (1, &(render_scene.vaos[1]));
	glBindVertexArray (render_scene.vaos[1]);
	vertex_vbo = VBO_init (malloc (sizeof (VBO)), teapot_mesh, teapot_size * 8 * sizeof (float), GL_ARRAY_BUFFER);
	render_scene.model_sizes[1] = teapot_size;
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof (float)));
	glEnableVertexAttribArray (2);
	matrix_iden4 (&(render_scene.models[1]));
	
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
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