#ifndef MESH_H
#define MESH_H

#include "buffers_gl.h"
#include "matrix.h"

struct mesh {
	
	char* name;
	
	int num_bones;
	int num_faces;
	int num_vertices;
	
	float* vertex_positions;
	float* vertex_normals;
	float* uv_coords;
	
	unsigned int material;
	
	VBO vbo;
	
};

struct mesh_node {
	
	char* name;
	
	int num_children;
	struct mesh_node* children;
	struct mesh_node* parent;
	
	int num_meshes;
	unsigned int* meshes;
	struct mesh* mesh_data; //Shared across all nodes in a hierarchy
	
	mat4 transform;
	
};

typedef struct mesh mesh;
typedef struct mesh_node mesh_node;

#endif