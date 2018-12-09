#pragma once

#include "General.h"
#include "Primitive.h"

struct Sphere : public Primitive
{
private:
    // Members
    const glm::vec3 center;
    const float radius;

protected:
    // Operations
    bool intersectV(const Ray& ray, LocalGeo* localGeoP) const final
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
            glm::vec3 point{ray.getPoint()+less*ray.getDir()};
            new(localGeoP) LocalGeo(point, glm::normalize(point-center));
            return ray.inRange(less);
        }

        // Only one positive root.
        glm::vec3 point{ray.getPoint()+more*ray.getDir()};
        new(localGeoP) LocalGeo(point, glm::normalize(point-center));
        return ray.inRange(more);
    }

public:
    // Constructor
    Sphere(
        const glm::vec3& center, float radius,
        const glm::vec3& ambient, const Material& material,
        const glm::mat4& objToWorld
    ) : Primitive(ambient, material, objToWorld), center(center), radius(radius) {}
};
