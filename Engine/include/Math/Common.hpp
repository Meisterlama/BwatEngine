#ifndef MATH_COMMON_HPP
#define MATH_COMMON_HPP

#include "Math/Meta.hpp"
#include <cmath>
#include <algorithm>

// Currently only wrapping std functions
namespace BwatEngine::Math
{

#pragma region Declarations

    [[nodiscard]] ML_FUNC_DECL float ToRads(float x);

    [[nodiscard]] ML_FUNC_DECL float ToDegs(float x);

    [[nodiscard]] ML_FUNC_DECL float Clamp(float x, float minVal, float maxVal);

    [[nodiscard]] ML_FUNC_DECL float Sin(float x);

    [[nodiscard]] ML_FUNC_DECL float Asin(float x);

    [[nodiscard]] ML_FUNC_DECL float Cos(float x);

    [[nodiscard]] ML_FUNC_DECL float Acos(float x);

    [[nodiscard]] ML_FUNC_DECL float Tan(float x);

    [[nodiscard]] ML_FUNC_DECL float Atan(float x);
    [[nodiscard]] ML_FUNC_DECL float Atan2(float x, float y);

    [[nodiscard]] ML_FUNC_DECL float Abs(float x);

    [[nodiscard]] ML_FUNC_DECL float Pow(float x, float y);

    [[nodiscard]] ML_FUNC_DECL float Sqrt(float x);

    [[nodiscard]] ML_FUNC_DECL float Exp(float x);

    [[nodiscard]] ML_FUNC_DECL float Log(float x);

    [[nodiscard]] ML_FUNC_DECL float Log10(float x);

    [[nodiscard]] ML_FUNC_DECL float Log2(float x);

    [[nodiscard]] ML_FUNC_DECL float Floor(float x);

    [[nodiscard]] ML_FUNC_DECL float Ceil(float x);

    [[nodiscard]] ML_FUNC_DECL float Round(float x);

    [[nodiscard]] ML_FUNC_DECL float Trunc(float x);

#pragma endregion

#ifdef BMATH_IMPLEMENTATION
#pragma region Definitions

    [[nodiscard]] ML_FUNC_DECL float ToRads(float x)
    {
        return (x / 180) * PI;
    }

    [[nodiscard]] ML_FUNC_DECL float ToDegs(float x)
    {
        return (x / PI) * 180;
    }

    [[nodiscard]] ML_FUNC_DECL float Clamp(float x, float minVal, float maxVal)
    {
        return std::min(std::max(x, minVal), maxVal);
    }

    [[nodiscard]] ML_FUNC_DECL float Sin(float x)
    {
        return std::sin(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Asin(float x)
    {
        return std::asin(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Cos(float x)
    {
        return std::cos(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Acos(float x)
    {
        return std::acos(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Tan(float x)
    {
        return std::tan(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Atan(float x)
    {
        return std::atan(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Atan2(float x, float y)
    {
        return std::atan2(x, y);
    }

    [[nodiscard]] ML_FUNC_DECL float Abs(float x)
    {
        return (x < 0) ? -x : x;
    }

    [[nodiscard]] ML_FUNC_DECL float Pow(float x, float y)
    {
        return std::pow(x, y);
    }

    [[nodiscard]] ML_FUNC_DECL float Sqrt(float x)
    {
        return std::sqrt(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Exp(float x)
    {
        return std::exp(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Log(float x)
    {
        return std::log(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Log10(float x)
    {
        return std::log10(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Log2(float x)
    {
        return std::log2(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Floor(float x)
    {
        return std::floor(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Ceil(float x)
    {
        return std::ceil(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Round(float x)
    {
        return std::round(x);
    }

    [[nodiscard]] ML_FUNC_DECL float Trunc(float x)
    {
        return std::trunc(x);
    }

#pragma endregion
#endif //BMATH_IMPLEMENTATION
}

#endif //MATH_COMMON_HPP