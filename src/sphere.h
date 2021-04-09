#ifndef _SPHERE_H
#define _SPHERE_H

#include "common.h"
#include "hittable.h"

class sphere : public hittable
{
public:
	sphere() {}
	sphere(point3 center, double radius, std::shared_ptr<material> material) : m_center(center), m_radius(radius), m_material(material) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 m_center;
	double m_radius;
	std::shared_ptr<material> m_material;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - m_center;
	auto a = r.direction().length_squared();
	auto half_b = oc.dot(r.direction());
	auto c = oc.length_squared() - (m_radius * m_radius);

	auto descriminant = (half_b * half_b) - (a * c);

	if (descriminant < 0)
		return false;

	auto sqrtd = sqrt(descriminant);
	auto root = (-half_b - sqrtd) / a;

	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;

		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - m_center) / m_radius;
	rec.set_face_normal(r, outward_normal);
	rec.material = m_material;

	return true;
}

#endif