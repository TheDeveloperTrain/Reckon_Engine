#include "vec4.h"

namespace DLL_WRAPPERS {

    vec4::vec4(float x, float y, float z, float w) 
    {
        vec = glm::vec4(x, y, z, w);
    }

    vec4::vec4(glm::vec4 vector)
    {
        vec = vector;
    }

    float vec4::GetX() const
    {
        return vec.x; 
    }

    float vec4::GetY() const 
    {
        return vec.y; 
    }

    float vec4::GetZ() const 
    {
        return vec.z; 
    }

    float vec4::GetW() const 
    {
        return vec.w; 
    }

    void vec4::SetX(float x) 
    {
        vec.x = x; 
    }

    void vec4::SetY(float y) 
    {
        vec.y = y; 
    }

    void vec4::SetZ(float z) 
    {
        vec.z = z; 
    }

    void vec4::SetW(float w) 
    {
        vec.w = w; 
    }

    // Operator Overloads
    vec4 vec4::operator+(const vec4& other) const
    {
        return vec4(vec + other.vec);
    }

    vec4 vec4::operator-(const vec4& other) const 
    {
        return vec4(vec - other.vec);
    }

    vec4& vec4::operator+=(const vec4& other) 
    {
        vec += other.vec;
        return *this;
    }

    vec4& vec4::operator-=(const vec4& other)
    {
        vec -= other.vec;
        return *this;
    }

    vec4 vec4::operator*(float scalar) const 
    {
        return vec4(vec * scalar);
    }

    vec4& vec4::operator*=(float scalar) 
    {
        vec *= scalar;
        return *this;
    }

    bool vec4::operator==(const vec4& other) const 
    {
        return vec == other.vec;
    }

    bool vec4::operator!=(const vec4& other) const 
    {
        return !(*this == other);
    }

    float vec4::Length() const 
    {
        return glm::length(vec);
    }
}