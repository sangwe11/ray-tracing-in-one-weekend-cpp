#include <iostream>
#include <fstream>

#include "common.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - (radius * radius);
    auto descriminant = (half_b * half_b) - (a * c);
    
    if (descriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(descriminant)) / a;
    }
}

color ray_color(const ray& r, const hittable_list& scene, const int depth)
{
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if (scene.hit(r, 0.001, inf, rec))
    {
        point3 target = rec.p + rec.normal + random_in_unit_sphere().unit();

        return 0.5 * ray_color(ray(rec.p, target - rec.p), scene, depth - 1);
    }

    vec3 unit_direction = r.direction().unit();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Output file
    std::ofstream output_file;
    output_file.open("output.ppm");

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Scene
    hittable_list scene;
    scene.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    scene.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    auto focal_length = 1.0;
    camera cam(point3(0, 0, 0), aspect_ratio, focal_length);

    // Render
    output_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);

                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, scene, max_depth);
            }

            write_color(output_file, pixel_color, samples_per_pixel);
        }
    }

    output_file.close();
    std::cout << "\nDone.\n";
    return 0;
}