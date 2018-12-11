#pragma once

#include "General.h"
#include "Light.h"

struct PointLight : public Light
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 color;
    glm::vec3 attenuation;

public:
    // Constructors and Destructors
    PointLight(const glm::vec3& point, const glm::vec3& color, const glm::vec3& attenuation):
        point(point), color(color), attenuation(attenuation) {}

    // Operations
    void generateLightRay(const LocalGeo& localGeo, Ray* rayP, glm::vec3* colorP) const final
    {
        const auto mag = point-localGeo.getPoint();
        float r2 = mag.x*mag.x+mag.y*mag.y+mag.z*mag.z;
        float r = glm::sqrt(r2);

        // Return ray after slight movement.
        new(rayP) Ray(localGeo.getPoint(), point-localGeo.getPoint(), 1e-2f, r);

        // Return color.
        new(colorP) glm::vec3(color/(attenuation.x+attenuation.y*r+attenuation.z*r2));
    }
};
