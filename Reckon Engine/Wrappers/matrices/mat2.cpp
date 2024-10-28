#include "mat2.h"

namespace DLL_wrappers
{
    // Constructors
    mat2::mat2()
    {
        matrix = glm::mat2(1.0f);  // Identity matrix
    }

    mat2::mat2(float diagonal)
    {
        matrix = glm::mat2(diagonal);
    }

    mat2::mat2(const glm::mat2& _matrix)
    {
        matrix = _matrix;
    }

    // Getters and Setters
    float* mat2::GetValues()
    {
        return &matrix[0][0];
    }

    void mat2::SetValues(const glm::mat2& _matrix)
    {
        matrix = _matrix;
    }

    // Operators
    mat2 mat2::operator+(const mat2& other) const
    {
        return mat2(matrix + other.matrix);
    }

    mat2 mat2::operator-(const mat2& other) const
    {
        return mat2(matrix - other.matrix);
    }

    mat2 mat2::operator*(const mat2& other) const
    {
        return mat2(matrix * other.matrix);
    }

    mat2& mat2::operator+=(const mat2& other)
    {
        matrix += other.matrix;
        return *this;
    }

    mat2& mat2::operator-=(const mat2& other)
    {
        matrix -= other.matrix;
        return *this;
    }

    mat2& mat2::operator*=(const mat2& other)
    {
        matrix *= other.matrix;
        return *this;
    }

    mat2 mat2::operator*(float scalar) const
    {
        return mat2(matrix * scalar);
    }

    mat2& mat2::operator*=(float scalar)
    {
        matrix *= scalar;
        return *this;
    }

    bool mat2::operator==(const mat2& other) const
    {
        return matrix == other.matrix;
    }

    bool mat2::operator!=(const mat2& other) const
    {
        return !(*this == other);
    }
}
