#pragma once

#include "General.h"
#include "Ray.h"

struct Shape
{
public:
    // Base class requires a virtual destructor.
    virtual ~Shape() {}

    // Operations
    virtual bool intersect(const Ray& ray, float& t) const = 0;
};