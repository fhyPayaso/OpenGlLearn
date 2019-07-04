#include "common.h"
#include "math.h"
#include "zbuffer.h"
#include <iostream>
using namespace std;

//求扫描线Y=y与边AB的交点的x坐标，如果无交点，返回-1
int linejoin(int A[2],int B[2],int y)
{
	float t;
	if (B[1]==A[1])
		return -1;

	t = (y-A[1]) / float(B[1]-A[1]);
	if (t>=0.0 && t<=1.0){
		return ROUND(A[0] + (B[0]-A[0])*t);
	}else
		return -1;
}

//可能用到的函数
void SetPixel(int x,int y);
float GetDepth(int x,int y);
void SetDepth(int x,int y,float depth);


void getX(int X[2],int y, int coord[][2], int n)
{
	X[0] = 100000, X[1] = -100000;
	for (int i = 0 ;i < n; i++)
	{
		int cur[2], nex[2];
		cur[0] = coord[i][0], cur[1] = coord[i][1];
		nex[0] = coord[(i + 1) % n][0], nex[1] = coord[(i + 1) % n][1];
		int res = linejoin(cur, nex, y);

		if (X[0] >= res && res > 0) X[0] = res;
		if (X[1] <= res && res > 0) X[1] = res;
	}
}
//扫描线填充算法
//coord 像素坐标 ,coord[0],...coord[n-1]依次相连构成一个多边形区域
//depth 像素对应的深度
//n 像素个数
void linefill(int coord[][2],float depth[],int n)
{	
	int miny,maxy;
	int X[10];
	float A[3],B[3],C[3],D[3],E[3],R[3];

	R[2] = 1;

	// 找出y坐标最大和最小的顶点 
	miny=coord[0][1];maxy=coord[0][1];
	for (int i=0;i<n;i++){
		if (coord[i][1]<miny)
			miny=coord[i][1];
		if (coord[i][1]>maxy)
			maxy=coord[i][1];
	}

	// ABC 组成平面 其中A为点，BC为向量
	A[0] = coord[0][0]; 
	A[1] = coord[0][1]; 
	A[2] = depth[0];
	
	B[0] = coord[1][0] - coord[0][0]; 
	B[1] = coord[1][1] - coord[0][1]; 
	B[2] = depth[1] - depth[0];

	C[0] = coord[3][0] - coord[0][0]; 
	C[1] = coord[3][1] - coord[0][1]; 
	C[2] = depth[3] - depth[0];

	E[0] = 0.0; E[1] = 0.0; E[2] = 1.0;	

	// 使扫描线从y坐标最小的递增1到y最大的顶点 
	for (int y=miny;y<=maxy;y++)
	{
		int X[2];
		// 获取扫描线与多边形的相交点
		getX(X, y, coord, n);
		for (int x = X[0]; x <= X[1]; x++)
		{
			D[0] = x; D[1] = y; D[2] = 0;	
			facejoin(R, A, B, C, D, E);
			float oldDepth = GetDepth(x, y);
			float newDepth = R[2];
			// 比较缓存的深度，越小的越靠近观察者
			if (newDepth <= oldDepth)
			{
				SetPixel(x, y);
				SetDepth(x, y, newDepth);
			}
		}
	}
}
