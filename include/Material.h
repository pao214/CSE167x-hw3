#pragma once

#include "General.h"

struct Material
{
    glm::vec3 ambient, diffuse, specular, emission;
    float shininess;
};
