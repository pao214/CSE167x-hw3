#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <cstdlib>

// Type definitions
using Vec3 = std::array<float, 3>;
using Vec4 = std::array<float, 4>;
using Mat3 = std::array<std::array<float, 3>, 3>;
using Mat4 = std::array<std::array<float, 4>, 4>;
using Pixels = std::vector<uint8_t>;
using String = std::string;

// Value definitions
constexpr double PI = 3.14159265358979323846;

// Final output
extern Pixels pixels;

// General
extern int width, height;
extern int maxDepth;
extern String inputFileName, outputFileName;

// Camera
extern Vec3 lookfrom, lookat, up;
extern double fovx, fovy;

// Inline functions
inline double radians(const double degrees)
{
    return degrees*(PI/180.);
}
