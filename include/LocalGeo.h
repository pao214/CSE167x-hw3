#pragma once

#include "General.h"

struct LocalGeo
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 normal;

public:
    // Constructor
    LocalGeo() {}
    LocalGeo(const glm::vec3& point, const glm::vec3& normal): point(point), normal(glm::normalize(normal)) {}

    // Setters and getters
    glm::vec3 getPoint() const
    {
        return point;
    }

    glm::vec3 getNormal() const
    {
        return normal;
    }
};
