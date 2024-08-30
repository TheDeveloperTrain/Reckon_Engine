#include "vec4.h"

namespace DLL_wrappers {

    vec4::vec4(float _x, float _y, float _z, float _w) 
    {
        vec = glm::vec4(x, y, z, w);
        x = _x;
        y = _y;
        z = _z;
        w = _w;


        r = _x;
        g = _y;
        b = _z;
        a = _w;
    }

    vec4::vec4(glm::vec4 vector)
    {
        vec = vector;
        x = vector.x;
        y = vector.y;
        z = vector.z;
        w = vector.w;

        r = vector.x;
        g = vector.y;
        b = vector.z;
        a = vector.w;
    }

    float vec4::GetX() const
    {
        return x; 
    }

    float vec4::GetY() const 
    {
        return y; 
    }

    float vec4::GetZ() const 
    {
        return z; 
    }

    float vec4::GetW() const 
    {
        return w; 
    }

    float vec4::GetR() const
    {
        return r;
    }

    float vec4::GetG() const
    {
        return g;
    }

    float vec4::GetB() const
    {
        return b;
    }

    float vec4::GetA() const
    {
        return a;
    }

    void vec4::SetX(float _x) 
    {
        vec.x = _x; 
        x = _x;
        r = _x;

    }

    void vec4::SetY(float _y) 
    {
        vec.y = _y; 
        y = _y;
        g = _y;
    }

    void vec4::SetZ(float _z) 
    {
        vec.z = _z; 
        z = _z;
        b = _z;
    }

    void vec4::SetW(float _w) 
    {
        vec.w = _w; 
        w = _w;
        a = _w;
    }

    void vec4::SetR(float _r)
    {
        vec.r = _r;
        r = _r;
        x = _r;
    }

    void vec4::SetG(float _g)
    {
        vec.g = _g;
        g = _g;
        y = _g;
    }

    void vec4::SetB(float _b)
    {
        vec.b = _b;
        b = _b;
        z = _b;
    }

    void vec4::SetA(float _a)
    {
        vec.a = _a;
        a = _a;
        w = _a;
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