#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>

namespace MathClasses
{
    class Vector4
    {
    public:
        float x, y, z, w;

        // Constructors
        Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector4(float _x, float _y, float _z, float _w)
            : x(_x), y(_y), z(_z), w(_w) {
        }

        // Operator overloads
        Vector4 operator+(const Vector4& rhs) const
        {
            return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        Vector4 operator-(const Vector4& rhs) const
        {
            return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        Vector4 operator*(float scalar) const
        {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        Vector4 operator/(float scalar) const
        {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        Vector4& operator+=(const Vector4& rhs)
        {
            x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
            return *this;
        }

        Vector4& operator-=(const Vector4& rhs)
        {
            x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
            return *this;
        }

        Vector4& operator*=(float scalar)
        {
            x *= scalar; y *= scalar; z *= scalar; w *= scalar;
            return *this;
        }

        Vector4& operator/=(float scalar)
        {
            x /= scalar; y /= scalar; z /= scalar; w /= scalar;
            return *this;
        }

        // Dot product
        float Dot(const Vector4& rhs) const
        {
            return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
        }

        // Magnitude
        float Magnitude() const
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        // Magnitude squared (faster, no sqrt)
        float MagnitudeSqr() const
        {
            return (x * x + y * y + z * z + w * w);
        }

        // Normalize (unsafe if zero vector)
        void Normalize()
        {
            float mag = Magnitude();
            if (mag > 0.0f)
            {
                x /= mag; y /= mag; z /= mag; w /= mag;
            }
        }

        // SafeNormalize (returns zero instead of NaN)
        void SafeNormalize()
        {
            float mag = Magnitude();
            if (mag > 0.0f)
            {
                x /= mag; y /= mag; z /= mag; w /= mag;
            }
            else
            {
                x = y = z = w = 0.0f;
            }
        }

        // Distance between two vectors
        float Distance(const Vector4& rhs) const
        {
            float dx = rhs.x - x;
            float dy = rhs.y - y;
            float dz = rhs.z - z;
            float dw = rhs.w - w;
            return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
        }

        // Distance squared
        float DistanceSqr(const Vector4& rhs) const
        {
            float dx = rhs.x - x;
            float dy = rhs.y - y;
            float dz = rhs.z - z;
            float dw = rhs.w - w;
            return dx * dx + dy * dy + dz * dz + dw * dw;
        }
    };
}

