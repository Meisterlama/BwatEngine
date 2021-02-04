//
// Created by lama on 16/12/2020.
//

#ifndef MATH_VECTOR3_HPP
#define MATH_VECTOR3_HPP

#include "Math/Meta.hpp"

namespace Math
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

        ML_FUNC_DECL Vector3(const Vector3& vec) = default;
        ML_FUNC_DECL Vector3(Vector3&& vec) noexcept = default;
        ~Vector3() = default;

        [[nodiscard]] ML_FUNC_DECL float DotProduct(const Vector3& v) const;

        // Compute the amplitude without computing the sqrt
        // Valid for comparisons, but actually equals to length squared
        [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

        // Return the length of the vector
        // If you only need it for comparison consider using Amplitude()
        [[nodiscard]] ML_FUNC_DECL float Length() const;

        // Scale in place
        ML_FUNC_DECL Vector3& Scale(const float& factor);

        // Get a scaled copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector3 GetScaled(const float& factor) const;

        // Normalize in place
        ML_FUNC_DECL Vector3& Normalize();

        // Get a normalized copy of the vector
        [[nodiscard]] ML_FUNC_DECL Vector3 GetNormalized() const;

        // Normalize in place.
        // Check for length != 0
        ML_FUNC_DECL Vector3& SafeNormalize();

        // Get a normalized copy of the vector
        // If vector length == 0, return Vector{0}
        [[nodiscard]] ML_FUNC_DECL Vector3 GetSafeNormalized() const;

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Vector3& rhs) const;
        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Vector3& operator=(const Vector3& other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Vector3& rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Vector3& rhs) const;

        [[nodiscard]] ML_FUNC_DECL const T& operator[](int idx) const;
        [[nodiscard]] ML_FUNC_DECL T& operator[](int idx);

        ML_FUNC_DECL Vector3& Add(const Vector3& vec);
        [[nodiscard]] ML_FUNC_DECL Vector3 operator+(const Vector3& rhs) const;
        ML_FUNC_DECL Vector3& operator+=(const Vector3& vec);
        ML_FUNC_DECL Vector3& operator++();

        ML_FUNC_DECL Vector3& Sub(const Vector3& vec);
        [[nodiscard]] ML_FUNC_DECL Vector3 operator-(const Vector3& rhs) const;
        ML_FUNC_DECL Vector3& operator-=(const Vector3& vec);
        ML_FUNC_DECL Vector3& operator--();

        [[nodiscard]] ML_FUNC_DECL Vector3 operator*(const float& scalar) const;
        ML_FUNC_DECL Vector3& operator*=(const float& scalar);

        [[nodiscard]] ML_FUNC_DECL Vector3 operator/(const float& scalar) const;
        ML_FUNC_DECL Vector3& operator/=(const float& scalar);

    };
    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector3<T> operator-(Vector3<T> vec);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector3<T> operator*(const float& scalar, Vector3<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector3<T> Lerp(Vector3<T> begin, Vector3<T> end, float ratio);

    #include "inl/Vector3.inl.hpp"
}
#endif //MATH_VECTOR3_HPP
