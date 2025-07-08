#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <glad/glad.h>

struct mat4 {
	double elems[4][4];
};

typedef struct mat4 mat4;

mat4* matrix_init4 (void* loc, double e11, double e12, double e13, double e14, double e21, double e22, double e23, double e24, double e31, double e32, double e33, double e34, double e41, double e42, double e43, double e44);
void matrix_print4 (mat4* m);
mat4* matrix_iden4 (void* loc);
mat4* matrix_trans4 (void* loc, double x, double y, double z);
mat4* matrix_scalex4 (void* loc, double s);
mat4* matrix_scaley4 (void* loc, double s);
mat4* matrix_scalez4 (void* loc, double s);
mat4* matrix_scale4 (void* loc, double x, double y, double z);
mat4* matrix_rotx4 (void* loc, double theta);
mat4* matrix_roty4 (void* loc, double theta);
mat4* matrix_rotz4 (void* loc, double theta);
mat4* matrix_rotxyz4 (void* loc, double x, double y, double z, int* rot_order);
mat4* matrix_rot4 (void* loc, double theta, v3* axis);
mat4* matrix_lookat (void* loc, v3* eye, v3* at, v3* up);
mat4* matrix_perspective (void* loc, double fov, double aspect, double near, double far);
mat4* matrix_ortho (void* loc, double fov, double aspect, double near, double far);
mat4* matrix_mul4m (mat4* res, mat4* a, mat4* b);
mat4* matrix_mul4v (v4* res, mat4* m, v4* v);
mat4* matrix_add4 (mat4* res, mat4* a, mat4* b);
mat4* matrix_diff4 (mat4* res, mat4* a, mat4* b);
mat4* matrix_inverse4 (mat4* res, mat4* mat);
GLfloat* to_gl_matrix4 (GLfloat* loc, mat4* mat);

#endif