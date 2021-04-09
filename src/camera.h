#ifndef _CAMERA_H
#define _CAMERA_H

#include "common.h"

class camera
{
public:
	camera(point3 origin, vec3 direction, vec3 up, double vfov, double aspect_ratio, double aperture, double focus_distance)
	{
		double theta = degrees_to_radians(vfov);
		double h = tan(theta / 2);
		double viewport_height = 2.0 * h;
		double viewport_width = aspect_ratio * viewport_height;

		point3 look_at = origin + direction;
		w = (origin - look_at).unit();
		u = up.cross(w).unit();
		v = w.cross(u);

		m_origin = origin;
		m_horizontal = focus_distance * viewport_width * u;
		m_vertical = focus_distance * viewport_height * v;
		m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - focus_distance * w;

		m_lens_radius = aperture / 2.0;
	}

	ray get_ray(double s, double t) const
	{
		vec3 rd = m_lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();

		return ray(m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset);
	}

private:
	point3 m_origin;
	point3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 u, v, w;
	double m_lens_radius;
};

#endif