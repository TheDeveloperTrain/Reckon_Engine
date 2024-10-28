#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers
{
    class RCK_API mat4
    {
    public:
        // Constructors
        mat4();  // Identity matrix
        mat4(float diagonal);
        mat4(const glm::mat4& matrix);

        // Getters and Setters
        float* GetValues();
        void SetValues(const glm::mat4& matrix);

        // Operators
        mat4 operator+(const mat4& other) const;
        mat4 operator-(const mat4& other) const;
        mat4 operator*(const mat4& other) const;
        mat4& operator+=(const mat4& other);
        mat4& operator-=(const mat4& other);
        mat4& operator*=(const mat4& other);

        mat4 operator*(float scalar) const;
        mat4& operator*=(float scalar);

        bool operator==(const mat4& other) const;
        bool operator!=(const mat4& other) const;

        // Transformation functions
        mat4 Translate(const glm::vec3& translation);
        mat4 Rotate(float angle, const glm::vec3& axis);
        mat4 Scale(const glm::vec3& scale);

    private:
        glm::mat4 matrix;
    };
}
