#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "matrix.h"
#include "inputs.h"
#include "camera.h"
#include "render_info.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float last_frame = 0;
float delta_time = -1;

v3 camera_pos, camera_direction, camera_up;

GLfloat lightPos[3];

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

float frame_delta_time () {
	return delta_time;
}

scene* init_scene (void* loc) {
	scene* ptr = (scene*)loc;
	ptr->num_objs = 2;
	ptr->vaos = malloc (sizeof (void*) * ptr->num_objs);
	ptr->programs = malloc (sizeof (void*) * ptr->num_objs);
	ptr->models = malloc (sizeof (mat4) * ptr->num_objs);
	lightPos[0] = 1.2;
	lightPos[1] = 1.0;
	lightPos[2] = 2.0;
}

void render_init (scene* init_scene) {
	glEnable(GL_DEPTH_TEST); 
	camera* cam = camera_init (malloc (sizeof (camera)));
	set_active_camera (cam);
}

void render_frame (scene* render_scene) {
	
	//Save timings related to deltaTime calculation
	float curr_time = glfwGetTime ();
	if (last_frame == 0) {
		last_frame = curr_time;
	}
	delta_time = curr_time - last_frame;
	last_frame = curr_time;
	
	//Process key inputs for camera controls
	camera_process_key_inputs ();
	
	//Clear the screen
	glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Set uniforms
	int i;
	//glUniform1i (glGetUniformLocation (render_scene->programs[0], "tex1"), 0);
	//glUniform1i (glGetUniformLocation (render_scene->programs[0], "tex2"), 1); //We really ought to be querying the texture structs here instead of assuming their texture units
	
	camera* cam = get_active_camera ();
	
	//Setup the view matrix
	mat4* view = camera_get_view_matrix (cam);
	
	//Setup the perspective matrix
	mat4* proj = camera_get_proj_matrix (cam);
	
	for (i = 0; i < 2; i++) {
		
		//Set the correct shader program...
		glUseProgram (render_scene->programs[i]);
		glBindVertexArray (render_scene->vaos[i]);
		
		//
		if (i == 0) {
			glUniform1i (glGetUniformLocation (render_scene->programs[0], "tex1"), 0);
			glUniform1i (glGetUniformLocation (render_scene->programs[0], "tex2"), 1); //We really ought to be querying the texture structs here instead of assuming their texture units
			glUniform3f (glGetUniformLocation (render_scene->programs[0], "lightPos"), lightPos[0], lightPos[1], lightPos[2]);
		} else if (i == 1) {
			mat4 a, b;
			matrix_scale4 (&a, 0.2, 0.2, 0.2);
			matrix_trans4 (&b, lightPos[0], lightPos[1], lightPos[2]);
			matrix_mul4m (&(render_scene->models[1]), &b, &a);
		}
		
		//Send the model, view, and proj matrices to the vertex shader as uniforms
		GLfloat* gl_mat = malloc (sizeof (GLfloat) * 16);
		to_gl_matrix4 (gl_mat, &(render_scene->models[i]));
		glUniformMatrix4fv (glGetUniformLocation (render_scene->programs[i], "model"), 1, GL_FALSE, gl_mat);
		to_gl_matrix4 (gl_mat, view);
		glUniformMatrix4fv (glGetUniformLocation (render_scene->programs[i], "view"), 1, GL_FALSE, gl_mat);
		to_gl_matrix4 (gl_mat, proj);
		glUniformMatrix4fv (glGetUniformLocation (render_scene->programs[i], "proj"), 1, GL_FALSE, gl_mat);
		
		//Render the vertices
		glDrawArrays (GL_TRIANGLES, 0, 36);
	
	}
	
}