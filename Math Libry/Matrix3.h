#pragma once
#include <cmath>

namespace MathClasses
{

    struct Matrix3
    {
        float m[3][3]{};

        Matrix3() = default;

        Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22)
        {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
        }

        // Identity
        static Matrix3 Identity()
        {
            return Matrix3(
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        // Scale (2D)
        static Matrix3 MakeScale(float sx, float sy)
        {
            return Matrix3(
                sx, 0.0f, 0.0f,
                0.0f, sy, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        // Translation (2D homogeneous)
        static Matrix3 MakeTranslation(float tx, float ty)
        {
            return Matrix3(
                1.0f, 0.0f, tx,
                0.0f, 1.0f, ty,
                0.0f, 0.0f, 1.0f
            );
        }

        // Rotation (around Z in 2D)
        static Matrix3 MakeRotation(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);
            return Matrix3(
                c, -s, 0.0f,
                s, c, 0.0f,
                0.0f, 0.0f, 1.0f
            );
        }

        // Multiply
        Matrix3 operator*(const Matrix3& rhs) const
        {
            Matrix3 result;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result.m[i][j] = 0.0f;
                    for (int k = 0; k < 3; ++k)
                        result.m[i][j] += m[i][k] * rhs.m[k][j];
                }
            }
            return result;
        }
    };

} // namespace MathClasses
