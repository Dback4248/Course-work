#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>

namespace MathClasses
{
    struct Vector2
    {
        float x, y;
    };

    struct Vector3
    {
        union {
            struct { float x, y, z; };
            float v[3];
        };

        // Constructors
        Vector3() : x(0), y(0), z(0) {}
        Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}
        Vector3(const Vector2& vec2) : x(vec2.x), y(vec2.y), z(0) {}
        Vector3(const Vector2& vec2, float inZ) : x(vec2.x), y(vec2.y), z(inZ) {}

        // Math functions
        float Magnitude() const { return std::sqrt(x * x + y * y + z * z); }
        float MagnitudeSqr() const { return x * x + y * y + z * z; }
        float Dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
        static float Dot(const Vector3& a, const Vector3& b) { return a.Dot(b); }

        Vector3 Cross(const Vector3& rhs) const
        {
            return { y * rhs.z - z * rhs.y,
                     z * rhs.x - x * rhs.z,
                     x * rhs.y - y * rhs.x };
        }
        static Vector3 Cross(const Vector3& a, const Vector3& b) { return a.Cross(b); }

        void Normalise()
        {
            float m = Magnitude();
            if (m != 0) { x /= m; y /= m; z /= m; }
        }
        void SafeNormalise()
        {
            float m = Magnitude();
            if (m > 1e-6f) { x /= m; y /= m; z /= m; }
        }
        Vector3 Normalised() const { Vector3 r(*this); r.Normalise(); return r; }
        Vector3 SafeNormalised() const { Vector3 r(*this); r.SafeNormalise(); return r; }

        float Distance(const Vector3& o) const { return (*this - o).Magnitude(); }
        float DistanceSqr(const Vector3& o) const { return (*this - o).MagnitudeSqr(); }
        static float Distance(const Vector3& a, const Vector3& b) { return (a - b).Magnitude(); }
        static float DistanceSqr(const Vector3& a, const Vector3& b) { return (a - b).MagnitudeSqr(); }

        float AngleBetween(const Vector3& o) const
        {
            float d = Dot(o);
            float mags = Magnitude() * o.Magnitude();
            return (mags > 0) ? std::acos(d / mags) : 0.0f;
        }

        // Operators
        Vector3 operator+(const Vector3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
        Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }

        Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
        Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

        Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
        Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }

        Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }
        Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

        Vector3 operator*(const Vector3& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
        Vector3& operator*=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }

        Vector3 operator/(const Vector3& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
        Vector3& operator/=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

        Vector3 operator-() const { return { -x, -y, -z }; }

        float& operator[](int dim)
        {
            if (dim < 0 || dim > 2) throw std::out_of_range("Vector3 index out of range");
            return v[dim];
        }
        const float& operator[](int dim) const
        {
            if (dim < 0 || dim > 2) throw std::out_of_range("Vector3 index out of range");
            return v[dim];
        }

        bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }
        bool Equals(const Vector3& rhs, float tol = 1e-6f) const
        {
            return std::fabs(x - rhs.x) < tol &&
                std::fabs(y - rhs.y) < tol &&
                std::fabs(z - rhs.z) < tol;
        }

        std::string ToString() const
        {
            std::ostringstream ss;
            ss << "(" << x << ", " << y << ", " << z << ")";
            return ss.str();
        }
    };

    inline Vector3 operator*(float s, const Vector3& v) { return v * s; }
}
