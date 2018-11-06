#include <iostream>

#include "triangle.h"

using namespace mathlib;

int main(int, char **)
{
    Triangle triangle(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f));

    Vector3 ray_origin(0.5f, 0.0f, -0.6f);
    Vector3 ray_direction(0.0f, 0.0f, 1.0f);

    Vector3 intersection_point;
    bool intersects = triangle.intersectsRay(ray_origin,
                                             ray_direction,
                                             intersection_point);

    std::cout << "=========================================" << std::endl;
    std::cout << "Triangle Ray intersection example" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Ray:          ( origin = " << ray_origin << ", direction = " << ray_direction << " )" << std::endl;
    std::cout << "and triangle: " << triangle << std::endl;

    if (intersects)
    {
        std::cout << "intersect at: " << intersection_point << std::endl;

        float distance = (ray_origin - intersection_point).Length();
        std::cout << "The distance between ray origin and the intersection point: " << distance << std::endl;
    }
}