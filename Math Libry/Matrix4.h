#pragma once
#include <cmath>

namespace MathClasses
{

    struct Matrix4
    {
        float m[4][4]{};

        Matrix4() = default;

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

        // Identity
        static Matrix4 Identity()
        {
            return Matrix4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Scale
        static Matrix4 MakeScale(float sx, float sy, float sz)
        {
            return Matrix4(
                sx, 0.0f, 0.0f, 0.0f,
                0.0f, sy, 0.0f, 0.0f,
                0.0f, 0.0f, sz, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Translation
        static Matrix4 MakeTranslation(float tx, float ty, float tz)
        {
            return Matrix4(
                1.0f, 0.0f, 0.0f, tx,
                0.0f, 1.0f, 0.0f, ty,
                0.0f, 0.0f, 1.0f, tz,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Rotation X
        static Matrix4 MakeRotateX(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);
            return Matrix4(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, c, -s, 0.0f,
                0.0f, s, c, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Rotation Y
        static Matrix4 MakeRotateY(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);
            return Matrix4(
                c, 0.0f, s, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                -s, 0.0f, c, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Rotation Z
        static Matrix4 MakeRotateZ(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);
            return Matrix4(
                c, -s, 0.0f, 0.0f,
                s, c, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
        }

        // Euler: pitch = X, yaw = Y, roll = Z
        // Uses convention: R = Rz * Ry * Rx
        static Matrix4 MakeEuler(float pitch, float yaw, float roll)
        {
            Matrix4 rx = MakeRotateX(pitch);
            Matrix4 ry = MakeRotateY(yaw);
            Matrix4 rz = MakeRotateZ(roll);
            return rz * ry * rx;
        }

        // Multiply
        Matrix4 operator*(const Matrix4& rhs) const
        {
            Matrix4 result;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    result.m[i][j] = 0.0f;
                    for (int k = 0; k < 4; ++k)
                        result.m[i][j] += m[i][k] * rhs.m[k][j];
                }
            }
            return result;
        }
    };

} // namespace MathClasses
