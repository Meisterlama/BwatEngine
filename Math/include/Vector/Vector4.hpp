#ifndef MATH_VECTOR4_HPP
#define MATH_VECTOR4_HPP

#include "Meta.hpp"

namespace Math
{
    template<typename T>
    class Vector4
    {
    public:
        union
        {
            struct
            {
                T X;
                T Y;
                T Z;
                T W;
            };
            T values[4];
        };

        ML_FUNC_DECL Vector4(T x = 0)
                : X(x), Y(x), Z(x), W(x)
        {}

        ML_FUNC_DECL Vector4(T x, T y, T z, T w)
                : X(x), Y(y), Z(z), W(w)
        {}

        ML_FUNC_DECL Vector4(const Vector4& vec) = default;
        ML_FUNC_DECL Vector4(Vector4&& vec) noexcept = default;
        ~Vector4() = default;

        [[nodiscard]] ML_FUNC_DECL float DotProduct(const Vector4& v) const;

        // Compute the amplitude without computing the sqrt
        // Valid for comparisons, but actually equals to length squared
        [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

        // Return the length of the vector
        // If you only need it for comparison consider using Amplitude()
        [[nodiscard]] ML_FUNC_DECL float Length() const;

        // Scale in place
        ML_FUNC_DECL Vector4& Scale(const float& factor);

        // Get a scaled copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector4 GetScaled(const float& factor) const;

        // Normalize in place
        ML_FUNC_DECL Vector4& Normalize();

        // Get a normalized copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector4 GetNormalized() const;

        // Normalize in place.
        // Check for length != 0
        ML_FUNC_DECL Vector4& SafeNormalize();

        // Get a normalized copy of the vector
        // If vector length == 0, return Vector{0}
        [[nodiscard]] ML_FUNC_DECL Vector4 GetSafeNormalized() const;

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Vector4& rhs) const;
        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Vector4& operator=(const Vector4& other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Vector4& rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Vector4& rhs) const;

        [[nodiscard]] ML_FUNC_DECL const T& operator[](int idx) const;
        [[nodiscard]] ML_FUNC_DECL T& operator[](int idx);

        ML_FUNC_DECL Vector4& Add(const Vector4& vec);
        [[nodiscard]] ML_FUNC_DECL Vector4 operator+(const Vector4& rhs) const;
        ML_FUNC_DECL Vector4& operator+=(const Vector4& vec);
        ML_FUNC_DECL Vector4& operator++();

        ML_FUNC_DECL Vector4& Sub(const Vector4& vec);
        [[nodiscard]] ML_FUNC_DECL Vector4 operator-(const Vector4& rhs) const;
        ML_FUNC_DECL Vector4& operator-=(const Vector4& vec);
        ML_FUNC_DECL Vector4& operator--();

        [[nodiscard]] ML_FUNC_DECL Vector4 operator*(const float& scalar) const;
        ML_FUNC_DECL Vector4& operator*=(const float& scalar);

        [[nodiscard]] ML_FUNC_DECL Vector4 operator/(const float& scalar) const;
        ML_FUNC_DECL Vector4& operator/=(const float& scalar);

    };
    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector4<T> operator-(Vector4<T> vec);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector4<T> operator*(const float& scalar, Vector4<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector4<T> Lerp(Vector4<T> begin, Vector4<T> end, float ratio);

}
#endif //MATH_VECTOR4_HPP