
#include "object.h"
#include "Geometry/geometry.h"
#include "../maths/vec3.h"
#include "world.h"


Object::Object(const Material& material_, Geometry* geometry_)
:	m_material(material_),
	m_geometry(geometry_)
{

}
	
Object::~Object()
{
	delete m_geometry;
}



