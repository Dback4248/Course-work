#include "pch.h"
#include "CppUnitTest.h"
#include "Vector3.h"
#include "Vector2.h"
#include <Vector4.h>
#include <Matrix4.h>
#include <Matrix3.h>
#include <Color.h>
#include "Colour.h"
using namespace MathClasses;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathClassesTests
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

TEST_CLASS(Matrix4Tests)
{
public:

    TEST_METHOD(Constructor_DefaultIdentity)
    {
        MathClasses::Matrix4 m;
        // Check diagonal = 1, rest = 0
        Assert::AreEqual(1.0f, m.m[0][0]);
        Assert::AreEqual(1.0f, m.m[1][1]);
        Assert::AreEqual(1.0f, m.m[2][2]);
        Assert::AreEqual(1.0f, m.m[3][3]);

        Assert::AreEqual(0.0f, m.m[0][1]);
        Assert::AreEqual(0.0f, m.m[1][0]);
    }

    TEST_METHOD(Constructor_WithValues)
    {
        MathClasses::Matrix4 m(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        );

        Assert::AreEqual(1.0f, m.m[0][0]);
        Assert::AreEqual(6.0f, m.m[1][1]);
        Assert::AreEqual(11.0f, m.m[2][2]);
        Assert::AreEqual(16.0f, m.m[3][3]);
    }

    TEST_METHOD(Matrix_Multiply_Identity)
    {
        MathClasses::Matrix4 I; // identity
        MathClasses::Matrix4 A(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        );

        MathClasses::Matrix4 result = A * I;

        Assert::AreEqual(1.0f, result.m[0][0]);
        Assert::AreEqual(6.0f, result.m[1][1]);
        Assert::AreEqual(11.0f, result.m[2][2]);
        Assert::AreEqual(16.0f, result.m[3][3]);
    }

    TEST_METHOD(Matrix_Multiply_Vector4)
    {
        MathClasses::Matrix4 M(
            1, 0, 0, 0,
            0, 2, 0, 0,
            0, 0, 3, 0,
            0, 0, 0, 1
        );
        MathClasses::Vector4 v(1, 1, 1, 1);

        MathClasses::Vector4 result = M * v;

        Assert::AreEqual(1.0f, result.x);
        Assert::AreEqual(2.0f, result.y);
        Assert::AreEqual(3.0f, result.z);
        Assert::AreEqual(1.0f, result.w);
    }

    TEST_METHOD(Matrix_Transpose)
    {
        MathClasses::Matrix4 M(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        );

        MathClasses::Matrix4 T = M.Transpose();

        Assert::AreEqual(1.0f, T.m[0][0]);
        Assert::AreEqual(5.0f, T.m[0][1]);
        Assert::AreEqual(9.0f, T.m[0][2]);
        Assert::AreEqual(13.0f, T.m[0][3]);
        Assert::AreEqual(2.0f, T.m[1][0]);
        Assert::AreEqual(6.0f, T.m[1][1]);
    }

    TEST_METHOD(Matrix_Determinant)
    {
        MathClasses::Matrix4 M(
            1, 0, 0, 0,
            0, 2, 0, 0,
            0, 0, 3, 0,
            0, 0, 0, 4
        );

        float det = M.Determinant();
        Assert::AreEqual(24.0f, det); // 1*2*3*4
    }

    TEST_METHOD(Matrix_Inverse)
    {
        MathClasses::Matrix4 M(
            1, 0, 0, 0,
            0, 2, 0, 0,
            0, 0, 3, 0,
            0, 0, 0, 4
        );

        MathClasses::Matrix4 Inv = M.Inverse();
        MathClasses::Matrix4 I = M * Inv;

        // Check product is identity
        Assert::AreEqual(1.0f, I.m[0][0], 0.0001f);
        Assert::AreEqual(1.0f, I.m[1][1], 0.0001f);
        Assert::AreEqual(1.0f, I.m[2][2], 0.0001f);
        Assert::AreEqual(1.0f, I.m[3][3], 0.0001f);

        Assert::AreEqual(0.0f, I.m[0][1], 0.0001f);
        Assert::AreEqual(0.0f, I.m[2][3], 0.0001f);
    }
};

TEST_CLASS(Matrix3Tests)
{
public:

    TEST_METHOD(Constructor_DefaultIdentity)
    {
        MathClasses::Matrix3 m;
        Assert::AreEqual(1.0f, m.m[0][0]);
        Assert::AreEqual(1.0f, m.m[1][1]);
        Assert::AreEqual(1.0f, m.m[2][2]);
        Assert::AreEqual(0.0f, m.m[0][1]);
    }

    TEST_METHOD(Constructor_WithValues)
    {
        MathClasses::Matrix3 m(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        );
        Assert::AreEqual(1.0f, m.m[0][0]);
        Assert::AreEqual(5.0f, m.m[1][1]);
        Assert::AreEqual(9.0f, m.m[2][2]);
    }

    TEST_METHOD(Matrix_Multiply_Identity)
    {
        MathClasses::Matrix3 I;
        MathClasses::Matrix3 A(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        );

        MathClasses::Matrix3 result = A * I;
        Assert::AreEqual(1.0f, result.m[0][0]);
        Assert::AreEqual(5.0f, result.m[1][1]);
        Assert::AreEqual(9.0f, result.m[2][2]);
    }

    TEST_METHOD(Matrix_Multiply_Vector3)
    {
        MathClasses::Matrix3 M(
            2, 0, 0,
            0, 3, 0,
            0, 0, 4
        );
        MathClasses::Vector3 v(1, 1, 1);

        MathClasses::Vector3 result = M * v;

        Assert::AreEqual(2.0f, result.x);
        Assert::AreEqual(3.0f, result.y);
        Assert::AreEqual(4.0f, result.z);
    }

    TEST_METHOD(Matrix_Transpose)
    {
        MathClasses::Matrix3 M(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        );
        MathClasses::Matrix3 T = M.Transpose();

        Assert::AreEqual(1.0f, T.m[0][0]);
        Assert::AreEqual(4.0f, T.m[0][1]);
        Assert::AreEqual(7.0f, T.m[0][2]);
        Assert::AreEqual(2.0f, T.m[1][0]);
    }

    TEST_METHOD(Matrix_Determinant)
    {
        MathClasses::Matrix3 M(
            1, 2, 3,
            0, 1, 4,
            5, 6, 0
        );

        float det = M.Determinant();
        Assert::AreEqual(1.0f, det); // known determinant
    }

    TEST_METHOD(Matrix_Inverse)
    {
        MathClasses::Matrix3 M(
            2, 0, 0,
            0, 3, 0,
            0, 0, 4
        );

        MathClasses::Matrix3 Inv = M.Inverse();
        MathClasses::Matrix3 I = M * Inv;

        Assert::AreEqual(1.0f, I.m[0][0], 0.0001f);
        Assert::AreEqual(1.0f, I.m[1][1], 0.0001f);
        Assert::AreEqual(1.0f, I.m[2][2], 0.0001f);
        Assert::AreEqual(0.0f, I.m[0][1], 0.0001f);
        Assert::AreEqual(0.0f, I.m[1][2], 0.0001f);
    }
};

TEST_CLASS(ColorTests)
{
public:

    TEST_METHOD(Constructor_Default)
    {
        MathClasses::Color c;
        Assert::AreEqual(255, (int)c.r);
        Assert::AreEqual(255, (int)c.g);
        Assert::AreEqual(255, (int)c.b);
        Assert::AreEqual(255, (int)c.a);
    }

    TEST_METHOD(Constructor_WithValues)
    {
        MathClasses::Color c((char8_t)10, (char8_t)20, (char8_t)30, (char8_t)40);
        Assert::AreEqual(10, (int)c.r);
        Assert::AreEqual(20, (int)c.g);
        Assert::AreEqual(30, (int)c.b);
        Assert::AreEqual(40, (int)c.a);
    }

    TEST_METHOD(Addition_Clamp)
    {
        MathClasses::Color c1((char8_t)200, (char8_t)200, (char8_t)200, (char8_t)200);
        MathClasses::Color c2((char8_t)100, (char8_t)100, (char8_t)100, (char8_t)100);
        MathClasses::Color result = c1 + c2;

        Assert::AreEqual(255, (int)result.r);
        Assert::AreEqual(255, (int)result.g);
        Assert::AreEqual(255, (int)result.b);
        Assert::AreEqual(255, (int)result.a);
    }

    TEST_METHOD(Subtraction_Floor)
    {
        MathClasses::Color c1((char8_t)50, (char8_t)50, (char8_t)50, (char8_t)50);
        MathClasses::Color c2((char8_t)100, (char8_t)100, (char8_t)100, (char8_t)100);
        MathClasses::Color result = c1 - c2;

        Assert::AreEqual(0, (int)result.r);
        Assert::AreEqual(0, (int)result.g);
        Assert::AreEqual(0, (int)result.b);
        Assert::AreEqual(0, (int)result.a);
    }

    TEST_METHOD(Multiplication_ComponentWise)
    {
        MathClasses::Color c1((char8_t)128, (char8_t)128, (char8_t)128, (char8_t)128);
        MathClasses::Color c2((char8_t)128, (char8_t)128, (char8_t)128, (char8_t)128);
        MathClasses::Color result = c1 * c2;

        // 128 * 128 / 255 â‰ˆ 64
        Assert::AreEqual(64, (int)result.r);
        Assert::AreEqual(64, (int)result.g);
        Assert::AreEqual(64, (int)result.b);
        Assert::AreEqual(64, (int)result.a);
    }

    TEST_METHOD(Equality)
    {
        MathClasses::Color c1((char8_t)10, (char8_t)20, (char8_t)30, (char8_t)40);
        MathClasses::Color c2((char8_t)10, (char8_t)20, (char8_t)30, (char8_t)40);
        Assert::IsTrue(c1 == c2);
    }

    TEST_METHOD(Inequality)
    {
        MathClasses::Color c1((char8_t)10, (char8_t)20, (char8_t)30, (char8_t)40);
        MathClasses::Color c2((char8_t)11, (char8_t)20, (char8_t)30, (char8_t)40);
        Assert::IsFalse(c1 == c2);
    }
};

TEST_CLASS(ColourTests)
{
public:

    // Test 1: Default constructor
    TEST_METHOD(DefaultConstructor)
    {
        Colour c;
        Assert::AreEqual((int)c.getRed(), 0);
        Assert::AreEqual((int)c.getGreen(), 0);
        Assert::AreEqual((int)c.getBlue(), 0);
        Assert::AreEqual((int)c.getAlpha(), 0);
    }

    // Test 2: Constructor with values
    TEST_METHOD(ConstructorWithValues)
    {
        Colour c(255, 128, 64, 32);
        Assert::AreEqual((int)c.getRed(), 255);
        Assert::AreEqual((int)c.getGreen(), 128);
        Assert::AreEqual((int)c.getBlue(), 64);
        Assert::AreEqual((int)c.getAlpha(), 32);
    }

    // Test 3: Setters and Getters
    TEST_METHOD(SettersAndGetters)
    {
        Colour c;
        c.setRed(10);
        c.setGreen(20);
        c.setBlue(30);
        c.setAlpha(40);

        Assert::AreEqual((int)c.getRed(), 10);
        Assert::AreEqual((int)c.getGreen(), 20);
        Assert::AreEqual((int)c.getBlue(), 30);
        Assert::AreEqual((int)c.getAlpha(), 40);
    }

    // Test 4: Store red = 94 (Q3â€“Q5 from exercise)
    TEST_METHOD(Red94Value)
    {
        Colour c(94, 0, 0, 0);
        Assert::AreEqual((int)c.getRed(), 94);

        unsigned int expected = 94u << 24; // red in left-most byte
        Assert::AreEqual(expected, c.getValue());
    }

    // Test 5: Shift red into green (Q6â€“Q7 from exercise)
    TEST_METHOD(ShiftRedIntoGreen)
    {
        Colour c(94, 0, 0, 0);
        unsigned int val = c.getValue();

        // Move red into green
        val = (val >> 8) & 0x00FF0000;
        c.setValue(val);

        Assert::AreEqual((int)c.getRed(), 0);
        Assert::AreEqual((int)c.getGreen(), 94);
        Assert::AreEqual((int)c.getBlue(), 0);
        Assert::AreEqual((int)c.getAlpha(), 0);

        unsigned int expected = 94u << 16;
        Assert::AreEqual(expected, c.getValue());
    }

    // Test 6: Edge case (all max values)
    TEST_METHOD(AllMaxValues)
    {
        Colour c(255, 255, 255, 255);
        Assert::AreEqual((int)c.getRed(), 255);
        Assert::AreEqual((int)c.getGreen(), 255);
        Assert::AreEqual((int)c.getBlue(), 255);
        Assert::AreEqual((int)c.getAlpha(), 255);

        unsigned int expected = 0xFFFFFFFF;
        Assert::AreEqual(expected, c.getValue());
    }
};
