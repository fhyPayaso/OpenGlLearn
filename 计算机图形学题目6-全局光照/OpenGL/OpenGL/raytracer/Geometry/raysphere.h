
#ifndef __RAYSPHERE_H__
#define __RAYSPHERE_H__

#include "geometry.h"
#include "../../maths/vec3.h"


/*====================================================================
射线球体
====================================================================*/
class RaySphere : public Geometry
{
public:
	//构造函数
	RaySphere(const Vec3& pos_, float radius_)
	{
		m_centerpos = pos_;
		m_radius = radius_;
		m_radiusSquared = radius_ * radius_;
		m_recipRadius = 1.0f / m_radius;
	}

	~RaySphere(){}

	//返回从射线起点沿射线到达球面的距离，若射线和球体没有交点，返回负值
	//注意，从球体内部射出的射线与球面，被视为没有交点
	virtual float getDistanceUntilHit(const Ray& ray) const;

	//返回球体上pos处的法向量
	virtual const Vec3 getNormalForPos(const Vec3& pos) const;

	//球心
	Vec3 m_centerpos;

private:

	float m_radius;//半径

	float m_radiusSquared;//半径的平方

	float m_recipRadius;//半径的倒数
};





#endif //__RAYSPHERE_H__