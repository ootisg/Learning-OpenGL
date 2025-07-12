#include "matrix.h"

#include <math.h>
#include <stdio.h>

mat4* matrix_init4 (void* loc, double e11, double e12, double e13, double e14, double e21, double e22, double e23, double e24, double e31, double e32, double e33, double e34, double e41, double e42, double e43, double e44) {
	mat4* m = (mat4*)loc;
	m->elems [0][0] = e11;
	m->elems [0][1] = e12;
	m->elems [0][2] = e13;
	m->elems [0][3] = e14;
	m->elems [1][0] = e21;
	m->elems [1][1] = e22;
	m->elems [1][2] = e23;
	m->elems [1][3] = e24;
	m->elems [2][0] = e31;
	m->elems [2][1] = e32;
	m->elems [2][2] = e33;
	m->elems [2][3] = e34;
	m->elems [3][0] = e41;
	m->elems [3][1] = e42;
	m->elems [3][2] = e43;
	m->elems [3][3] = e44;
	return (mat4*)loc;
}

void matrix_print4 (mat4* m) {
	printf ("[%.6f,%.6f,%.6f,%.6f]\n", m->elems [0][0], m->elems [0][1], m->elems [0][2], m->elems [0][3]);
	printf ("[%.6f,%.6f,%.6f,%.6f]\n", m->elems [1][0], m->elems [1][1], m->elems [1][2], m->elems [1][3]);
	printf ("[%.6f,%.6f,%.6f,%.6f]\n", m->elems [2][0], m->elems [2][1], m->elems [2][2], m->elems [2][3]);
	printf ("[%.6f,%.6f,%.6f,%.6f]\n", m->elems [3][0], m->elems [3][1], m->elems [3][2], m->elems [3][3]);
}

mat4* matrix_iden4 (void* loc) {
	matrix_init4 (loc,	1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_trans4 (void* loc, double x, double y, double z) {
	matrix_init4 (loc,	1, 0, 0, x,
						0, 1, 0, y,
						0, 0, 1, z,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_scalex4 (void* loc, double s) {
	matrix_init4 (loc,	s, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_scaley4 (void* loc, double s) {
	matrix_init4 (loc,	1, 0, 0, 0,
						0, s, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_scalez4 (void* loc, double s) {
	matrix_init4 (loc,	1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, s, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_scale4 (void* loc, double x, double y, double z) {
	matrix_init4 (loc,	x, 0, 0, 0,
						0, y, 0, 0,
						0, 0, z, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_rotx4 (void* loc, double theta) {
	matrix_init4 (loc,	1, 0, 0, 0,
						0, cos (theta), -sin (theta), 0,
						0, sin (theta), cos (theta), 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_roty4 (void* loc, double theta) {
	matrix_init4 (loc,	cos (theta), 0, sin (theta), 0,
						0, 1, 0, 0,
						-sin (theta), 0, cos (theta), 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_rotz4 (void* loc, double theta) {
	matrix_init4 (loc,	cos (theta), -sin (theta), 0, 0,
						sin (theta), cos (theta), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	return (mat4*)loc;
}

mat4* matrix_rotxyz4 (void* loc, double x, double y, double z, int* rot_order) {
	
	if (!rot_order) {
		mat4 rotx, roty, rotz, temp;
		matrix_rotx4 (&rotx, x);
		matrix_roty4 (&roty, y);
		matrix_rotz4 (&rotz, z);
		mat4* res = (mat4*)loc;
		matrix_mul4m (&temp, &rotx, &roty);
		matrix_mul4m (res, &temp, &rotz);
		return res;
	} else {
		int i;
		mat4 rots[3];
		for (i = 0; i < 3; i++) {
			if (rot_order[i] == 0) {
				matrix_rotx4 (&(rots[i]), x);
			} else if (rot_order[i] == 1) {
				matrix_roty4 (&(rots[i]), y);
			} else if (rot_order[i] == 2) {
				matrix_rotz4 (&(rots[i]), z);
			}
		}
		mat4 temp;
		mat4* res = (mat4*)loc;
		matrix_mul4m (&temp, &(rots[0]), &(rots[1]));
		matrix_mul4m (res, &temp, &(rots[2]));
		return res;
	}
	
}

mat4* matrix_rot4 (void* loc, double theta, v3* axis) {
	
	mat4* res = (mat4*)loc;
	v3 u;
	vector_normalize3 (&u, axis);
	matrix_init4 (res,	cos (theta) + u.x * u.x * (1 - cos (theta)),		u.x * u.y * (1 - cos (theta)) - u.z * sin (theta),	u.x * u.z * (1 - cos (theta)) + u.y * sin (theta),	0,
						u.y * u.x * (1 - cos (theta)) + u.z * sin (theta),	cos (theta) + u.y * u.y * (1 - cos (theta)),		u.y * u.z * (1 - cos (theta)) - u.x * sin (theta),	0,
						u.z * u.x * (1 - cos (theta)) - u.y * sin (theta),	u.z * u.y * (1 - cos (theta)) + u.x * sin (theta),	cos (theta) + u.z * u.z * (1 - cos (theta)),		0,
						0,													0,													0,													1);
	return res;
	
}

mat4* matrix_lookat (void* loc, v3* eye, v3* at, v3* up) {
	
	//The internet told me how to do it
	v3 x_axis, y_axis, z_axis, tmp;
	vector_normalize3 (&z_axis, vector_diff3 (&tmp, at, eye));
	vector_normalize3 (&x_axis, vector_cross3 (&tmp, &z_axis, up));
	vector_cross3 (&y_axis, &x_axis, &z_axis);
	
	mat4* res = (mat4*)loc;
	matrix_init4 (res,	x_axis.x, x_axis.y, x_axis.z, -vector_dot3 (&x_axis, eye),
						y_axis.x, y_axis.y, y_axis.z, -vector_dot3 (&y_axis, eye),
						z_axis.x, z_axis.y, z_axis.z, -vector_dot3 (&z_axis, eye),
						0, 0, 0, 1);
	return res;
	
}

mat4* matrix_ortho (void* loc, double fov, double aspect, double near, double far) {
	
	double len = (2 * sin (fov / 2)) / (1 / near);
	double height = (len / aspect);
	double top = height;
	double bottom = -height;
	double left = -len;
	double right = len;
	mat4* m = (mat4*)loc;
	m->elems [0][0] = 2 / (right - left);
	m->elems [0][1] = 0;
	m->elems [0][2] = 0;
	m->elems [0][3] = -((right + left) / (right - left));
	m->elems [1][0] = 0;
	m->elems [1][1] = 2 / (top - bottom);
	m->elems [1][2] = 1;
	m->elems [1][3] = 0;
	m->elems [2][0] = -((top + bottom) / (top - bottom));
	m->elems [2][1] = 0;
	m->elems [2][2] = -2 / (far - near);
	m->elems [2][3] = -((far + near) / (far - near));
	m->elems [3][0] = 0;
	m->elems [3][1] = 0;
	m->elems [3][2] = 0;
	m->elems [3][3] = 1;
	return m;
	
}

mat4* matrix_perspective (void* loc, double fov, double aspect, double near, double far) {
	
	double len = (2 * sin (fov / 2)) / (1 / near);
	double height = (len / aspect);
	double top = height;
	double bottom = -height;
	double left = -len;
	double right = len;
	mat4* m = (mat4*)loc;
	m->elems [0][0] = (2 * near) / (right - left);
	m->elems [0][1] = 0;
	m->elems [0][2] = (right + left) / (right - left);
	m->elems [0][3] = 0;
	m->elems [1][0] = 0;
	m->elems [1][1] = (2 * near) / (top - bottom);
	m->elems [1][2] = (top + bottom) / (top - bottom);
	m->elems [1][3] = 0;
	m->elems [2][0] = 0;
	m->elems [2][1] = 0;
	m->elems [2][2] = (-(far + near) / (far - near));
	m->elems [2][3] = (-(2 * far * near) / (far - near));
	m->elems [3][0] = 0;
	m->elems [3][1] = 0;
	m->elems [3][2] = -1;
	m->elems [3][3] = 0;
	return m;
	
}

mat4* matrix_mul4f (mat4* res, mat4* mat, float f) {
	res->elems [0][0] = mat->elems[0][0] * f;
	res->elems [0][1] = mat->elems[0][1] * f;
	res->elems [0][2] = mat->elems[0][2] * f;
	res->elems [0][3] = mat->elems[0][3] * f;
	res->elems [1][0] = mat->elems[1][0] * f;
	res->elems [1][1] = mat->elems[1][1] * f;
	res->elems [1][2] = mat->elems[1][2] * f;
	res->elems [1][3] = mat->elems[1][3] * f;
	res->elems [2][0] = mat->elems[2][0] * f;
	res->elems [2][1] = mat->elems[2][1] * f;
	res->elems [2][2] = mat->elems[2][2] * f;
	res->elems [2][3] = mat->elems[2][3] * f;
	res->elems [3][0] = mat->elems[3][0] * f;
	res->elems [3][1] = mat->elems[3][1] * f;
	res->elems [3][2] = mat->elems[3][2] * f;
	res->elems [3][3] = mat->elems[3][3] * f;
	return (mat4*)res;
}

mat4* matrix_mul4m (mat4* res, mat4* a, mat4* b) {
	res->elems [0][0] = a->elems [0][0] * b->elems [0][0] + a->elems [0][1] * b->elems [1][0] + a->elems [0][2] * b->elems [2][0] + a->elems [0][3] * b->elems [3][0];
	res->elems [0][1] = a->elems [0][0] * b->elems [0][1] + a->elems [0][1] * b->elems [1][1] + a->elems [0][2] * b->elems [2][1] + a->elems [0][3] * b->elems [3][1];
	res->elems [0][2] = a->elems [0][0] * b->elems [0][2] + a->elems [0][1] * b->elems [1][2] + a->elems [0][2] * b->elems [2][2] + a->elems [0][3] * b->elems [3][2];
	res->elems [0][3] = a->elems [0][0] * b->elems [0][3] + a->elems [0][1] * b->elems [1][3] + a->elems [0][2] * b->elems [2][3] + a->elems [0][3] * b->elems [3][3];
	res->elems [1][0] = a->elems [1][0] * b->elems [0][0] + a->elems [1][1] * b->elems [1][0] + a->elems [1][2] * b->elems [2][0] + a->elems [1][3] * b->elems [3][0];
	res->elems [1][1] = a->elems [1][0] * b->elems [0][1] + a->elems [1][1] * b->elems [1][1] + a->elems [1][2] * b->elems [2][1] + a->elems [1][3] * b->elems [3][1];
	res->elems [1][2] = a->elems [1][0] * b->elems [0][2] + a->elems [1][1] * b->elems [1][2] + a->elems [1][2] * b->elems [2][2] + a->elems [1][3] * b->elems [3][2];
	res->elems [1][3] = a->elems [1][0] * b->elems [0][3] + a->elems [1][1] * b->elems [1][3] + a->elems [1][2] * b->elems [2][3] + a->elems [1][3] * b->elems [3][3];
	res->elems [2][0] = a->elems [2][0] * b->elems [0][0] + a->elems [2][1] * b->elems [1][0] + a->elems [2][2] * b->elems [2][0] + a->elems [2][3] * b->elems [3][0];
	res->elems [2][1] = a->elems [2][0] * b->elems [0][1] + a->elems [2][1] * b->elems [1][1] + a->elems [2][2] * b->elems [2][1] + a->elems [2][3] * b->elems [3][1];
	res->elems [2][2] = a->elems [2][0] * b->elems [0][2] + a->elems [2][1] * b->elems [1][2] + a->elems [2][2] * b->elems [2][2] + a->elems [2][3] * b->elems [3][2];
	res->elems [2][3] = a->elems [2][0] * b->elems [0][3] + a->elems [2][1] * b->elems [1][3] + a->elems [2][2] * b->elems [2][3] + a->elems [2][3] * b->elems [3][3];
	res->elems [3][0] = a->elems [3][0] * b->elems [0][0] + a->elems [3][1] * b->elems [1][0] + a->elems [3][2] * b->elems [2][0] + a->elems [3][3] * b->elems [3][0];
	res->elems [3][1] = a->elems [3][0] * b->elems [0][1] + a->elems [3][1] * b->elems [1][1] + a->elems [3][2] * b->elems [2][1] + a->elems [3][3] * b->elems [3][1];
	res->elems [3][2] = a->elems [3][0] * b->elems [0][2] + a->elems [3][1] * b->elems [1][2] + a->elems [3][2] * b->elems [2][2] + a->elems [3][3] * b->elems [3][2];
	res->elems [3][3] = a->elems [3][0] * b->elems [0][3] + a->elems [3][1] * b->elems [1][3] + a->elems [3][2] * b->elems [2][3] + a->elems [3][3] * b->elems [3][3];
	return (mat4*)res;
}

mat4* matrix_mul4v (v4* res, mat4* m, v4* v) {
	res->x = m->elems [0][0] * v->x + m->elems [0][1] * v->y + m->elems [0][2] * v->z + m->elems [0][3] * v->w;
	res->y = m->elems [1][0] * v->x + m->elems [1][1] * v->y + m->elems [1][2] * v->z + m->elems [1][3] * v->w;
	res->z = m->elems [2][0] * v->x + m->elems [2][1] * v->y + m->elems [2][2] * v->z + m->elems [2][3] * v->w;
	res->w = m->elems [3][0] * v->x + m->elems [3][1] * v->y + m->elems [3][2] * v->z + m->elems [3][3] * v->w;
	return (mat4*)res;
}

mat4* matrix_add4 (mat4* res, mat4* a, mat4* b) {
	res->elems [0][0] = a->elems[0][0] + b->elems[0][0];
	res->elems [0][1] = a->elems[0][1] + b->elems[0][1];
	res->elems [0][2] = a->elems[0][2] + b->elems[0][2];
	res->elems [0][3] = a->elems[0][3] + b->elems[0][3];
	res->elems [1][0] = a->elems[1][0] + b->elems[1][0];
	res->elems [1][1] = a->elems[1][1] + b->elems[1][1];
	res->elems [1][2] = a->elems[1][2] + b->elems[1][2];
	res->elems [1][3] = a->elems[1][3] + b->elems[1][3];
	res->elems [2][0] = a->elems[2][0] + b->elems[2][0];
	res->elems [2][1] = a->elems[2][1] + b->elems[2][1];
	res->elems [2][2] = a->elems[2][2] + b->elems[2][2];
	res->elems [2][3] = a->elems[2][3] + b->elems[2][3];
	res->elems [3][0] = a->elems[3][0] + b->elems[3][0];
	res->elems [3][1] = a->elems[3][1] + b->elems[3][1];
	res->elems [3][2] = a->elems[3][2] + b->elems[3][2];
	res->elems [3][3] = a->elems[3][3] + b->elems[3][3];
	return (mat4*)res;
}

mat4* matrix_diff4 (mat4* res, mat4* a, mat4* b) {
	res->elems [0][0] = a->elems[0][0] - b->elems[0][0];
	res->elems [0][1] = a->elems[0][1] - b->elems[0][1];
	res->elems [0][2] = a->elems[0][2] - b->elems[0][2];
	res->elems [0][3] = a->elems[0][3] - b->elems[0][3];
	res->elems [1][0] = a->elems[1][0] - b->elems[1][0];
	res->elems [1][1] = a->elems[1][1] - b->elems[1][1];
	res->elems [1][2] = a->elems[1][2] - b->elems[1][2];
	res->elems [1][3] = a->elems[1][3] - b->elems[1][3];
	res->elems [2][0] = a->elems[2][0] - b->elems[2][0];
	res->elems [2][1] = a->elems[2][1] - b->elems[2][1];
	res->elems [2][2] = a->elems[2][2] - b->elems[2][2];
	res->elems [2][3] = a->elems[2][3] - b->elems[2][3];
	res->elems [3][0] = a->elems[3][0] - b->elems[3][0];
	res->elems [3][1] = a->elems[3][1] - b->elems[3][1];
	res->elems [3][2] = a->elems[3][2] - b->elems[3][2];
	res->elems [3][3] = a->elems[3][3] - b->elems[3][3];
	return (mat4*)res;
}

//Helper function for matrix_inverse4
float compute_cofactor4 (mat4* mat, int r, int c) {
	float working[3][3];
	int i, j, wr, wc;
	wr = 0;
	wc = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i != r && j != c) {
				working[wr][wc] = mat->elems[i][j];
				wc++;
			}
		}
		wc = 0;
		if (i != r) {
			wr++;
		}
	}
	float det = working[0][0] * working[1][1] * working[2][2] +
				working[0][1] * working[1][2] * working[2][0] +
				working[0][2] * working[1][0] * working[2][1] -
				working[2][0] * working[1][1] * working[0][2] -
				working[2][1] * working[1][2] * working[0][0] -
				working[2][2] * working[1][0] * working[0][1];
	return det;
}

mat4* matrix_transpose4 (mat4* res, mat4* mat) {
	res->elems[0][0] = mat->elems[0][0];
	res->elems[0][1] = mat->elems[1][0];
	res->elems[0][2] = mat->elems[2][0];
	res->elems[0][3] = mat->elems[3][0];
	res->elems[1][0] = mat->elems[0][1];
	res->elems[1][1] = mat->elems[1][1];
	res->elems[1][2] = mat->elems[2][1];
	res->elems[1][3] = mat->elems[3][1];
	res->elems[2][0] = mat->elems[0][2];
	res->elems[2][1] = mat->elems[1][2];
	res->elems[2][2] = mat->elems[2][2];
	res->elems[2][3] = mat->elems[3][2];
	res->elems[3][0] = mat->elems[0][3];
	res->elems[3][1] = mat->elems[1][3];
	res->elems[3][2] = mat->elems[2][3];
	res->elems[3][3] = mat->elems[3][3];
	return res;
}

mat4* matrix_inverse4 (mat4* res, mat4* mat) {
	int i, j;
	mat4 cofactor;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			(&cofactor)->elems[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * compute_cofactor4 (mat, i, j);
		}
	}
	float det = (&cofactor)->elems[0][0] * mat->elems[0][0] + (&cofactor)->elems[0][1] * mat->elems[0][1] + (&cofactor)->elems[0][2] * mat->elems[0][2] + (&cofactor)->elems[0][3] * mat->elems[0][3];
	matrix_transpose4 (res, &cofactor);
	matrix_mul4f (res, res, 1 / det);
	return res;
}

GLfloat* to_gl_matrix4 (GLfloat* loc, mat4* mat) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			loc[i * 4 + j] = mat->elems[j][i];
		}
	}
	return loc;
}