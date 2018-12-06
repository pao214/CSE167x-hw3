#pragma once

#include "General.h"
#include "LocalGeo.h"
#include "Ray.h"

// FIXME: Attenuation.
struct Light
{
public:
    // Base class requires a virtual destructor.
    virtual ~Light() {};

    // Operations
    virtual void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) const = 0;
};
