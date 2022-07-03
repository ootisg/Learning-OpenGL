#include "textures_gl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture* texture_load_from_file (void* loc, char* file_path) {
	
	//Cast to texture
	texture* tex = (texture*)loc; 
	
	//Load the image from the given filepath
	tex->img_data = stbi_load (file_path, &(tex->img_width), &(tex->img_height), &(tex->num_channels), 3);
	printf ("%d, %d\n", tex->img_width, tex->img_height);
	
	//Allocate and bind the OpenGL texture
	glGenTextures (1, &(tex->texture_id));
	glBindTexture (GL_TEXTURE_2D, tex->texture_id);
	
	//Set default texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//Fill the texture data
	glTexImage2D (	GL_TEXTURE_2D,
					0,
					GL_RGB,
					tex->img_width,
					tex->img_height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					tex->img_data );
					
	//Generate the mipmap for this texture
	glGenerateMipmap (GL_TEXTURE_2D);
	
	//Set other parameters accordingly
	tex->texture_unit_idx = -1;
	tex->img_data_loaded = 1;
	
	//Return the texture struct
	return tex;
	
}

GLuint texture_enable (texture* tex) {
	
}

GLuint texture_disable (texture* tex) {
	
}

void free_texture_data (texture* tex) {
	stbi_image_free (tex->img_data);
}