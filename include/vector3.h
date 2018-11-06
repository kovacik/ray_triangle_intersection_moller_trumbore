#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <iomanip>
#include <math.h>

namespace mathlib
{

class Vector3
{
  private:
    float x_;
    float y_;
    float z_;

  public:
    Vector3() : x_(0.0f), y_(0.0f), z_(0.0f) {}

    Vector3(float x, float y, float z)
    {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
     * @brief Calculates the cross product with given vector.
     *
     * @param vector The vector to perform cross product with.
     * @return The cross product with given vector.
     */
    Vector3 CrossProduct(const Vector3 &vector) const
    {
        return Vector3(y_ * vector.z_ - z_ * vector.y_,
                       z_ * vector.x_ - x_ * vector.z_,
                       x_ * vector.y_ - y_ * vector.x_);
    }

    /**
     * @brief Calculates the dot product with given vector.
     *
     * @param vector The vector to perform dot product with.
     * @return The dot product with given vector.
     */
    float DotProduct(const Vector3 &vector) const
    {
        return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
    }

    /**
     * @brief Returns length of the vector.
     *
     * @return The length.
     */
    float Length() const
    {
        return sqrt(this->DotProduct(*this));
    }

    Vector3 operator-(const Vector3 &vector) const
    {
        return Vector3(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_);
    }

    Vector3 operator+(const Vector3 &vector) const
    {
        return Vector3(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_);
    }

    Vector3 operator*(float multiplier) const
    {
        return Vector3(x_ * multiplier, y_ * multiplier, z_ * multiplier);
    }

    bool operator==(const Vector3 &vector) const
    {
        constexpr float EPSILON = 0.000001;
        return (abs(x_ - vector.x_) < EPSILON) && (abs(y_ - vector.y_) < EPSILON) && (abs(z_ - vector.z_) < EPSILON);
    }

    float GetX() const { return x_; }
    float GetY() const { return y_; }
    float GetZ() const { return z_; }
};

Vector3 operator*(float multiplier, const Vector3 &vector)
{
    return vector * multiplier;
}

static std::ostream &operator<<(std::ostream &stream, const Vector3 &vertex)
{
    stream << std::setprecision(8) << std::fixed << std::showpoint;
    stream << "[" << vertex.GetX() << ", " << vertex.GetY() << ", " << vertex.GetZ() << "]";
    return stream;
}

} // namespace mathlib

#endif // __VECTOR3_H__