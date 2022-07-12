#ifndef VECTOR_H
#define VECTOR_H

//Define vector structs
struct v1 {
	double x;
};

struct v2 {
	double x;
	double y;
};

struct v3 {
	double x;
	double y;
	double z;
};

struct v4 {
	double x;
	double y;
	double z;
	double w;
};

typedef struct v1 v1;
typedef struct v2 v2;
typedef struct v3 v3;
typedef struct v4 v4;

//Define print functions for vectors
void printv1 (v1* v);
void printv2 (v2* v);
void printv3 (v3* v);
void printv4 (v4* v);

//Define vector init funcs
v1* initv1 (void* loc, double x);
v2* initv2 (void* loc, double x, double y);
v3* initv3 (void* loc, double x, double y, double z);
v4* initv4 (void* loc, double x, double y, double z, double w);

//Define "new vector" funcs
v1* newv1 (double x);
v2* newv2 (double x, double y);
v3* newv3 (double x, double y, double z);
v4* newv4 (double x, double y, double z, double w);

//Vector math funcs
//Normalize
v2* vector_normalize2 (v2* res, v2* v);
v3* vector_normalize3 (v3* res, v3* v);
v4* vector_normalize4 (v4* res, v4* v);

//Scaling
v1* vector_scale1 (v1* res, v1* v, double amt);
v2* vector_scale2 (v2* res, v2* v, double amt);
v3* vector_scale3 (v3* res, v3* v, double amt);
v4* vector_scale4 (v4* res, v4* v, double amt);

//Addition
v1* vector_add1 (v1* res, v1* a, v1* b);
v2* vector_add2 (v2* res, v2* a, v2* b);
v3* vector_add3 (v3* res, v3* a, v3* b);
v4* vector_add4 (v4* res, v4* a, v4* b);

//Subtraction
v1* vector_diff1 (v1* res, v1* a, v1* b);
v2* vector_diff2 (v2* res, v2* a, v2* b);
v3* vector_diff3 (v3* res, v3* a, v3* b);
v4* vector_diff4 (v4* res, v4* a, v4* b);

//Dot product
double vector_dot1 (v1* a, v1* b);
double vector_dot2 (v2* a, v2* b);
double vector_dot3 (v3* a, v3* b);
double vector_dot4 (v4* a, v4* b);

//Cross product
v3* vector_cross3 (v3* res, v3* a, v3* b);
v4* vector_cross4 (v4* res, v4* a, v4* b);

#endif