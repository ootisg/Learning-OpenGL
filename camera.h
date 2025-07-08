#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vector.h"
#include "matrix.h"

/// @struct camera
///	@brief An encapsulation of camera state. Includes parameters relevant to computing a view and a projection matrix.
///	@var view_matrix the view matrix for this camera; do not access directly, instead use camera_get_view_matrix()
/// @var proj_matrix the projection matrix for this camera; do not access directly, instead use camera_get_proj_matrix()
/// @var pos the position of the camera
/// @var dir the view direction of the camera
/// @var up the up vector for the camera's coordinate system; defaults to (0, 1, 0)
///	@var fov the fov (in radians) for this camera
/// @var aspect the aspect ratio (stored as width divided by height) for this camera
/// @var near the distance of the near clipping plane
/// @var far the distance of the far clipping plane
struct camera {
	
	//Matrices
	mat4 view_matrix;
	mat4 proj_matrix;
	
	//View-related state
	v3 pos;
	v3 dir;
	v3 up;
	double pitch;
	double yaw;
	
	//Projection-related state
	double fov;
	double aspect;
	double near;
	double far;
	
};

typedef struct camera camera;

/// Initializes a camera with default parameters at the given location
/// @param loc the location to initialize the camera
/// @return loc cast to a camera*
camera* camera_init (void* loc);

/// Sets the given camera as the active camera (the active camera recieves mouse and keyboard events)
/// @param cam the camera to set as active
void set_active_camera (camera* cam);
/// Gets the currently active camera
/// @return the camera currently set as active
camera* get_active_camera ();

/// Calculates and returns the view matrix associated with the given camera. Also updates cam->view_matrix
/// @param cam the camera whose view matrix to calculate
/// @return the view matrix calculated from cam's view parameters
mat4* camera_get_view_matrix (camera* cam);
/// Calculates and returns the projection matrix associated with the given camera. Also updates cam->proj_matrix
/// @param cam the camera whose projection matrix to calculate
/// @return the projection matrix calculated from the cam's projection parameters
mat4* camera_get_proj_matrix (camera* cam);

/// Active camera callback for mouse motion; mouse movement controls the view direction of the active camera. Function parameters are as specified by GLFW
void camera_mouse_callback (GLFWwindow* window, double xpos, double ypos);
/// Active camera callback for mouse scrolling; mouse scrollign controls the zoom of the active camera by adjusting its FOV. Function parameters are as specified by GLFW
void camera_scroll_callback (GLFWwindow* window, double xoffset, double yoffset);
/// Function to process key inputs for one frame; must be manually called by the user once every frame. Key inputs control the active camera's movement
void camera_process_key_inputs ();
/// Returns non-zero if the flashlight is active
int flashlight_active ();

#endif