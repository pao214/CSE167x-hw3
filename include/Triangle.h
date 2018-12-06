#pragma once

#include "General.h"
#include "Normal.h"
#include "Shape.h"

struct Triangle : public Shape
{
private:
    // Members
    const glm::vec3 A, B, C;
    const Normal normal;

public:
    // Constructor
    Triangle(const glm::vec3& A, const glm::vec3 B, const glm::vec3& C):
        A(A), B(B), C(C),
        normal(glm::cross(B-A, C-A)) {}

    // Operations
    bool intersect(const Ray& ray, float& t) const final
    {
        float den = glm::dot(ray.getDir(), normal.get());

        if (glm::abs(den) < 10e-6)
        // Ray parallel to surface.
        {
            return false;
        }

        // Hit point.
        t = (glm::dot(A, normal.get())-glm::dot(ray.getPoint(), normal.get()))/den;
        glm::vec3 point = ray.getPoint()+t*ray.getDir();

        // Linear equations' coefficients.
        float a1 = B[0]-A[0];
        float b1 = C[0]-A[0];
        float c1 = point[0]-A[0];
        float a2 = B[1]-A[1];
        float b2 = C[1]-A[1];
        float c2 = point[1]-A[1];

        // Solve the equation and check in range.
        float invden = 1.0f/(a1*b2-a2*b1);
        float beta = (b2*c1-b1*c2)*invden;
        float gamma = (c2*a1-c1*a2)*invden;
        float alpha = 1.0f-beta-gamma;
        auto inRange = [] (float val) { return 0.0f <= val && val <= 1.0f; };
        return ray.inRange(t) && inRange(alpha) && inRange(beta) && inRange(gamma);
    }
};
