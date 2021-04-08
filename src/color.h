#ifndef _COLOR_H
#define _COLOR_H

#include "vec3.h"

// Type alias vec3 as color
using color = vec3;

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	//double scale = 1.0 / samples_per_pixel;
	//pixel_color *= scale;
	//pixel_color = clamp(pixel_color, 0.0, 0.999);	
	//pixel_color = color(clamp(pixel_color.r(), 0.0, 0.999), clamp(pixel_color.g(), 0.0, 0.999), clamp(pixel_color.b(), 0.0, 0.999));

	//out << static_cast<int>(256 * pixel_color.r()) << ' ' << static_cast<int>(256 * pixel_color.g()) << ' ' << static_cast<int>(256 * pixel_color.b()) << '\n';

	auto r = pixel_color.r();
	auto g = pixel_color.g();
	auto b = pixel_color.b();

	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' ' << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif