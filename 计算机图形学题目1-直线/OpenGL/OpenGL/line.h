
#ifndef LINE_H
#define LINE_H

//DDA算法绘制直线
//(xa,ya),起点像素坐标
//(xb,yb),终点像素坐标
//setPixel,像素处理函数
void DDA(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y));

//Bresenham算法绘制直线
//参数同DDA
void Bres(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y));

#endif