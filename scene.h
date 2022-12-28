#ifndef SCENE_H
#define SCENE_H

#include "model.h"

struct scene {

	int num_objects;
	int num_lights; //TODO
	int num_meshes;
	int num_materials;

	model* objects;
	void* lights; //TODO
	mesh* meshes;
	material* materials;

};

typedef struct scene scene;

scene* import_scene (void* loc, struct aiScene* src);

#endif