
#include <math.h>
#include "common.h"

#include "line.h"

//DDA算法绘制直线
//(xa,ya),起点像素坐标
//(xb,yb),终点像素坐标
//setPixel,像素处理函数
void DDA(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y))
{

	// 获取差值
	int dx = xb - xa;
	int dy = yb - ya;
	// 选择步长较大的作为阶数
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	double incX = dx * 1.0 / steps;
	double incY = dy * 1.0 / steps;
	double x = xa, y = ya;
	for (int i = 0; i <= steps; i++)
	{
		setPixel(x, y);
		x += incX;
		y += incY;
	}
}

void Bres(int xa, int ya, int xb, int yb, void (*setPixel)(int x, int y))
{
	int dx = xb - xa;
	int dy = yb - ya;
	double k = dy * 1.0 / dx, e = -0.5;
	int x = xa, y = ya;


	bool chooseX = fabs(k) < 1;

	int step = chooseX ? abs(dx) : abs(dy);

	double de = chooseX ? fabs(k) : 1.0 / fabs(k);

	for (int j = 0; j <= step; ++j)
	{
		setPixel(x, y);

		if (chooseX)
			x += dx >= 0 ? 1 : -1;
		else
			y += dy >= 0 ? 1 : -1;

		e += de;
		if (e >= 0)
		{
			if (!chooseX)
				x += dx >= 0 ? 1 : -1;
			else
				y += dy >= 0 ? 1 : -1;
			e -= 1;
		}
	}
}
