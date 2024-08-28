#include "vec3.h"

namespace DLL_WRAPPERS {

    vec3::vec3(float x, float y, float z)
    {
        vec = glm::vec3(x, y, z);
    }

    vec3::vec3(glm::vec3 vector)
    {
        vec = vector;
    }

    float vec3::GetX() const
    {
        return vec.x;
    }

    float vec3::GetY() const
    {
        return vec.y;
    }

    float vec3::GetZ() const
    {
        return vec.z;
    }

    void vec3::SetX(float x)
    {
        vec.x = x;
    }

    void vec3::SetY(float y)
    {
        vec.y = y;
    }

    void vec3::SetZ(float z)
    {
        vec.z = z;
    }

    // Operator Overloads
    vec3 vec3::operator+(const vec3& other) const
    {
        return vec3(vec + other.vec);
    }

    vec3 vec3::operator-(const vec3& other) const
    {
        return vec3(vec - other.vec);
    }

    vec3& vec3::operator+=(const vec3& other)
    {
        vec += other.vec;
        return *this;
    }

    vec3& vec3::operator-=(const vec3& other)
    {
        vec -= other.vec;
        return *this;
    }

    vec3 vec3::operator*(float scalar) const
    {
        return vec3(vec * scalar);
    }

    vec3& vec3::operator*=(float scalar)
    {
        vec *= scalar;
        return *this;
    }

    bool vec3::operator==(const vec3& other) const
    {
        return vec == other.vec;
    }

    bool vec3::operator!=(const vec3& other) const
    {
        return !(*this == other);
    }

    float vec3::Length() const
    {
        return glm::length(vec);
    }
}