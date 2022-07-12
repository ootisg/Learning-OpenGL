#include "render.h"
#include "matrix.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

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
	glUniform1i (glGetUniformLocation (render_scene->program, "tex1"), 0);
	glUniform1i (glGetUniformLocation (render_scene->program, "tex2"), 1); //We really ought to be querying the texture structs here instead of assuming their texture units
	//Transform matrix
	mat4* model = malloc (sizeof (mat4));
	mat4* view = malloc (sizeof (mat4));
	mat4* proj = malloc (sizeof (mat4));
	mat4* a = malloc (sizeof (mat4)); 
	mat4* b = malloc (sizeof (mat4));
	//matrix_look_at (a, newv3 (), newv3 (), newv3 ());
	matrix_rotx4 (model, -0.959931);
	matrix_trans4 (view, 0.0, 0.0, -3.0);
	matrix_perspective (proj, 3.14 / 4, 1.78, 0.1, 100.0);
	matrix_mul4m (a, proj, view);
	matrix_mul4m (b, a, model);
	GLfloat* gl_mat = malloc (sizeof (GLfloat) * 16);
	to_gl_matrix4 (gl_mat, b);
	glUniformMatrix4fv (glGetUniformLocation (render_scene->program, "transform"), 1, GL_FALSE, gl_mat);
	
	//Render the vertices
	glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}