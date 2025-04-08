#include "utils/common.h"

#include "utils/camera.h"
#include "utils/hittable.h"
#include "utils/hittable_list.h"
#include "utils/sphere.h"

#include <iostream>

int main() 
{
    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.render(world);
}