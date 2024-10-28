#include "mat4.h"

namespace DLL_wrappers
{
    // Constructors
    mat4::mat4()
    {
        matrix = glm::mat4(1.0f);  // Identity matrix
    }

    mat4::mat4(float diagonal)
    {
        matrix = glm::mat4(diagonal);
    }

    mat4::mat4(const glm::mat4& _matrix)
    {
        matrix = _matrix;
    }

    // Getters and Setters
    float* mat4::GetValues()
    {
        return &matrix[0][0];
    }

    void mat4::SetValues(const glm::mat4& _matrix)
    {
        matrix = _matrix;
    }

    // Operators
    mat4 mat4::operator+(const mat4& other) const
    {
        return mat4(matrix + other.matrix);
    }

    mat4 mat4::operator-(const mat4& other) const
    {
        return mat4(matrix - other.matrix);
    }

    mat4 mat4::operator*(const mat4& other) const
    {
        return mat4(matrix * other.matrix);
    }

    mat4& mat4::operator+=(const mat4& other)
    {
        matrix += other.matrix;
        return *this;
    }

    mat4& mat4::operator-=(const mat4& other)
    {
        matrix -= other.matrix;
        return *this;
    }

    mat4& mat4::operator*=(const mat4& other)
    {
        matrix *= other.matrix;
        return *this;
    }

    mat4 mat4::operator*(float scalar) const
    {
        return mat4(matrix * scalar);
    }

    mat4& mat4::operator*=(float scalar)
    {
        matrix *= scalar;
        return *this;
    }

    bool mat4::operator==(const mat4& other) const
    {
        return matrix == other.matrix;
    }

    bool mat4::operator!=(const mat4& other) const
    {
        return !(*this == other);
    }

    // Transformation functions
    mat4 mat4::Translate(const glm::vec3& translation)
    {
        return mat4(glm::translate(matrix, translation));
    }

    mat4 mat4::Rotate(float angle, const glm::vec3& axis)
    {
        return mat4(glm::rotate(matrix, glm::radians(angle), axis));
    }

    mat4 mat4::Scale(const glm::vec3& scale)
    {
        return mat4(glm::scale(matrix, scale));
    }
}
