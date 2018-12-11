#pragma once

#include "General.h"
#include "Light.h"

/**
 * Direction is always normalized.
 */
struct DirLight : public Light
{
private:
    // Members
    glm::vec3 dir;
    glm::vec3 color;

public:
    // Constructors and destrructors
    DirLight(const glm::vec3& dir, const glm::vec3& color): dir(glm::normalize(dir)), color(color) {}

    // Operations
    void generateLightRay(const LocalGeo& localGeo, Ray* rayP, glm::vec3* colorP) const final
    {
        // Return the ray after slight movement.
        new(rayP) Ray(localGeo.getPoint(), dir, 1e-2f);

        // Return color.
        new(colorP) glm::vec3(this->color);
    }
};
