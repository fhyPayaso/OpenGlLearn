#include "scene.h"
#include <stdlib.h>
#include <math.h>

Scene::Scene(int width,int height):m_iWidth(width),m_iHeight(height)
{
	m_world=new World();
	m_campos=Vec3(0,5,2);
	m_screenBuffer=(unsigned char***)malloc(height*sizeof(unsigned char**));
	for(int i=0;i<height;i++){
		m_screenBuffer[i]=(unsigned char**)malloc(width*sizeof(unsigned char*));
		for(int j=0;j<width;j++)
			m_screenBuffer[i][j]=(unsigned char*)malloc(3*sizeof(unsigned char));
	}
}

Scene::~Scene(void)
{
	shutdown();
}
void Scene::insertObject(Object* ob){
	m_world->insertObject(ob);
}
void Scene::insertLight(Light* light){
	m_world->insertLight(light);
}
void Scene::draw()
{

	//绘制场景
	for(int x=0; x<m_iWidth; ++x)
		for(int y=0; y<m_iHeight; ++y)
		{
			//从摄像机位置开始追踪计算射线
			const Ray ray(m_campos, getUnitDirForImageCoords(x, y));

			Colour colour;
			m_world->getColourForRay(ray, colour,m_world->getTraceNum());

			colour.positiveClipComponents();

			//设置像素
			drawPixel(x, y, colour);
		}
}
void Scene::shutdown()
{
	/*for(int i=0;i<m_iHeight;i++){
		for(int j=0;j<m_iWidth;j++)
			free(m_screenBuffer[i][j]);
		free(m_screenBuffer[i]);
	}
	free(m_screenBuffer);*/
	//delete m_world;
	//m_world = NULL;
	m_world->clear();
}
Vec3 Scene::getUnitDirForImageCoords(int x, int y)
{
	if(x>=0&&x<m_iWidth&&y>=0&&y<m_iHeight){
		float vx=-10+20*((float)x)/m_iWidth-m_campos.x;
		float vy=-10+20*((float)y)/m_iHeight-m_campos.y;
		float vz=-m_campos.z;
		return normalise(Vec3(vx,vy,vz));
	}
	else return Vec3(0,0,-1);
}
void Scene::drawPixel(int x,int y, Colour colour)
{
	m_screenBuffer[y][x][0]= unsigned char(colour.r * 255);
	m_screenBuffer[y][x][1]= unsigned char(colour.g * 255);
	m_screenBuffer[y][x][2]= unsigned char(colour.b * 255);
}
