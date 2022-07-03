#include "render.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>

scene* init_scene (void* loc) {
	scene* ptr = (scene*)loc;
}

void render_init (scene* init_scene) {
	//Nothing yet
}

void render_frame (scene* render_scene) {
	
	//Clear the screen
	glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	
	//Bind the rendering parameters
	glUseProgram (render_scene->program);
	glBindVertexArray (render_scene->vao);
	
	//Set uniforms
	glUniform1i (glGetUniformLocation (render_scene->program, "ourTexture"), 0);
	
	//Render the vertices
	glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}