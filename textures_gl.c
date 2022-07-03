#include "textures_gl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture* texture_table[16]; //TODO update to query max texture units

void textures_init () {
	
	//Initialize the texture table
	int i;
	for (i = 0; i < 16; i++) { //TODO update to query max texture units
		texture_table[i] = NULL;
	}
	
	//Configure stbi_image.h
	stbi_set_flip_vertically_on_load (1);
	
}

texture* texture_load_from_file (void* loc, char* file_path) {
	
	//Cast to texture
	texture* tex = (texture*)loc; 
	
	//Load the image from the given filepath
	tex->img_data = stbi_load (file_path, &(tex->img_width), &(tex->img_height), &(tex->num_channels), 4);
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
					GL_RGBA,
					tex->img_width,
					tex->img_height,
					0,
					GL_RGBA,
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

int texture_enable (texture* tex) {
	int i;
	for (i = 0; i < 16; i++) { //TODO magic number
		if (texture_table[i] == NULL) {
			glActiveTexture (GL_TEXTURE0 + i);
			glBindTexture (GL_TEXTURE_2D, tex->texture_id);
			tex->texture_unit_idx = i;
			texture_table[i] = tex;
			return 1;
		}
	}
	return 0;
}

int texture_disable (texture* tex) {
	texture_table[tex->texture_unit_idx] = NULL;
	tex->texture_unit_idx = -1;
}

void free_texture_data (texture* tex) {
	stbi_image_free (tex->img_data);
}