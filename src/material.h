#ifndef MATERIAL_H
#define MATERIAL_H

#include "textures_gl.h"

struct material {
	
	texture* tex_diffuse;
	texture* tex_specular;
	texture* tex_normal;
	
	float shininess;
	
};

typedef struct material material;

#endif