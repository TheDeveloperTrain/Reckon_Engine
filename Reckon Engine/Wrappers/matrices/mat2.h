#pragma once
#include <glm/glm.hpp>
#include <ReckonCore.h>

namespace DLL_wrappers
{
    class RCK_API mat2
    {
    public:
        // Constructors
        mat2();  // Identity matrix
        mat2(float diagonal);
        mat2(const glm::mat2& matrix);

        // Getters and Setters
        float* GetValues();
        void SetValues(const glm::mat2& matrix);

        // Operators
        mat2 operator+(const mat2& other) const;
        mat2 operator-(const mat2& other) const;
        mat2 operator*(const mat2& other) const;
        mat2& operator+=(const mat2& other);
        mat2& operator-=(const mat2& other);
        mat2& operator*=(const mat2& other);

        mat2 operator*(float scalar) const;
        mat2& operator*=(float scalar);

        bool operator==(const mat2& other) const;
        bool operator!=(const mat2& other) const;

    private:
        glm::mat2 matrix;
    };
}
