#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
using namespace MathClasses;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTransformTests
{
    // -------------------------------------------------------------
    // MATRIX 3 TESTS
    // -------------------------------------------------------------
    TEST_CLASS(Matrix3TransformTests)
    {
    public:

        TEST_METHOD(TestTranslateMatrix3)
        {
            Matrix3 m = Matrix3::MakeTranslate(2.0f, 3.0f);
            Vector3 v(1.0f, 1.0f, 1.0f);
            Vector3 result = m * v;

            Assert::AreEqual(3.0f, result.x, 0.0001f);
            Assert::AreEqual(4.0f, result.y, 0.0001f);
            Assert::AreEqual(1.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestScaleMatrix3)
        {
            Matrix3 m = Matrix3::MakeScale(2.0f, 3.0f);
            Vector3 v(1.0f, 1.0f, 1.0f);
            Vector3 result = m * v;

            Assert::AreEqual(2.0f, result.x, 0.0001f);
            Assert::AreEqual(3.0f, result.y, 0.0001f);
            Assert::AreEqual(1.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestRotateMatrix3)
        {
            Matrix3 m = Matrix3::MakeRotateZ(3.1415926f / 2); // 90°
            Vector3 v(1.0f, 0.0f, 1.0f);
            Vector3 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(1.0f, result.y, 0.0001f);
        }

        TEST_METHOD(TestEulerMatrix3)
        {
            Vector3 euler(3.1415926f / 2, 0.0f, 0.0f); // Rotate 90° about X
            Matrix3 m = Matrix3::MakeEuler(euler);
            Vector3 v(0.0f, 1.0f, 0.0f);
            Vector3 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(0.0f, result.y, 0.0001f);
            Assert::AreEqual(1.0f, result.z, 0.0001f);
        }
    };

    // -------------------------------------------------------------
    // MATRIX 4 TESTS
    // -------------------------------------------------------------
    TEST_CLASS(Matrix4TransformTests)
    {
    public:

        TEST_METHOD(TestTranslateMatrix4)
        {
            Matrix4 m = Matrix4::MakeTranslate(2.0f, 3.0f, 4.0f);
            Vector4 v(1.0f, 1.0f, 1.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(3.0f, result.x, 0.0001f);
            Assert::AreEqual(4.0f, result.y, 0.0001f);
            Assert::AreEqual(5.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestScaleMatrix4)
        {
            Matrix4 m = Matrix4::MakeScale(2.0f, 3.0f, 4.0f);
            Vector4 v(1.0f, 1.0f, 1.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(2.0f, result.x, 0.0001f);
            Assert::AreEqual(3.0f, result.y, 0.0001f);
            Assert::AreEqual(4.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestRotateXMatrix4)
        {
            Matrix4 m = Matrix4::MakeRotateX(3.1415926f / 2);
            Vector4 v(0.0f, 1.0f, 0.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(0.0f, result.y, 0.0001f);
            Assert::AreEqual(1.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestRotateYMatrix4)
        {
            Matrix4 m = Matrix4::MakeRotateY(3.1415926f / 2);
            Vector4 v(1.0f, 0.0f, 0.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(0.0f, result.y, 0.0001f);
            Assert::AreEqual(-1.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestRotateZMatrix4)
        {
            Matrix4 m = Matrix4::MakeRotateZ(3.1415926f / 2);
            Vector4 v(1.0f, 0.0f, 0.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(1.0f, result.y, 0.0001f);
            Assert::AreEqual(0.0f, result.z, 0.0001f);
        }

        TEST_METHOD(TestEulerMatrix4)
        {
            Vector3 euler(3.1415926f / 2, 0.0f, 0.0f);
            Matrix4 m = Matrix4::MakeEuler(euler);
            Vector4 v(0.0f, 1.0f, 0.0f, 1.0f);
            Vector4 result = m * v;

            Assert::AreEqual(0.0f, result.x, 0.0001f);
            Assert::AreEqual(0.0f, result.y, 0.0001f);
            Assert::AreEqual(1.0f, result.z, 0.0001f);
        }
    };
}
