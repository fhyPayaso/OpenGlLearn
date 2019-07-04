
#ifndef CIRCLE_H
#define CIRCLE_H

//Bresenham算法绘制直线
//参数同DDA
void Bres(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y));

#endif