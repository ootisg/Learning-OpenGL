#include "mesh.h"
#include "model.h"

#include <stdlib.h>

mesh_node* init_mesh_node (void* loc, struct aiNode* src, struct mesh_node* parent, void* curr_model) {
	
	//Cast the ptr
	mesh_node* curr_node = (mesh_node*)loc;
	
	//Assign non-recursive misc. values
	curr_node->parent = parent;
	curr_node->name = src->mName.data;
	curr_node->num_children = src->mNumChildren;
	curr_node->num_meshes = src->mNumMeshes;
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
		curr_mesh->uv_coords[i * 2] = src->mTextureCoords[0][i].x; //TODO multiple UV components
		curr_mesh->uv_coords[i * 2 + 1] = src->mTextureCoords[0][i].y;
	}
	
	//Assign the material
	curr_mesh->used_material = NULL; //TODO assign material properly
	
	//TODO create a VBO for the mesh
	
	//Return the imported mesh
	return curr_mesh;
	
}