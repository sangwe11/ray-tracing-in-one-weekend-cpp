#include <iostream>
#include <fstream>

#include "common.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

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
        ray scattered;
        color attenuation;

        if (rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, scene, depth - 1);

        return color(0, 0, 0);
    }

    vec3 unit_direction = r.direction().unit();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene()
{
    hittable_list scene;

    std::shared_ptr<lambertian> ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    scene.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double choose_material = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<material> sphere_material;

                if (choose_material < 0.8)
                {
                    vec3 albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_material < 0.95)
                {
                    vec3 albedo = color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    sphere_material = std::make_shared<dielectric>(1.5);
                    scene.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    std::shared_ptr<material> material1 = std::make_shared<dielectric>(1.5);
    scene.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    std::shared_ptr<material> material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    scene.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    std::shared_ptr<material> material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    scene.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return scene;
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
    hittable_list scene = random_scene();

    // Camera
    double focus_distance = 10;
    double aperture = 0.1;
    camera cam(point3(13, 2, 3), vec3(-13, -2, -3), vec3(0, 1,0), 20, aspect_ratio, aperture, focus_distance);

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
                auto u = (i + random_double()) / (double)(image_width - 1);
                auto v = (j + random_double()) / (double)(image_height - 1);

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