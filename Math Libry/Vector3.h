#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>


namespace MathClasses
{
    class Vector3
    {
    public:
        float x, y, z;

        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        // Magnitude squared
        float MagnitudeSqr() const { return x * x + y * y + z * z; }

        // Magnitude (length)
        float Magnitude() const { return std::sqrt(MagnitudeSqr()); }

        // Normalize (unsafe – assumes length > 0)
        void Normalize()
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                x /= m;
                y /= m;
                z /= m;
            }
        }

        // Safe normalize (if length == 0, stays zero vector)
        void SafeNormalize()
        {
            float m = Magnitude();
            if (m > 0.000001f)
            {
                x /= m;
                y /= m;
                z /= m;
            }
        }

        // Distance
        float Distance(const Vector3& other) const
        {
            return std::sqrt(DistanceSqr(other));
        }

        // Distance squared
        float DistanceSqr(const Vector3& other) const
        {
            float dx = x - other.x;
            float dy = y - other.y;
            float dz = z - other.z;
            return dx * dx + dy * dy + dz * dz;
        }

        // Operators
        Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
        Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
        float   Dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
        Vector3 Cross(const Vector3& rhs) const
        {
            return {
                y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x
            };
        }
    };
}
