#ifndef _RAY_H
#define _RAY_H

#include "vec3.h"

class ray
{
public:
	ray() {}
	ray(const point3& o, const vec3& d) : m_origin(o), m_direction(d) {}

	point3 origin() const { return m_origin; }
	vec3 direction() const { return m_direction; }

	point3 at(double t) const
	{
		return m_origin + t * m_direction;
	}

public:
	point3 m_origin;
	vec3 m_direction;
};

#endif