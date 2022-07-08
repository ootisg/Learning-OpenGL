#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void printv1 (v1* v) {
	printf ("[%f]", v->x);
}

void printv2 (v2* v) {
	printf ("[%f, %f]", v->x, v->y);
}

void printv3 (v3* v) {
	printf ("[%f, %f, %f]", v->x, v->y, v->z);
}

void printv4 (v4* v) {
	printf ("[%f, %f, %f, %f]", v->x, v->y, v->z, v->w);
}

v1* initv1 (void* loc, double x) {
	v1* v = (v1*)loc;
	v->x = x;
	return v;
}

v2* initv2 (void* loc, double x, double y) {
	v2* v = (v2*)loc;
	v->x = x;
	v->y = y;
	return v;
}

v3* initv3 (void* loc, double x, double y, double z) {
	v3* v = (v3*)loc;
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

v4* initv4 (void* loc, double x, double y, double z, double w) {
	v4* v = (v4*)loc;
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
	return v;
}

v1* newv1 (double x) {
	return initv1 (malloc (sizeof (v1)), x);
}

v2* newv2 (double x, double y) {
	return initv2 (malloc (sizeof (v2)), x, y);
}

v3* newv3 (double x, double y, double z) {
	return initv3 (malloc (sizeof (v3)), x, y, z);
}

v4* newv4 (double x, double y, double z, double w) {
	return initv4 (malloc (sizeof (v4)), x, y, z, w);
}

v1* vector_scale1 (v1* res, v1* v, double amt) {
	res->x = v->x * amt;
	return res;
}

v2* vector_scale2 (v2* res, v2* v, double amt) {
	res->x = v->x * amt;
	res->y = v->y * amt;
	return res;
}

v3* vector_scale3 (v3* res, v3* v, double amt) {
	res->x = v->x * amt;
	res->y = v->y * amt;
	res->z = v->z * amt;
	return res;
}

v4* vector_scale4 (v4* res, v4* v, double amt) {
	res->x = v->x * amt;
	res->y = v->y * amt;
	res->z = v->z * amt;
	res->w = v->w * amt;
	return res;
}

//Addition
v1* vector_add1 (v1* res, v1* a, v1* b) {
	res->x = a->x + b->x;
	return res;
}

v2* vector_add2 (v2* res, v2* a, v2* b) {
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	return res;
}

v3* vector_add3 (v3* res, v3* a, v3* b) {
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return res;
}

v4* vector_add4 (v4* res, v4* a, v4* b) {
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	res->w = a->w + b->w;
}

//Subtraction
v1* vector_diff1 (v1* res, v1* a, v1* b) {
	res->x = a->x - b->x;
	return res;
}

v2* vector_diff2 (v2* res, v2* a, v2* b) {
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	return res;
}

v3* vector_diff3 (v3* res, v3* a, v3* b) {
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return res;
}

v4* vector_diff4 (v4* res, v4* a, v4* b) {
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	res->w = a->w - b->w;
}

//Dot product
double vector_dot1 (v1* a, v1* b) {
	return a->x * b->x;
}

double vector_dot2 (v2* a, v2* b) {
	return a->x * b->x + a->y * b->y;
}

double vector_dot3 (v3* a, v3* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

double vector_dot4 (v4* a, v4* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

//Cross product
v3* vector_cross3 (v3* res, v3* a, v3* b) {
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	return res;
}

v4* vector_cross4 (v4* res, v4* a, v4* b) {
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	res->w = a->w;
	return res;
}