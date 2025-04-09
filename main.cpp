#include "utils/common.h"

#include "utils/camera.h"
#include "utils/hittable.h"
#include "utils/hittable_list.h"
#include "utils/material.h"
#include "utils/sphere.h"

#include <iostream>
#include <chrono>

void render1_test(int samples_per_pixel)
{
    // Render 15 times
    for (int i = 0; i < 15; ++i)
    {
        auto start_time = std::chrono::steady_clock::now();

        hittable_list world;
        
        auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = std::make_shared<dielectric>(1.50);
        auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50);
        auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.1 );
        
        world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1), 100, material_ground));
        world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1), 0.5, material_center));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
        world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        // Camera settings
        camera cam;
        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 1200;
        cam.samples_per_pixel = samples_per_pixel;
        cam.max_depth = 50;

        cam.vfov = 60;
        cam.lookfrom = point3(-1, 1, 1);
        cam.lookat = point3(0, 0, -1);
        cam.vup = vec3(0, 1, 0);

        cam.render(world);

        // Calculate time elapsed
        auto end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> seconds_elapsed = end_time - start_time;
        std::clog << "Time elapsed: " << static_cast<int>(seconds_elapsed.count() / 60) << " minutes and " 
                                        << fmod(seconds_elapsed.count(), 60) << " seconds.\n";
    }
}

void render2_test(int samples_per_pixel)
{
    auto start_time = std::chrono::steady_clock::now();

    hittable_list world;
    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) 
    {
        for (int b = -11; b < 11; b++) 
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) 
            {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) 
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } 
                else if (choose_mat < 0.95) 
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } 
                else 
                {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    
    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    // Camera settings
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);

    // Calculate time elapsed
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds_elapsed = end_time - start_time;
    std::clog << "Time elapsed: " << static_cast<int>(seconds_elapsed.count() / 60) << " minutes and " 
                                    << fmod(seconds_elapsed.count(), 60) << " seconds.\n";
}

int main() 
{
    // Test 1
    // render1_test(10);

    // Test 2
    // render1_test(50);

    // Test 3
    // render2_test(10);

    // Test 4
    // render2_test(500);
}