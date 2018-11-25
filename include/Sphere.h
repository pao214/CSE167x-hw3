#pragma once

#include "General.h"

struct Sphere
{
private:
    // Members
    const glm::vec3 center;
    const float radius;

public:
    // Constructor
    Sphere(const glm::vec3& center, float radius): center(center), radius(radius) {}

    // Operations
    bool intersect(const Ray& ray, float& t) const
    {
        float a = glm::dot(ray.dir, ray.dir);
        float b = 2.0f*glm::dot(ray.dir, ray.point-center);
        float c = glm::dot(ray.point-center, ray.point-center)-radius*radius;
        float disc = b*b-4*a*c;

        if (disc < 0.0f)
        // Complex roots.
        {
            return false;
        }

        float disc_root = glm::sqrt(disc);
        float less = (-b-disc_root)/(2.0f*a);
        float more = (-b+disc_root)/(2.0f*a);

        // Both roots positive.
        if (less > 0.0f)
        {
            t = less;
            return true;
        }

        // Only one positive root.
        t = more;
        return true;
    }
};
