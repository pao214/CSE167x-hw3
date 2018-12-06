#pragma once

#include "General.h"
#include "Shape.h"

struct Sphere : public Shape
{
private:
    // Members
    const glm::vec3 center;
    const float radius;

public:
    // Constructor
    Sphere(const glm::vec3& center, float radius): center(center), radius(radius) {}

    // Operations
    bool intersect(const Ray& ray, float& t) const final
    {
        float a = glm::dot(ray.getDir(), ray.getDir());
        float b = 2.0f*glm::dot(ray.getDir(), ray.getPoint()-center);
        float c = glm::dot(ray.getPoint()-center, ray.getPoint()-center)-radius*radius;
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
            return ray.inRange(t);
        }

        // Only one positive root.
        t = more;
        return ray.inRange(t);
    }
};
