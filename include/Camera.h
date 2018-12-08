#pragma once

#include "General.h"
#include "Ray.h"

/**
 * Undefined behaviour
 *  height or width is non-positive
 *  fovx >= 180, fovy >= 180
 *  lookfrom and lookat are the same point
 *  you're looking in the same direction as up vector
 * Latency Sensitive: generateRay
 */
struct Camera
{
private:
    // Members
    int width, height;
    glm::vec3 lookfrom, lookat, up;
    glm::vec3 w, u, v;
    float tanx, tany;
    float xMul, yMul;

public:
    // Constructor
    Camera():
        width(100), height(100),
        lookfrom(.0f, .0f, 1.0f), lookat(.0f), up(.0f, 1.0f, .0f),
        w(glm::normalize(lookfrom-lookat)), u(glm::normalize(glm::cross(up, w))), v(glm::cross(w, u)),
        tanx(1.0f), tany(1.0f),
        xMul(tanx/width), yMul(tany/height) {}

    // Setters and getters
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;

        // Pre-compute multipliers.
        this->xMul = (this->tanx)/width;
        this->yMul = (this->tany)/height;
    }

    void setCamera(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& up, float fovy)
    {
        this->lookfrom = lookfrom;
        this->lookat = lookat;
        this->up = up;
        this->tanx = (glm::tan(fovy/2.0f)*width)/height;
        this->tany = glm::tan(fovy/2.0f);

        // Pre-compute coordinates.
        this->w = glm::normalize(lookfrom-lookat);
        this->u = glm::normalize(glm::cross(up, w));
        this->v = glm::cross(w, u);

        // Pre-compute multipliers.
        this->xMul = (this->tanx)/width;
        this->yMul = (this->tany)/height;
    }

    // Operations
    void generateRay(const glm::vec2& sample, Ray* rayP)
    {
        float x = sample[0];
        float y = sample[1];
        float alpha = xMul*(2.0f*x-width);
        float beta = yMul*(2.0f*y-height);

        // Return the output.
        new(rayP) Ray(lookfrom, alpha*u+beta*v-w);
    }
};
