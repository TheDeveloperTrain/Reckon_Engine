#include <glm/glm.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers
{

    class RCK_API vec3
    {

    public:
        // Constructor
        vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        vec3(glm::vec3 vector);

        //individual positional components
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // colour alternatives
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;

        // Getters
        float GetX() const;
        float GetY() const;
        float GetZ() const;

        float GetR() const;
        float GetG() const;
        float GetB() const;

        // Setters
        void SetX(float x);
        void SetY(float y);
        void SetZ(float z);

        void SetR(float r);
        void SetG(float g);
        void SetB(float b);

        // Operators
        vec3 operator+(const vec3& other) const;
        vec3 operator-(const vec3& other) const;
        vec3& operator+=(const vec3& other);
        vec3& operator-=(const vec3& other);
        vec3 operator*(float scalar) const;
        vec3& operator*=(float scalar);

        bool operator==(const vec3& other) const;
        bool operator!=(const vec3& other) const;

        // Length
        float Length() const;

    private:
        glm::vec3 vec;
    };
}