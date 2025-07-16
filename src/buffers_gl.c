#include "buffers_gl.h"

#include <stdlib.h>
#include <string.h>

VBO* VBO_init (void* loc, void* data, int data_len, GLuint buffer_type) {
	VBO* vbo = (VBO*)loc;
	vbo->data = malloc (data_len);
	memcpy (vbo->data, data, data_len);
	vbo->len = data_len;
	vbo->buffer_type = buffer_type;
	vbo->buffer_hint = GL_STATIC_DRAW;
	glGenBuffers (1, &(vbo->buffer_id));
	sync_VBO (vbo);
	return vbo;
}

void sync_VBO (VBO* vbo) {
	glBindBuffer (vbo->buffer_type, vbo->buffer_id);
	glBufferData (vbo->buffer_type, vbo->len, vbo->data, vbo->buffer_hint);
	vbo->valid = 1;
}

void vao_bind_VBO (GLuint vao, VBO* vbo) {
	glBindVertexArray (vao);
	glBindBuffer (vbo->buffer_type, vbo->buffer_id);
	glBindVertexArray (0); //Can be removed, but doing so may cause buggy behavior
}

void free_VBO_data (VBO* vbo) {
	free (vbo->data);
}