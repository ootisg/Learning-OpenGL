#include "model.h"
#include "scene.h"

#include <stdlib.h>

model* init_model (void* loc, void* parent_scene, struct aiNode* src_node, struct aiScene* src_scene) {
	
	model* curr_model = (model*)loc;
	
	curr_model->num_meshes = ((scene*)parent_scene)->num_meshes;
	curr_model->num_materials = ((scene*)parent_scene)->num_materials;
	
	curr_model->meshes = malloc (sizeof (mesh**) * curr_model->num_meshes);
	curr_model->materials = malloc (sizeof (material**) * curr_model->num_materials);
	
	int i;
	for (i = 0; i < curr_model->num_meshes; i++) {
		curr_model->meshes[i] = &(((scene*)parent_scene)->meshes[i]);
	}
	for (i = 0; i < curr_model->num_materials; i++) {
		curr_model->materials[i] = &(((scene*)parent_scene)->materials[i]);
	}
	
	curr_model->root_node = init_mesh_node (malloc (sizeof (mesh_node)), src_scene->mRootNode, NULL, curr_model);
	
	return curr_model;
	
}