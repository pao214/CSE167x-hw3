#pragma once

#include "General.h"
#include "Ray.h"

/**
 * Undefined behaviour
 *  height or width is non-positive
 *  fovx >= 180, fovy >= 180
 *  lookfrom and lookat are the same point
 *  you're looking in the same direction as up vector
 */
struct Camera
{
private:
    // Members
    int width, height;
    glm::vec3 lookfrom, lookat, up;
    float fovx, fovy;
    float tanx, tany;
    float invw, invh;

public:
    // Constructor
    Camera():
        width(100), height(100),
        lookfrom(.0f, .0f, 1.0f), lookat(.0f), up(.0f, 1.0f, .0f), fovx(90), fovy(90)
    {
        tanx = glm::tan(fovx/2.0f);
        tany = glm::tan(fovy/2.0f);
        invw = 1.0f/width;
        invh = 1.0f/height;
    }

    // Setters and getters
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->invw = 1.0f/width;
        this->invh = 1.0f/height;
    }

    // FIXME: Do we really need fovx, fovy
    void setCamera(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& up, float fovy)
    {
        this->lookfrom = lookfrom;
        this->lookat = lookat;
        this->up = up;
        this->fovx = 2.0f*std::atan((std::tan(fovy/2.0f)*width)/height);
        this->fovy = fovy;
        this->tanx = glm::tan(this->fovx/2.0f);
        this->tany = glm::tan(this->fovy/2.0f);
    }

    // Operations
    void generateRay(const glm::vec2& sample, Ray& ray)
    {
        float x = sample[0];
        float y = sample[1];
        float alpha = tanx*invw*(2.0f*x-width);
        float beta = tany*invh*(2.0f*y-height);
        glm::vec3 w = glm::normalize(lookfrom-lookat);
        glm::vec3 u = glm::normalize(glm::cross(up, w));
        glm::vec3 v = glm::cross(w, u);

        // Return the output.
        ray.point = lookfrom;
        ray.dir = glm::normalize(alpha*u+beta*v-w);
    }
};
