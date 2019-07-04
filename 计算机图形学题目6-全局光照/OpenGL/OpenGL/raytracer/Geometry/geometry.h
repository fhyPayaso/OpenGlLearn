

#ifndef __GEOMETRY_H_666_
#define __GEOMETRY_H_666_


class Ray;
class Vec3;
class World;
class Colour;

/*=====================================================================
几何体
--------
接口，代表object的形状
=====================================================================*/
class Geometry
{
public:

	virtual ~Geometry(){}


	//返回从射线起点沿射线到达几何体的距离，若射线和几何体没有交点，返回负值
	virtual float getDistanceUntilHit(const Ray& ray) const = 0;

	//返回几何体上pos处的法向量
	virtual const Vec3 getNormalForPos(const Vec3& pos) const = 0;
};



#endif //__GEOMETRY_H_666_




