#pragma once

#include <cmath>
#include <string>
#include <sstream>

namespace MathClasses
{
    struct Vector4
    {
        union {
            struct { float x, y, z, w; };
            float v[4];
        };

        Vector4() : x(0), y(0), z(0), w(0) {}
        Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

        float Magnitude() const { return std::sqrt(x * x + y * y + z * z + w * w); }
        float MagnitudeSqr() const { return x * x + y * y + z * z + w * w; }

        float Dot(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }

        Vector4 Cross(const Vector4& rhs) const
        {
            return { y * rhs.z - z * rhs.y,
                     z * rhs.x - x * rhs.z,
                     x * rhs.y - y * rhs.x,
                     0.0f };
        }

        void Normalise() { float m = Magnitude(); if (m > 0) { x /= m; y /= m; z /= m; w /= m; } }
        void SafeNormalise() { if (MagnitudeSqr() > 1e-6f) Normalise(); }
        Vector4 Normalised() const { Vector4 v = *this; v.Normalise(); return v; }
        Vector4 SafeNormalised() const { Vector4 v = *this; v.SafeNormalise(); return v; }

        Vector4 operator +(const Vector4& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
        Vector4& operator +=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
        Vector4 operator -(const Vector4& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
        Vector4& operator -=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }

        Vector4 operator *(const Vector4& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w }; }
        Vector4& operator *=(const Vector4& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
        Vector4 operator /(const Vector4& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w }; }
        Vector4& operator /=(const Vector4& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return *this; }

        Vector4 operator *(float rhs) const { return { x * rhs, y * rhs, z * rhs, w * rhs }; }
        Vector4& operator *=(float rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
        Vector4 operator /(float rhs) const { return { x / rhs, y / rhs, z / rhs, w / rhs }; }
        Vector4& operator /=(float rhs) { x /= rhs; y /= rhs; z /= rhs; w /= rhs; return *this; }

        Vector4 operator -() const { return { -x, -y, -z, -w }; }

        bool operator==(const Vector4& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
        bool operator!=(const Vector4& rhs) const { return !(*this == rhs); }
        bool Equals(const Vector4& rhs, float Tolerance = 0.00001f) const
        {
            return std::fabs(x - rhs.x) < Tolerance && std::fabs(y - rhs.y) < Tolerance &&
                std::fabs(z - rhs.z) < Tolerance && std::fabs(w - rhs.w) < Tolerance;
        }

        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
            return oss.str();
        }

        operator float* () { return v; }
        operator const float* () const { return v; }

        float& operator[](int dim) { return v[dim]; }
        const float& operator[](int dim) const { return v[dim]; }
    };

    inline Vector4 operator*(float scalar, const Vector4& vector)
    {
        return Vector4(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar);
    }
}

