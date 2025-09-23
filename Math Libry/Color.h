#pragma once
#include <cmath>
#include <string>
#include <algorithm>

namespace MathClasses
{
    class Color
    {
    public:
        float r, g, b, a;

        // Default: white opaque
        Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

        // Constructor with values
        Color(float red, float green, float blue, float alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha) {
        }

        // Clamp values to [0,1]
        void Clamp()
        {
            r = std::max(0.0f, std::min(1.0f, r));
            g = std::max(0.0f, std::min(1.0f, g));
            b = std::max(0.0f, std::min(1.0f, b));
            a = std::max(0.0f, std::min(1.0f, a));
        }

        // Add
        Color operator+(const Color& rhs) const
        {
            return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
        }

        // Subtract
        Color operator-(const Color& rhs) const
        {
            return Color(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
        }

        // Multiply (component-wise)
        Color operator*(const Color& rhs) const
        {
            return Color(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
        }

        // Scale
        Color operator*(float s) const
        {
            return Color(r * s, g * s, b * s, a * s);
        }

        // Equality (with tolerance)
        bool operator==(const Color& rhs) const
        {
            return fabs(r - rhs.r) < 1e-6f &&
                fabs(g - rhs.g) < 1e-6f &&
                fabs(b - rhs.b) < 1e-6f &&
                fabs(a - rhs.a) < 1e-6f;
        }
    };
}
