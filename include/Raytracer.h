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
    glm::vec3 attenuation, ambient;

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

public:
    // Constructor
    Raytracer(): maxDepth(5), attenuation(1.0f, .0f, .0f), ambient(.2f) {}

    // Setters and getters
    void setMaxDepth(int maxDepth)
    {
        this->maxDepth = maxDepth;
    }

    void addSphere(const glm::vec3& center, float radius)
    {
        primitives.push_back(std::make_shared<Sphere>(center, radius, ambient));
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
        primitives.push_back(std::make_shared<Triangle>(vertices[A], vertices[B], vertices[C], ambient));
    }

    void addDirLight(const glm::vec3& dir, const glm::vec3& color)
    {
        lights.push_back(std::make_shared<DirLight>(dir, color));
    }

    void addPointLight(const glm::vec3& point, const glm::vec3& color)
    {
        lights.push_back(std::make_shared<PointLight>(point, color, attenuation));
    }

    void setAttenuation(const glm::vec3& attenuation)
    {
        this->attenuation = attenuation;
    }

    void setAmbient(const glm::vec3& ambient)
    {
        this->ambient = ambient;
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
        // ambient+emission+sum(v[i]*l[i]/atten[i]*(D*max(N.L,0)+S*max(N.H,0)^s))
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
                const auto& normal = localGeo.getNormal();
                const auto& lightDir = lightRay.getDir();
                const auto& halfAngle = glm::normalize(lightDir-ray.getDir());
                color += lightColor*(
                    material.diffuse*std::max(glm::dot(normal, lightDir), .0f)+
                    material.specular*glm::pow(std::max(glm::dot(normal, halfAngle), .0f), material.shininess)
                );
            }
        }

        // Return the color.
        new(colorP) glm::vec3(color);
    }
};
