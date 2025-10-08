#pragma once
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdint>

namespace MathClasses
{
    struct Color
    {
        union
        {
            struct
            {
                char8_t r, g, b, a;
            };
            char8_t v[4];
        };

        // Default: opaque white
        Color() : r(255), g(255), b(255), a(255) {}

        // Constructor with values
        Color(char8_t red, char8_t green, char8_t blue, char8_t alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {
        }

        // Clamp values
        void Clamp()
        {
            r = static_cast<char8_t>(std::max(0, std::min(255, int(r))));
            g = static_cast<char8_t>(std::max(0, std::min(255, int(g))));
            b = static_cast<char8_t>(std::max(0, std::min(255, int(b))));
            a = static_cast<char8_t>(std::max(0, std::min(255, int(a))));
        }

        // Add
        Color operator+(const Color& rhs) const
        {
            return Color(
                static_cast<char8_t>(std::min(255, int(r) + int(rhs.r))),
                static_cast<char8_t>(std::min(255, int(g) + int(rhs.g))),
                static_cast<char8_t>(std::min(255, int(b) + int(rhs.b))),
                static_cast<char8_t>(std::min(255, int(a) + int(rhs.a)))
            );
        }

        // Subtract
        Color operator-(const Color& rhs) const
        {
            return Color(
                static_cast<char8_t>(std::max(0, int(r) - int(rhs.r))),
                static_cast<char8_t>(std::max(0, int(g) - int(rhs.g))),
                static_cast<char8_t>(std::max(0, int(b) - int(rhs.b))),
                static_cast<char8_t>(std::max(0, int(a) - int(rhs.a)))
            );
        }

        // Multiply (component-wise)
        Color operator*(const Color& rhs) const
        {
            return Color(
                static_cast<char8_t>((int(r) * int(rhs.r)) / 255),
                static_cast<char8_t>((int(g) * int(rhs.g)) / 255),
                static_cast<char8_t>((int(b) * int(rhs.b)) / 255),
                static_cast<char8_t>((int(a) * int(rhs.a)) / 255)
            );
        }

        // Equality
        bool operator==(const Color& rhs) const
        {
            return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
        }
    };
}

