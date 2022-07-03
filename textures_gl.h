#ifndef TEXTURES_GL_H
#define TEXTURES_GL_H

#include <GL/glew.h>

/// @struct texture
///	@brief The wrapper struct for an OpenGL texture
///	@var img_data the raw image data of the texture (in RGBA format)
///	@var texture_id the OpenGL object handle for the texture
/// @var texture_unit_idx the texture unit this texture is assigned to; if not assigned to any texture unit, set this to -1
struct texture {
	unsigned char* img_data;
	int img_width;
	int img_height;
	int num_channels;
	GLuint texture_id;
	int texture_unit_idx;
	int img_data_loaded;
};

typedef struct texture texture;

void textures_init ();
texture* texture_load_from_file (void* loc, char* file_path);
int texture_enable (texture* tex);
int texture_disable (texture* tex);
void free_texture_data (texture* tex);

#endif