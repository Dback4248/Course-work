#include "pch.h"
#include "CppUnitTest.h"
#include "Vector3.h"
#include "Vector2.h"
#include <Vector4.h>

using namespace MathClasses;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorClassesTests
{
    TEST_CLASS(Vector3Tests)
    {
    public:

        TEST_METHOD(Constructor_Default)
        {
            Vector3 v;
            Assert::AreEqual(0.0f, v.x);
            Assert::AreEqual(0.0f, v.y);
            Assert::AreEqual(0.0f, v.z);
        }

        TEST_METHOD(Constructor_WithValues)
        {
            Vector3 v(1.0f, 2.0f, 3.0f);
            Assert::AreEqual(1.0f, v.x);
            Assert::AreEqual(2.0f, v.y);
            Assert::AreEqual(3.0f, v.z);
        }

        TEST_METHOD(Vector_Addition)
        {
            Vector3 a(1.0f, 2.0f, 3.0f);
            Vector3 b(4.0f, 5.0f, 6.0f);
            Vector3 result = a + b;

            Assert::AreEqual(5.0f, result.x);
            Assert::AreEqual(7.0f, result.y);
            Assert::AreEqual(9.0f, result.z);
        }

        TEST_METHOD(Vector_Subtraction)
        {
            Vector3 a(5.0f, 7.0f, 9.0f);
            Vector3 b(1.0f, 2.0f, 3.0f);
            Vector3 result = a - b;

            Assert::AreEqual(4.0f, result.x);
            Assert::AreEqual(5.0f, result.y);
            Assert::AreEqual(6.0f, result.z);
        }

        TEST_METHOD(Vector_DotProduct)
        {
            Vector3 a(1.0f, 2.0f, 3.0f);
            Vector3 b(4.0f, -5.0f, 6.0f);
            float dot = a.Dot(b);

            Assert::AreEqual(12.0f, dot); // (1*4 + 2*(-5) + 3*6) = 12
        }

        TEST_METHOD(Vector_CrossProduct)
        {
            Vector3 a(1.0f, 2.0f, 3.0f);
            Vector3 b(4.0f, 5.0f, 6.0f);
            Vector3 cross = a.Cross(b);

            Assert::AreEqual(-3.0f, cross.x);
            Assert::AreEqual(6.0f, cross.y);
            Assert::AreEqual(-3.0f, cross.z);
        }

        TEST_METHOD(Vector_Normalize)
        {
            Vector3 v(3.0f, 4.0f, 0.0f);
            v.Normalize();

            Assert::AreEqual(0.6f, v.x, 0.0001f);
            Assert::AreEqual(0.8f, v.y, 0.0001f);
            Assert::AreEqual(0.0f, v.z, 0.0001f);
        }

        TEST_METHOD(Vector_SafeNormalize)
        {
            Vector3 v(0.0f, 0.0f, 0.0f);
            v.SafeNormalize();

            // Should remain zero instead of NaN
            Assert::AreEqual(0.0f, v.x);
            Assert::AreEqual(0.0f, v.y);
            Assert::AreEqual(0.0f, v.z);

            Vector3 u(3.0f, 4.0f, 0.0f);
            u.SafeNormalize();

            Assert::AreEqual(0.6f, u.x, 0.0001f);
            Assert::AreEqual(0.8f, u.y, 0.0001f);
            Assert::AreEqual(0.0f, u.z, 0.0001f);
        }

        TEST_METHOD(Vector_MagnitudeSqr)
        {
            Vector3 v(3.0f, 4.0f, 12.0f);
            float magSqr = v.MagnitudeSqr();

            Assert::AreEqual(169.0f, magSqr); // 9 + 16 + 144
        }

        TEST_METHOD(Vector_Distance)
        {
            Vector3 a(1.0f, 2.0f, 3.0f);
            Vector3 b(4.0f, 6.0f, 3.0f);

            float dist = a.Distance(b);
            Assert::AreEqual(5.0f, dist, 0.0001f); // sqrt(3² + 4²)
        }

        TEST_METHOD(Vector_DistanceSqr)
        {
            Vector3 a(1.0f, 2.0f, 3.0f);
            Vector3 b(4.0f, 6.0f, 3.0f);

            float distSqr = a.DistanceSqr(b);
            Assert::AreEqual(25.0f, distSqr); // 3² + 4²
        }
    };
}
TEST_CLASS(Vector2Tests)
{
public:

    TEST_METHOD(Constructor_Default)
    {
        MathClasses::Vector2 v;
        Assert::AreEqual(0.0f, v.x);
        Assert::AreEqual(0.0f, v.y);
    }

    TEST_METHOD(Constructor_WithValues)
    {
        MathClasses::Vector2 v(3.0f, 4.0f);
        Assert::AreEqual(3.0f, v.x);
        Assert::AreEqual(4.0f, v.y);
    }

    TEST_METHOD(Vector_Addition)
    {
        MathClasses::Vector2 a(1.0f, 2.0f);
        MathClasses::Vector2 b(4.0f, 5.0f);
        MathClasses::Vector2 result = a + b;

        Assert::AreEqual(5.0f, result.x);
        Assert::AreEqual(7.0f, result.y);
    }

    TEST_METHOD(Vector_Subtraction)
    {
        MathClasses::Vector2 a(5.0f, 7.0f);
        MathClasses::Vector2 b(1.0f, 2.0f);
        MathClasses::Vector2 result = a - b;

        Assert::AreEqual(4.0f, result.x);
        Assert::AreEqual(5.0f, result.y);
    }

    TEST_METHOD(Vector_DotProduct)
    {
        MathClasses::Vector2 a(3.0f, 4.0f);
        MathClasses::Vector2 b(2.0f, -1.0f);
        float dot = a.Dot(b);

        Assert::AreEqual(2.0f, dot); // 3*2 + 4*(-1) = 6 - 4
    }

    TEST_METHOD(Vector_Normalize)
    {
        MathClasses::Vector2 v(3.0f, 4.0f);
        v.Normalize();

        Assert::AreEqual(0.6f, v.x, 0.0001f);
        Assert::AreEqual(0.8f, v.y, 0.0001f);
    }

    TEST_METHOD(Vector_SafeNormalize)
    {
        MathClasses::Vector2 v(0.0f, 0.0f);
        v.SafeNormalize();

        Assert::AreEqual(0.0f, v.x);
        Assert::AreEqual(0.0f, v.y);

        MathClasses::Vector2 u(3.0f, 4.0f);
        u.SafeNormalize();

        Assert::AreEqual(0.6f, u.x, 0.0001f);
        Assert::AreEqual(0.8f, u.y, 0.0001f);
    }

    TEST_METHOD(Vector_MagnitudeSqr)
    {
        MathClasses::Vector2 v(3.0f, 4.0f);
        float magSqr = v.MagnitudeSqr();

        Assert::AreEqual(25.0f, magSqr);
    }

    TEST_METHOD(Vector_Distance)
    {
        MathClasses::Vector2 a(1.0f, 2.0f);
        MathClasses::Vector2 b(4.0f, 6.0f);

        float dist = a.Distance(b);
        Assert::AreEqual(5.0f, dist, 0.0001f);
    }

    TEST_METHOD(Vector_DistanceSqr)
    {
        MathClasses::Vector2 a(1.0f, 2.0f);
        MathClasses::Vector2 b(4.0f, 6.0f);

        float distSqr = a.DistanceSqr(b);
        Assert::AreEqual(25.0f, distSqr);
    }
};

TEST_CLASS(Vector4Tests)
{
public:

    TEST_METHOD(Constructor_Default)
    {
        MathClasses::Vector4 v;
        Assert::AreEqual(0.0f, v.x);
        Assert::AreEqual(0.0f, v.y);
        Assert::AreEqual(0.0f, v.z);
        Assert::AreEqual(0.0f, v.w);
    }

    TEST_METHOD(Constructor_WithValues)
    {
        MathClasses::Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);
        Assert::AreEqual(1.0f, v.x);
        Assert::AreEqual(2.0f, v.y);
        Assert::AreEqual(3.0f, v.z);
        Assert::AreEqual(4.0f, v.w);
    }

    TEST_METHOD(Vector_Addition)
    {
        MathClasses::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        MathClasses::Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);
        MathClasses::Vector4 result = a + b;

        Assert::AreEqual(5.0f, result.x);
        Assert::AreEqual(7.0f, result.y);
        Assert::AreEqual(9.0f, result.z);
        Assert::AreEqual(11.0f, result.w);
    }

    TEST_METHOD(Vector_Subtraction)
    {
        MathClasses::Vector4 a(5.0f, 7.0f, 9.0f, 11.0f);
        MathClasses::Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);
        MathClasses::Vector4 result = a - b;

        Assert::AreEqual(4.0f, result.x);
        Assert::AreEqual(5.0f, result.y);
        Assert::AreEqual(6.0f, result.z);
        Assert::AreEqual(7.0f, result.w);
    }

    TEST_METHOD(Vector_DotProduct)
    {
        MathClasses::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        MathClasses::Vector4 b(2.0f, -1.0f, 0.0f, 5.0f);
        float dot = a.Dot(b);

        Assert::AreEqual(20.0f, dot); // (1*2 + 2*-1 + 3*0 + 4*5) = 2 - 2 + 0 + 20
    }

    TEST_METHOD(Vector_Normalize)
    {
        MathClasses::Vector4 v(1.0f, 2.0f, 2.0f, 1.0f);
        v.Normalize();

        float mag = std::sqrt(1 * 1 + 2 * 2 + 2 * 2 + 1 * 1); // sqrt(10) = 3.1623
        Assert::AreEqual(1.0f / mag, v.x, 0.0001f);
        Assert::AreEqual(2.0f / mag, v.y, 0.0001f);
        Assert::AreEqual(2.0f / mag, v.z, 0.0001f);
        Assert::AreEqual(1.0f / mag, v.w, 0.0001f);
    }

    TEST_METHOD(Vector_SafeNormalize)
    {
        MathClasses::Vector4 v(0.0f, 0.0f, 0.0f, 0.0f);
        v.SafeNormalize();

        Assert::AreEqual(0.0f, v.x);
        Assert::AreEqual(0.0f, v.y);
        Assert::AreEqual(0.0f, v.z);
        Assert::AreEqual(0.0f, v.w);

        MathClasses::Vector4 u(1.0f, 2.0f, 2.0f, 1.0f);
        u.SafeNormalize();

        float mag = std::sqrt(10.0f);
        Assert::AreEqual(1.0f / mag, u.x, 0.0001f);
        Assert::AreEqual(2.0f / mag, u.y, 0.0001f);
        Assert::AreEqual(2.0f / mag, u.z, 0.0001f);
        Assert::AreEqual(1.0f / mag, u.w, 0.0001f);
    }

    TEST_METHOD(Vector_MagnitudeSqr)
    {
        MathClasses::Vector4 v(1.0f, 2.0f, 2.0f, 1.0f);
        float magSqr = v.MagnitudeSqr();

        Assert::AreEqual(10.0f, magSqr);
    }

    TEST_METHOD(Vector_Distance)
    {
        MathClasses::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        MathClasses::Vector4 b(4.0f, 6.0f, 3.0f, 8.0f);

        float dist = a.Distance(b);
        Assert::AreEqual(6.4031f, dist, 0.0001f); // sqrt(3² + 4² + 0² + 4²)
    }

    TEST_METHOD(Vector_DistanceSqr)
    {
        MathClasses::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        MathClasses::Vector4 b(4.0f, 6.0f, 3.0f, 8.0f);

        float distSqr = a.DistanceSqr(b);
        Assert::AreEqual(41.0f, distSqr); // 3² + 4² + 0² + 4²
    }
};
