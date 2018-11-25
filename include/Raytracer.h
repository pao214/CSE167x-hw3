#pragma once

#include "Sphere.h"
#include "Triangle.h"

struct Raytracer
{
private:
    int maxDepth;
    std::vector<Sphere> spheres;
    std::vector<glm::vec3> vertices;
    std::vector<Triangle> triangles;

    bool intersect(const Ray& ray)
    {
        float t;
        for (const auto& sphere: spheres)
        {
            if (sphere.intersect(ray, t))
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
        spheres.push_back(Sphere{center, radius});
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
        triangles.push_back(Triangle{vertices[A], vertices[B], vertices[C]});
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

        color = glm::vec3(1.0f, .0f, .0f);
    }
};
