#include <glm/glm.hpp>
#include <ReckonCore.h>

namespace DLL_WRAPPERS
{

    class RCK_API vec3
    {

    public:
        // Constructor
        vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        vec3(glm::vec3 vector);

        // Getters
        float GetX() const;
        float GetY() const;
        float GetZ() const;

        // Setters
        void SetX(float x);
        void SetY(float y);
        void SetZ(float z);

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