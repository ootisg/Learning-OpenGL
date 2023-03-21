#ifndef SCENE_H
#define SCENE_H

#include "textures_gl.h"
#include "buffers_gl.h"
#include "matrix.h"

//Material

struct material {
	
	texture* tex_diffuse;
	texture* tex_specular;
	texture* tex_normal;
	
	float shininess;
	
};

typedef struct material material;

//Mesh

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

//Model

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

//Scene

struct scenee {

	int num_objects;
	int num_lights; //TODO
	int num_meshes;
	int num_materials;

	model* objects;
	void* lights; //TODO
	mesh* meshes;
	material* materials;

};

typedef struct scenee scenee;

scenee* import_scene (void* loc, char* path);

#endif