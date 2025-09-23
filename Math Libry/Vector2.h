#pragma once
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>


    namespace MathClasses
{
        class Vector2
        {
        public:
            float x, y;
	
            // Constructors
            Vector2() : x(0.0f), y(0.0f) {}
            Vector2(float _x, float _y) : x(_x), y(_y) {}
	
            // Operator overloads
            Vector2 operator+(const Vector2& rhs) const
	{
                return Vector2(x + rhs.x, y + rhs.y);
            }

            Vector2 operator-(const Vector2& rhs) const
            {
                return Vector2(x - rhs.x, y - rhs.y);
            }

            Vector2 operator*(float scalar) const
            {
                return Vector2(x * scalar, y * scalar);
            }

            Vector2 operator/(float scalar) const
            {
                return Vector2(x / scalar, y / scalar);
            }

            // Dot product
            float Dot(const Vector2& rhs) const
            {
                return (x * rhs.x + y * rhs.y);
            }

            // Magnitude
            float Magnitude() const
            {
                return std::sqrt(x * x + y * y);
            }

            // Magnitude squared (faster, no sqrt)
            float MagnitudeSqr() const
            {
                return (x * x + y * y);
            }

            // Normalize (unsafe if zero vector)
            void Normalize()
            {
                float mag = Magnitude();
                if (mag > 0.0f)
	{
                    x /= mag;
                    y /= mag;
                }
            }

            // SafeNormalize (returns zero instead of NaN)
            void SafeNormalize()
            {
                float mag = Magnitude();
                if (mag > 0.0f)
                {
                    x /= mag;
                    y /= mag;
                }
                else
                {
                    x = 0.0f;
                    y = 0.0f;
                }
            }
		
            // Distance between two vectors
            float Distance(const Vector2& rhs) const
            {
                float dx = rhs.x - x;
                float dy = rhs.y - y;
                return std::sqrt(dx * dx + dy * dy);
            }
		
            // Distance squared
            float DistanceSqr(const Vector2& rhs) const
            {
                float dx = rhs.x - x;
                float dy = rhs.y - y;
                return dx * dx + dy * dy;
            }
	};
}
	
