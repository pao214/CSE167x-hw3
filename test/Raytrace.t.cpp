#include <gtest/gtest.h>
#include <Vector.h>
#include <tuple>

class PointTest : public ::testing::TestWithParam<std::tuple<float, float, float>> {};

TEST_P(PointTest, TestConstructor)
{
    float x = std::get<0>(GetParam());
    float y = std::get<1>(GetParam());
    float z = std::get<2>(GetParam());
    Point point{x, y, z};
    ASSERT_NEAR(x, point.x, 10e-6);
    ASSERT_NEAR(y, point.y, 10e-6);
    ASSERT_NEAR(z, point.z, 10e-6);
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
    ASSERT_NEAR(x, point.x, 10e-6);
    ASSERT_NEAR(y, point.y, 10e-6);
    ASSERT_NEAR(z, point.z, 10e-6);
}

INSTANTIATE_TEST_CASE_P(
    VectorConstructorTest,
    VectorTest,
    ::testing::Values(std::make_tuple(3.0f, 4.0f, 5.0f), std::make_tuple(.3f, .4f, .5f))
);
