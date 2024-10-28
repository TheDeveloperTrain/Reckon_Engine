#include "mat3.h"

namespace DLL_wrappers
{
    // Constructors
    mat3::mat3()
    {
        matrix = glm::mat3(1.0f);  // Identity matrix
    }

    mat3::mat3(float diagonal)
    {
        matrix = glm::mat3(diagonal);
    }

    mat3::mat3(const glm::mat3& _matrix)
    {
        matrix = _matrix;
    }

    // Getters and Setters
    float* mat3::GetValues()
    {
        return &matrix[0][0];
    }

    void mat3::SetValues(const glm::mat3& _matrix)
    {
        matrix = _matrix;
    }

    // Operators
    mat3 mat3::operator+(const mat3& other) const
    {
        return mat3(matrix + other.matrix);
    }

    mat3 mat3::operator-(const mat3& other) const
    {
        return mat3(matrix - other.matrix);
    }

    mat3 mat3::operator*(const mat3& other) const
    {
        return mat3(matrix * other.matrix);
    }

    mat3& mat3::operator+=(const mat3& other)
    {
        matrix += other.matrix;
        return *this;
    }

    mat3& mat3::operator-=(const mat3& other)
    {
        matrix -= other.matrix;
        return *this;
    }

    mat3& mat3::operator*=(const mat3& other)
    {
        matrix *= other.matrix;
        return *this;
    }

    mat3 mat3::operator*(float scalar) const
    {
        return mat3(matrix * scalar);
    }

    mat3& mat3::operator*=(float scalar)
    {
        matrix *= scalar;
        return *this;
    }

    bool mat3::operator==(const mat3& other) const
    {
        return matrix == other.matrix;
    }

    bool mat3::operator!=(const mat3& other) const
    {
        return !(*this == other);
    }

    mat3 mat3::Translate(const glm::vec2& translation)
    {
        glm::mat3 result(1.0f);
        result[2][0] = translation.x;
        result[2][1] = translation.y;
        return mat3(result);
    }

    mat3 mat3::Rotate(float angle)
    {
        float radians = glm::radians(angle);
        float cosAngle = cos(radians);
        float sinAngle = sin(radians);

        glm::mat3 result(1.0f);
        result[0][0] = cosAngle;
        result[0][1] = -sinAngle;
        result[1][0] = sinAngle;
        result[1][1] = cosAngle;

        return mat3(result);
    }

    mat3 mat3::Scale(const glm::vec2& scale)
    {
        glm::mat3 result(1.0f);
        result[0][0] = scale.x;
        result[1][1] = scale.y;
        return mat3(result);
    }
}
