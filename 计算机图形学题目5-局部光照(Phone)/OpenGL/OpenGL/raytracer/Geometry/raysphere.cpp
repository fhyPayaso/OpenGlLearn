
#include "raysphere.h"

#include "../ray.h"


float RaySphere::getDistanceUntilHit(const Ray& ray) const
{
	const Vec3 raystarttosphere = this->m_centerpos - ray.m_startPos;

	const float dist_to_rayclosest = dotProduct(raystarttosphere, ray.m_unitDir);


	if(dist_to_rayclosest < 0.0f)
		return -666.0f;


	const float sph_cen_to_ray_closest_len2 = raystarttosphere.length2() - 
		dist_to_rayclosest*dist_to_rayclosest;

	if(sph_cen_to_ray_closest_len2 > this->m_radiusSquared)
		return -666.0f;

	
	
	return dist_to_rayclosest - sqrt(this->m_radiusSquared - sph_cen_to_ray_closest_len2);
}


const Vec3 RaySphere::getNormalForPos(const Vec3& point) const 
{ 
	return (point - m_centerpos) * m_recipRadius;
}