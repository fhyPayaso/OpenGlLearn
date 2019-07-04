
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Material/material.h"
class Geometry;
class Vec3;
class World;

/*===================================================================
物体,由形状和材质构成
====================================================================*/
class Object
{
public:

	//构造函数
	Object(const Material& material, Geometry* geometry);
	~Object();


	//返回材质
	const Material& getMaterial() const { return m_material; }

	//返回形状
	Geometry& getGeometry(){ return *m_geometry; }

private:
	Material m_material;//材质
	Geometry* m_geometry;//形状

};



#endif //__OBJECT_H__
