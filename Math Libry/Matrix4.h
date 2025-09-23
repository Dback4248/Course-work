#pragma once
#include <cmath>
#include "Vector4.h"

namespace MathClasses
{
    class Matrix4
    {
    public:
        float m[4][4]; // Row-major order

        // Default constructor: Identity matrix
        Matrix4()
        {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
        }

        // Constructor with 16 floats (row-major)
        Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33)
        {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
            m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }

        // Matrix * Matrix
        Matrix4 operator*(const Matrix4& rhs) const
        {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    result.m[i][j] = 0.0f;
                    for (int k = 0; k < 4; k++)
                    {
                        result.m[i][j] += m[i][k] * rhs.m[k][j];
                    }
                }
            }
            return result;
        }

        // Matrix * Vector4
        Vector4 operator*(const Vector4& v) const
        {
            return Vector4(
                m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
                m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
            );
        }

        // Transpose
        Matrix4 Transpose() const
        {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    result.m[i][j] = m[j][i];
            return result;
        }

        // Determinant (expansion by minors)
        float Determinant() const
        {
            float det =
                m[0][0] * (
                    m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                    m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
                    m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
                    )
                - m[0][1] * (
                    m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
                    m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
                    m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
                    )
                + m[0][2] * (
                    m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
                    m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
                    m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
                    )
                - m[0][3] * (
                    m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
                    m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) +
                    m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
                    );

            return det;
        }

        // Inverse (Gauss-Jordan elimination)
        Matrix4 Inverse() const
        {
            Matrix4 inv;
            Matrix4 a = *this;

            // Initialize as identity
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    inv.m[i][j] = (i == j) ? 1.0f : 0.0f;

            // Gaussian elimination
            for (int i = 0; i < 4; i++)
            {
                float pivot = a.m[i][i];
                if (fabs(pivot) < 1e-6f) return Matrix4(); // return identity if singular

                float invPivot = 1.0f / pivot;
                for (int j = 0; j < 4; j++)
                {
                    a.m[i][j] *= invPivot;
                    inv.m[i][j] *= invPivot;
                }

                for (int k = 0; k < 4; k++)
                {
                    if (k == i) continue;
                    float factor = a.m[k][i];
                    for (int j = 0; j < 4; j++)
    {
                        a.m[k][j] -= factor * a.m[i][j];
                        inv.m[k][j] -= factor * inv.m[i][j];
                    }
                }
            }
            return inv;
        }
    };
}
