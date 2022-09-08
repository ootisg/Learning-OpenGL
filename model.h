#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "material.h"

struct model {
	
	mesh_node* root_node;
	
	int num_meshes;
	int num_materials;
	int num_animations; //TODO
	
	mesh** meshes;
	material** materials;
	void** animations; //TODO
	
};

typedef struct model model;

#endif