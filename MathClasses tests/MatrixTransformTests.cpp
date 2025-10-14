#include "pch.h"
#include <cmath>
#include "CppUnitTest.h"

using namespace MathClasses;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixClassesTests
{
    TEST_CLASS(Matrix3TransformTests)
    {
    public:

        TEST_METHOD(TestIdentity3)
        {
            Matrix3 I = Matrix3::Identity();
            Assert::AreEqual(1.0f, I.m[0][0], 0.0001f);
            Assert::AreEqual(1.0f, I.m[1][1], 0.0001f);
            Assert::AreEqual(1.0f, I.m[2][2], 0.0001f);
        }

        TEST_METHOD(TestTranslation3)
        {
            Matrix3 T = Matrix3::MakeTranslation(3.0f, 5.0f);
            Assert::AreEqual(3.0f, T.m[0][2], 0.0001f);
            Assert::AreEqual(5.0f, T.m[1][2], 0.0001f);
        }

        TEST_METHOD(TestScale3)
        {
            Matrix3 S = Matrix3::MakeScale(2.0f, 4.0f);
            Assert::AreEqual(2.0f, S.m[0][0], 0.0001f);
            Assert::AreEqual(4.0f, S.m[1][1], 0.0001f);
        }

        TEST_METHOD(TestRotate3)
        {
            float angle = 3.14159265f / 2.0f; // 90 degrees
            Matrix3 R = Matrix3::MakeRotation(angle);

            float c = cosf(angle);
            float s = sinf(angle);

            Assert::AreEqual(c, R.m[0][0], 0.001f);
            Assert::AreEqual(-s, R.m[0][1], 0.001f);
            Assert::AreEqual(s, R.m[1][0], 0.001f);
            Assert::AreEqual(c, R.m[1][1], 0.001f);
        }

        TEST_METHOD(TestMultiply3)
        {
            Matrix3 A = Matrix3::MakeScale(2.0f, 3.0f);
            Matrix3 B = Matrix3::MakeTranslation(1.0f, 2.0f);
            Matrix3 C = A * B;

            Assert::AreEqual(2.0f, C.m[0][0], 0.001f);
            Assert::AreEqual(3.0f, C.m[1][1], 0.001f);
            Assert::AreEqual(2.0f, C.m[0][2], 0.001f); // tx scaled by sx
            Assert::AreEqual(6.0f, C.m[1][2], 0.001f); // ty scaled by sy
        }
    };

    TEST_CLASS(Matrix4TransformTests)
    {
    public:
        TEST_METHOD(TestIdentity4)
        {
            Matrix4 I = Matrix4::Identity();
            Assert::AreEqual(1.0f, I.m[0][0], 0.0001f);
            Assert::AreEqual(1.0f, I.m[1][1], 0.0001f);
            Assert::AreEqual(1.0f, I.m[2][2], 0.0001f);
            Assert::AreEqual(1.0f, I.m[3][3], 0.0001f);
        }

        TEST_METHOD(TestTranslation4)
        {
            Matrix4 T = Matrix4::MakeTranslation(4.0f, 5.0f, 6.0f);
            Assert::AreEqual(4.0f, T.m[0][3], 0.0001f);
            Assert::AreEqual(5.0f, T.m[1][3], 0.0001f);
            Assert::AreEqual(6.0f, T.m[2][3], 0.0001f);
        }

        TEST_METHOD(TestScale4)
        {
            Matrix4 S = Matrix4::MakeScale(2.0f, 3.0f, 4.0f);
            Assert::AreEqual(2.0f, S.m[0][0], 0.0001f);
            Assert::AreEqual(3.0f, S.m[1][1], 0.0001f);
            Assert::AreEqual(4.0f, S.m[2][2], 0.0001f);
        }

        TEST_METHOD(TestRotateX)
        {
            float angle = 3.14159265f / 2.0f;
            Matrix4 R = Matrix4::MakeRotateX(angle);
            float c = cosf(angle);
            float s = sinf(angle);

            Assert::AreEqual(1.0f, R.m[0][0], 0.001f);
            Assert::AreEqual(c, R.m[1][1], 0.001f);
            Assert::AreEqual(-s, R.m[1][2], 0.001f);
            Assert::AreEqual(s, R.m[2][1], 0.001f);
            Assert::AreEqual(c, R.m[2][2], 0.001f);
        }

        TEST_METHOD(TestRotateY)
        {
            float angle = 3.14159265f / 2.0f;
            Matrix4 R = Matrix4::MakeRotateY(angle);
            float c = cosf(angle);
            float s = sinf(angle);

            Assert::AreEqual(c, R.m[0][0], 0.001f);
            Assert::AreEqual(s, R.m[0][2], 0.001f);
            Assert::AreEqual(-s, R.m[2][0], 0.001f);
            Assert::AreEqual(c, R.m[2][2], 0.001f);
        }

        TEST_METHOD(TestRotateZ)
        {
            float angle = 3.14159265f / 2.0f;
            Matrix4 R = Matrix4::MakeRotateZ(angle);
            float c = cosf(angle);
            float s = sinf(angle);

            Assert::AreEqual(c, R.m[0][0], 0.001f);
            Assert::AreEqual(-s, R.m[0][1], 0.001f);
            Assert::AreEqual(s, R.m[1][0], 0.001f);
            Assert::AreEqual(c, R.m[1][1], 0.001f);
        }

        TEST_METHOD(TestEulerRotation)
        {
            float pitch = 0.5f, yaw = 1.0f, roll = 0.3f;
            Matrix4 E = Matrix4::MakeEuler(pitch, yaw, roll);
            Matrix4 Combined = Matrix4::MakeRotateZ(roll) *
                Matrix4::MakeRotateY(yaw) *
                Matrix4::MakeRotateX(pitch);

            Assert::AreEqual(Combined.m[0][0], E.m[0][0], 0.001f);
            Assert::AreEqual(Combined.m[1][1], E.m[1][1], 0.001f);
            Assert::AreEqual(Combined.m[2][2], E.m[2][2], 0.001f);
        }

        TEST_METHOD(TestMatrixMultiply4)
        {
            Matrix4 A = Matrix4::MakeScale(2.0f, 2.0f, 2.0f);
            Matrix4 B = Matrix4::MakeTranslation(1.0f, 2.0f, 3.0f);
            Matrix4 C = A * B;

            Assert::AreEqual(2.0f, C.m[0][0], 0.001f);
            Assert::AreEqual(2.0f, C.m[1][1], 0.001f);
            Assert::AreEqual(2.0f, C.m[2][2], 0.001f);

            // Translation components scaled by A
            Assert::AreEqual(2.0f, C.m[0][3], 0.001f); // 1 * 2
            Assert::AreEqual(4.0f, C.m[1][3], 0.001f); // 2 * 2
            Assert::AreEqual(6.0f, C.m[2][3], 0.001f); // 3 * 2
        }
    };
}
