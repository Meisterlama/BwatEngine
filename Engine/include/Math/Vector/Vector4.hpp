//
// Created by lama on 16/12/2020.
//

#ifndef MATH_VECTOR4_HPP
#define MATH_VECTOR4_HPP

#include "Math/Meta.hpp"

namespace BMath
{

#pragma region Declarations

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

#pragma endregion

#pragma region Definitions

    template<typename T>
    ML_FUNC_DECL float Vector4<T>::DotProduct(const Vector4& v) const
    {
        return (X * v.X + Y * v.Y + Z * v.Z + W * v.W);
    }

    template<typename T>
    ML_FUNC_DECL float Vector4<T>::Amplitude() const
    {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Vector4<T>::Length() const
    {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::Add(const Vector4& vec)
    {
        *this += vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::Sub(const Vector4& vec)
    {
        *this -= vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::Scale(const float& factor)
    {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::GetScaled(const float& factor) const
    {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::Normalize()
    {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::GetNormalized() const
    {
        return Vector4{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::SafeNormalize()
    {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::GetSafeNormalized() const
    {
        if (Amplitude() == 0) return Vector4<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL bool Vector4<T>::Equals(const Vector4& rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector4<T>::IsZero() const
    {
        return *this == Vector4<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator=(const Vector4& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector4<T>::operator==(const Vector4& rhs) const
    {
        return (X == rhs.X &&
                Y == rhs.Y &&
                Z == rhs.Z &&
                W == rhs.W);
    }

    template<typename T>
    ML_FUNC_DECL bool Vector4<T>::operator!=(const Vector4& rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T& Vector4<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T& Vector4<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::operator+(const Vector4& rhs) const
    {
        return Vector4<T>{X + rhs.X,
                          Y + rhs.Y,
                          Z + rhs.Z,
                          W + rhs.W};
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator+=(const Vector4& vec)
    {
        X += vec.X;
        Y += vec.Y;
        Z += vec.Z;
        W += vec.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator++()
    {
        X++;
        Y++;
        Z++;
        W++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::operator-(const Vector4& rhs) const
    {
        return Vector4<T>{X - rhs.X,
                          Y - rhs.Y,
                          Z - rhs.Z,
                          W - rhs.W};
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator-=(const Vector4& vec)
    {
        X -= vec.X;
        Y -= vec.Y;
        Z -= vec.Z;
        W -= vec.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator--()
    {
        X--;
        Y--;
        Z--;
        W--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector4<T> operator-(Vector4<T> vec)
    {
        return Vector4<T>{-vec.X, -vec.Y, -vec.Z, -vec.W};
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::operator*(const float& scalar) const
    {
        return Vector4<T>{X * scalar,
                          Y * scalar,
                          Z * scalar,
                          W * scalar};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector4<T> operator*(const float& scalar, Vector4<T> rhs)
    {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator*=(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Vector4<T>::operator/(const float& scalar) const
    {
        return Vector4<T>{X / scalar,
                          Y / scalar,
                          Z / scalar,
                          W / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T>& Vector4<T>::operator/=(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector4<T> Lerp(Vector4<T> begin, Vector4<T> end, float ratio) {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ?  0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }

#pragma endregion

}
#endif //MATH_VECTOR4_HPP
