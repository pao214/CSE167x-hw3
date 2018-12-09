#pragma once

#include "General.h"

struct Material
{
public:
    glm::vec3 ambient, diffuse, specular, emission;
    float shininess;

    // Default constructor sets default values
    Material(): ambient(.2f, .2f, .2f) {}
};
