#include "scene.h"

#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags
#include <assimp/mesh.h>
#include <assimp/vector3.h>

mesh_node* init_mesh_node (void* loc, struct aiNode* src, struct mesh_node* parent, void* curr_model) {
	
	//Cast the ptr
	mesh_node* curr_node = (mesh_node*)loc;
	
	//Assign non-recursive misc. values
	curr_node->parent = parent;
	curr_node->name = src->mName.data;
	curr_node->num_children = src->mNumChildren;
	curr_node->num_meshes = src->mNumMeshes;
	printf ("a %d\n", src->mNumMeshes);
	printf ("%s\n", src->mName.data);
	matrix_iden4 (&(curr_node->transform)); //TODO import transformation
	
	//Assign meshes
	curr_node->meshes = malloc (sizeof (mesh*) * curr_node->num_meshes);
	int i;
	for (i = 0; i < curr_node->num_meshes; i++) {
		unsigned int curr_mesh_id = src->mMeshes[i];
		mesh* curr_mesh = ((model*)curr_model)->meshes[curr_mesh_id];
		curr_node->meshes[i] = curr_mesh;
	}
	
	//Recursively initialize the children
	curr_node->children = malloc (sizeof (mesh_node) * curr_node->num_children);
	for (i = 0; i < curr_node->num_children; i++) {
		struct aiNode* curr_src_child = src->mChildren[i];
		init_mesh_node (&(curr_node->children[i]), curr_src_child, curr_node, ((model*)curr_model));
	}
	
	//Return the node
	return curr_node;
	
}

mesh* init_mesh (void* loc, struct aiMesh* src) {
	
	//Cast the ptr
	mesh* curr_mesh = (mesh*)loc;
	
	//Assign sizes
	curr_mesh->num_bones = src->mNumBones;
	curr_mesh->num_faces = src->mNumFaces;
	curr_mesh->num_vertices = src->mNumVertices;
	
	//Init vertex data
	curr_mesh->vertex_positions = malloc (sizeof (float) * 3 * curr_mesh->num_vertices);
	curr_mesh->vertex_normals = malloc (sizeof (float) * 3 * curr_mesh->num_vertices);
	curr_mesh->uv_coords = malloc (sizeof (float) * 2 * curr_mesh->num_vertices);
	
	//Fill vertex data
	int i;
	for (i = 0; i < curr_mesh->num_vertices; i++) {
		curr_mesh->vertex_positions[i * 3] = src->mVertices[i].x;
		curr_mesh->vertex_positions[i * 3 + 1] = src->mVertices[i].y;
		curr_mesh->vertex_positions[i * 3 + 2] = src->mVertices[i].z;
		curr_mesh->vertex_normals[i * 3] = src->mNormals[i].x;
		curr_mesh->vertex_normals[i * 3 + 1] = src->mNormals[i].y;
		curr_mesh->vertex_normals[i * 3 + 2] = src->mNormals[i].z;
		/*
		curr_mesh->uv_coords[i * 2] = src->mTextureCoords[0][i].x; //TODO multiple UV components
		curr_mesh->uv_coords[i * 2 + 1] = src->mTextureCoords[0][i].y;*/
	}
	
	//Assign the material
	curr_mesh->used_material = NULL; //TODO assign material properly
	
	//TODO create a VBO for the mesh
	
	//Return the imported mesh
	return curr_mesh;
	
}

model* init_model (void* loc, void* parent_scene, struct aiNode* src_node, struct aiScene* src_scene) {
	
	model* curr_model = (model*)loc;

	curr_model->num_meshes = ((scenee*)parent_scene)->num_meshes;
	curr_model->num_materials = ((scenee*)parent_scene)->num_materials;
	
	curr_model->meshes = malloc (sizeof (mesh**) * curr_model->num_meshes);
	curr_model->materials = malloc (sizeof (material**) * curr_model->num_materials);
	
	int i;
	for (i = 0; i < curr_model->num_meshes; i++) {
		curr_model->meshes[i] = &(((scenee*)parent_scene)->meshes[i]);
	}
	for (i = 0; i < curr_model->num_materials; i++) {
		curr_model->materials[i] = &(((scenee*)parent_scene)->materials[i]);
	}
	
	curr_model->root_node = init_mesh_node (malloc (sizeof (mesh_node)), src_scene->mRootNode, NULL, curr_model);
	
	return curr_model;
	
}

scenee* import_scene (void* loc, char* path) {
	
	// Start the import on the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll t
	// probably to request more postprocessing than we do in this example.
	const struct aiScene* src = aiImportFile (path,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
	aiProcess_GenNormals 			 |
    aiProcess_SortByPType);
	
	// If the import failed, report it
	if (NULL == src) {
		printf ("%s\n", aiGetErrorString());
		return NULL;
	}
	
	//Init scene vars
	scenee* curr_scene = (scenee*)loc;
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
	init_model (curr_model, curr_scene, src->mRootNode, (struct aiScene*)src);
	
	// We're done. Release all resources associated with this import
	aiReleaseImport (src);
	
	//Return the initialized scene
	return curr_scene;
	
}