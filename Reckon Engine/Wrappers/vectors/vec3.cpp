#include "vec3.h"

namespace DLL_wrappers {

    vec3::vec3(float _x, float _y, float _z)
    {
        vec = glm::vec3(x, y, z);
        x = _x;
        y = _y;
        z = _z;
    }

    vec3::vec3(glm::vec3 vector)
    {
        vec = vector;
        x = vector.x;
        y = vector.y;
        z = vector.z;
    }

    float vec3::GetX() const
    {
        return x;
    }

    float vec3::GetY() const
    {
        return y;
    }

    float vec3::GetZ() const
    {
        return z;
    }

    float vec3::GetR() const
    {
        return r;
    }

    float vec3::GetG() const
    {
        return g;
    }

    float vec3::GetB() const
    {
        return b;
    }

    void vec3::SetX(float _x)
    {
        vec.x = _x;
        x = _x;

    }

    void vec3::SetY(float _y)
    {
        vec.y = _y;
        y = _y;
    }

    void vec3::SetZ(float _z)
    {
        vec.z = _z;
        z = _z;
    }

    void vec3::SetR(float _r)
    {
        vec.r = _r;
        r = _r;
        x = _r;
    }

    void vec3::SetG(float _g)
    {
        vec.g = _g;
        g = _g;
        y = _g;
    }

    void vec3::SetB(float _b)
    {
        vec.b = _b;
        b = _b;
        z = _b;
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