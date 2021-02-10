#ifndef MATH_COMMON_HPP
#define MATH_COMMON_HPP

#include "Math/Meta.hpp"

// Currently only wrapping std functions
namespace BMath
{
    [[nodiscard]] ML_FUNC_DECL float ToRads(float x);

    [[nodiscard]] ML_FUNC_DECL float ToDegs(float x);

    [[nodiscard]] ML_FUNC_DECL float Sin(float x);

    [[nodiscard]] ML_FUNC_DECL float Asin(float x);

    [[nodiscard]] ML_FUNC_DECL float Cos(float x);

    [[nodiscard]] ML_FUNC_DECL float Acos(float x);

    [[nodiscard]] ML_FUNC_DECL float Tan(float x);

    [[nodiscard]] ML_FUNC_DECL float Atan(float x);

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

    #include "inl/Common.inl.hpp"
}

#endif //MATH_COMMON_HPP