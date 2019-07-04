/*=====================================================================
光源
=====================================================================*/
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "colour.h"
#include "../maths/vec3.h"



class Light
{
public:
	//构造函数
	Light(const Vec3& pos_, const Colour& c)
	:	pos(pos_),
		colour(c)
	{}

	~Light(){}

	//获取光源位置
	inline const Vec3& getPos() const { return pos; }

	//获取光颜色
	inline const Colour& getColour() const { return colour; }

	Vec3 pos;
	Colour colour;
};


#endif //__LIGHT_H__