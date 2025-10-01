#pragma once
#include <cmath>

namespace MathClasses
{
    class Matrix3
    {
        float m[3][3];

        // Constructor
        Matrix3(float m00 = 1, float m01 = 0, float m02 = 0,
            float m10 = 0, float m11 = 1, float m12 = 0,
            float m20 = 0, float m21 = 0, float m22 = 1)
        {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
        }

        // --------------------------
        // TRANSLATION
        // --------------------------
        static Matrix3 MakeTranslation(float x, float y, float z)
        {
            return Matrix3(
                1, 0, x,
                0, 1, y,
                0, 0, 1   // z ignored in 3x3
            );
        }

        static Matrix3 MakeTranslation(const Vector3& vec)
        {
            return Matrix3(
                1, 0, vec.x,
                0, 1, vec.y,
                0, 0, 1   // z ignored in 3x3
            );
        }

        // ✅ NEW 2D Overload
        static Matrix3 MakeTranslation(float x, float y)
            {
            return Matrix3(
                1, 0, x,
                0, 1, y,
                0, 0, 1
            );
        }

        // --------------------------
        // ROTATION
        // --------------------------
        static Matrix3 MakeRotateX(float a)
                {
            return Matrix3(
                1, 0, 0,
                0, cosf(a), -sinf(a),
                0, sinf(a), cosf(a)
            );
        }

        static Matrix3 MakeRotateY(float a)
                    {
            return Matrix3(
                cosf(a), 0, sinf(a),
                0, 1, 0,
                -sinf(a), 0, cosf(a)
            );
        }

        static Matrix3 MakeRotateZ(float a)
        {
            return Matrix3(
                cosf(a), -sinf(a), 0,
                sinf(a), cosf(a), 0,
                0, 0, 1
            );
                }

        static Matrix3 MakeEuler(float pitch, float yaw, float roll)
                {
            return MakeRotateX(pitch) * MakeRotateY(yaw) * MakeRotateZ(roll);
        }

        static Matrix3 MakeEuler(const Vector3& rot)
        {
            return MakeEuler(rot.x, rot.y, rot.z);
        }

        // --------------------------
        // SCALE
        // --------------------------
        static Matrix3 MakeScale(float xScale, float yScale)
                    {
            return Matrix3(
                xScale, 0, 0,
                0, yScale, 0,
                0, 0, 1
            );
                    }

        static Matrix3 MakeScale(float xScale, float yScale, float zScale)
        {
            return Matrix3(
                xScale, 0, 0,
                0, yScale, 0,
                0, 0, 1   // z ignored in 3x3
            );
        }

        static Matrix3 MakeScale(const Vector3& scale)
        {
            return MakeScale(scale.x, scale.y, scale.z);
        }

        // --------------------------
        // MATRIX MULTIPLICATION
        // --------------------------
        Matrix3 operator*(const Matrix3& rhs) const
        {
            Matrix3 result;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
        {
                    result.m[i][j] = m[i][0] * rhs.m[0][j] +
                        m[i][1] * rhs.m[1][j] +
                        m[i][2] * rhs.m[2][j];
                }
            }
            return result;
        }
    };
