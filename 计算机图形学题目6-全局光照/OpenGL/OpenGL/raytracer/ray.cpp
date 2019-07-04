#include "ray.h"

Vec3 const Ray::getPoint(float t)
{
	return m_startPos + m_unitDir * t;
}
