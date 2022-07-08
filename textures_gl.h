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

/// Initializes the texture allocator; must be run before creating any textures
void textures_init ();

/// Loads a texture from the given file and stores it at the given location as a texture struct
/// @param loc the pointer to initialize the struct at
/// @param file_path the image filepath to load
/// @return loc cast to texture*
texture* texture_load_from_file (void* loc, char* file_path);

/// Binds the given texture to an available texture unit and updates tex->texture_unit_idx accordingly
/// @param tex the texture to enable
/// @return non-zero if the texture was successfully allocated; zero otherwise
int texture_enable (texture* tex);

/// Frees the texture unit this texture is bound to
/// @param tex the texture to free
void texture_disable (texture* tex);

/// Frees the image data stored in the given texture struct. Calling this does not affect the texture data stored by OpenGL.
/// @param tex the texture whose image data to free
void free_texture_data (texture* tex);

#endif