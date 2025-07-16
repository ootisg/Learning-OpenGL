#include "shaders_gl.h"

#include <stdio.h>
#include <stdlib.h>

const char *default_vertex_shader_src = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
	
const char *default_fragment_shader_src = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

/// A helper function to read the contents of a file
char* read_from_file (const char* filename) {
	FILE* f = fopen (filename, "r");
	int len = 0;
	while (fgetc (f) != EOF) {
		len++;
	}
	fseek (f, SEEK_SET, 0);
	char* contents = malloc (len + 1);
	int i;
	for (i = 0; i < len; i++) {
		contents[i] = fgetc (f);
	}
	contents[i] = 0;
	return contents;
}

GLuint make_program (const char* vertex_shader, const char* geometry_shader, const char* fragment_shader) {
	
	//Make the program to bind the shaders to
	GLuint program = glCreateProgram ();
	
	//Allocate and compile the vertex shader
	int success;
	char err[512];
	GLuint vertex_handle = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertex_handle, 1, &vertex_shader, NULL);
	glCompileShader (vertex_handle);
	glGetShaderiv (vertex_handle, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog (vertex_handle, 512, NULL, err);
		printf ("Error compiling vertex shader: \n%s", err);
	}
	//Allocate and compile the frag shader
	GLuint fragment_handle = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragment_handle, 1, &fragment_shader, NULL);
	glCompileShader (fragment_handle);
	glGetShaderiv (fragment_handle, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog (fragment_handle, 512, NULL, err);
		printf ("Error compiling fragment shader: \n%s", err);
	}
	
	//Allocate and compile the geometry shader (if applicable), then attach it to the program
	GLuint geometry_handle;
	if (geometry_shader) {
		geometry_handle = glCreateShader (GL_GEOMETRY_SHADER);
		glShaderSource (geometry_handle, 1, &geometry_shader, NULL);
		glCompileShader (geometry_handle);
		glGetShaderiv (geometry_handle, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog (geometry_handle, 512, NULL, err);
			printf ("Error compiling geometry shader: \n%s", err);
		}
		glAttachShader (program, geometry_handle);
	}
	
	//Attach the vertex/frag shaders then link the program
	glAttachShader (program, vertex_handle);
	glAttachShader (program, fragment_handle);
	glLinkProgram (program);
	glGetProgramiv (program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog (program, 512, NULL, err);
		printf ("Error linking shaders: \n%s", err);
	}
	
	//Delete the shader objects
	glDeleteShader (vertex_handle);
	glDeleteShader (fragment_handle);
	if (geometry_shader) {
		glDeleteShader (geometry_handle);
	}
	
	//Return the program handle
	return program;
	
}

GLuint make_program_from_files (const char* vertex_shader, const char* geometry_shader, const char* fragment_shader) {
	char* vertex_src = read_from_file (vertex_shader);
	char* fragment_src = read_from_file ((const char*)fragment_shader);
	GLuint program;
	if (geometry_shader == NULL) {
		program = make_program ((const char*)vertex_src, NULL, fragment_src);
	} else {
		char* geometry_src = read_from_file (geometry_shader);
		program = make_program ((const char*)vertex_src, geometry_src, fragment_src);
		free (geometry_src);
	}
	free (vertex_src);
	free (fragment_src);
	return program;
}

GLuint get_default_shader_program () {
	return make_program (default_vertex_shader_src, NULL, default_fragment_shader_src);
}