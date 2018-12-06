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
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;

    bool intersect(const Ray& ray)
    {
        float t;
        for (const auto& shape: shapes)
        {
            if (shape->intersect(ray, t))
            {
                return true;
            }
        }

        return false;
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
        shapes.push_back(std::make_shared<Sphere>(center, radius));
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
        shapes.push_back(std::make_shared<Triangle>(vertices[A], vertices[B], vertices[C]));
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
    void trace(const Ray& ray, glm::vec3& color)
    {
        // Color black if there is no intersection.
        if (!intersect(ray))
        {
            color = glm::vec3(.0f, .0f, .0f);
            return;
        }

        // Color red otherwise.
        color = glm::vec3(1.0f, .0f, .0f);
    }
};
