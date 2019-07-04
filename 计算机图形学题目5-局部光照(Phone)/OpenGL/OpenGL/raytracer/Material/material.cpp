

#include "material.h"

#include <assert.h>
#include <stdio.h>

Material::Material(const Colour ambient,const Colour diffuse,const Colour specular,float specularFactor)
{
	ka=ambient;
	kd=diffuse;
	ks=specular;
	ns=specularFactor;

}

Colour Material::sample(const Ray& ray, Vec3 postion, Vec3 normal, Light* light)
{
	Vec3 lightDir = light->getPos();
	lightDir = lightDir.normalise();
	Colour lightColor = light->getColour();


	float NdotL = normal.dot(lightDir);
	Vec3 H = lightDir - ray.m_unitDir;
	H = H.normalise();
	float NdotH = normal.dot(H);

	Colour diffuseTerm = this->kd * fmax(NdotL, (float)0);
	Colour specularTerm = this->ks * (pow(fmax(NdotH, (float)0), this->ns));
	return lightColor * (this->ka + diffuseTerm + specularTerm);
}