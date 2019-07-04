
#include "common.h"
#include <iostream>
using namespace std;

//向量点乘
float dot(float A[3],float B[3]){
   return(A[0]*B[0]+A[1]*B[1]+A[2]*B[2]);
}

//向量叉乘.向量的叉积的方向，与两个乘数向量都垂直，也即两个乘数向量决定的平面的法向量
void cross(float R[3],float A[3],float B[3]){
   R[0] = A[1]*B[2] - A[2]*B[1];
   R[1] = A[2]*B[0] - A[0]*B[2];
   R[2] = A[0]*B[1] - A[1]*B[0];
}

//求平面P(u,w)=A+uB+wC与直线Q(t)=D+tE的交点R 
//注意函数参数的含义
//A是点的坐标; B,C是不平行的非零向量;  u,w∈(-∞,+∞) ;A+uB+wC确定一个平面
//D是点的坐标; E是非零向量; t∈(-∞,+∞); D+tE 确定一条直线
int facejoin(float R[3],float A[3],float B[3],float C[3],float D[3],float E[3])
{
   float Temp[3],t;

   cross(Temp,B,C);
   
   if (dot(Temp,E)==0)
      return -1;//点积为0,E与平面法相量垂直,即直线与平面平行,无交点(包括直线被平面包含)
   
   t = (dot(Temp,A)-dot(Temp,D)) / dot(Temp,E);
   //cout << t << endl;
   
   R[0] = D[0] + t*E[0];
   R[1] = D[1] + t*E[1];
   R[2] = D[2] + t*E[2];
   return 1;
}
