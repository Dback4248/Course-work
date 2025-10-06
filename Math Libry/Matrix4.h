#pragma once
#include <cmath>
#include "Vector3.h"
#include "Vector4.h"

class Matrix4
{
    public:
    float m[4][4];

    Matrix4()
    {
        // Identity by default
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
        }

    // ----- Factory Methods -----
    static Matrix4 MakeTranslate(float x, float y, float z)
    {
        Matrix4 result;
        result.m[0][3] = x;
        result.m[1][3] = y;
        result.m[2][3] = z;
        return result;
    }

    static Matrix4 MakeScale(float sx, float sy, float sz)
    {
        Matrix4 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        return result;
    }

    static Matrix4 MakeRotateX(float radians)
    {
        Matrix4 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[1][1] = c;  result.m[1][2] = -s;
        result.m[2][1] = s;  result.m[2][2] = c;
        return result;
    }

    static Matrix4 MakeRotateY(float radians)
    {
        Matrix4 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[0][0] = c;  result.m[0][2] = s;
        result.m[2][0] = -s; result.m[2][2] = c;
        return result;
                }

    static Matrix4 MakeRotateZ(float radians)
    {
        Matrix4 result;
        float c = cosf(radians), s = sinf(radians);
        result.m[0][0] = c;  result.m[0][1] = -s;
        result.m[1][0] = s;  result.m[1][1] = c;
        return result;
            }

    static Matrix4 MakeEuler(float pitch, float yaw, float roll)
    {
        Matrix4 rx = MakeRotateX(pitch);
        Matrix4 ry = MakeRotateY(yaw);
        Matrix4 rz = MakeRotateZ(roll);
        return rz * ry * rx;
        }

    static Matrix4 MakeEuler(const Vector3& euler)
    {
        return MakeEuler(euler.x, euler.y, euler.z);
        }

    // ----- Operators -----
    Vector4 operator*(const Vector4& v) const
    {
        return Vector4(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
            m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
        );
        }

    Matrix4 operator*(const Matrix4& rhs) const
    {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.m[i][j] =
                    m[i][0] * rhs.m[0][j] +
                    m[i][1] * rhs.m[1][j] +
                    m[i][2] * rhs.m[2][j] +
                    m[i][3] * rhs.m[3][j];
            }
        }
        return result;
}
    };

