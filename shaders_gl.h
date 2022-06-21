#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

/// Allocates an OpenGL program object using the given shader sources and returns its handle
/// @param vertex_shader the source for the vertex shader to use
/// @param geometry_shader the source for the geometry shader to use (may be NULL if not applicable)
/// @param fragment_shader the source for the fragment shader to use
/// @return the handle of the created program object
GLuint make_program (const char* vertex_shader, const char* geometry_shader, const char* fragment_shader);

/// Allocates an OpenGL program object using the shaders located at the given filepaths and returns its handle
/// @param vertex_shader the filepath of the vertex shader to use
/// @param geometry_shader the filepath of the geometry shader to use (may be NULL if not applicable)
/// @param fragment_shader the filepath of the fragment shader to use
/// @return the handle of the created program object
GLuint make_program_from_files (const char* vertex_shader, const char* geometry_shader, const char* fragment_shader);

/// Makes an OpenGL program object with the default vertex and fragment shaders.
/// @return GLuint the handle for the created program object
GLuint get_default_shader_program ();

#endif