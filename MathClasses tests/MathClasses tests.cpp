#include "pch.h"
#include "CppUnitTest.h"
#include "Colour.h"

using namespace MathClasses;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColorClassesTests
{

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