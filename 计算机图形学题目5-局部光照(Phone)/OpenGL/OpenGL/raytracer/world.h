
#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>
#include "../maths/vec3.h"

class Vec3;
class Object;
class Light;
class Ray;
class Colour;

/*====================================================================
World
提供场景的计算（光线跟踪，基于物理原理的光计算等）
====================================================================*/
class World
{
public:
	World();
	~World();

	//通过光线跟踪获得射线ray的颜色
	//若ray的起点是摄像机，那么ray所穿过的像素颜色就是colour_out
	void getColourForRay(const Ray& ray, Colour& colour_out,int traceNum);
	

	//加入一个物体
	void insertObject(Object* ob);

	//加入一个光源
	void insertLight(Light* light);

	//返回跟踪次数
	int getTraceNum(){return m_traceNum;}

	//设置跟踪次数
	void setTraceNum(int traceNum);

	//清除所有物体和光源
	void clear();


private:

	//返回与ray相交的最近的Object,并将ray起点与交点的距离存入dist；若没有Object与ray相交，返回NULL,dist为负数
	Object* closestObject(const Ray& ray,float& dist);

	std::vector<Object*> m_objects;//物体

	std::vector<Light*> m_lights;//光源

	int m_traceNum;//跟踪次数
};


#endif //__WORLD_H__