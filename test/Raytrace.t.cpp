#include <gtest/gtest.h>

#include "General.h"
#include "Sampler.h"
#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Raytracer.h"

// FIXME: Add support for different camera configrations.
struct CameraTest : public ::testing::TestWithParam<std::pair<glm::vec2, glm::vec3>>
{
protected:
    Camera camera;
    int width, height;
    glm::vec3 lookfrom;
    glm::vec3 lookat;
    glm::vec3 up;
    float fovy;

    CameraTest():
        width(60), height(80),
        lookfrom(.0f, .0f, 1.0f), lookat(.0f, .0f, .0f), up(.0f, 1.0f, .0f),
        fovy(glm::radians(90.0f))
    {
        camera.setSize(width, height);
        camera.setCamera(lookfrom, lookat, up, fovy);
    }

    void runTestCase(const glm::vec2& sample, const glm::vec3& dir)
    {
        Ray ray;
        camera.generateRay(sample, &ray);
        ASSERT_NEAR(ray.getPoint().x, lookfrom.x, 1e-6);
        ASSERT_NEAR(ray.getPoint().y, lookfrom.y, 1e-6);
        ASSERT_NEAR(ray.getPoint().z, lookfrom.z, 1e-6);
        ASSERT_NEAR(ray.getDir().x, dir.x, 1e-6);
        ASSERT_NEAR(ray.getDir().y, dir.y, 1e-6);
        ASSERT_NEAR(ray.getDir().z, dir.z, 1e-6);
    }
};

TEST_P(CameraTest, GenerateRay)
{
    const auto& param = GetParam();
    runTestCase(param.first, glm::normalize(param.second));
}

INSTANTIATE_TEST_CASE_P(
    TestRayGeneration,
    CameraTest,
    ::testing::Values(
        std::make_pair(glm::vec2{60.0f, 40.0f}, glm::vec3{3.0f, .0f, -4.0f}),
        std::make_pair(glm::vec2{.0f, 40.0f}, glm::vec3{-3.0f, .0f, -4.0f}),
        std::make_pair(glm::vec2{30.0f, 80.0f}, glm::vec3{.0f, 1.0f, -1.0f}),
        std::make_pair(glm::vec2{30.0f, .0f}, glm::vec3{.0f, -1.0f, -1.0f}),
        std::make_pair(glm::vec2{60.0f, 80.0f}, glm::vec3{3.0f, 4.0f, -4.0f}),
        std::make_pair(glm::vec2{.0f, .0f}, glm::vec3{-3.0f, -4.0f, -4.0f}),
        std::make_pair(glm::vec2{60.0f, .0f}, glm::vec3{3.0f, -4.0f, -4.0f}),
        std::make_pair(glm::vec2{.0f, 80.0f}, glm::vec3{-3.0f, 4.0f, -4.0f}),
        std::make_pair(glm::vec2{30.0f, 40.0f}, glm::vec3{.0f, .0f, -1.0f})
    )
);

TEST(SamplerTest, TestSamples)
{
    Sampler sampler;
    sampler.setSize(2, 3);
    glm::vec2 sample;
    float xs[] = {.5f, 1.5f, .5f, 1.5f, .5f, 1.5f};
    float ys[] = {.5f, .5f, 1.5f, 1.5f, 2.5f, 2.5f};
    for (int i = 0; i < 6; i++)
    {
        sampler.generateSample(&sample);
        ASSERT_NEAR(xs[i], sample[0], 1e-6);
        ASSERT_NEAR(ys[i], sample[1], 1e-6);
    }
}

// TODO: Sphere test using transformations.
TEST(SphereTest, TestIntersect)
{
    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 1.0f};
        // Ray ray{glm::vec3(.0f, .0f, 2.0f), glm::vec3(.0f, .0f, -1.0f)};
        // LocalGeo localGeo;
        // ASSERT_TRUE(sphere.intersect(ray, &localGeo));
        // ASSERT_NEAR(t, 1.0f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        // Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(3.0f/5.0f, .0f, -4.0f/5)};
        // float t;
        // ASSERT_TRUE(sphere.intersect(ray, t));
        // ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        // Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(-3.0f/5.0f, .0f, -4.0f/5)};
        // float t;
        // ASSERT_TRUE(sphere.intersect(ray, t));
        // ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        // Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, -3.0f/5.0f, -4.0f/5)};
        // float t;
        // ASSERT_TRUE(sphere.intersect(ray, t));
        // ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        // Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, 3.0f/5.0f, -4.0f/5)};
        // float t;
        // ASSERT_TRUE(sphere.intersect(ray, t));
        // ASSERT_NEAR(t, 1.4f, 1e-6);
    }

    {
        Sphere sphere{glm::vec3(.0f, .0f, .0f), 3.0f};
        // Ray ray{glm::vec3(.0f, .0f, 4.0f), glm::normalize(glm::vec3(5.0f, .0f, -4.0f))};
        // float t;
        // ASSERT_FALSE(sphere.intersect(ray, t));
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
        // Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))};
        // float t;
        // ASSERT_TRUE(triangle.intersect(ray, t));
        // ASSERT_NEAR(t, 1.0f/glm::sqrt(3.0f), 1e-6);
    }

    {
        Triangle triangle{
            glm::vec3(1.0f, .0f, .0f),
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec3(.0f, .0f, 1.0f)
        };
        // Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(.4f, .4f, .2f))};
        // float t;
        // ASSERT_TRUE(triangle.intersect(ray, t));
        // ASSERT_NEAR(t, .6f, 1e-6);
    }

    {
        Triangle triangle{
            glm::vec3(1.0f, .0f, .0f),
            glm::vec3(.0f, 1.0f, .0f),
            glm::vec3(.0f, .0f, 1.0f)
        };
        // Ray ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.4f, .4f, -0.8f))};
        // float t;
        // ASSERT_FALSE(triangle.intersect(ray, t));
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
        // raytracer.trace(ray, color);
        // ASSERT_NEAR(color[0], 1.0f, 1e-6);
        // ASSERT_NEAR(color[1], .0f, 1e-6);
        // ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #2 (.0f, .0f, 1.0f), (-1.0f, .0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(-1.0f, .0f, -1.0f))};
        // raytracer.trace(ray, color);
        // ASSERT_NEAR(color[0], 1.0f, 1e-6);
        // ASSERT_NEAR(color[1], .0f, 1e-6);
        // ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #3 (.0f, .0f, 1.0f), (.0f, 1.0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(.0f, 1.0f, -1.0f))};
        // raytracer.trace(ray, color);
        // ASSERT_NEAR(color[0], .0f, 1e-6);
        // ASSERT_NEAR(color[1], .0f, 1e-6);
        // ASSERT_NEAR(color[2], .0f, 1e-6);
    }

    // Test case #4 (.0f, .0f, 1.0f), (.0f, -1.0f, -1.0f)
    {
        Ray ray{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(.0f, -1.0f, -1.0f))};
        // raytracer.trace(ray, color);
        // ASSERT_NEAR(color[0], .0f, 1e-6);
        // ASSERT_NEAR(color[1], .0f, 1e-6);
        // ASSERT_NEAR(color[2], .0f, 1e-6);
    }
}


