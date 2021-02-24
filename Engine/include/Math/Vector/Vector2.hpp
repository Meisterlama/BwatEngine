//
// Created by lama on 16/12/2020.
//

#ifndef MATH_VECTOR2_HPP
#define MATH_VECTOR2_HPP

#include "Math/Meta.hpp"

namespace BMath
{

#pragma region Declarations

    template<typename T>
    class Vector2
    {
    public:
        union
        {
            struct
            {
                T X;
                T Y;
            };
            T values[2];
        };

        ML_FUNC_DECL Vector2(T x = 0)
            : X(x), Y(x)
        {}

        ML_FUNC_DECL Vector2(T x, T y)
            : X(x), Y(y)
        {}

        ML_FUNC_DECL Vector2(const Vector2& vec) = default;
        ML_FUNC_DECL Vector2(Vector2&& vec) noexcept = default;

        template<typename U>
        ML_FUNC_DECL Vector2(const Vector2<U>& vec)
            : X(static_cast<T>(vec.X)), Y(static_cast<T>(vec.Y))
        {}

        ~Vector2() = default;

        [[nodiscard]] ML_FUNC_DECL float DotProduct(const Vector2& v) const;

        // Compute the amplitude without computing the sqrt
        // Valid for comparisons, but actually equals to length squared
        [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

        // Return the length of the vector
        // If you only need it for comparison consider using Amplitude()
        [[nodiscard]] ML_FUNC_DECL float Length() const;

        // Scale in place
        ML_FUNC_DECL Vector2& Scale(const float& factor);

        // Get a scaled copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector2 GetScaled(const float& factor) const;

        // Normalize in place
        ML_FUNC_DECL Vector2& Normalize();

        // Get a normalized copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector2 GetNormalized() const;

        // Normalize in place.
        // Check for length != 0
        ML_FUNC_DECL Vector2& SafeNormalize();

        // Get a normalized copy of the vector
        // If vector length == 0, return Vector{0}
        [[nodiscard]] ML_FUNC_DECL Vector2 GetSafeNormalized() const;

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Vector2& rhs) const;
        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Vector2& operator=(const Vector2& other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Vector2& rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Vector2& rhs) const;

        [[nodiscard]] ML_FUNC_DECL const T& operator[](int idx) const;
        [[nodiscard]] ML_FUNC_DECL T& operator[](int idx);

        ML_FUNC_DECL Vector2& Add(const Vector2& vec);
        [[nodiscard]] ML_FUNC_DECL Vector2 operator+(const Vector2& rhs) const;
        ML_FUNC_DECL Vector2& operator+=(const Vector2& vec);
        ML_FUNC_DECL Vector2& operator++();

        ML_FUNC_DECL Vector2& Sub(const Vector2& vec);
        [[nodiscard]] ML_FUNC_DECL Vector2 operator-(const Vector2& rhs) const;
        ML_FUNC_DECL Vector2& operator-=(const Vector2& vec);
        ML_FUNC_DECL Vector2& operator--();

        [[nodiscard]] ML_FUNC_DECL Vector2 operator*(const float& scalar) const;
        ML_FUNC_DECL Vector2& operator*=(const float& scalar);

        [[nodiscard]] ML_FUNC_DECL Vector2 operator/(const float& scalar) const;
        ML_FUNC_DECL Vector2& operator/=(const float& scalar);


    };

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator-(Vector2<T> vec);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator*(const float& scalar, Vector2<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> Lerp(Vector2<T> begin, Vector2<T> end, float ratio);

#pragma endregion

#pragma region Definitions

    template<typename T>
    ML_FUNC_DECL float Vector2<T>::DotProduct(const Vector2& v) const
    {
        return (X * v.X + Y * v.Y);
    }

    template<typename T>
    ML_FUNC_DECL float Vector2<T>::Amplitude() const
    {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Vector2<T>::Length() const
    {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::Add(const Vector2& vec)
    {
        *this += vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::Sub(const Vector2& vec)
    {
        *this -= vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::Scale(const float& factor)
    {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetScaled(const float& factor) const
    {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::Normalize()
    {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetNormalized() const
    {
        return Vector2{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::SafeNormalize()
    {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetSafeNormalized() const
    {
        if (Amplitude() == 0) return Vector2<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::Equals(const Vector2& rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::IsZero() const
    {
        return *this == Vector2<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator=(const Vector2& other)
    {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::operator==(const Vector2& rhs) const
    {
        return (X == rhs.X &&
                Y == rhs.Y);
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::operator!=(const Vector2& rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T& Vector2<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T& Vector2<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator+(const Vector2& rhs) const
    {
        return Vector2<T>{X + rhs.X,
                          Y + rhs.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator+=(const Vector2& vec)
    {
        X += vec.X;
        Y += vec.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator++()
    {
        X++;
        Y++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator-(const Vector2& rhs) const
    {
        return Vector2<T>{X - rhs.X,
                          Y - rhs.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator-=(const Vector2& vec)
    {
        X -= vec.X;
        Y -= vec.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator--()
    {
        X--;
        Y--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator-(Vector2<T> vec)
    {
        return Vector2<T>{-vec.X, -vec.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator*(const float& scalar) const
    {
        return Vector2<T>{X * scalar,
                          Y * scalar};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator*(const float& scalar, Vector2<T> rhs)
    {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator*=(const float& scalar)
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator/(const float& scalar) const
    {
        return Vector2<T>{X / scalar,
                          Y / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T>& Vector2<T>::operator/=(const float& scalar)
    {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Lerp(Vector2<T> begin, Vector2<T> end, float ratio) {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ?  0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }

#pragma endregion

}
#endif //MATH_VECTOR2_HPP
