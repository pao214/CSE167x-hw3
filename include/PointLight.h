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
    void generateLightRay(const LocalGeo& localGeo, Ray* rayP, glm::vec3* colorP) const final
    {
        // Return ray after slight movement.
        new(rayP) Ray(localGeo.getPoint(), point-localGeo.getPoint(), 1e-6f);

        // Return color.
        new(colorP) glm::vec3(this->color); 
    }
};
