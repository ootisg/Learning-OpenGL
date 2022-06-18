#include "shaders_gl.h"

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

GLuint make_program (const char* vertex_shader, const char* geometry_shader, const char* fragment_shader) {
	
	//Make the program to bind the shaders to
	GLuint program = glCreateProgram ();
	
	//Allocate and compile the vertex/frag shaders
	GLuint vertex_handle = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertex_handle, 1, &vertex_shader, NULL);
	glCompileShader (vertex_handle);
	GLuint fragment_handle = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragment_handle, 1, &fragment_shader, NULL);
	glCompileShader (fragment_handle);
	
	//Allocate and compile the geometry shader (if applicable), then attach it to the program
	GLuint geometry_handle;
	if (geometry_shader) {
		geometry_handle = glCreateShader (GL_GEOMETRY_SHADER);
		glShaderSource (geometry_handle, 1, &geometry_shader, NULL);
		glCompileShader (geometry_handle);
		glAttachShader (program, geometry_handle);
	}
	
	//Attach the vertex/frag shaders then link the program
	glAttachShader (program, vertex_handle);
	glAttachShader (program, fragment_handle);
	glLinkProgram (program);
	
	//Delete the shader objects
	glDeleteShader (vertex_handle);
	glDeleteShader (fragment_handle);
	if (geometry_shader) {
		glDeleteShader (geometry_handle);
	}
	
	//Return the program handle
	return program;
	
}

GLuint get_default_shader_program () {
	return make_program (default_vertex_shader_src, NULL, default_fragment_shader_src);
}