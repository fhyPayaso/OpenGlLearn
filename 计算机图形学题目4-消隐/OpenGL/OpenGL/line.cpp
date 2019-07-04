
#include <math.h>
#include "common.h"
#include "line.h"

//DDA算法绘制直线
//(xa,ya),起点像素坐标
//(xb,yb),终点像素坐标
//setPixel,像素处理函数
void DDA(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	bool u=false,v=false,w=false;
	int tx,ty;
	int dsx=xb-xa;
	int dsy=yb-ya;
	int dx=dsx,dy=dsy,steps,k;
	float xIncrement,yIncrement,x=0,y=0;

	if(abs(dx)>abs(dy))steps=abs(dx);
	else steps=abs(dy);

	xIncrement=dx/(float)steps;
	yIncrement=dy/(float)steps;

	setPixel(ROUND(xa),ROUND(ya));
	for(k=0;k<steps;k++){
		x+=xIncrement;
		y+=yIncrement;

		tx=ROUND(x);
		ty=ROUND(y);
		tx+=xa;
		ty+=ya;
		setPixel(tx,ty);
	}

}

//Bresenham算法绘制直线
//参数同DDA
void Bres(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	bool u=false,v=false,w=false;
	int tx,ty;
	int dsx=xb-xa;
	int dsy=yb-ya;

	if(dsx<0){
		dsx=-dsx;//dsx取反
		u=true;
	}
	if(dsy<0){
		dsy=-dsy;//dsy取反
		v=true;
	}
	if(dsx<dsy){
		swap(dsx,dsy);//dsx,dsy互换
		w=true;
	}

	int dx=dsx,dy=dsy;
	int p=2*dy-dx;
	int twoDy=2*dy,twoDyDx=2*(dy-dx);
	int x,y,xEnd;

	x=0;
	y=0;
	xEnd=dsx;
	setPixel(xa,ya);

	while(x<xEnd){
		x++;

		if(p<0)
			p+=twoDy;
		else{
			y++;
			p+=twoDyDx;
		}
		tx=ROUND(x);
		ty=ROUND(y);

		if(w)swap(tx,ty);
		if(v)ty=-ty;
		if(u)tx=-tx;

		tx+=xa;
		ty+=ya;
		setPixel(tx,ty);
	}
}