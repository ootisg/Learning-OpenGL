#ifndef BUFFERS_GL_H
#define BUFFERS_GL_H

#include <glad/glad.h>

/// @struct VBO
///	@brief The wrapper struct for a VBO
///	@var data the vertex data contained in the VBO (if valid is true)
///	@var len the length (in bytes) of the data stored at the data field
/// @var buffer_id the OpenGL object handle for the buffer
///	@var buffer_type the OpenGL buffer type of the buffer (GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER)
/// @var buffer_hint the hint for this buffer (GL_STATIC_DRAW or GL_DYNAMIC_DRAW)
/// @var valid TRUE iff the data in the OpenGL buffer matches the data field
struct VBO {
	void* data;
	unsigned int len;
	GLuint buffer_id;
	GLuint buffer_type;
	GLuint buffer_hint;
	int valid;
};

typedef struct VBO VBO;

///	Initializes a VBO struct at loc with the given parameters
/// @param loc the pointer to initialize the struct at
/// @param data the data to store in the VBO (uses memcpy)
/// @param data_len the length (in bytes) of the data stored at the data field
/// @param buffer_type the OpenGL buffer type of the buffer (GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER)
/// @return loc cast to VBO*
VBO* VBO_init (void* loc, void* data, int data_len, GLuint buffer_type);

/// Syncs the OpenGL buffer object with this VBO's data with a call to glBufferData.
/// @param vbo the VBO to sync
void sync_VBO (VBO* vbo);

/// Binds the given vbo to the given vao. Does not need to be called if the VBO was initialized while the desired VAO was bound.
/// @param the vbo to bind
/// @param the vao to bind to
void vao_bind_VBO (GLuint vao, VBO* vbo);

/// Frees the data field inside of the VBO struct. Call before freeing the VBO.
/// @param the vbo to free
void free_VBO_data (VBO* vbo);

#endif