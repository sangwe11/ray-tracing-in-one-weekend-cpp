#ifndef _RT_COMMON_H
#define _RT_COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants
const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utilities
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double radians_to_degrees(double radians)
{
	return radians * (180.0 / pi);
}

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;

	return x;
}

// Common headers
#include "vec3.h"
#include "ray.h"

#endif