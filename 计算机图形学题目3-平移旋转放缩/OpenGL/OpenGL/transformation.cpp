#include <math.h>
#include <FLOAT.H>
#include <stdio.h>
#include "transformation.h"
#include "line.h"

//单位矩阵
void resetIdentity(float M[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			M[i][j] = (i == j ? 1 : 0);
}

//平移(tx,ty,tz)的矩阵Txyz 
void matTxyz(float Txyz[4][4], float tx, float ty, float tz)
{
	float vector[4] = { tx, ty, tz, 1 };
	float res[4];
	MVMul(res, Txyz, vector);
	Txyz[0][3] = res[0];
	Txyz[1][3] = res[1];
	Txyz[2][3] = res[2];
}

//绕x轴旋转theta角的矩阵Rx 
void matRx(float Rx[4][4], float theta)
{
	resetIdentity(Rx);
	//theta余弦:cos(theta),正弦:sin(theta)
	Rx[1][1] = cos(theta);
	Rx[1][2] = -sin(theta);
	Rx[2][1] = sin(theta);
	Rx[2][2] = cos(theta);
}

//绕y轴旋转theta角的矩阵Ry 
void matRy(float Ry[4][4], float theta)
{
	resetIdentity(Ry);

	Ry[0][0] = cos(theta);
	Ry[0][2] = sin(theta);
	Ry[2][0] = -sin(theta);
	Ry[2][2] = cos(theta);
}

//绕z轴旋转theta角的矩阵Rz 
void matRz(float Rz[4][4], float theta)
{
	resetIdentity(Rz);
	
	Rz[0][0] = cos(theta);
	Rz[0][1] = -sin(theta);
	Rz[1][0] = sin(theta);
	Rz[1][1] = cos(theta);
}


//绕指定轴(起点(0,0,0),终点(x,y,z))旋转theta角的矩阵R
void matR(float R[4][4], float theta, float x, float y, float z)
{
	//number的平方根:sqrt(number)
	float c = cos(theta), s = sin(theta), onec = 1 - c;
	float len = sqrt(x * x + y * y + z * z);
	if (len <= 0)return;
	float ux = x / len, uy = y / len, uz = z / len;

	resetIdentity(R);

	R[0][0] = ux * ux * onec + c;
	R[0][1] = ux * uy * onec - uz * s;
	R[0][2] = ux * uz * onec + uy * s;
	R[1][0] = uy * ux * onec + uz * s;
	R[1][1] = uy * uy * onec + c;
	R[1][2] = uy * uz * onec - ux * s;
	R[2][0] = uz * ux * onec - uy * s;
	R[2][1] = uz * uy * onec + ux * s;
	R[2][2] = uz * uz * onec + c;
}


//缩放矩阵Sxyz
void matSxyz(float Sxyz[4][4], float sx, float sy, float sz)
{
	float vector[4] = { sx, sy, sz, 1 };
	float res[4];
	MVMul(res, Sxyz, vector);
	Sxyz[0][0] = res[0];
	Sxyz[1][1] = res[1];
	Sxyz[2][2] = res[2];
}

//----------------------------------------------------------------------------------------------------------

// 4阶方阵相乘 R=A*B 
void MatMul(float R[4][4], float A[4][4], float B[4][4])
{
	int i, j, k;
	float TR[4][4];

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			TR[i][j] = 0;
			for (k = 0; k < 4; k++)
				TR[i][j] = TR[i][j] + A[i][k] * B[k][j];
		}
	}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			R[i][j] = TR[i][j];
}

// 4阶方阵与4维向量相乘 PV=Mat*Vector 
void MVMul(float PV[], float Mat[][4], float Vector[])
{
	int i, j;
	for (i = 0; i < 4; i++) {
		PV[i] = 0;
		for (j = 0; j < 4; j++) {
			PV[i] = PV[i] + Mat[i][j] * Vector[j];
		}
	}
}
