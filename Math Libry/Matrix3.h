#pragma once
#include <cmath>
#include "Vector3.h"

namespace MathClasses
{
    class Matrix3
    {
    public:
        float m[3][3]; // Row-major order

        // Default constructor: Identity matrix
        Matrix3()
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
        }

        // Constructor with 9 floats (row-major)
        Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22)
        {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
        }

        // Matrix * Matrix
        Matrix3 operator*(const Matrix3& rhs) const
        {
            Matrix3 result;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    result.m[i][j] = 0.0f;
                    for (int k = 0; k < 3; k++)
                    {
                        result.m[i][j] += m[i][k] * rhs.m[k][j];
        }
                }
            }
            return result;
        }

        // Matrix * Vector3
        Vector3 operator*(const Vector3& v) const
                {
            return Vector3(
                m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
            );
        }

        // Transpose
        Matrix3 Transpose() const
                    {
            Matrix3 result;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    result.m[i][j] = m[j][i];
            return result;
                    }

        // Determinant
        float Determinant() const
        {
            return
                m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        }

        // Inverse
        Matrix3 Inverse() const
        {
            float det = Determinant();
            if (fabs(det) < 1e-6f)
                return Matrix3(); // return identity if singular

            float invDet = 1.0f / det;

            Matrix3 result;
            result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
            result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
            result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;

            result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
            result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
            result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet;

            result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
            result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet;
            result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

            return result;
        }
    };
}
