#ifndef _CAMERA_H
#define _CAMERA_H

#include "common.h"

class camera
{
public:
	camera(point3 origin, vec3 direction, vec3 up, double vfov, double aspect_ratio)
	{
		double theta = degrees_to_radians(vfov);
		double h = tan(theta / 2);
		double viewport_height = 2.0 * h;
		double viewport_width = aspect_ratio * viewport_height;

		point3 look_at = origin + direction;
		vec3 w = (origin - look_at).unit();
		vec3 u = up.cross(w).unit();
		vec3 v = w.cross(u);

		m_origin = origin;
		m_horizontal = viewport_width * u;
		m_vertical = viewport_height * v;
		m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - w;
	}

	ray get_ray(double s, double t) const
	{
		return ray(m_origin, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin);
	}

private:
	point3 m_origin;
	point3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;
};

#endif