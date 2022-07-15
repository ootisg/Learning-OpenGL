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
float last_x = 0;
float last_y = 0;
int first_frame = 1;
float last_w_duration = 0;
float last_w_time = 0;
float last_w_press = 0;
int w_down = 0;
int speedup = 0;

double pitch = 0;
double yaw = -3.14159 / 2;

v3 camera_pos, camera_direction, camera_up;

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

void mouse_callback (GLFWwindow* window, double xpos, double ypos) {
	
	if (first_frame) {
		last_x = xpos;
		last_y = ypos;
		first_frame = 0;
	}
	double offs_x = xpos - last_x;
	double offs_y = ypos - last_y;
	float delta_time = glfwGetTime () - last_frame;
	pitch += offs_y * delta_time * 1.0;
	yaw -= offs_x * delta_time * 1.0;
	last_x = xpos;
	last_y = ypos;
	if (pitch > 1.55334) {
		pitch = 1.55334;
	}
	if (pitch < -1.55334) {
		pitch = -1.55334;
	}
	
}

void render_init (scene* init_scene) {
	glEnable(GL_DEPTH_TEST); 
	initv3 (&camera_pos, 0.0, 0.0, 0.0);
	initv3 (&camera_direction, 0.0, 0.0, -1.0);
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
	
	//Calculate deltaTime
	if (last_frame == 0) {
		last_frame = glfwGetTime ();
	}
	float delta_time = glfwGetTime () - last_frame;
	last_frame = glfwGetTime ();
	float camera_speed = delta_time * (speedup ? 10 : 2.5);
	float camera_rot_speed = delta_time;
	
	//Calculate view direction vector based on current pitch and yaw
	camera_direction.x = cos (yaw) * cos (pitch);
	camera_direction.y = sin (pitch);
	camera_direction.z = sin (yaw) * cos (pitch);
	
	//WASD movement
	v3 scaled;
	if (key_down (GLFW_KEY_W)) {
		//Down edge of w press detection
		if (!w_down) {
			w_down = 1;
			if (glfwGetTime () - last_w_press < .25 && last_w_time < 0.1) { //Double tap; first tap is < 100ms in length, followed by a second press less than 250ms later
				speedup = 1;
			}
			last_w_press = glfwGetTime ();
		}
		//Do movement
		vector_scale3 (&scaled, &camera_direction, camera_speed);
		vector_diff3 (&camera_pos, &camera_pos, &scaled);
		
	} else {
		//Up edge of w press detection
		if (w_down) {
			w_down = 0;
			last_w_time = glfwGetTime () - last_w_press;
		}
		if (speedup) {
			speedup = 0;
		}
	}
	if (key_down (GLFW_KEY_S)) {
		vector_scale3 (&scaled, &camera_direction, camera_speed);
		vector_add3 (&camera_pos, &camera_pos, &scaled);
	}
	//Take cross products for left/right strafe
	if (key_down (GLFW_KEY_A)) {
		v3 strafe;
		vector_cross3 (&strafe, &camera_up, &camera_direction);
		vector_scale3 (&scaled, &strafe, camera_speed);
		vector_add3 (&camera_pos, &camera_pos, &scaled);
	}
	if (key_down (GLFW_KEY_D)) {
		v3 strafe;
		vector_cross3 (&strafe, &camera_up, &camera_direction);
		vector_scale3 (&scaled, &strafe, camera_speed);
		vector_diff3 (&camera_pos, &camera_pos, &scaled);
	}
	
	//Space and shift for up and down movement
	if (key_down (GLFW_KEY_SPACE)) {
		vector_scale3 (&scaled, &camera_up, camera_speed);
		vector_add3 (&camera_pos, &camera_pos, &scaled);
	}
	if (key_down (GLFW_KEY_LEFT_SHIFT)) {
		vector_scale3 (&scaled, &camera_up, camera_speed);
		vector_diff3 (&camera_pos, &camera_pos, &scaled);
	}
	
	//Setup the view matrix
	mat4* view = malloc (sizeof (mat4));
	double radius = 10;
	double cam_x = cos (glfwGetTime ()) * radius;
	double cam_z = sin (glfwGetTime ()) * radius;
	v3 lookpt;
	v3 scl;
	vector_scale3 (&scl, &camera_direction, .001);
	vector_add3 (&lookpt, &camera_pos, &scl);
	matrix_lookat (view, 	&camera_pos,
							&lookpt,
							&camera_up);
	
	//Setup the perspective matrix
	mat4* proj = malloc (sizeof (mat4));
	matrix_perspective (proj, 3.14 / 4, 1.78, 0.001, 100.0);
	
	for (i = 0; i < 10; i++) {
		
		//Transform matrix
		mat4* a = malloc (sizeof (mat4)); 
		mat4* b = malloc (sizeof (mat4));
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