#pragma once

#include <Vector.h>

struct Ray
{
    // Members
    Point pos;
    Vector dir;
    float t_min, t_max;

    // Constructor
    Ray(const Point& pos, const Vector& dir, float t_min, float t_max) : pos(pos), dir(dir), t_min(t_min), t_max(t_max) {}
};
