#include <glm/glm.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers
{

    class RCK_API vec2
    {

    public:
        // Constructor
        vec2(float x = 0.0f, float y = 0.0f);
        vec2(glm::vec2 vector);

        //individual positional components
        float x = 0.0f;
        float y = 0.0f;

        // colour alternatives
        float r = 0.0f;
        float g = 0.0f;

        // Getters
        float GetX() const;
        float GetY() const;

        float GetR() const;
        float GetG() const;

        // Setters
        void SetX(float x);
        void SetY(float y);

        void SetR(float r);
        void SetG(float g);

        // Operators
        vec2 operator+(const vec2& other) const;
        vec2 operator-(const vec2& other) const;
        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2 operator*(float scalar) const;
        vec2& operator*=(float scalar);

        bool operator==(const vec2& other) const;
        bool operator!=(const vec2& other) const;

        // Length
        float Length() const;

    private:
        glm::vec2 vec;
    };
}