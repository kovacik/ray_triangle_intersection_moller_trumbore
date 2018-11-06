#include <gtest/gtest.h>
#include "triangle.h"

using namespace mathlib;

TEST(TriangleRayIntersectionTest, CenteredTriangleIntersectsAtZero)
{
    Triangle triangle(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

    Vector3 ray_origin(0.0f, 0.0f, -0.6f);
    Vector3 ray_direction(0.0f, 0.0f, 1.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    EXPECT_TRUE(intersects);
    ASSERT_EQ(intersection_point, Vector3(0.0f, 0.0f, 0.0f));
    ASSERT_FLOAT_EQ((intersection_point - ray_origin).Length(), 0.6f);
}

TEST(TriangleRayIntersectionTest, NonCenteredTriangleIntersects)
{
    Triangle triangle(Vector3(2.0f, 0.0f, 0.0f), Vector3(3.5f, 2.2f, 0.0f), Vector3(3.9f, 0.0f, 0.0f));

    Vector3 ray_origin(2.2f, 0.2f, -1.39f);
    Vector3 ray_direction(0.0f, 0.0f, 1.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    EXPECT_TRUE(intersects);
    ASSERT_EQ(intersection_point, Vector3(2.2f, 0.2f, 0.0f));
    ASSERT_FLOAT_EQ((intersection_point - ray_origin).Length(), 1.39f);
}

TEST(TriangleRayIntersectionTest, RayOverlapsTriangle)
{
    Triangle triangle(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f));

    Vector3 ray_origin(0.0f, -1.0f, 0.0f);
    Vector3 ray_direction(0.0f, 1.0f, 0.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    EXPECT_FALSE(intersects);
    ASSERT_EQ(intersection_point, Vector3(0.0f, 0.0f, 0.0f));
}

TEST(TriangleRayIntersectionTest, RayParallelWithTriangle)
{
    Triangle triangle(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 1.0f));

    Vector3 ray_origin(0.0f, -1.0f, 0.0f);
    Vector3 ray_direction(0.0f, 0.0f, 1.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    EXPECT_FALSE(intersects);
    ASSERT_EQ(intersection_point, Vector3(0.0f, 0.0f, 0.0f));

    intersects = triangle.intersectsRay(ray_origin,
                                        -1.0f * ray_direction,
                                        intersection_point);
    EXPECT_FALSE(intersects);
    ASSERT_EQ(intersection_point, Vector3(0.0f, 0.0f, 0.0f));
}

TEST(TriangleRayIntersectionTest, RayOpositeDirectionFromTriangleNoIntersection)
{
    Triangle triangle(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

    Vector3 ray_origin(0.0f, 0.0f, -0.6f);
    Vector3 ray_direction(0.0f, 0.0f, -1.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    EXPECT_FALSE(intersects);
    ASSERT_EQ(intersection_point, Vector3(0.0f, 0.0f, 0.0f));
}