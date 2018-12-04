#pragma once

#include "General.h"
#include "LocalGeo.h"
#include "Ray.h"

/**
 * We move the geometry a little towards the light source.
 */
struct Light
{
public:
    virtual void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) = 0;
};

struct PointLight : public Light
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 intensity;

public:
    // Constructor
    PointLight(const glm::vec3& point): point(point) {}

    // Operations
    void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color)
    {
        // Return ray after slight movement.
        new(&ray) Ray(local.point, point-local.point, 1e-6f);

        // Return color.
        // FIXME: I = A + E + sum(Vi*Li/(c0+c1*r_c2*r^2)*(D*max(dot(N,L),0)+S*max(dot(N,H),0)^s))
    }
};

/**
 * Direction is always normalized.
 */
struct DirLight : public Light
{
private:
    // Members
    glm::vec3 dir;
    glm::vec3 intensity;

public:
    // Constructor
    DirLight(const glm::vec3& dir, const glm::vec3& intensity): dir(glm::normalize(dir)), intensity(intensity) {}

    // Operations
    void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color)
    {
        // Return the ray after slight movement.
        new(&ray) Ray(local.point, dir, 1e-6f);

        // Return color.
    }
};