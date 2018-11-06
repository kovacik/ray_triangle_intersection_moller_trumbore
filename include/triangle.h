#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <iomanip>
#include "vector3.h"

namespace mathlib
{

/* Used by intersection algorithms within this file.
 * Determines precision of when a number is treated as a 0. */
constexpr float EPSILON = 0.0000001;

class Triangle
{
  private:
    Vector3 vertex_0_;
    Vector3 vertex_1_;
    Vector3 vertex_2_;

  public:
    /**
     * @brief Constructs a triangle with clock-wise orientation out of tree 3-coordinate points.
     */
    Triangle(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
    {
        vertex_0_ = v0;
        vertex_1_ = v1;
        vertex_2_ = v2;
    }

    Vector3 getVertex0() const { return vertex_0_; }
    Vector3 getVertex1() const { return vertex_1_; }
    Vector3 getVertex2() const { return vertex_2_; }

    /**
     * @brief Determines intersection point (if any) of the triangle and ray with fixed precision,
     *        irrespectively of triangle facing.
     *
     * Based on: Fast, Minimum Storage Ray/Triangle Intersection; Moller and Trumbore
     * http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
     * 
     * @param      ray_origin          The origin of the Ray.
     * @param      ray_direction       The direction of the Ray.
     * @param[out] intersection_point  Represents the intersection point if existing. Untouched if no intersection found.
     *
     * @return True if the intersection exists at the same time assigns the @a intersection_point and @a distance.
     *         False otherwise, the @a intersection_point and @a distance are left untouched.
     *         If triangle is found to be parallel with the ray, this is assumed as no intersection.
     */
    bool
    intersectsRay(const Vector3 &ray_origin,
                  const Vector3 &ray_direction,
                  Vector3 &intersection_point) const
    {
        // The algorithm is based on solving a linear system of equations defined by
        // equality of any point on triangle represented using barycentric coordinates and a ray formula:
        //
        // (1 - u - v) * V0 + u * V1 + v * V2    =   Origin + t * direction
        //
        // The algorithm uses Cramer's rule to solve the equation.

        // Determine vectors for 2 edges sharing Vertex 0
        Vector3 edge1 = vertex_1_ - vertex_0_;
        Vector3 edge2 = vertex_2_ - vertex_0_;

        Vector3 h = ray_direction.CrossProduct(edge2);
        float determinant = edge1.DotProduct(h);

        // Negative determinant would indicate back facing triangle
        // and could theoretically be ignored and early out.
        // This implementation ignores this and assumes double-sided triangle.
        // Very small determinant means the ray is almost parallel with the triangle plane.
        if (determinant > -EPSILON && determinant < EPSILON)
        {
            return false;
        }

        float inverse_determinant = 1.0 / determinant;

        Vector3 origins_diff_vector = ray_origin - vertex_0_;
        float u = origins_diff_vector.DotProduct(h) * inverse_determinant;

        // Check the u-barycentric coordinate for validity to save further expensive calculations
        if (u < 0.0 || u > 1.0)
        {
            return false;
        }

        Vector3 q = origins_diff_vector.CrossProduct(edge1);
        float v = inverse_determinant * ray_direction.DotProduct(q);

        // Check the v-barycentric coordinate for validity to save further expensive calculations
        if (v < 0.0 || u + v > 1.0)
        {
            return false;
        }

        // At this stage we can compute t to find out where the intersection point is on the line
        float t = inverse_determinant * edge2.DotProduct(q);

        if (t > EPSILON)
        {
            intersection_point = ray_origin + ray_direction * t;
            return true;
        }
        else
        {
            // This means that there is a line intersection but not a ray intersection
            return false;
        }
    }
};

static std::ostream &operator<<(std::ostream &stream, const Triangle &triangle)
{
    stream << std::setprecision(8) << std::fixed << std::showpoint;
    stream << "( V1 = " << triangle.getVertex0() << ", V2 = " << triangle.getVertex1() << ", V3 = " << triangle.getVertex2() << " )";
    return stream;
}

} // namespace mathlib

#endif // __TRIANGLE_H__