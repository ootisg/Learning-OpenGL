#include "scene.h"

#include <stdlib.h>

scene* import_scene (void* loc, struct aiScene* src) {
	
	//Init scene vars
	scene* curr_scene = (scene*)loc;
	curr_scene->num_objects = 1;
	curr_scene->num_meshes = src->mNumMeshes;
	curr_scene->num_materials = src->mNumMaterials;
	curr_scene->objects = malloc (sizeof (model) * curr_scene->num_objects);
	curr_scene->meshes = malloc (sizeof (mesh) * curr_scene->num_meshes);
	curr_scene->materials = malloc (sizeof (model) * curr_scene->num_materials);
	
	//Import all the meshes
	int i;
	for (i = 0; i < curr_scene->num_meshes; i++) {
		init_mesh (&(curr_scene->meshes[i]), src->mMeshes[i]);
	}
	
	//TODO import all the materials
	
	//Init the model
	model* curr_model = &(curr_scene->objects[0]);
	
	//Return the initialized scene
	return curr_scene;
	
}