#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

// 生成平移(tx,ty,tz)的矩阵Txyz 
void matTxyz(float Txyz[][4],float tx,float ty,float tz);

// 生成绕x轴旋转theta角（单位为弧度）的矩阵Rx 
void matRx(float Rx[4][4],float theta);

// 生成绕y轴旋转theta角的矩阵Ry 
void matRy(float Ry[4][4],float theta);

// 生成绕z轴旋转theta角的矩阵Rz 
void matRz(float Rz[4][4],float theta);

//绕指定轴(起点(0,0,0),终点(x,y,z))旋转theta角的矩阵R
void matR(float R[4][4],float theta,float x,float y,float z);

// 生成缩放矩阵Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz);

// 4阶方阵相乘 R=A*B 
void MatMul(float R[4][4],float A[4][4],float B[4][4]);

// 4阶方阵与4维向量相乘 PV=Mat*Vector 
void MVMul(float PV[],float Mat[][4],float Vector[]);

#endif