#pragma once

#include "General.h"
#include "Sampler.h"
#include "Camera.h"
#include "Ray.h"
#include "Raytracer.h"
#include "Film.h"

struct Scene
{
private:
    // Composition
    Sampler sampler;
    Camera camera;
    Raytracer raytracer;
    Film film;

public:
    // Setters and getters
    void setSize(int width, int height)
    {
        sampler.setSize(width, height);
        camera.setSize(width, height);
        film.setSize(width, height);
    }

    void setMaxDepth(int maxDepth)
    {
        raytracer.setMaxDepth(maxDepth);
    }

    void setOutputFilename(const std::string& outputFilename)
    {
        film.setOutputFilename(outputFilename);
    }

    void setCamera(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& up, float fovy)
    {
        camera.setCamera(lookfrom, lookat, up, fovy);
    }

    // Geometry
    void addSphere(const glm::vec3& center, float radius)
    {
        raytracer.addSphere(center, radius);
    }

    void setMaxVerts(int maxVerts)
    {
        raytracer.setMaxVerts(maxVerts);
    }

    void addVertex(const glm::vec3& vertex)
    {
        raytracer.addVertex(vertex);
    }

    void addTriangle(int A, int B, int C)
    {
        raytracer.addTriangle(A, B, C);
    }

    // Lighting
    void addDirLight(const glm::vec3& dir, const glm::vec3& color)
    {
        raytracer.addDirLight(dir, color);
    }

    void addPointLight(const glm::vec3& point, const glm::vec3& color)
    {
        raytracer.addPointLight(point, color);
    }

    void setAttenuation(const glm::vec3& attenuation)
    {
        raytracer.setAttenuation(attenuation);
    }

    void setAmbient(const glm::vec3& ambient)
    {
        raytracer.setAmbient(ambient);
    }

    // Material properties
    void setDiffuse(const glm::vec3& diffuse)
    {
        raytracer.setDiffuse(diffuse);
    }

    void setSpecular(const glm::vec3& specular)
    {
        raytracer.setSpecular(specular);
    }

    void setShininess(float shininess)
    {
        raytracer.setShininess(shininess);
    }

    void setEmission(const glm::vec3& emission)
    {
        raytracer.setEmission(emission);
    }

    // Transforms
    void translate(const glm::vec3& translation)
    {
        raytracer.translate(translation);
    }

    void rotate(const glm::vec3& axis, float angle)
    {
        raytracer.rotate(axis, angle);
    }

    void scale(const glm::vec3& scaling)
    {
        raytracer.scale(scaling);
    }

    void pushTransform()
    {
        raytracer.pushTransform();
    }

    void popTransform()
    {
        raytracer.popTransform();
    }

    // Operations
    void render()
    {
        glm::vec2 sample;
        Ray ray;
        glm::vec3 color;

        // Loop through all the samples.
        while (sampler.generateSample(&sample))
        {
            camera.generateRay(sample, &ray);
            raytracer.trace(ray, &color);
            film.commit(static_cast<int>(sample[0]), static_cast<int>(sample[1]), color);
        }

        film.saveImage();
    }
};
