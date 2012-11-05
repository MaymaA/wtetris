#ifndef NGLU_MATH
#define NGLU_MATH

#include <math.h>

void vecAdd(float* vec4_A, float* vec4_B, float* vec4_result);

void vecMul(float* vec4_A, float sclr);

float vecDot(float* vec4_A, float* vec4_B);

void matPrint(float* mat4);

void matZero(float* mat4);

void matScale(float* mat4, float scale);

void matIdent(float* mat4);

void matRow(float* mat4, short row, float* vec4);

void matRowSet(float* mat4, short row, float* vec4);

void matMul(float* mat4_A, float* mat4_B, float* mat4_result);

void matMulVec(float* mat4, float* vec4, float* vec4_result);

void matTranspose(float* mat4);

void matRot(float* mat4, float angle_rad, short axis);

void matOrtho(float* m,
		float left,
		float right,
		float bottom,
		float top,
		float near,
		float far);

void matProjection(float *m, float fov, float aspect, float znear, float zfar);

int floatToInt(float n);

#endif
