//
// Created by lama on 16/12/2020.
//

#ifndef MATH_VECTOR3_HPP
#define MATH_VECTOR3_HPP

#include "Math/Meta.hpp"

namespace BwatEngine::Math
{

#pragma region Declarations

    namespace Internal
    {
        template<typename T>
        class Vector3
        {
        public:
            union
            {
                struct
                {
                    T X;
                    T Y;
                    T Z;
                };
                T values[3];
            };

            ML_FUNC_DECL Vector3(T x = 0)
                : X(x), Y(x), Z(x)
            {}

            ML_FUNC_DECL Vector3(T x, T y, T z)
                : X(x), Y(y), Z(z)
            {}

            ML_FUNC_DECL Vector3(const Vector3 &vec) = default;
            ML_FUNC_DECL Vector3(Vector3 &&vec) noexcept = default;

            template<typename U>
            ML_FUNC_DECL Vector3(const Vector3<U> &vec)
                : X(static_cast<T>(vec.X)), Y(static_cast<T>(vec.Y)), Z(static_cast<T>(vec.Z))
            {}

            ~Vector3() = default;

            [[nodiscard]] ML_FUNC_DECL float DotProduct(const Vector3 &v) const;

            [[nodiscard]] ML_FUNC_DECL Vector3 CrossProduct(const Vector3 &other) const;

            // Compute the amplitude without computing the sqrt
            // Valid for comparisons, but actually equals to length squared
            [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

            // Return the length of the vector
            // If you only need it for comparison consider using Amplitude()
            [[nodiscard]] ML_FUNC_DECL float Length() const;

            // Scale in place
            ML_FUNC_DECL Vector3 &Scale(const float &factor);

            // Get a scaled copy of the vector
            [[nodiscard]] ML_FUNC_DECL Vector3 GetScaled(const float &factor) const;

            // Normalize in place
            ML_FUNC_DECL Vector3 &Normalize();

            // Get a normalized copy of the vector
            [[nodiscard]] ML_FUNC_DECL Vector3 GetNormalized() const;

            // Normalize in place.
            // Check for length != 0
            ML_FUNC_DECL Vector3 &SafeNormalize();

            // Get a normalized copy of the vector
            // If vector length == 0, return Vector{0}
            [[nodiscard]] ML_FUNC_DECL Vector3 GetSafeNormalized() const;

            [[nodiscard]] ML_FUNC_DECL bool Equals(const Vector3 &rhs) const;
            [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

            ML_FUNC_DECL Vector3 &operator=(const Vector3 &other);

            [[nodiscard]] ML_FUNC_DECL bool operator==(const Vector3 &rhs) const;

            [[nodiscard]] ML_FUNC_DECL bool operator!=(const Vector3 &rhs) const;

            [[nodiscard]] ML_FUNC_DECL const T &operator[](int idx) const;
            [[nodiscard]] ML_FUNC_DECL T &operator[](int idx);

            ML_FUNC_DECL Vector3 &Add(const Vector3 &vec);
            [[nodiscard]] ML_FUNC_DECL Vector3 operator+(const Vector3 &rhs) const;
            ML_FUNC_DECL Vector3 &operator+=(const Vector3 &vec);
            ML_FUNC_DECL Vector3 &operator++();

            ML_FUNC_DECL Vector3 &Sub(const Vector3 &vec);
            [[nodiscard]] ML_FUNC_DECL Vector3 operator-(const Vector3 &rhs) const;
            ML_FUNC_DECL Vector3 &operator-=(const Vector3 &vec);
            ML_FUNC_DECL Vector3 &operator--();

            [[nodiscard]] ML_FUNC_DECL Vector3 operator*(const float &scalar) const;
            ML_FUNC_DECL Vector3 &operator*=(const float &scalar);

            [[nodiscard]] ML_FUNC_DECL Vector3 operator/(const float &scalar) const;
            ML_FUNC_DECL Vector3 &operator/=(const float &scalar);

        };
    }

    typedef Internal::Vector3<float> Vec3f;

    typedef Internal::Vector3<double> Vec3d;

    typedef Internal::Vector3<signed int> Vec3i;

    typedef Internal::Vector3<unsigned int> Vec3u;
}
template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> operator-(BwatEngine::Math::Internal::Vector3<T> vec);

template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> operator*(const float &scalar,
                                                                            BwatEngine::Math::Internal::Vector3<T> rhs);

template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> Lerp(BwatEngine::Math::Internal::Vector3<T> begin,
                                                                       BwatEngine::Math::Internal::Vector3<T> end,
                                                                       float ratio);

#pragma endregion

#pragma region Definitions
namespace BwatEngine::Math
{

    template<typename T>
    ML_FUNC_DECL float Internal::Vector3<T>::DotProduct(const Internal::Vector3<T> &v) const
    {
        return (X * v.X + Y * v.Y + Z * v.Z);
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::CrossProduct(const Internal::Vector3<T> &other) const
    {
        return Internal::Vector3<T>{Y * other.Z - other.Y * Z,
                                    Z * other.X - other.Z * X,
                                    X * other.Y - other.X * Y};
    }

    template<typename T>
    ML_FUNC_DECL float Internal::Vector3<T>::Amplitude() const
    {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Internal::Vector3<T>::Length() const
    {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::Add(const Internal::Vector3<T> &vec)
    {
        *this += vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::Sub(const Internal::Vector3<T> &vec)
    {
        *this -= vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::Scale(const float &factor)
    {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::GetScaled(const float &factor) const
    {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::Normalize()
    {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::GetNormalized() const
    {
        return Internal::Vector3{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::SafeNormalize()
    {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::GetSafeNormalized() const
    {
        if (Amplitude() == 0) return Internal::Vector3<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Vector3<T>::Equals(const Internal::Vector3<T> &rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Vector3<T>::IsZero() const
    {
        return *this == Internal::Vector3<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator=(const Internal::Vector3<T> &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Vector3<T>::operator==(const Internal::Vector3<T> &rhs) const
    {
        return (X == rhs.X &&
            Y == rhs.Y &&
            Z == rhs.Z);
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Vector3<T>::operator!=(const Internal::Vector3<T> &rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T &Internal::Vector3<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T &Internal::Vector3<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::operator+(const Internal::Vector3<T> &rhs) const
    {
        return Internal::Vector3<T>{X + rhs.X,
                                    Y + rhs.Y,
                                    Z + rhs.Z};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator+=(const Internal::Vector3<T> &vec)
    {
        X += vec.X;
        Y += vec.Y;
        Z += vec.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator++()
    {
        X++;
        Y++;
        Z++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::operator-(const Internal::Vector3<T> &rhs) const
    {
        return Internal::Vector3<T>{X - rhs.X,
                                    Y - rhs.Y,
                                    Z - rhs.Z};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator-=(const Internal::Vector3<T> &vec)
    {
        X -= vec.X;
        Y -= vec.Y;
        Z -= vec.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator--()
    {
        X--;
        Y--;
        Z--;
        return *this;
    }


    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::operator*(const float &scalar) const
    {
        return Internal::Vector3<T>{X * scalar,
                                    Y * scalar,
                                    Z * scalar};
    }


    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator*=(const float &scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> Internal::Vector3<T>::operator/(const float &scalar) const
    {
        return Internal::Vector3<T>{X / scalar,
                                    Y / scalar,
                                    Z / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector3<T> &Internal::Vector3<T>::operator/=(const float &scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }


}

template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> operator-(BwatEngine::Math::Internal::Vector3<T> vec)
{
    return BwatEngine::Math::Internal::Vector3<T>{-vec.X, -vec.Y, -vec.Z};
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> operator*(const float &scalar, BwatEngine::Math::Internal::Vector3<T> rhs)
{
    return rhs * scalar;
}

template<typename T>
ML_FUNC_DECL BwatEngine::Math::Internal::Vector3<T> Lerp(BwatEngine::Math::Internal::Vector3<T> begin, BwatEngine::Math::Internal::Vector3<T> end, float ratio)
{
    ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
    return (1 - ratio) * begin + ratio * end;
}
#pragma endregion;


#endif //MATH_VECTOR3_HPP
