#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "transformation.h"
#include "common.h"
#include "line.h"

#define defSCREEN_WIDTH 700								
#define defSCREEN_HEIGHT 700								

//屏幕像素数组
GLubyte g_abyScreenImage[defSCREEN_HEIGHT][defSCREEN_WIDTH][3];

#define PI 3.1415926

//颜色
struct RGB{
	RGB(GLubyte nr=255,GLubyte ng=255,GLubyte nb=255):r(nr),g(ng),b(nb){}
	GLubyte r,g,b;
};
typedef RGB COLOR;

COLOR g_color=RGB(255,255,255);

float g_vertex[8][3]={{-50,-50,50},{50,-50,50},{50,50,50},{-50,50,50},{50,-50,-50},{50,50,-50},{-50,50,-50},{-50,-50,-50}};//六面体顶点
float g_pvertex[8][3];//变换后的六面体顶点
float Txyz[4][4],Rxyz[4][4],Sxyz[4][4],ComT[4][4]; //平移,旋转,缩放矩阵 



//自定义函数---------------------------------------------------------------------------

//单位矩阵
void SetIdentity(float m[4][4])
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			m[i][j]=(i==j?1:0);
}

//顶点变换
void VerTransfer(float pv[][3],float v[][3],int n,float m[4][4])
{
	static float tpv[4],tv[4];

	for(int i=0;i<n;i++){
		tv[0]=v[i][0];
		tv[1]=v[i][1];
		tv[2]=v[i][2];
		tv[3]=1;
		MVMul(tpv,m,tv);
		pv[i][0]=tpv[0];
		pv[i][1]=tpv[1];
		pv[i][2]=tpv[2];
	}

}

//-------------------------------------------------------------------------------------

//初始化
void MyInit()
{
	int i;
	float r[4][4];

	SetIdentity(Txyz);
	SetIdentity(Rxyz);
	SetIdentity(Sxyz);
	SetIdentity(ComT);
	SetIdentity(r);

	matTxyz(Txyz,0,0,0);
	matSxyz(Sxyz,1,1,1);

	matRx(r,PI/6);//绕x轴旋转30°
	MatMul(Rxyz,r,Rxyz);
	matRy(r,PI/6);//绕y轴旋转30°
	MatMul(Rxyz,r,Rxyz);
	matRz(r,PI/6);//绕z轴旋转30°
	MatMul(Rxyz,r,Rxyz);

	//求复合变换矩阵
	MatMul(ComT,Rxyz,ComT);
	MatMul(ComT,Sxyz,ComT);
	MatMul(ComT,Txyz,ComT);

	for(i=0;i<8;i++)
	{
		g_pvertex[i][0]=g_vertex[i][0];
		g_pvertex[i][1]=g_vertex[i][1];
		g_pvertex[i][2]=g_vertex[i][2];
	}
	VerTransfer(g_pvertex,g_vertex,8,ComT);

}

//像素处理
inline void SetPixel(int x,int y)
{
	if(0<=x&&x<defSCREEN_WIDTH&&0<=y&&y<defSCREEN_HEIGHT){
		g_abyScreenImage[y][x][0]=g_color.r;
		g_abyScreenImage[y][x][1]=g_color.g;
		g_abyScreenImage[y][x][2]=g_color.b;
	}
}
inline void SetColor(GLubyte r,GLubyte g,GLubyte b)
{
	g_color.r=r;
	g_color.g=g;
	g_color.b=b;
}

//绘制
void Draw(float v[][3])
{
	int i;
	static int halWidth=defSCREEN_WIDTH/2,halHeight=defSCREEN_HEIGHT/2;
	static int index[12][2]={{0,1},{1,2},{2,3},{3,0},   {4,5},{5,6},{6,7},{7,4},    {1,4},{2,5},    {3,6},{0,7}};
	static int sx,sy,ex,ey;

	SetColor(100,100,100);
	//x轴
	DDA(20,halHeight,defSCREEN_WIDTH-20,halHeight,SetPixel);
	DDA(defSCREEN_WIDTH-20,halHeight,defSCREEN_WIDTH-40,halHeight+20,SetPixel);
	DDA(defSCREEN_WIDTH-20,halHeight,defSCREEN_WIDTH-40,halHeight-20,SetPixel);

	//y轴
	DDA(halWidth,20,halWidth,defSCREEN_HEIGHT-20,SetPixel);
	DDA(halWidth,defSCREEN_HEIGHT-20,halWidth-20,defSCREEN_HEIGHT-40,SetPixel);
	DDA(halWidth,defSCREEN_HEIGHT-20,halWidth+20,defSCREEN_HEIGHT-40,SetPixel);

	//轴
	DDA(halWidth,halHeight,halWidth+300,halHeight+300,SetPixel);

	//六面体
	for(i=0;i<12;i++)
	{
		if(i<4)SetColor(255,0,0);
		else SetColor(255,255,255);
		sx=ROUND(g_pvertex[index[i][0]][0])+halWidth;
		sy=ROUND(g_pvertex[index[i][0]][1])+halHeight;
		ex=ROUND(g_pvertex[index[i][1]][0])+halWidth;
		ey=ROUND(g_pvertex[index[i][1]][1])+halHeight;
		DDA(sx,sy,ex,ey,SetPixel);
	}

}

//初始化屏幕像素数组为全黑
void InitScreenImage()
{
	int iHeight,iWidth;
	int iColorRed,iColorGreen,iColorBlue;
	for(iHeight=0;iHeight<defSCREEN_HEIGHT;iHeight++){
		for(iWidth=0;iWidth<defSCREEN_WIDTH;iWidth++){
			iColorRed=0;
			iColorGreen=0;
			iColorBlue=0;
			g_abyScreenImage[iHeight][iWidth][0]=(GLubyte)iColorRed;
			g_abyScreenImage[iHeight][iWidth][1]=(GLubyte)iColorGreen;
			g_abyScreenImage[iHeight][iWidth][2]=(GLubyte)iColorBlue;
		}
	}
}

//改变屏幕像素数组
void ModifyScreenImage()
{
	Draw(g_pvertex);
}

//响应键盘按键
void Keyboard(unsigned char uchKey, int iXPos, int iYPos)
{
	static float t[4][4];
	SetIdentity(t);
	if(uchKey == 27) {
		exit(0);
	}
	switch(uchKey){
		//平移
		case 'd':
		case 'D'://x增大
			matTxyz(t,4,0,0);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'a':
		case 'A'://x减小
			matTxyz(t,-4,0,0);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'w':
		case 'W'://y增大
			matTxyz(t,0,4,0);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 's':
		case 'S'://y减小
			matTxyz(t,0,-4,0);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'q':
		case 'Q'://z增大
			matTxyz(t,0,0,4);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'e':
		case 'E'://z减小
			matTxyz(t,0,0,-4);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;

		//缩放
		case 'z':
		case 'Z'://放大
			matSxyz(t,1.05,1.05,1.05);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'x':
		case 'X'://缩小
			matSxyz(t,0.95,0.95,0.95);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;

		//旋转
		case 'l':
		case 'L'://绕x轴
			matRx(t,0.1);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'i':
		case 'I'://绕y轴
			matRy(t,0.1);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'j':
		case 'J'://绕z轴
			matRz(t,0.1);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
		case 'k':
		case 'K'://绕指定轴
			matR(t,0.1,1,1,0);
			MatMul(ComT,t,ComT);
			VerTransfer(g_pvertex,g_pvertex,8,t);
			break;
	}
	glutPostRedisplay();
}

//响应特殊按键
void Special(int iKey, int iXPos, int iYPos)
{
	
}

//响应鼠标按键
void Mouse(int iButton,int iState,int iXPos, int iYPos)
{
	
}

//响应按下一个鼠标按钮移动鼠标
void Motion(int iXPos, int iYPos)
{
	
}

void Reshape(int iWidth, int iHeight)
{
	glutReshapeWindow(defSCREEN_WIDTH,defSCREEN_HEIGHT);
}

//初始化
void Init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	InitScreenImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

//绘制回调函数
void Display() 
{	
	glClear(GL_COLOR_BUFFER_BIT);
	InitScreenImage();
	ModifyScreenImage();
	glDrawPixels(defSCREEN_WIDTH,defSCREEN_HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,g_abyScreenImage);
	glutSwapBuffers();
}

int main(int argc,char** argv)
{
	MyInit();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(defSCREEN_WIDTH,defSCREEN_HEIGHT);
	glutCreateWindow("矩阵变换: 平移(w,a,s,d,q,e)  旋转(l绕x轴,i绕y轴,j绕z轴,k绕指定轴)  放缩(z,x)");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
	return 0;
}

