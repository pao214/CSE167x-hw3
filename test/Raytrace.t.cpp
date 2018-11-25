#include <gtest/gtest.h>

#include "General.h"
#include "Sampler.h"
#include "Camera.h"

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
    int width = 100, height = 100;
    camera.setSize(width, height);
    glm::vec3 lookfrom(.0f, .0f, 1.0f);
    glm::vec3 lookat(.0f, .0f, .0f);
    glm::vec3 up(.0f, 1.0f, .0f);
    float fovy = glm::radians(90.0f);
    camera.setCamera(lookfrom, lookat, up, fovy);

    // Test case #1 +x
    {
        glm::vec2 sample(100.0f, 50.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], 1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.dir[1], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(2), 1e-6);
    }

    // Test case #2 -x
    {
        glm::vec2 sample(.0f, 50.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], -1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.dir[1], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(2), 1e-6);
    }

    // Test case #3 +y
    {
        glm::vec2 sample(50.0f, 100.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[1], 1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(2), 1e-6);
    }

    // Test case #4 -y
    {
        glm::vec2 sample(50.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[1], -1.0f/glm::sqrt(2), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(2), 1e-6);
        /* assert_near(ray.point, lookfrom); */
        /* assert_near(ray.dir, glm::vec3(.0f, -1.0f/glm::sqrt(2), -1.0f/glm::sqrt(2))); */
    }

    // Test case #5 +x+y
    {
        glm::vec2 sample(100.0f, 100.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], 1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[1], 1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(3), 1e-6);
    }

    // Test case #6 -x-y
    {
        glm::vec2 sample(.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], -1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[1], -1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(3), 1e-6);
    }

    // Test case #7 +x-y
    {
        glm::vec2 sample(100.0f, .0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], 1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[1], -1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(3), 1e-6);
    }

    // Test case #8 -x+y
    {
        glm::vec2 sample(.0f, 100.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], -1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[1], 1.0f/glm::sqrt(3), 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f/glm::sqrt(3), 1e-6);
    }

    // Test case #9 0x0y
    {
        glm::vec2 sample(50.0f, 50.0f);
        Ray ray;
        camera.generateRay(sample, ray);
        ASSERT_NEAR(ray.point[0], lookfrom[0], 1e-6);
        ASSERT_NEAR(ray.point[1], lookfrom[1], 1e-6);
        ASSERT_NEAR(ray.point[2], lookfrom[2], 1e-6);
        ASSERT_NEAR(ray.dir[0], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[1], .0f, 1e-6);
        ASSERT_NEAR(ray.dir[2], -1.0f, 1e-6);
    }
}

/*
class PointTest : public ::testing::TestWithParam<std::tuple<float, float, float>> {};

TEST_P(PointTest, TestConstructor)
{
    float x = std::get<0>(GetParam());
    float y = std::get<1>(GetParam());
    float z = std::get<2>(GetParam());
    Point point{x, y, z};
    ASSERT_NEAR(x, point.x, 1e-6);
    ASSERT_NEAR(y, point.y, 1e-6);
    ASSERT_NEAR(z, point.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    PointConstructorTest,
    PointTest,
    ::testing::Values(std::make_tuple(3.0f, 4.0f, 5.0f), std::make_tuple(.3f, .4f, .5f))
);

class VectorTest : public ::testing::TestWithParam<std::tuple<float, float, float>> {};

TEST_P(VectorTest, TestConstructor)
{
    float x = std::get<0>(GetParam());
    float y = std::get<1>(GetParam());
    float z = std::get<2>(GetParam());
    Point point{x, y, z};
    ASSERT_NEAR(x, point.x, 1e-6);
    ASSERT_NEAR(y, point.y, 1e-6);
    ASSERT_NEAR(z, point.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    VectorConstructorTest,
    VectorTest,
    ::testing::Values(std::make_tuple(3.0f, 4.0f, 5.0f), std::make_tuple(.3f, .4f, .5f))
);
*/
