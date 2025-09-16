#pragma once

#include <string>
#include <sstream>

namespace MathClasses
{
    struct Color
    {
        float r, g, b, a;
        Color() : r(0), g(0), b(0), a(1) {}
        Color(float red, float green, float blue, float alpha = 1.0f) : r(red), g(green), b(blue), a(alpha) {}

        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "(" << r << ", " << g << ", " << b << ", " << a << ")";
            return oss.str();
        }
    };
}
