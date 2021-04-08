#ifndef _VEC3_H
#define _VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
public:
	vec3() : e{0, 0, 0} {}
	vec3(const double& x, const double& y, const double& z) : e{x, y, z} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	double r() const { return x(); }
	double g() const { return y(); }
	double b() const { return z(); }

	vec3 operator-() const
	{
		return vec3(-e[0], -e[1], -e[2]);
	}

	vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3 operator+(const vec3& v) const
	{
		return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
	}

	vec3& operator++()
	{
		e[0] += 1;
		e[1] += 1;
		e[2] += 1;
		return *this;
	}

	vec3& operator-=(const vec3& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	vec3 operator-(const vec3& v) const
	{
		return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
	}

	vec3& operator*=(const vec3& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	vec3& operator*=(const double c)
	{
		e[0] *= c;
		e[1] *= c;
		e[2] *= c;
		return *this;
	}

	vec3 operator*(const vec3& v) const
	{
		return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
	}

	vec3 operator*(const double c) const
	{
		return vec3(e[0] * c, e[1] * c, e[2] * c);
	}

	vec3& operator/=(const vec3& v)
	{
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	vec3 operator/(const vec3& v) const
	{
		return vec3(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
	}

	vec3 operator/(double c) const
	{
		return vec3(e[0] / c, e[1] / c, e[2] / c);
	}

	std::ostream& operator<<(std::ostream& out) const
	{
		return out << e[0] << ' ' << e[1] << ' ' << e[2];
	}

	double length() const
	{
		return sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	double dot(const vec3& v) const
	{
		return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
	}

	vec3 cross(const vec3& v) const
	{
		return vec3(e[1] * v.e[2] - e[2] * v.e[1], e[2] * v.e[0] - e[0] * v.e[2], e[0] * v.e[1] - e[1] * v.e[0]);
	}

	vec3 unit() const
	{
		return *this / length();
	}

	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(const double min, const double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

public:
	double e[3];
};

inline vec3 operator*(double t, const vec3& v)
{
	return v * t;
}

inline double dot(const vec3& v, const vec3& u)
{
	return v.dot(u);
}

inline vec3 cross(const vec3& v, const vec3& u)
{
	v.cross(u);
}

vec3 random_in_unit_sphere()
{
	while (true)
	{
		vec3 p = vec3::random(-1, 1);
		if (p.length_squared() >= 1)
			continue;

		return p;
	}
}

// Type aliases
using point3 = vec3;

#endif