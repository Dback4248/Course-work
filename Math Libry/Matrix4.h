#pragma once
#include <cmath>
#include "Vector3.h"

    struct Matrix4
    {
        float m[4][4];

        // Constructors
        Matrix4()
        {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = (i == j ? 1.0f : 0.0f);
        }

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

    static Matrix4 Identity()
    {
        return Matrix4(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    // ----------------------
    // Translation
    // ----------------------
    static Matrix4 MakeTranslation(float x, float y, float z)
    {
        return Matrix4(1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1);
    }

    static Matrix4 MakeTranslation(Vector3 v)
    {
        return MakeTranslation(v.x, v.y, v.z);
    }

    // ----------------------
    // Rotation
    // ----------------------
        static Matrix4 MakeRotateX(float a)
                {
            return Matrix4(
                1, 0, 0, 0,
                0, cosf(a), -sinf(a), 0,
                0, sinf(a), cosf(a), 0,
                0, 0, 0, 1
            );
        }

        static Matrix4 MakeRotateY(float a)
                    {
            return Matrix4(
                cosf(a), 0, sinf(a), 0,
                0, 1, 0, 0,
                -sinf(a), 0, cosf(a), 0,
                0, 0, 0, 1
            );
                    }

        static Matrix4 MakeRotateZ(float a)
        {
            return Matrix4(
                cosf(a), -sinf(a), 0, 0,
                sinf(a), cosf(a), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            );
                }

        static Matrix4 MakeEuler(float pitch, float yaw, float roll)
        {
            Matrix4 rx = MakeRotateX(pitch);
            Matrix4 ry = MakeRotateY(yaw);
            Matrix4 rz = MakeRotateZ(roll);
            return rz * ry * rx;
            }

        static Matrix4 MakeEuler(const Vector3& rot)
        {
            return MakeEuler(rot.x, rot.y, rot.z);
        }

        // --- Scale ---
        static Matrix4 MakeScale(float xScale, float yScale, float zScale)
        {
            return Matrix4(
                xScale, 0, 0, 0,
                0, yScale, 0, 0,
                0, 0, zScale, 0,
                0, 0, 0, 1
            );
        }

        static Matrix4 MakeScale(const Vector3& scale)
        {
            return MakeScale(scale.x, scale.y, scale.z);
        }

        // --- Translation ---
        static Matrix4 MakeTranslation(float x, float y, float z)
        {
            return Matrix4(
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
                    );
        }

        static Matrix4 MakeTranslation(const Vector3& vec)
        {
            return MakeTranslation(vec.x, vec.y, vec.z);
        }

        // --- Operators ---
        Matrix4 operator*(const Matrix4& rhs) const
                {
            Matrix4 result;
            for (int i = 0; i < 4; ++i)
                {
                for (int j = 0; j < 4; ++j)
    {
                    result.m[i][j] = m[i][0] * rhs.m[0][j] +
                        m[i][1] * rhs.m[1][j] +
                        m[i][2] * rhs.m[2][j] +
                        m[i][3] * rhs.m[3][j];
                }
            }
            return result;
        }
    };
}
