#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

#include "Math/Vector/Vector3.hpp"

namespace BMath
{

#pragma region Declarations

    template<typename T>
    class Quaternion
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

        ML_FUNC_DECL Quaternion(T x = 0)
                : X(x), Y(x), Z(x), W(x)
        {}

        ML_FUNC_DECL Quaternion(T x, T y, T z, T w)
                : X(x), Y(y), Z(z), W(w)
        {}

        ML_FUNC_DECL Quaternion(Vector3 <T> vec)
                : X(0), Y(vec.X), Z(vec.Y), W(vec.Z)
        {}

        ML_FUNC_DECL Quaternion(T roll, T pitch, T yaw)
        {
            T x0 = Cos(roll / 2);
            T x1 = Sin(roll / 2);
            T y0 = Cos(pitch / 2);
            T y1 = Sin(pitch / 2);
            T z0 = Cos(yaw / 2);
            T z1 = Sin(yaw / 2);

            X = x1 * y0 * z0 - x0 * y1 * z1;
            Y = x0 * y1 * z0 - x1 * y0 * z1;
            Z = x0 * y0 * z1 - x1 * y1 * z0;
            W = x0 * y0 * z0 - x1 * y1 * z1;
        }

        ML_FUNC_DECL Quaternion(const Quaternion &quat) = default;

        ML_FUNC_DECL Quaternion(Quaternion &&quat) noexcept = default;

        ~Quaternion() = default;

        // Compute the amplitude without computing the sqrt
        // Valid for comparisons, but actually equals to length squared
        [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

        // Return the length of the quaternion
        // If you only need it for comparison consider using Amplitude()
        [[nodiscard]] ML_FUNC_DECL float Length() const;

        [[nodiscard]] ML_FUNC_DECL float DotProduct(const Quaternion &q) const;

        // Scale in place
        ML_FUNC_DECL Quaternion &Scale(const float &factor);

        // Get a scaled copy of the quaternion
        [[nodiscard]] ML_FUNC_DECL Quaternion GetScaled(const float &factor) const;

        // Normalize in place
        ML_FUNC_DECL Quaternion &Normalize();

        // Get a normalized copy of the quaternion
        [[nodiscard]] ML_FUNC_DECL Quaternion GetNormalized() const;

        // Normalize in place.
        // Check for length != 0
        ML_FUNC_DECL Quaternion &SafeNormalize();

        // Get a normalized copy of the quaternion
        // If quaternion length == 0, return quaternion{0}
        [[nodiscard]] ML_FUNC_DECL Quaternion GetSafeNormalized() const;

        // Conjugate in place
        ML_FUNC_DECL Quaternion &Conjugate();

        // Get a conjugate copy of the quaternion
        [[nodiscard]] ML_FUNC_DECL Quaternion GetConjugate() const;

        ML_FUNC_DECL Quaternion &Invert();

        [[nodiscard]] ML_FUNC_DECL Quaternion GetInverted() const;

        [[nodiscard]] ML_FUNC_DECL Matrix4 <T> GetRotationMatrix();

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Quaternion &rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Quaternion &operator=(const Quaternion &other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Quaternion &rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Quaternion &rhs) const;

        [[nodiscard]] ML_FUNC_DECL const T &operator[](int idx) const;

        [[nodiscard]] ML_FUNC_DECL T &operator[](int idx);

        ML_FUNC_DECL Quaternion &Add(const Quaternion &quat);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator+(const Quaternion &rhs) const;

        ML_FUNC_DECL Quaternion &operator+=(const Quaternion &quat);

        ML_FUNC_DECL Quaternion &operator++();

        ML_FUNC_DECL Quaternion &Sub(const Quaternion &quat);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator-(const Quaternion &rhs) const;

        ML_FUNC_DECL Quaternion &operator-=(const Quaternion &quat);

        ML_FUNC_DECL Quaternion &operator--();

        ML_FUNC_DECL Quaternion &Mul(const Quaternion &quat);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator*(const Quaternion &quat) const;

        ML_FUNC_DECL Quaternion &operator*=(const Quaternion &quat);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator*(const float &scalar) const;

        ML_FUNC_DECL Quaternion &operator*=(const float &scalar);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator/(const float &scalar) const;

        ML_FUNC_DECL Quaternion &operator/=(const float &scalar);

    };

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator-(Quaternion<T> quat);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator*(const float &scalar, Quaternion<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> Lerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> NLerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> SLerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

#pragma endregion

#pragma region Definitions

    template<typename T>
    ML_FUNC_DECL float Quaternion<T>::Amplitude() const
    {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Quaternion<T>::Length() const
    {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL float Quaternion<T>::DotProduct(const Quaternion &q) const
    {
        return (X * X + Y * Y + Z * Z + W * W);
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Add(const Quaternion &quat)
    {
        *this += quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Sub(const Quaternion &quat)
    {
        *this -= quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Mul(const Quaternion &quat)
    {
        *this *= quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Scale(const float &factor)
    {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::GetScaled(const float &factor) const
    {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Normalize()
    {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::GetNormalized() const
    {
        return Quaternion{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::SafeNormalize()
    {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::GetSafeNormalized() const
    {
        if (Amplitude() == 0) return Quaternion<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Conjugate()
    {
        X *= -1;
        Y *= -1;
        Z *= -1;

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::GetConjugate() const
    {
        return Quaternion<T>{X, Y, Z, W};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::Invert()
    {
        *this = Conjugate() / Amplitude();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::GetInverted() const
    {
        *this = Conjugate() / Amplitude();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Matrix4 <T> Quaternion<T>::GetRotationMatrix()
    {
        float x2 = 2 * (X * X), y2 = 2 * (Y * Y), z2 = 2 * (Z * Z);

        float xy = 2 * (X * Y), xz = 2 * (X * Z), yz = 2 * (Y * Z);
        float xw = 2 * (X * W), yw = 2 * (Y * W), zw = 2 * (Z * W);

        return Matrix4<T>{1 - y2 - z2, xy + zw    , xz - yw    , 0,
                          xy - zw    , 1 - x2 - z2, yz + xw    , 0,
                          xz + yw    , yz - xw    , 1 - x2 - y2, 0,
                          0          , 0          , 0          , 1};
    }

    template<typename T>
    ML_FUNC_DECL bool Quaternion<T>::Equals(const Quaternion &rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Quaternion<T>::IsZero() const
    {
        return *this == Quaternion<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator=(const Quaternion &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Quaternion<T>::operator==(const Quaternion &rhs) const
    {
        return (X == rhs.X &&
                Y == rhs.Y &&
                Z == rhs.Z &&
                W == rhs.W);
    }

    template<typename T>
    ML_FUNC_DECL bool Quaternion<T>::operator!=(const Quaternion &rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T &Quaternion<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T &Quaternion<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::operator+(const Quaternion &rhs) const
    {
        return Quaternion<T>{X + rhs.X,
                             Y + rhs.Y,
                             Z + rhs.Z,
                             W + rhs.W};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator+=(const Quaternion &quat)
    {
        X += quat.X;
        Y += quat.Y;
        Z += quat.Z;
        W += quat.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator++()
    {
        X++;
        Y++;
        Z++;
        W++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::operator-(const Quaternion &rhs) const
    {
        return Quaternion<T>{X - rhs.X,
                             Y - rhs.Y,
                             Z - rhs.Z,
                             W - rhs.W};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator-=(const Quaternion &quat)
    {
        X -= quat.X;
        Y -= quat.Y;
        Z -= quat.Z;
        W -= quat.W;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator--()
    {
        X--;
        Y--;
        Z--;
        W--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator-(Quaternion<T> quat)
    {
        return Quaternion<T>{-quat.X, -quat.Y, -quat.Z, -quat.W};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> Quaternion<T>::operator*(const Quaternion &quat) const
    {
        return Quaternion<T>{W * quat.W - X * quat.X - Y * quat.Y - Z * quat.Z,
                             W * quat.X + X * quat.W + Y * quat.Z - Z * quat.Y,
                             W * quat.Y + Y * quat.W + Z * quat.X - X * quat.Z,
                             W * quat.Z + Z * quat.W + X * quat.Y - Y * quat.X};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator*=(const Quaternion &quat)
    {
        *this = *this * quat;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::operator*(const float &scalar) const
    {
        return Quaternion<T>{X * scalar,
                             Y * scalar,
                             Z * scalar,
                             W * scalar};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator*(const float &scalar, Quaternion<T> rhs)
    {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator*=(const float &scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Quaternion<T>::operator/(const float &scalar) const
    {
        return Quaternion<T>{X / scalar,
                             Y / scalar,
                             Z / scalar,
                             W / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> &Quaternion<T>::operator/=(const float &scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Quaternion<T> Lerp(Quaternion<T> begin, Quaternion<T> end, float ratio)
    {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }

#pragma endregion

}

#endif //MATH_QUATERNION_HPP