#include <glm/glm.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers 
{

    class RCK_API vec4 
    {

    public:
        // Constructor
        vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
        vec4(glm::vec4 vector);

        //individual positional components
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        // colour alternatives
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;

        // Getters
        float GetX() const;
        float GetY() const;
        float GetZ() const;
        float GetW() const;

        float GetR() const;
        float GetG() const;
        float GetB() const;
        float GetA() const;

        // Setters
        void SetX(float x);
        void SetY(float y);
        void SetZ(float z);
        void SetW(float w);

        void SetR(float r);
        void SetG(float g);
        void SetB(float b);
        void SetA(float a);

        // Operators
        vec4 operator+(const vec4& other) const;
        vec4 operator-(const vec4& other) const;
        vec4& operator+=(const vec4& other);
        vec4& operator-=(const vec4& other);
        vec4 operator*(float scalar) const;
        vec4& operator*=(float scalar);

        bool operator==(const vec4& other) const;
        bool operator!=(const vec4& other) const;

        // Length
        float Length() const;

    private:
        glm::vec4 vec;
    };
}