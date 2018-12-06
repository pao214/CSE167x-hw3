#pragma once

#include "General.h"
#include "Light.h"

struct PointLight : public Light
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 color;

public:
    // Constructors and Destructors
    PointLight(const glm::vec3& point, const glm::vec3& color): point(point), color(color) {}

    // Operations
    void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) const final
    {
        // Return ray after slight movement.
        new(&ray) Ray(local.point, point-local.point, 1e-6f);

        // Return color.
        new(&color) glm::vec3(color.x, color.y, color.z); 
    }
};
