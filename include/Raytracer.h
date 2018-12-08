#pragma once

#include "Sphere.h"
#include "Triangle.h"
#include "DirLight.h"
#include "PointLight.h"

// FIXME: Modify shared pointers to use unique pointers.
struct Raytracer
{
private:
    int maxDepth;
    std::vector<glm::vec3> vertices;
    std::vector<std::shared_ptr<Primitive>> primitives;
    std::vector<std::shared_ptr<Light>> lights;
    glm::vec3 ambient;

protected:
    bool intersect(const Ray& ray, LocalGeo* localGeoP, std::shared_ptr<Primitive>* primitiveP)
    {
        for (const auto& primitive: primitives)
        {
            if (primitive->intersect(ray, localGeoP))
            {
                new(primitiveP) std::shared_ptr<Primitive>(primitive);
                return true;
            }
        }

        return false;
    }

    glm::vec3 shade(const LocalGeo& localGeo, const Material& material, const Ray& lightRay, const glm::vec3& lightColor)
    {
        return lightColor;
    }

public:
    // Constructor
    Raytracer(): maxDepth(1) {}

    // Setters and getters
    void setMaxDepth(int maxDepth)
    {
        this->maxDepth = maxDepth;
    }

    void addSphere(const glm::vec3& center, float radius)
    {
        primitives.push_back(std::make_shared<Sphere>(center, radius));
    }

    void setMaxVerts(int maxVerts)
    {
        vertices.reserve(maxVerts);
    }

    void addVertex(const glm::vec3& vertex)
    {
        vertices.push_back(vertex);
    }

    void addTriangle(int A, int B, int C)
    {
        primitives.push_back(std::make_shared<Triangle>(vertices[A], vertices[B], vertices[C]));
    }

    void addDirLight(const glm::vec3& dir, const glm::vec3& color)
    {
        lights.push_back(std::make_shared<DirLight>(dir, color));
    }

    void addPointLight(const glm::vec3& point, const glm::vec3& color)
    {
        lights.push_back(std::make_shared<PointLight>(point, color));
    }

    // Operations
    void trace(const Ray& ray, glm::vec3* colorP)
    {
        LocalGeo localGeo;
        std::shared_ptr<Primitive> primitive;

        // Color black if there is no intersection.
        if (!intersect(ray, &localGeo, &primitive))
        {
            new(colorP) glm::vec3(.0f, .0f, .0f);
            return;
        }

        // Color the pixel.
        Material material;
        primitive->getMaterial(&material);
        glm::vec3 color{material.ambient+material.emission};

        Ray lightRay;
        glm::vec3 lightColor;
        LocalGeo lightGeo;
        for (const auto& light: lights)
        {
            light->generateLightRay(localGeo, &lightRay, &lightColor);

            // Shade only if not blocked.
            if (!primitive->intersect(lightRay, &lightGeo))
            {
                color += shade(localGeo, material, lightRay, lightColor);
            }
        }

        // Return the color.
        new(colorP) glm::vec3(color);
    }
};
