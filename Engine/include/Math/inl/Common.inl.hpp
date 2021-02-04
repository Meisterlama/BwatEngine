#ifndef MATH_COMMON_INL_HPP
#define MATH_COMMON_INL_HPP

// Currently only wrapping std functions


[[nodiscard]] ML_FUNC_DECL float ToRads(float x)
{
    return (x / 180) * PI;
}

[[nodiscard]] ML_FUNC_DECL float ToDegs(float x)
{
    return (x / PI) * 180;
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

#endif //MATH_COMMON_INL_HPP