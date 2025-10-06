#pragma once
#include <cmath>
#include "Vector3.h"

class Matrix3
{
    public:
    float m[3][3];

    Matrix3()
    {
        // Identity by default
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
        }

    // ----- Factory Methods -----
    static Matrix3 MakeTranslate(float x, float y)
    {
        Matrix3 result;
        result.m[0][2] = x;
        result.m[1][2] = y;
        return result;
        }

    static Matrix3 MakeScale(float sx, float sy)
    {
        Matrix3 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        return result;
        }

    static Matrix3 MakeRotateX(float radians)
    {
        Matrix3 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[1][1] = c;  result.m[1][2] = -s;
        result.m[2][1] = s;  result.m[2][2] = c;
        return result;
        }

    static Matrix3 MakeRotateY(float radians)
    {
        Matrix3 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[0][0] = c;  result.m[0][2] = s;
        result.m[2][0] = -s; result.m[2][2] = c;
        return result;
        }

    static Matrix3 MakeRotateZ(float radians)
    {
        Matrix3 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[0][0] = c;  result.m[0][1] = -s;
        result.m[1][0] = s;  result.m[1][1] = c;
        return result;
        }

    static Matrix3 MakeEuler(float pitch, float yaw, float roll)
    {
        Matrix3 rx = MakeRotateX(pitch);
        Matrix3 ry = MakeRotateY(yaw);
        Matrix3 rz = MakeRotateZ(roll);
        return rz * ry * rx;
                    }

    static Matrix3 MakeEuler(const Vector3& euler)
    {
        return MakeEuler(euler.x, euler.y, euler.z);
        }

    // ----- Operators -----
    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
        );
        }

    Matrix3 operator*(const Matrix3& rhs) const
    {
        Matrix3 result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result.m[i][j] =
                    m[i][0] * rhs.m[0][j] +
                    m[i][1] * rhs.m[1][j] +
                    m[i][2] * rhs.m[2][j];
                }
            }
        return result;
        }
    };

} // namespace MathClasses

