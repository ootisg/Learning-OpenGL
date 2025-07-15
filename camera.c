#include "camera.h"
#include "render_info.h"

#include <stdio.h>
#include <math.h>

camera* active_camera = NULL;

float last_x = 0;
float last_y = 0;
int first_frame = 1;

float last_w_duration = 0;
float last_w_time = 0;
float last_w_press = 0;
int w_down = 0;
int f_down = 0;
int speedup = 0;

int flashlight = 1;

camera* camera_init (void* loc) {
	
	//Cast loc to camera*
	camera* cam = (camera*)loc;
	
	//Initialize the lookat vectors (except dir)
	initv3 (&(cam->pos), 0, 0, 0);
	initv3 (&(cam->up), 0, 1, 0);
	
	//Initialize pitch and yaw for viewing direction
	cam->pitch = 0;
	cam->yaw = 3.14159265 / 2;
	
	//Set the dir vector to match pitch and yaw
	cam->dir.x = cos (cam->yaw) * cos (cam->pitch);
	cam->dir.y = sin (cam->pitch);
	cam->dir.z = sin (cam->yaw) * cos (cam->pitch);
	
	//Initialize projection attributes
	cam->fov = 3.14159265 / 2;
	cam->aspect = 1.78;
	cam->near = .1;
	cam->far = 100;
	
	//Return loc cast to camera*
	return cam;
	
}

void set_active_camera (camera* cam) {
	active_camera = cam;
}

camera* get_active_camera () {
	return active_camera;
}

mat4* camera_get_view_matrix (camera* cam) {
	v3 at;
	vector_add3 (&at, &(cam->pos), &(cam->dir));
	matrix_lookat (&(cam->view_matrix), &(cam->pos), &at, &(cam->up));
	return &(cam->view_matrix);
}

mat4* camera_get_proj_matrix (camera* cam) {
	matrix_perspective (&(cam->proj_matrix), cam->fov, cam->aspect, cam->near, cam->far);
	return &(cam->proj_matrix);
}

int flashlight_active () {
	return flashlight;
}

void camera_bind_mouse_callbacks (GLFWwindow* window) {
	glfwSetCursorPosCallback (window, camera_mouse_callback);
	glfwSetScrollCallback (window, camera_scroll_callback);
}

void camera_mouse_callback (GLFWwindow* window, double xpos, double ypos) {
	
	//Setup mouse x and y correctly to prevent view jumps on frame 1
	if (first_frame) {
		last_x = xpos;
		last_y = ypos;
		first_frame = 0;
	}
	
	//Calculate offests for pitch and yaw
	double sensitivity = 0.001;
	double offs_x = xpos - last_x;
	double offs_y = ypos - last_y;
	last_x = xpos;
	last_y = ypos;
	
	if (active_camera != NULL) {
		
		//Adjust pitch and yaw accordingly
		active_camera->pitch += offs_y * sensitivity;
		active_camera->yaw -= offs_x * sensitivity;
		if (active_camera->pitch > 1.55334) {
			active_camera->pitch = 1.55334; //Clamp to 89 degrees
		}
		if (active_camera->pitch < -1.55334) {
			active_camera->pitch = -1.55334; //Clamp to -89 degrees
		}
		
		//Calculate view direction vector based on current pitch and yaw
		active_camera->dir.x = cos (active_camera->yaw) * cos (active_camera->pitch);
		active_camera->dir.y = sin (active_camera->pitch);
		active_camera->dir.z = sin (active_camera->yaw) * cos (active_camera->pitch);
		
	}
	
}

void camera_scroll_callback (GLFWwindow* window, double xoffset, double yoffset) {
	if (active_camera != NULL) {
		//Adjust the FOV based on the scroll wheel to simulate zoom
		active_camera->fov -= yoffset * .01745 * 5;
		if (active_camera->fov < .01745) {
			active_camera->fov = .01745; //Clamp to 1 degree min
		}
		if (active_camera->fov > 1.57078) {
			active_camera->fov = 1.57078; //Clamp to 90 degrees max
		}
	}
}

void camera_process_key_inputs () {
	
	if (active_camera != NULL) {
		
		//Flashlight
		if (key_down (GLFW_KEY_F)) {
			if (f_down == 0) {
				flashlight = !flashlight;
			}
			f_down = 1;
		} else {
			f_down = 0;
		}
		
		//WASD movement
		v3 scaled;
		float camera_speed = frame_delta_time () * (speedup ? 10 : 2.5);
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
			vector_scale3 (&scaled, &(active_camera->dir), camera_speed);
			vector_diff3 (&(active_camera->pos), &(active_camera->pos), &scaled);
			
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
			vector_scale3 (&scaled, &(active_camera->dir), camera_speed);
			vector_add3 (&(active_camera->pos), &(active_camera->pos), &scaled);
		}
		//Take cross products for left/right strafe
		if (key_down (GLFW_KEY_A)) {
			v3 strafe;
			vector_cross3 (&strafe, &(active_camera->up), &(active_camera->dir));
			vector_scale3 (&scaled, &strafe, camera_speed);
			vector_add3 (&(active_camera->pos), &(active_camera->pos), &scaled);
		}
		if (key_down (GLFW_KEY_D)) {
			v3 strafe;
			vector_cross3 (&strafe, &(active_camera->up), &(active_camera->dir));
			vector_scale3 (&scaled, &strafe, camera_speed);
			vector_diff3 (&(active_camera->pos), &(active_camera->pos), &scaled);
		}
		
		//Space and shift for up and down movement
		if (key_down (GLFW_KEY_SPACE)) {
			vector_scale3 (&scaled, &(active_camera->up), camera_speed);
			vector_add3 (&(active_camera->pos), &(active_camera->pos), &scaled);
		}
		if (key_down (GLFW_KEY_LEFT_SHIFT)) {
			vector_scale3 (&scaled, &(active_camera->up), camera_speed);
			vector_diff3 (&(active_camera->pos), &(active_camera->pos), &scaled);
		}
		
	}
	
}