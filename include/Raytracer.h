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
    glm::vec3 attenuation;
    Material material;
    std::stack<glm::mat4> transformStack;

protected:
    bool intersect(const Ray& ray, LocalGeo* localGeoP=nullptr, std::shared_ptr<Primitive>* primitiveP=nullptr)
    {
        float tHitMin = std::numeric_limits<float>::infinity();
        float tHit;
        bool hit = false;
        LocalGeo localGeo;

        for (const auto& primitive: primitives)
        {
            if (primitive->intersect(ray, &tHit, &localGeo) && (tHit < tHitMin))
            {
                hit = true;
                tHitMin = tHit;
                if (localGeoP) new(localGeoP) LocalGeo(localGeo);
                if (primitiveP) new(primitiveP) std::shared_ptr<Primitive>(primitive);
            }
        }

        return hit;
    }

public:
    // Constructor
    Raytracer(): maxDepth(5), attenuation(1.0f, .0f, .0f)
    {
        transformStack.push(glm::mat4(1.0f));
    }

    // Setters and getters
    void setMaxDepth(int maxDepth)
    {
        this->maxDepth = maxDepth;
    }

    // Geometry
    void addSphere(const glm::vec3& center, float radius)
    {
        primitives.push_back(std::make_shared<Sphere>(
            center, radius, material, transformStack.top()
        ));
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
        primitives.push_back(std::make_shared<Triangle>(
            vertices[A], vertices[B], vertices[C], material, transformStack.top()
        ));
    }

    // Lighting
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
        this->material.ambient = ambient;
    }

    // Material properties
    void setDiffuse(const glm::vec3& diffuse)
    {
        this->material.diffuse = diffuse;
    }

    void setSpecular(const glm::vec3& specular)
    {
        this->material.specular = specular;
    }

    void setShininess(float shininess)
    {
        this->material.shininess = shininess;
    }

    void setEmission(const glm::vec3& emission)
    {
        this->material.emission = emission;
    }

    // Transforms
    void translate(const glm::vec3& translation)
    {
        auto& transform = transformStack.top();
        transform = transform*glm::translate(glm::mat4(1.0f), translation);
    }

    void rotate(const glm::vec3& axis, float angle)
    {
        auto& transform = transformStack.top();
        transform = transform*glm::rotate(glm::mat4(1.0f), angle, axis);
    }

    void scale(const glm::vec3& scaling)
    {
        auto& transform = transformStack.top();
        transform = transform*glm::scale(glm::mat4(1.0f), scaling);
    }

    void pushTransform()
    {
        transformStack.push(transformStack.top());
    }

    void popTransform()
    {
        transformStack.pop();
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
            if (!intersect(lightRay))
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
