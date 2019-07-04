
#ifndef __MATERIAL_H_666_
#define __MATERIAL_H_666_


#include "../colour.h"
#include <stdio.h>
#include "../ray.h"
#include "../light.h"
/*=====================================================================
材质
=====================================================================*/
class Material
{
public:

	Material(const Colour ambient=Colour(0.2f,0.2f,0.2f),const Colour diffuse=Colour(0.8f,0.8f,0.8f),const Colour specular=Colour(0.0f,0.0f,0.0f),float specularFactor=5.0f);

	Material(const Material& m):ka(m.ka),kd(m.kd),ks(m.ks),ns(m.ns){
		
	}

	inline Material& operator=(const Material m){
		ka=m.ka;
		kd=m.kd;
		ks=m.ks;
		ns=m.ns;
		
	}
	Colour sample(const Ray& ray, Vec3 postion, Vec3 normal, Light* light);

	~Material(){}

	Colour 
		ka,//环境光反射系数
		kd,//漫反射系数
		ks;//镜面反射系数
	float ns;//镜面反射参数

};


#endif //__MATERIAL_H_666_




