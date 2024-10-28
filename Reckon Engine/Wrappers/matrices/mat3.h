#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers
{
    class RCK_API mat3
    {
    public:
        // Constructors
        mat3();  // Identity matrix
        mat3(float diagonal);
        mat3(const glm::mat3& matrix);

        // Getters and Setters
        float* GetValues();
        void SetValues(const glm::mat3& matrix);

        // Operators
        mat3 operator+(const mat3& other) const;
        mat3 operator-(const mat3& other) const;
        mat3 operator*(const mat3& other) const;
        mat3& operator+=(const mat3& other);
        mat3& operator-=(const mat3& other);
        mat3& operator*=(const mat3& other);

        mat3 operator*(float scalar) const;
        mat3& operator*=(float scalar);

        bool operator==(const mat3& other) const;
        bool operator!=(const mat3& other) const;

        // Transformation functions
        mat3 Translate(const glm::vec2& translation);
        mat3 Rotate(float angle);
        mat3 Scale(const glm::vec2& scale);

    private:
        glm::mat3 matrix;
    };
}
