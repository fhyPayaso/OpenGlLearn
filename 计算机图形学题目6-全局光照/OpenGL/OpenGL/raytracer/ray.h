
#ifndef __RAY_H_666_
#define __RAY_H_666_



#include "../maths/vec3.h"

/*=====================================================================
射线
=====================================================================*/
class Ray
{
public:
	//构造函数
	Ray(const Vec3& m_startPos_, const Vec3& unitdir_)
	:	m_startPos(m_startPos_),
		m_unitDir(unitdir_)
	{}

	~Ray(){}

	Vec3 m_startPos;//起点
	Vec3 m_unitDir;//单位方向向量

	const Vec3 getPoint(float t);
};


#endif //__RAY_H_666_