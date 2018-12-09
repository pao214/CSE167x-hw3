#include <gtest/gtest.h>

#include "General.h"
#include "Sampler.h"
#include "Camera.h"
#include "Raytracer.h"

// FIXME: Add support for different camera configrations.
struct CameraTest : public ::testing::TestWithParam<std::tuple<glm::vec2, glm::vec3>>
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
};

TEST_P(CameraTest, GenerateRay)
{
    const auto& param = GetParam();
    const auto& sample = std::get<0>(param);
    const auto& expectedDir = glm::normalize(std::get<1>(param));
    Ray ray;
    camera.generateRay(sample, &ray);
    const auto& actualPoint = ray.getPoint();
    const auto& actualDir = ray.getDir();
    const auto& expectedPoint = lookfrom;
    ASSERT_NEAR(actualPoint.x, expectedPoint.x, 1e-6);
    ASSERT_NEAR(actualPoint.y, expectedPoint.y, 1e-6);
    ASSERT_NEAR(actualPoint.z, expectedPoint.z, 1e-6);
    ASSERT_NEAR(actualDir.x, expectedDir.x, 1e-6);
    ASSERT_NEAR(actualDir.y, expectedDir.y, 1e-6);
    ASSERT_NEAR(actualDir.z, expectedDir.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    TestRayGeneration,
    CameraTest,
    ::testing::Values(
        std::make_tuple(glm::vec2{60.0f, 40.0f}, glm::vec3{3.0f, .0f, -4.0f}),
        std::make_tuple(glm::vec2{.0f, 40.0f}, glm::vec3{-3.0f, .0f, -4.0f}),
        std::make_tuple(glm::vec2{30.0f, 80.0f}, glm::vec3{.0f, 1.0f, -1.0f}),
        std::make_tuple(glm::vec2{30.0f, .0f}, glm::vec3{.0f, -1.0f, -1.0f}),
        std::make_tuple(glm::vec2{60.0f, 80.0f}, glm::vec3{3.0f, 4.0f, -4.0f}),
        std::make_tuple(glm::vec2{.0f, .0f}, glm::vec3{-3.0f, -4.0f, -4.0f}),
        std::make_tuple(glm::vec2{60.0f, .0f}, glm::vec3{3.0f, -4.0f, -4.0f}),
        std::make_tuple(glm::vec2{.0f, 80.0f}, glm::vec3{-3.0f, 4.0f, -4.0f}),
        std::make_tuple(glm::vec2{30.0f, 40.0f}, glm::vec3{.0f, .0f, -1.0f})
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
struct SphereTest : public ::testing::TestWithParam<std::tuple<
    Sphere, Ray, bool, LocalGeo
>> {};

TEST_P(SphereTest, Intersect)
{
    const auto& param = GetParam();
    const auto& sphere = std::get<0>(param);
    const auto& ray = std::get<1>(param);
    const auto hit = std::get<2>(param);
    const auto& expected = std::get<3>(param);
    LocalGeo actual;

    // Check return value.
    ASSERT_TRUE(hit == sphere.intersect(ray, &actual));

    // Check intersection point.
    if (!hit) return;
    const auto& actualPoint = actual.getPoint();
    const auto& actualNormal = actual.getNormal();
    const auto& expectedPoint = expected.getPoint();
    const auto& expectedNormal = expected.getNormal();
    ASSERT_NEAR(actualPoint.x, expectedPoint.x, 1e-6);
    ASSERT_NEAR(actualPoint.y, expectedPoint.y, 1e-6);
    ASSERT_NEAR(actualPoint.z, expectedPoint.z, 1e-6);
    ASSERT_NEAR(actualNormal.x, expectedNormal.x, 1e-6);
    ASSERT_NEAR(actualNormal.y, expectedNormal.y, 1e-6);
    ASSERT_NEAR(actualNormal.z, expectedNormal.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    TestIntersect,
    SphereTest,
    ::testing::Values(
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 1.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 2.0f), glm::vec3(.0f, .0f, -1.0f)},
            true,
            LocalGeo{glm::vec3(.0f, .0f, 1.0f), glm::normalize(glm::vec3(.0f, .0f, 1.0f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(3.0f, .0f, -4.0f)},
            true,
            LocalGeo{glm::vec3(.84f, .0f, 2.88f), glm::normalize(glm::vec3(.84f, .0f, 2.88f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(-3.0f, .0f, -4.0f)},
            true,
            LocalGeo{glm::vec3(-0.84f, .0f, 2.88f), glm::normalize(glm::vec3(-0.84f, .0f, 2.88f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, -3.0f, -4.0f)},
            true,
            LocalGeo{glm::vec3(.0f, -0.84f, 2.88f), glm::normalize(glm::vec3(.0f, -0.84f, 2.88f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(.0f, 3.0f, -4.0f)},
            true,
            LocalGeo{glm::vec3(.0f, 0.84f, 2.88f), glm::normalize(glm::vec3(.0f, 0.84f, 2.88f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, 4.0f), glm::vec3(5.0f, .0f, -4.0f)},
            false,
            LocalGeo{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))}
        ),
        std::make_tuple(
            Sphere{glm::vec3(.0f, .0f, .0f), 3.0f, glm::vec3(), Material(), glm::mat4()},
            Ray{glm::vec3(.0f, .0f, .0f), glm::vec3(.0f, .0f, 1.0f)},
            true,
            LocalGeo{glm::vec3(.0f, .0f, 3.0f), glm::normalize(glm::vec3(.0f, .0f, 1.0f))}
        )
    )
);

struct TriangleTest : public ::testing::TestWithParam<std::tuple<
    Triangle, Ray, bool, LocalGeo
>> {};

TEST_P(TriangleTest, Intersect)
{
    const auto& param = GetParam();
    const auto& triangle = std::get<0>(param);
    const auto& ray = std::get<1>(param);
    const auto hit = std::get<2>(param);
    const auto& expected = std::get<3>(param);
    LocalGeo actual;

    // Check return value.
    ASSERT_TRUE(hit == triangle.intersect(ray, &actual));

    // Check intersection point.
    if (!hit) return;
    const auto& actualPoint = actual.getPoint();
    const auto& actualNormal = actual.getNormal();
    const auto& expectedPoint = expected.getPoint();
    const auto& expectedNormal = expected.getNormal();
    ASSERT_NEAR(actualPoint.x, expectedPoint.x, 1e-6);
    ASSERT_NEAR(actualPoint.y, expectedPoint.y, 1e-6);
    ASSERT_NEAR(actualPoint.z, expectedPoint.z, 1e-6);
    ASSERT_NEAR(actualNormal.x, expectedNormal.x, 1e-6);
    ASSERT_NEAR(actualNormal.y, expectedNormal.y, 1e-6);
    ASSERT_NEAR(actualNormal.z, expectedNormal.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    TestIntersect,
    TriangleTest,
    ::testing::Values(
        std::make_tuple(
            Triangle{
                glm::vec3(1.0f, .0f, .0f),
                glm::vec3(.0f, 1.0f, .0f),
                glm::vec3(.0f, .0f, 1.0f),
                glm::vec3(), Material(), glm::mat4()
            },
            Ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))},
            true,
            LocalGeo{
                glm::vec3(1.0f/3, 1.0f/3, 1.0f/3),
                glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))
            }
        ),
        std::make_tuple(
            Triangle{
                glm::vec3(1.0f, .0f, .0f),
                glm::vec3(.0f, 1.0f, .0f),
                glm::vec3(.0f, .0f, 1.0f),
                glm::vec3(), Material(), glm::mat4()
            },
            Ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(.4f, .4f, .2f))},
            true,
            LocalGeo{
                glm::vec3(.4f, .4f, .2f),
                glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))
            }
        ),
        std::make_tuple(
            Triangle{
                glm::vec3(1.0f, .0f, .0f),
                glm::vec3(.0f, 1.0f, .0f),
                glm::vec3(.0f, .0f, 1.0f),
                glm::vec3(), Material(), glm::mat4()
            },
            Ray{glm::vec3(.0f, .0f, .0f), glm::normalize(glm::vec3(1.4f, .4f, -0.8f))},
            false,
            LocalGeo{
                glm::vec3(.0f, .0f, .0f),
                glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f))
            }
        )
    )
);

struct LightTest : public ::testing::TestWithParam<std::tuple<
    std::shared_ptr<Light>, LocalGeo, Ray, glm::vec3
>> {};

TEST_P(LightTest, GenerateLightRay)
{
    const auto& param = GetParam();
    const auto& light = std::get<0>(param);
    const auto& localGeo = std::get<1>(param);
    const auto& expectedRay = std::get<2>(param);
    const auto& expectedColor = std::get<3>(param);
    Ray actualRay;
    glm::vec3 actualColor;
    light->generateLightRay(localGeo, &actualRay, &actualColor);

    // Compare rays
    const auto& actualRayPoint = actualRay.getPoint();
    const auto& actualRayDir = actualRay.getDir();
    const auto actualRayMin = actualRay.getMin();
    const auto& expectedRayPoint = expectedRay.getPoint();
    const auto& expectedRayDir = expectedRay.getDir();
    const auto expectedRayMin = expectedRay.getMin();
    ASSERT_NEAR(actualRayPoint.x, expectedRayPoint.x, 1e-6);
    ASSERT_NEAR(actualRayPoint.y, expectedRayPoint.y, 1e-6);
    ASSERT_NEAR(actualRayPoint.z, expectedRayPoint.z, 1e-6);
    ASSERT_NEAR(actualRayDir.x, expectedRayDir.x, 1e-6);
    ASSERT_NEAR(actualRayDir.y, expectedRayDir.y, 1e-6);
    ASSERT_NEAR(actualRayDir.z, expectedRayDir.z, 1e-6);
    ASSERT_NEAR(actualRayMin, expectedRayMin, 1e-6);

    // Compare colors
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}

INSTANTIATE_TEST_CASE_P(
    TestLightRayGeneration,
    LightTest,
    ::testing::Values(
        std::make_tuple(
            std::make_shared<DirLight>(DirLight{
                glm::vec3(-1.0f, .0f, .0f),
                glm::vec3(1.0f, .0f, .0f)
            }),
            LocalGeo{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, .0f, .0f)},
            Ray{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, .0f, .0f)},
            glm::vec3(1.0f, .0f, .0f)
        ),
        std::make_tuple(
            std::make_shared<DirLight>(DirLight{
                glm::vec3(-1.0f, -1.0f, -1.0f),
                glm::vec3(.5f, .5f, .5f)
            }),
            LocalGeo{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, .0f, .0f)},
            Ray{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f)},
            glm::vec3(.5f, .5f, .5f)
        ),
        std::make_tuple(
            std::make_shared<PointLight>(PointLight{
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, .0f, 1.0f),
                glm::vec3(1.0f, .0f, .0f)
            }),
            LocalGeo{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, .0f, .0f)},
            Ray{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f)},
            glm::vec3(1.0f, .0f, 1.0f)
        ),
        std::make_tuple(
            std::make_shared<PointLight>(PointLight{
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)
            }),
            LocalGeo{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, .0f, .0f)},
            Ray{glm::vec3(.0f, .0f, .0f), glm::vec3(1.0f, 1.0f, 1.0f)},
            glm::vec3(1.0f, 1.0f, 1.0f)/(1.0f+glm::sqrt(3.0f)+3.0f)
        )
    )
);

TEST(RaytracerTest, TestCase1)
{
    Raytracer raytracer;

    // Lighting
    raytracer.addDirLight(glm::vec3(.0f, .0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setAttenuation(glm::vec3(1.0f, .0f, .0f));
    raytracer.setAmbient(glm::vec3(.0f, .0f, .0f));
    
    // Material
    raytracer.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setSpecular(glm::vec3(.0f, .0f, .0f));
    raytracer.setShininess(1.0f);
    raytracer.setEmission(glm::vec3(.0f, .0f, .0f));

    // Geometry
    raytracer.addSphere(glm::vec3(.0f, .0f, .0f), 1.0f);

    // Trace the color
    const Ray ray{glm::vec3(1.0f, .0f, 1.0f/glm::sqrt(2)), glm::vec3(-1.0f, .0f, .0f)};
    const glm::vec3 expectedColor{1.0f/glm::sqrt(2), 1.0f/glm::sqrt(2), 1.0f/glm::sqrt(2)};
    glm::vec3 actualColor;
    raytracer.trace(ray, &actualColor);

    // Compare
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}

TEST(RaytracerTest, TestCase2)
{
    Raytracer raytracer;

    // Lighting
    raytracer.addDirLight(glm::vec3(.0f, .0f, -1.0f), glm::vec3(1.0f, .0f, 1.0f));
    raytracer.setAttenuation(glm::vec3(1.0f, .0f, .0f));
    raytracer.setAmbient(glm::vec3(.0f, .0f, .0f));
    
    // Material
    raytracer.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setSpecular(glm::vec3(.0f, .0f, .0f));
    raytracer.setShininess(1.0f);
    raytracer.setEmission(glm::vec3(.0f, .0f, .0f));

    // Geometry
    raytracer.addSphere(glm::vec3(.0f, .0f, .0f), 1.0f);

    // Trace the color
    const Ray ray{glm::vec3(1.0f, .0f, 1.0f), glm::vec3(-1.0f, .0f, -1.0f)};
    const glm::vec3 expectedColor{1.0f/glm::sqrt(2), .0f, 1.0f/glm::sqrt(2)};
    glm::vec3 actualColor;
    raytracer.trace(ray, &actualColor);

    // Compare
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}

TEST(RaytracerTest, TestCase3)
{
    Raytracer raytracer;

    // Lighting
    raytracer.addDirLight(glm::vec3(.0f, .0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setAttenuation(glm::vec3(1.0f, .0f, .0f));
    raytracer.setAmbient(glm::vec3(.0f, .0f, .0f));
    
    // Material
    raytracer.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setSpecular(glm::vec3(.0f, .0f, .0f));
    raytracer.setShininess(1.0f);
    raytracer.setEmission(glm::vec3(.0f, .0f, .0f));

    // Geometry
    raytracer.addSphere(glm::vec3(.0f, .0f, .0f), 1.0f);

    // Trace the color
    const Ray ray{glm::vec3(.0f, .0f, -2.0f), glm::vec3(.0f, .0f, 1.0f)};
    const glm::vec3 expectedColor{.0f, .0f, .0f};
    glm::vec3 actualColor;
    raytracer.trace(ray, &actualColor);

    // Compare
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}

TEST(RaytracerTest, TestCase4)
{
    Raytracer raytracer;

    // Lighting
    raytracer.addDirLight(glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, 1.0f, 1.0f));
    raytracer.setAttenuation(glm::vec3(1.0f, .0f, .0f));
    raytracer.setAmbient(glm::vec3(.0f, .0f, .0f));
    
    // Material
    raytracer.setDiffuse(glm::vec3(.0f, .0f, .0f));
    raytracer.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setShininess(1.0f);
    raytracer.setEmission(glm::vec3(.0f, .0f, .0f));

    // Geometry
    raytracer.addSphere(glm::vec3(.0f, .0f, .0f), 1.0f);

    // Trace the color
    const Ray ray{glm::vec3(1.0f, .0f, 1.0f/glm::sqrt(2)), glm::vec3(-1.0f, .0f, .0f)};
    const glm::vec3 expectedColor{.0f, 1.0f, 1.0f};
    glm::vec3 actualColor;
    raytracer.trace(ray, &actualColor);

    // Compare
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}

TEST(RaytracerTest, TestCase5)
{
    Raytracer raytracer;

    // Lighting
    raytracer.addDirLight(glm::vec3(.0f, .0f, -1.0f), glm::vec3(1.0f, 1.0f, .0f));
    raytracer.setAttenuation(glm::vec3(1.0f, .0f, .0f));
    raytracer.setAmbient(glm::vec3(.0f, .0f, .0f));
    
    // Material
    raytracer.setDiffuse(glm::vec3(.0f, .0f, .0f));
    raytracer.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    raytracer.setShininess(2.0f);
    raytracer.setEmission(glm::vec3(.0f, .0f, .0f));

    // Geometry
    raytracer.addSphere(glm::vec3(.0f, .0f, .0f), 1.0f);

    // Trace the color
    const Ray ray{glm::vec3(1.0f, .0f, 1.0f), glm::vec3(-1.0f, .0f, .0f)};
    const glm::vec3 expectedColor{1.0f/2, 1.0f/2, .0f};
    glm::vec3 actualColor;
    raytracer.trace(ray, &actualColor);

    // Compare
    ASSERT_NEAR(actualColor.x, expectedColor.x, 1e-6);
    ASSERT_NEAR(actualColor.y, expectedColor.y, 1e-6);
    ASSERT_NEAR(actualColor.z, expectedColor.z, 1e-6);
}
