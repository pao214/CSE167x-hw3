#pragma once

#include "General.h"

struct Normal
{
private:
    // Members
    glm::vec3 normal;

public:
    // Constructor
    Normal(const glm::vec3& normal): normal(glm::normalize(normal)) {}

    // Operations
    Normal operator+(const Normal& operand)
    {
        return Normal(normal+operand.normal);
    }

    Normal operator-(const Normal& operand)
    {
        return Normal(normal-operand.normal);
    }

    glm::vec3 get() const
    {
        return normal;
    }
};