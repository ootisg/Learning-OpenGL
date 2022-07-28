#ifndef RENDER_H
#define RENDER_H

#include "matrix.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct scene { //TODO for now, this just contains a list of VAOs, a list of programs, and a list of model matrices
	int num_objs;
	GLuint* vaos;
	GLuint* programs;
	mat4* models;
};

typedef struct scene scene;

/// Initializes a new scene struct at the given pointer, then returns it.
/// @param loc the location to initialie the struct at
/// @return loc cast to scene*
scene* init_scene (void* loc);

/// Initializes the rendering pipeline for the given scene
/// @param init_scene the scene to initialize
void render_init (scene* init_scene);

/// Renders a frame of the given scene
/// @param render_scene the scene to render
void render_frame (scene* render_scene);

#endif