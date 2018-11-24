#pragma once

#include <cstdlib>

struct Normal
{
    // Members
    float x, y, z;

    // Constructor
    Normal(float x, float y, float z)
    {
        float den = std::sqrt(x*x+y*y+z*z);
        if (den < 10e-6) throw "Cannot normalize a zero normal.";
        this->x = x/den;
        this->y = y/den;
        this->z = z/den;
    }

    // Operations
    friend Normal operator+(const Normal& op1, const Normal& op2);
    friend Normal operator-(const Normal& op1, const Normal& op2);
};

inline Normal operator+(const Normal& op1, const Normal& op2)
{
    return Normal(op1.x+op2.x, op1.y+op2.y, op1.z+op2.z);
}

inline Normal operator-(const Normal& op1, const Normal& op2)
{
    return Normal(op1.x+op2.x, op1.y+op2.y, op1.z+op2.z);
}
