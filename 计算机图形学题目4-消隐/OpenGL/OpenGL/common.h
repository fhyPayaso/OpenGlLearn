#ifndef COMMON_H
#define COMMON_H

//线条类型
#define SOLID_LINE	0xffff//实线
#define DASH_LINE	0xf8f8//虚线
#define DOT_LINE	0x8888//点线

#define ROUND(a) ((int)(a+0.5))

typedef struct{
	int x,y;
}wcPt2D;

typedef struct{
	float x,y,z;
}wcPt3D;

inline int min(int a,int b)
{
	return a>b?b:a;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}

//两数互换
inline void swap(int& ia,int& ib)
{
	ia=ia^ib;
	ib=ib^ia;
	ia=ia^ib;
}

//数组排序
template<class T>
void sort(T a[],int n)
{
   int i,j,k;
   T temp;
   for (i=0;i<n;i++){
      k=i;
      for (j=i+1;j<n;j++)
         if (a[j]<a[k])
            k=j;
      temp = a[i];
      a[i]=a[k];
      a[k]=temp;
   }
}

//向量点乘
float dot(float A[3],float B[3]);

//向量叉乘.向量的叉积的方向，与两个乘数向量都垂直，也即两个乘数向量决定的平面的法向量
void cross(float R[3],float A[3],float B[3]);

//求平面P(u,w)=A+uB+wC与直线Q(t)=D+tE的交点R 
//注意函数参数的含义
//A是点的坐标; B,C是不平行的非零向量;  u,w∈(-∞,+∞) ;A+uB+wC确定一个平面
//D是点的坐标; E是非零向量; t∈(-∞,+∞); D+tE 确定一条直线
int facejoin(float R[3],float A[3],float B[3],float C[3],float D[3],float E[3]);
#endif