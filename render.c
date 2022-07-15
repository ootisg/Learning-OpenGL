#include "render.h"
#include "matrix.h"
#include "inputs.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

float last_frame = 0;

v3 camera_pos, camera_front, camera_up;

float cubePositions[] = {
    0.0f,  0.0f,  0.0f, 
    2.0f,  5.0f, -15.0f, 
    -1.5f, -2.2f, -2.5f,  
    -3.8f, -2.0f, -12.3f,  
    2.4f, -0.4f, -3.5f,  
    -1.7f,  3.0f, -7.5f,  
    1.3f, -2.0f, -2.5f,  
    1.5f,  2.0f, -2.5f, 
    1.5f,  0.2f, -1.5f, 
    -1.3f,  1.0f, -1.5f  
};

scene* init_scene (void* loc) {
	scene* ptr = (scene*)loc;
}

void render_init (scene* init_scene) {
	glEnable(GL_DEPTH_TEST); 
	initv3 (&camera_pos, 0.0, 0.0, 3.0);
	initv3 (&camera_front, 0.0, 0.0, -1.0);
	initv3 (&camera_up, 0.0, 1.0, 0.0);
}

void render_frame (scene* render_scene) {
	
	//Clear the screen
	glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Bind the rendering parameters
	glUseProgram (render_scene->program);
	glBindVertexArray (render_scene->vao);
	
	//Set uniforms
	int i;
	glUniform1i (glGetUniformLocation (render_scene->program, "tex1"), 0);
	glUniform1i (glGetUniformLocation (render_scene->program, "tex2"), 1); //We really ought to be querying the texture structs here instead of assuming their texture units
	
	//Setup the view matrix
	if (last_frame == 0) {
		last_frame = glfwGetTime ();
	}
	float delta_time = glfwGetTime () - last_frame;
	last_frame = glfwGetTime ();
	float camera_speed = delta_time * 2.5;
	v3 scaled;
	if (key_down (GLFW_KEY_W)) {
		vector_scale3 (&scaled, &camera_front, camera_speed);
		vector_add3 (&camera_pos, &camera_pos, &scaled);
	}
	if (key_down (GLFW_KEY_S)) {
		vector_scale3 (&scaled, &camera_front, camera_speed);
		vector_diff3 (&camera_pos, &camera_pos, &scaled);
	}
	if (key_down (GLFW_KEY_A)) {
		v3 strafe;
		vector_cross3 (&strafe, &camera_up, &camera_front);
		vector_scale3 (&scaled, &strafe, camera_speed);
		vector_diff3 (&camera_pos, &camera_pos, &scaled);
	}
	if (key_down (GLFW_KEY_D)) {
		v3 strafe;
		vector_cross3 (&strafe, &camera_up, &camera_front);
		vector_scale3 (&scaled, &strafe, camera_speed);
		vector_add3 (&camera_pos, &camera_pos, &scaled);
	}
	mat4* a = malloc (sizeof (mat4)); 
	mat4* b = malloc (sizeof (mat4));
	mat4* view = malloc (sizeof (mat4));
	double radius = 10;
	double cam_x = cos (glfwGetTime ()) * radius;
	double cam_z = sin (glfwGetTime ()) * radius;
	v3 lookpt;
	vector_add3 (&lookpt, &camera_pos, &camera_front);
	matrix_lookat (a, 		&camera_pos,
							&lookpt,
							&camera_up);
	matrix_trans4 (b, 0.0, 0.0, -3.0);
	matrix_mul4m (view, b, a);
	
	//Setup the perspective matrix
	mat4* proj = malloc (sizeof (mat4));
	matrix_perspective (proj, 3.14 / 4, 1.0, 0.1, 100.0);
	
	for (i = 0; i < 10; i++) {
		
		//Transform matrix
		mat4* model = malloc (sizeof (mat4));
		
		//Construct the model matrix
		matrix_trans4 (a, cubePositions[i * 3], cubePositions[i * 3 + 1], cubePositions[i * 3 + 2]);
		float angle = ((0.959931 / 5) * 2) * i;
		matrix_rot4 (b, angle, newv3 (1.0, 0.3, 0.5));
		matrix_mul4m (model, a, b);
		
		//Combine the model, view, and proj matrices
		matrix_mul4m (a, proj, view);
		matrix_mul4m (b, a, model);
		
		//Send the MVP matrix to the vertex shader as a uniform
		GLfloat* gl_mat = malloc (sizeof (GLfloat) * 16);
		to_gl_matrix4 (gl_mat, b);
		glUniformMatrix4fv (glGetUniformLocation (render_scene->program, "transform"), 1, GL_FALSE, gl_mat);
		
		//Render the vertices
		glDrawArrays (GL_TRIANGLES, 0, 36);
	
	}
	
}