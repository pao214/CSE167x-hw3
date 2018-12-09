#pragma once

#include "General.h"

/**
 * Undefined behaviour
 *  Direction is zero.
 *  Default constructed rays must be reconstructed.
 * Direction is always normalized.
 * Default values for t_min and t_max.
 * Represents a ray point+t*dir, where t_min <= t <= t_max.
 * FIXME: Is t_max any useful?
 */
struct Ray
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 dir;
    float t_min, t_max;

public:
    // Constructor
    Ray() {}
    Ray(const glm::vec3& point, const glm::vec3& dir, float t_min=.0f, float t_max=std::numeric_limits<float>::infinity()): point(point), dir(glm::normalize(dir)), t_min(t_min), t_max(t_max) {}

    // Setters and getters
    glm::vec3 getPoint() const
    {
        return point;
    }

    glm::vec3 getDir() const
    {
        return dir;
    }

    float getMin() const
    {
        return t_min;
    }

    float getMax() const
    {
        return t_max;
    }

    // Operations
    bool inRange(float t) const
    {
        return t_min <= t && t <= t_max;
    }
};
