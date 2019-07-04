#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

//平移(tx,ty,tz)的矩阵Txyz 
void matTxyz(float Txyz[4][4],float tx,float ty,float tz);

//绕x轴旋转theta角（单位为弧度）的矩阵Rx 
void matRx(float Rx[4][4],float theta);

//绕y轴旋转theta角的矩阵Ry 
void matRy(float Ry[4][4],float theta);

//绕z轴旋转theta角的矩阵Rz 
void matRz(float Rz[4][4],float theta);

//绕指定轴(起点(0,0,0),终点(x,y,z))旋转theta角的矩阵R
void matR(float R[4][4],float theta,float x,float y,float z);

//缩放矩阵Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz);

//单位矩阵
void SetIdentity(float M[4][4]);

//矩阵拷贝,MD=MS
void Copy(float MD[4][4],float MS[4][4]);

//矩阵转置,md=transpose(ms)
void Transpose(float MD[4][4],float MS[4][4]);

//4阶方阵相乘 R=A*B 
void MatMul(float R[4][4],float A[4][4],float B[4][4]);

//4阶方阵与4维向量相乘 PV=Mat*Vector 
void MVMul(float PV[4],float Mat[4][4],float Vector[4]);

#endif