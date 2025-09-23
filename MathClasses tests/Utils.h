#pragma once

#include <cmath>
#include <numbers> // for std::numbers::pi_v (C++20)

namespace MathClasses
{
    /* Maximum tolerance for comparing floats
     *
     * Alternatively written as "1.e-4f" or read as "1 times 10 to the power of -4".
     */
    constexpr float MAX_FLOAT_DELTA = 0.0001f;

    /* The former is a constant equivalent to Unreal Engine's default threshold.
     *
     * We can ensure this is applicable to our environment by using a
     * static_assert, which is checked at compile time.
     */
    static_assert(1.0e-4f == MAX_FLOAT_DELTA);

    // Check approximate equality
    template<typename T>
    inline bool ApproximatelyEquals(const T& a, const T& b, const T& Threshold = MAX_FLOAT_DELTA)
    {
        return std::abs(a - b) < Threshold;
    }

    // Compute angle from 2D vector (x, y)
    inline float AngleFrom2D(float x, float y)
    {
        return std::atan2(y, x);
    }

    // Linear interpolation
    template<typename T, typename A>
    inline T Lerp(const T& Start, const T& End, const A& Alpha)
    {
        return Start + (End - Start) * Alpha;
    }

    /* Constant for Pi
     * Prefer std::numbers::pi_v<float> (C++20) instead of this.
     */
    [[deprecated("Use std::numbers::pi_v<float> instead.")]]
    constexpr float Pi = 3.14159265358979323846264338327950288f;

    // Degrees <-> Radians conversions
    constexpr float Deg2Rad = std::numbers::pi_v<float> / 180.0f;
    constexpr float Rad2Deg = 180.0f / std::numbers::pi_v<float>;
}
