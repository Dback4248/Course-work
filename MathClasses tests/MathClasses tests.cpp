#include "pch.h"
#include "CppUnitTest.h"
#include <Color.h>
#include "Colour.h"
using namespace MathClasses;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColorClassesTests
{
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

            // 128 * 128 / 255 = 64
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

        TEST_METHOD(DefaultConstructor)
        {
            Colour c;
            Assert::AreEqual((int)c.getRed(), 0);
            Assert::AreEqual((int)c.getGreen(), 0);
            Assert::AreEqual((int)c.getBlue(), 0);
            Assert::AreEqual((int)c.getAlpha(), 0);
        }

        TEST_METHOD(ConstructorWithValues)
        {
            Colour c(255, 128, 64, 32);
            Assert::AreEqual((int)c.getRed(), 255);
            Assert::AreEqual((int)c.getGreen(), 128);
            Assert::AreEqual((int)c.getBlue(), 64);
            Assert::AreEqual((int)c.getAlpha(), 32);
        }

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

        TEST_METHOD(Red94Value)
        {
            Colour c(94, 0, 0, 0);
            Assert::AreEqual((int)c.getRed(), 94);

            unsigned int expected = 94u << 24; // red in left-most byte
            Assert::AreEqual(expected, c.getValue());
        }

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
}