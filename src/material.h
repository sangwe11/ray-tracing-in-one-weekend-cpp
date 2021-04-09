#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "common.h"
#include "color.h"
#include "hittable.h"

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const color& albedo) : m_albedo(albedo) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 scatter_direction = rec.normal + random_in_unit_sphere().unit();

		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = m_albedo;
		return true;
	}

public:
	color m_albedo;
};

class metal : public material
{
public:
	metal(const color& albedo, double fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(r_in.direction().unit(), rec.normal);
		scattered = ray(rec.p, reflected + m_fuzz * random_in_unit_sphere());
		attenuation = m_albedo;

		return (scattered.direction().dot(rec.normal) > 0);
	}

public:
	color m_albedo;
	double m_fuzz;
};

class dielectric : public material
{
public:
	dielectric(double refraction_index) : m_refraction_index(refraction_index) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1.0, 1.0, 1.0);
		double refraction_ratio = rec.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

		vec3 unit_direction = r_in.direction().unit();
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio);

		scattered = ray(rec.p, direction);
		return true;
	}

public:
	double m_refraction_index;

private:
	static double reflectance(double cosine, double refraction_ratio)
	{
		double r0 = (1 - refraction_ratio) / (1 + refraction_ratio);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif