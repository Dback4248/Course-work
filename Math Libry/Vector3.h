#pragma once

#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include "Vector2.h" // optional, if you have Vector2
using namespace Mathclasses;

namespace MathClasses
{
    struct Vector3
    {
        union {
            struct { float x, y, z; };
            float v[3];
        };

        // Constructors
        Vector3() : x(0), y(0), z(0) {}
        Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}
        Vector3(const Vector2& Vec2) : x(Vec2.x), y(Vec2.y), z(0) {}
        Vector3(const Vector2& Vec2, float InZ) : x(Vec2.x), y(Vec2.y), z(InZ) {}

        // Magnitudes
        float Magnitude() const { return std::sqrt(x * x + y * y + z * z); }
        float MagnitudeSqr() const { return x * x + y * y + z * z; }

        // Dot
        float Dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
        static float Dot(const Vector3& first, const Vector3& second) { return first.Dot(second); }

        // Cross
        Vector3 Cross(const Vector3& rhs) const
        {
            return { y * rhs.z - z * rhs.y,
                     z * rhs.x - x * rhs.z,
                     x * rhs.y - y * rhs.x };
        }
        static Vector3 Cross(const Vector3& a, const Vector3& b) { return a.Cross(b); }

        // Normalisation
        void Normalise()
        {
            float mag = Magnitude();
            if (mag > 0) { x /= mag; y /= mag; z /= mag; }
        }
        void SafeNormalise() { if (MagnitudeSqr() > 1e-6f) Normalise(); }
        Vector3 Normalised() const { Vector3 tmp = *this; tmp.Normalise(); return tmp; }
        Vector3 SafeNormalised() const { Vector3 tmp = *this; tmp.SafeNormalise(); return tmp; }

        // Distance
        float Distance(const Vector3& other) const { return (*this - other).Magnitude(); }
        float DistanceSqr(const Vector3& other) const { return (*this - other).MagnitudeSqr(); }
        static float Distance(const Vector3& start, const Vector3& end) { return (end - start).Magnitude(); }
        static float DistanceSqr(const Vector3& start, const Vector3& end) { return (end - start).MagnitudeSqr(); }

        float AngleBetween(const Vector3& other) const
        {
            float dot = Dot(other);
            float mags = Magnitude() * other.Magnitude();
            return (mags > 0) ? std::acos(dot / mags) : 0.0f;
        }

        // Operators
        Vector3 operator +(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
        Vector3& operator +=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        Vector3 operator -(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
        Vector3& operator -=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

        Vector3 operator *(float rhs) const { return { x * rhs, y * rhs, z * rhs }; }
        Vector3& operator *=(float rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
        Vector3 operator /(float rhs) const { return { x / rhs, y / rhs, z / rhs }; }
        Vector3& operator /=(float rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }

        Vector3 operator *(const Vector3& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
        Vector3& operator *=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
        Vector3 operator /(const Vector3& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
        Vector3& operator /=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

        Vector3 operator -() const { return { -x, -y, -z }; }

        float& operator [](int dim) { return v[dim]; }
        const float& operator [](int dim) const { return v[dim]; }

        bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        bool operator != (const Vector3& rhs) const { return !(*this == rhs); }
        bool Equals(const Vector3& rhs, float Tolerance = 0.00001f) const
        {
            return std::fabs(x - rhs.x) < Tolerance &&
                std::fabs(y - rhs.y) < Tolerance &&
                std::fabs(z - rhs.z) < Tolerance;
        }

        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "(" << x << ", " << y << ", " << z << ")";
            return oss.str();
        }

        operator float* () { return v; }
        operator const float* () const { return v; }
    };

    inline Vector3 operator*(float scalar, const Vector3& vector)
    {
        return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
    }
}

