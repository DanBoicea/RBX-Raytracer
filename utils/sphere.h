#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override
    {
        vec3 oc = center - r.origin();

        /* Solving the quadratic equation

        double a = dot(r.direction(), r.direction());
        double b = -2.0 * dot(r.direction(), oc);
        double c = dot(oc, oc) - radius * radius;

        double discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0)
            return -1.0;
        else
            return (-b - std::sqrt(discriminant)) / (2.0 * a);
        */

        // Simplifying the quadratic equation solution by considering b = -2h
        double a = r.direction().length_squared();
        double h = dot(r.direction(), oc);
        double c = oc.length_squared() - radius * radius;
        double discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;
        
        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        double root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        // Surface side determination
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif