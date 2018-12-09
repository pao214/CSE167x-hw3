#pragma once

#include "General.h"
#include "Primitive.h"

struct Triangle : public Primitive
{
private:
    // Members
    const glm::vec3 A, B, C;
    const glm::vec3 normal;
    int ord0, ord1;
    float mul;

protected:
    // Operations
    bool intersectV(const Ray& ray, float* tHitP, LocalGeo* localGeoP) const final
    {
        float den = glm::dot(ray.getDir(), normal);

        if (glm::abs(den) < 10e-6)
        // Ray parallel to surface.
        {
            return false;
        }

        // Hit point.
        float t = (glm::dot(A, normal)-glm::dot(ray.getPoint(), normal))/den;
        glm::vec3 point = ray.getPoint()+t*ray.getDir();

        // Linear equations' coefficients.
        float a1 = B[ord0]-A[ord0];
        float b1 = C[ord0]-A[ord0];
        float c1 = point[ord0]-A[ord0];
        float a2 = B[ord1]-A[ord1];
        float b2 = C[ord1]-A[ord1];
        float c2 = point[ord1]-A[ord1];

        // Solve the equation and check in range.
        float beta = (b2*c1-b1*c2)*mul;
        float gamma = (c2*a1-c1*a2)*mul;
        float alpha = 1.0f-beta-gamma;
        auto inRange = [] (float val) { return 0.0f <= val && val <= 1.0f; };
        new(tHitP) float(t);
        new(localGeoP) LocalGeo(point, normal);
        return ray.inRange(t) && inRange(alpha) && inRange(beta) && inRange(gamma);
    }

public:
    // Constructor
    Triangle(
        const glm::vec3& A, const glm::vec3 B, const glm::vec3& C,
        const Material& material, const glm::mat4& objToWorld
    ) : Primitive(material, objToWorld), A(A), B(B), C(C),
        normal(glm::normalize(glm::cross(B-A, C-A)))
    {
        for (int i = 0; i < 3; i++)
        {
            ord0 = i;
            ord1 = (i+1)%3;
            float a1 = B[ord0]-A[ord0];
            float b1 = C[ord0]-A[ord0];
            float a2 = B[ord1]-A[ord1];
            float b2 = C[ord1]-A[ord1];
            if (abs(a1*b2-a2*b1) < 1e-6) continue;
            mul = 1.0f/(a1*b2-a2*b1);
            break;
        }
    }
};
