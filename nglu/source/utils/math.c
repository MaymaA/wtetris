#include "utils/math.h"
#include <stdio.h>
#include <string.h>

void vecAdd(float* vec4_A, float* vec4_B, float* vec4_result){

	float vec_tmp[4];

	short i;
	for (i = 0; i < 4; ++i){
		vec_tmp[i] = vec4_A[i] + vec4_B[i];
	}

	memcpy(vec4_result, vec_tmp, sizeof(vec_tmp));
}

void vecMul(float* vec4_A, float sclr){

	short i;
	for (i = 0; i < 4; ++i){
		vec4_A[i] = vec4_A[i] * sclr;
	}

}

float vecDot(float* vec4_A, float* vec4_B){

	float sclr = 0;

	int i;
	for (i = 0; i < 4; ++i){
		sclr += vec4_A[i] * vec4_B[i];
	}

	return sclr;
}




void matPrint(float* mat4){

	printf("---------------------\n");

	float vec[4];
	short i;
	for (i = 0; i < 4; ++i){
		matRow(mat4, i, vec);
		printf("%0.1f, %0.1f, %0.1f, %0.1f\n",
			vec[0], vec[1], vec[2], vec[3]);
	}

	printf("---------------------\n");
}


void matZero(float* mat4){

	memset(mat4, 0, sizeof(float) * 16);
}


void matScale(float* mat4, float scale){

	*mat4 = scale;
	*(mat4 += 5) = scale;
	*(mat4 += 5) = scale;

}

void matIdent(float* mat4){

	matZero(mat4);
	matScale(mat4, 1);
	mat4[15] = 1;

}

void matRow(float* mat4, short row, float* vec4){

	short i;
	for (i = 0; i < 4; ++i){
		vec4[i] = mat4[row + 4 * i];
	}

}

void matRowSet(float* mat4, short row, float* vec4){

	short i;
	for (i = 0; i < 4; ++i){
		mat4[row + 4 * i] = vec4[i];
	}

}

void matMul(float* mat4_A, float* mat4_B, float* mat4_result){

	float mat_tmp[16];

	float vec_row[4];
	float vec_row_new[4];

	short i, j;
	for (i = 0; i < 4; ++i){

		matRow(mat4_A, i, vec_row);

		for (j = 0; j < 4; ++j){

			vec_row_new[j] = vecDot(vec_row, &mat4_B[4 * j]);

		}

		matRowSet(mat_tmp, i, vec_row_new);

	}
	
	memcpy(mat4_result, mat_tmp, sizeof(float) * 16);

}

void matMulVec(float* mat4, float* vec4, float* vec4_result){

	float vec_tmp[4];
	float vec_row[4];

	short i;
	for (i = 0; i < 4; ++i){
		matRow(mat4, i, vec_row);
		vec_tmp[i] = vecDot(vec_row, vec4);
	}
	
	memcpy(vec4_result, vec_tmp, sizeof(vec_tmp));
}

void matTranspose(float* mat4){

	float mat_tmp[16];

	short i;
	for (i = 0; i < 4; ++i){
		matRowSet(mat_tmp, i, &mat4[i * 4]);
	}

	memcpy(mat4, mat_tmp, sizeof(mat_tmp));
}

void matRot(float* mat4, float angle_rad, short axis){

	matIdent(mat4);

	float* X = &mat4[0];
	float* Y = &mat4[4];
	float* Z = &mat4[8];

	float cs = cos(angle_rad);
	float sn = sin(angle_rad);

	switch (axis){
		case 0:
			Y[1] = cs;
			Y[2] = sn;
			Z[1] = -sn;
			Z[2] = cs;
			break;
		case 1:
			X[0] = cs;
			X[2] = -sn;
			Z[0] = sn;
			Z[2] = cs;
			break;
		case 2:
			X[0] = cs;
			X[1] = sn;
			Y[0] = -sn;
			Y[1] = cs;
			break;
	}

}


void matOrtho(float* m,
		float left,
		float right,
		float bottom,
		float top,
		float near,
		float far){

	matZero(m);
	m[0] = 2.f / (right - left);
	m[5] = 2.f / (top - bottom);
	m[10] = -2.f / (far - near);
	m[12] = -(right + left) / (right - left);
	m[13] = -(top + bottom) / (top - bottom);
	m[14] = -(far + near) / (far - near);
	m[15] = 1;
	
	//matIdent(m);
	//matScale(m, 0.02);
	//m[5] *= 640.f/480;
	//m[10] = 0;
}


void matProjection(float* m, float fov, float aspect, float znear, float zfar){

	matZero(m);

	float xymax = znear * tan(fov * 3.1415f/360);
	float ymin = -xymax;
	float xmin = -xymax;

	float width = xymax - xmin;
	float height = xymax - ymin;

	float depth = zfar - znear;
	float q = -(zfar + znear) / depth;
	float qn = -2 * (zfar * znear) / depth;

	float w = 2 * znear / width;
	w = w / aspect;
	float h = 2 * znear / height;

	m[0]  = w;

	m[5]  = h;

	m[10] = q;
	m[11] = -1;

	m[14] = qn;
}

int floatToInt(float n){

	return n >= 0 ? (int)(n + 0.5) : (int)(n - 0.5);
}
