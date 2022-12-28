#ifndef MESH_H
#define MESH_H

#include "buffers_gl.h"
#include "matrix.h"
#include "material.h"

#include <stdbool.h>
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

struct mesh {
	
	char* name;
	
	int num_bones; //TODO store bones
	int num_faces; //TODO store faces
	int num_vertices;
	
	float* vertex_positions;
	float* vertex_normals;
	float* uv_coords;
	
	material* used_material;
	
	VBO vbo;
	
};

struct mesh_node {
	
	char* name;
	
	int num_children;
	struct mesh_node* children; //Children are stored in-place
	struct mesh_node* parent; //Parent is a reference
	
	int num_meshes;
	struct mesh** meshes; //List of meshes
	
	mat4 transform;
	
};

typedef struct mesh mesh;
typedef struct mesh_node mesh_node;

mesh_node* init_mesh_node (void* loc, struct aiNode* src, struct mesh_node* parent, void* curr_model);
mesh* init_mesh (void* loc, struct aiMesh* src);

#endif