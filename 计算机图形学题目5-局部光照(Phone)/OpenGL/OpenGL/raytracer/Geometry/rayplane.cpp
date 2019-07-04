

#include "rayplane.h"

#include "../ray.h"



RayPlane::RayPlane(const Plane& plane_)
:	m_plane(plane_)
{
	
}

float RayPlane::getDistanceUntilHit(const Ray& ray) const
{

	float d=dot(m_plane.getNormal(), ray.m_unitDir);
	if(d>=0)
		return -666.0f;
	else
		return (ray.m_startPos.dot(m_plane.getNormal()) - m_plane.getDist()) / 
			-dot(m_plane.getNormal(), ray.m_unitDir);
}
