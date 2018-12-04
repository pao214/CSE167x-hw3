#include <gtest/gtest.h>

#include "General.h"
#include "Sampler.h"
#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Raytracer.h"

TEST(SamplerTest, TestSamples)
{
    Sampler sampler;
    sampler.setSize(2, 3);
    glm::vec2 sample;
    float xs[] = {.5f, 1.5f, .5f, 1.5f, .5f, 1.5f};
    float ys[] = {.5f, .5f, 1.5f, 1.5f, 2.5f, 2.5f};
    for (int i = 0; i < 6; i++)
    {
        sampler.generateSample(sample);
        ASSERT_NEAR(xs[i], sample[0], 1e-6);
        ASSERT_NEAR(ys[i], sample[1], 1e-6);
    }
}

TEST(CameraTest, TestRayGeneration)
{
    Camera camera;
    int width = 60, height = 80;
    camera.setSize(width, height);
    glm::vec3 lookfrom(.0f, .0f, 1.0f);
    glm::vec3 lookat(.0f, .0f, .0f);
    glm::vec3 up(.0f, 1.0f, .0f);
    float fovy = glm::radians(90.0f);
    camera.setCamera(lookfrom, lookat, up, fovy);

    // Test case #1 +x
    {
        glm::vec2 sample(60.0f, 40.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], 3.0f/5, 1e-6);
        ASSERT_NEAR(ray.getDir()[1], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/5, 1e-6);
    }

    // Test case #2 -x
    {
        glm::vec2 sample(.0f, 40.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], -3.0f/5, 1e-6);
        ASSERT_NEAR(ray.getDir()[1], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/5, 1e-6);
    }

    // Test case #3 +y
    {
        glm::vec2 sample(30.0f, 80.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[1], 1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -1.0f/glm::sqrt(2), 1e-6);
    }

    // Test case #4 -y
    {
        glm::vec2 sample(30.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[1], -1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -1.0f/glm::sqrt(2), 1e-6);
    }

    // Test case #5 +x+y
    {
        glm::vec2 sample(60.0f, 80.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], 3.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[1], 4.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/glm::sqrt(41), 1e-6);
    }

    // Test case #6 -x-y
    {
        glm::vec2 sample(.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], -3.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[1], -4.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/glm::sqrt(41), 1e-6);
    }

    // Test case #7 +x-y
    {
        glm::vec2 sample(60.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], 3.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[1], -4.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/glm::sqrt(41), 1e-6);
    }

    // Test case #8 -x+y
    {
        glm::vec2 sample(.0f, 80.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], -3.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[1], 4.0f/glm::sqrt(41), 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -4.0f/glm::sqrt(41), 1e-6);
    }

    // Test case #9 0x0y
    {
        glm::vec2 sample(30.0f, 40.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.getPoint()[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.getPoint()[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.getPoint()[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.getDir()[0], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[1], .0f, 1e-6);
        ASSERT_NEAR(ray.getDir()[2], -1.0f, 1e-6);
    }
}

TEST(SphereTest, TestIntersect)
{
    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 1.0f};
        Ray ray{glm::vec3(.0f, .0f, 2.0f), glm::vec3(.0f, .0f, -1.0f)};
        float t;
        ASSERT_TRUE(sphere.intersect(ray, t));
        ASSERT_NEAR(t, 1.0f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(3.0f/5.0f, .0f, -4.0f/5)};
        float t;
        ASSERT_TRUE(sphere.intersect(ray, t));
        ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(-3.0f/5.0f, .0f, -4.0f/5)};
        float t;
        ASSERT_TRUE(sphere.intersect(ray, t));
        ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, -3.0f/5.0f, -4.0f/5)};
        float t;
        ASSERT_TRUE(sphere.intersect(ray, t));
        ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, 3.0f/5.0f, -4.0f/5)};
        float t;
        ASSERT_TRUE(sphere.intersect(ray, t));
        ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::normalize(glm::vec3(5.0f, .0f, -4.0f))};
        float t;
        ASSERT_FALSE(sphere.intersect(ray, t));
    }
}

TEST(TriangleTest, TestIntersect)
{
    {
        Triangle triangle{
            glm::vec3(1.0f, .0f, .0f),
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec3(.0f, .0f, 1.0f)
        };
        Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))};
        float t;
        ASSERT_TRUE(triangle.intersect(ray, t));
        ASSERT_NEAR(t, 1.0f/glm::sqrt(3.0f), 1e-6);
    }

    {
        Triangle triangle{
            glm::vec3(1.0f, .0f, .0f),
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec3(.0f, .0f, 1.0f)
        };
        Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(.4f, .4f, .2f))};
        float t;
        ASSERT_TRUE(triangle.intersect(ray, t));
        ASSERT_NEAR(t, .6f, 1e-6);
    }

    {
        Triangle triangle{
            glm::vec3(1.0f, .0f, .0f),
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec3(.0f, .0f, 1.0f)
        };
        Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.4f, .4f, -0.8f))};
        float t;
        ASSERT_FALSE(triangle.intersect(ray, t));
    }
}

TEST(RaytracerTest, TestIntersection)
{
    Raytracer raytracer;
    raytracer.addSphere(glm::vec3(1.0f, .0f, .0f), 1.0f);
    raytracer.addSphere(glm::vec3(-1.0f, .0f, .0f), 1.0f);
    glm::vec3 color;

    // Test case #1 (.0f, .0f, 1.0f), (1.0f, .0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(1.0f, .0f, -1.0f))};
        raytracer.trace(ray, color);
        ASSERT_NEAR(color[0], 1.0f, 1e-6);
        ASSERT_NEAR(color[1], .0f, 1e-6);
        ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #2 (.0f, .0f, 1.0f), (-1.0f, .0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(-1.0f, .0f, -1.0f))};
        raytracer.trace(ray, color);
        ASSERT_NEAR(color[0], 1.0f, 1e-6);
        ASSERT_NEAR(color[1], .0f, 1e-6);
        ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #3 (.0f, .0f, 1.0f), (.0f, 1.0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(.0f, 1.0f, -1.0f))};
        raytracer.trace(ray, color);
        ASSERT_NEAR(color[0], .0f, 1e-6);
        ASSERT_NEAR(color[1], .0f, 1e-6);
        ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #4 (.0f, .0f, 1.0f), (.0f, -1.0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(.0f, -1.0f, -1.0f))};
        raytracer.trace(ray, color);
        ASSERT_NEAR(color[0], .0f, 1e-6);
        ASSERT_NEAR(color[1], .0f, 1e-6);
        ASSERT_NEAR(color[2], .0f, 1e-6);
    }
}


