
#ifndef __RAYPLANE_H__
#define __RAYPLANE_H__

#include "geometry.h"
#include "../../maths/plane.h"

/*====================================================================
射线平面
====================================================================*/

class RayPlane : public Geometry
{
public:
	//构造函数
	RayPlane(const Plane& plane);

	~RayPlane(){}


	//返回从射线起点沿射线到达平面的距离，若射线和平面没有交点，返回负值
	//注意，这里的平面有方向，射线从平面“背后”穿过平面，被视为没有交点
	//射线包含于平面被视为没有交点
	virtual float getDistanceUntilHit(const Ray& ray) const;

	//返回法相量。因为是平面，不需要考虑pos
	virtual const Vec3 getNormalForPos(const Vec3& pos) const { 
		return m_plane.getNormal(); 
	}


private:
	//平面
	Plane m_plane;
};


#endif //__RAYPLANE_H__