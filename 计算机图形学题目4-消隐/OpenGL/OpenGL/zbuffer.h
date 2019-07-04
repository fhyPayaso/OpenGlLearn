
#ifndef ZBUFFER_H
#define ZBUFFER_H


// 扫描线填充算法---------------------------------------------------------- 
// 用扫描线算法填充由vertex顶点序列定义的多边形区域 
// 用深度缓存算法消隐 
//n  顶点个数

//void linefill(float vertex[][3],int n);
void linefill(int coord[][2],float depth[],int n);

#endif