#pragma once

#include "General.h"
#include "LocalGeo.h"
#include "Ray.h"

/**
 * The direction of light ray is from local point towards light source.
 */
struct Light
{
public:
    // Base class requires a virtual destructor.
    virtual ~Light() {};

    // Operations
    virtual void generateLightRay(const LocalGeo& localGeo, Ray* rayP, glm::vec3* colorP) const = 0;
};
