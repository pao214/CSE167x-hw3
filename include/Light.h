#pragma once

#include "General.h"
#include "LocalGeo.h"
#include "Ray.h"

// FIXME: Attenuation.
struct Light
{
public:
    virtual ~Light() {};
    virtual void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) const = 0;
};

struct PointLight : public Light
{
private:
    // Members
    glm::vec3 point;
    glm::vec3 color;

public:
    // Constructors and Destructors
    PointLight(const glm::vec3& point, const glm::vec3& color): point(point), color(color) {}

    // Operations
    void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) const final
    {
        // Return ray after slight movement.
        new(&ray) Ray(local.point, point-local.point, 1e-6f);

        // Return color.
        new(&color) glm::vec3(color.x, color.y, color.z); 
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
    glm::vec3 color;

public:
    // Constructors and destrructors
    DirLight(const glm::vec3& dir, const glm::vec3& color): dir(glm::normalize(dir)), color(color) {}

    // Operations
    void generateLightRay(const LocalGeo& local, Ray& ray, glm::vec3& color) const final
    {
        // Return the ray after slight movement.
        new(&ray) Ray(local.point, dir, 1e-6f);

        // Return color.
        new(&color) glm::vec3(color.x, color.y, color.z);
    }
};