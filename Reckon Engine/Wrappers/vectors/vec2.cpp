#include "vec2.h"

namespace DLL_wrappers {

    vec2::vec2(float x, float y)
    {
        vec = glm::vec2(x, y);
    }

    vec2::vec2(glm::vec2 vector)
    {
        vec = vector;
    }

    float vec2::GetX() const
    {
        return vec.x;
    }

    float vec2::GetY() const
    {
        return vec.y;
    }

    float vec2::GetR() const
    {
        return r;
    }

    float vec2::GetG() const
    {
        return g;
    }

    void vec2::SetX(float x)
    {
        vec.x = x;
    }

    void vec2::SetY(float y)
    {
        vec.y = y;
    }

    void vec2::SetR(float _r)
    {
        vec.r = _r;
        r = _r;
        x = _r;
    }

    void vec2::SetG(float _g)
    {
        vec.g = _g;
        g = _g;
        y = _g;
    }

    // Operator Overloads
    vec2 vec2::operator+(const vec2& other) const
    {
        return vec2(vec + other.vec);
    }

    vec2 vec2::operator-(const vec2& other) const
    {
        return vec2(vec - other.vec);
    }

    vec2& vec2::operator+=(const vec2& other)
    {
        vec += other.vec;
        return *this;
    }

    vec2& vec2::operator-=(const vec2& other)
    {
        vec -= other.vec;
        return *this;
    }

    vec2 vec2::operator*(float scalar) const
    {
        return vec2(vec * scalar);
    }

    vec2& vec2::operator*=(float scalar)
    {
        vec *= scalar;
        return *this;
    }

    bool vec2::operator==(const vec2& other) const
    {
        return vec == other.vec;
    }

    bool vec2::operator!=(const vec2& other) const
    {
        return !(*this == other);
    }

    float vec2::Length() const
    {
        return glm::length(vec);
    }
}