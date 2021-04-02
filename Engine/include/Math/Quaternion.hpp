
#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

#include "Math/Vector/Vectors.hpp"
#include "Math/Common.hpp"

namespace BwatEngine::Math
{

#pragma region Declarations
    namespace Internal
    {
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
                : W(x), X(x), Y(x), Z(x)
            {}

            ML_FUNC_DECL Quaternion(T w, T x, T y, T z)
                : W(w), X(x), Y(y), Z(z)
            {}

            /**
             * Create a Quaternion with each component equals to the vector's one
             * @remark The vector's constructor is (X, Y, Z, W) while the quaternion's one is (W,X,Y,Z)
             */
            ML_FUNC_DECL Quaternion(Vector4<T> vec)
                : W(vec.W), X(vec.X), Y(vec.Y), Z(vec.Z)
            {}

            /**
             * Create a Quaternion with the rotation represented by \p vec
             * @param vec Euler angle rotation (in radians)
             */
            ML_FUNC_DECL Quaternion(Vector3<T> vec)
            {
                T cx = Cos(vec.X / 2);
                T cy = Cos(vec.Y / 2);
                T cz = Cos(vec.Z / 2);
                T sx = Sin(vec.X / 2);
                T sy = Sin(vec.Y / 2);
                T sz = Sin(vec.Z / 2);

                W = cx * cy * cz + sx * sy * sz;
                X = sx * cy * cz - cx * sy * sz;
                Y = cx * sy * cz + sx * cy * sz;
                Z = cx * cy * sz - sx * sy * cz;
            }

            /**
             * Create a quaternion corresponding to the given rotation
             * @param roll  Rotation around X axis (in radians)
             * @param pitch Rotation around Y axis (in radians)
             * @param yaw   Rotation around Z axis (in radians)
             */
            ML_FUNC_DECL Quaternion(T pitch, T yaw, T roll)
            {
                *this = Quaternion{Vector3<T>{pitch, yaw, roll}};
            }

            /**
             * Create a quaterion corresponding to the rotation of \p angle around the given \p axis
             * @param axis Axis of the rotation
             * @param angle Angle of the rotation (in radians)
             */
            ML_FUNC_DECL Quaternion(Vector3<T> axis, T angle)
            {
                if (Vector3Length(axis) != 0.0f) {
                    *this = Quaternion{0};
                    return;
                }

                angle *= 0.5;
                axis.Normalize();

                float s = Sin(angle);
                float c = Cos(angle);

                *this = Quaternion<T>(axis.X * s, axis.Y * s, axis.Z * s, axis.W * c);
            }

            ML_FUNC_DECL Quaternion(const Quaternion &quat) = default;

            ML_FUNC_DECL Quaternion(Quaternion &&quat) noexcept = default;

            ~Quaternion() = default;

            /**
             * @remark Valid for comparisons, but actually equals to length squared, at the benefits of not computing sqrt
             * @return The amplitude of the quaternion
             */
            [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

            /**
             * @remark If you only need it for comparison consider using Amplitude()
             * @return The norm of the quaternion
             */
            [[nodiscard]] ML_FUNC_DECL float Norm() const;

            /**
             * Compute the dot product between two Quaternion, similarly to Vector4
             */
            [[nodiscard]] ML_FUNC_DECL float DotProduct(const Quaternion &q) const;

            /**
             * @brief Scale the Quaternion in place
             * @param factor Factor of the uniform scale
             * @return A reference to self
             */
            ML_FUNC_DECL Quaternion &Scale(const float &factor);

            /**
             * @param factor Factor of the uniform scale
             * @return A scaled copy of the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Quaternion GetScaled(const float &factor) const;

            /**
             * @brief Normalize the Quaternion in place
             * @warning Does not check for norm == 0
             * @return A reference to self
             */
            ML_FUNC_DECL Quaternion &Normalize();

            /**
             * @return A normalized copy of the Quaternion
             * @warning Does not check for norm == 0
             */
            [[nodiscard]] ML_FUNC_DECL Quaternion GetNormalized() const;

            /**
             * @brief Normalize the Quaternion in place
             * @remark If norm == 0, does nothing
             * @return A reference to self
             */
            ML_FUNC_DECL Quaternion &SafeNormalize();

            /**
             * @remark If norm == 0, return Quaternion{0}
             * @return Return a normalized copy of the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Quaternion GetSafeNormalized() const;

            /**
             * @brief Conjugate the Quaternion in place
             * @return A reference to self
             */
            ML_FUNC_DECL Quaternion &Conjugate();

            /**
             * @return A conjugated copy of the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Quaternion GetConjugate() const;

            /**
             * @brief Invert the quaternion in place
             * @return A reference to self
             */
            ML_FUNC_DECL Quaternion &Invert();

            /**
             * @return An inverted copy of the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Quaternion GetInverted() const;

            /**
             * @return A vector containing the euler angles corresponding to the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Vector3<T> GetEulerAngles();

            /**
             * @param vec Euler angles of the rotation (in radians)
             * @return The given vector \p vec composed with the rotation given by the Quaternion
             */
            [[nodiscard]] ML_FUNC_DECL Vector3<T> Rotate(Vector3<T> vec);

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
    }
    typedef Internal::Quaternion<float> Quatf;
    typedef Internal::Quaternion<double> Quatd;
}
    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Quaternion<T> operator-(BwatEngine::Math::Internal::Quaternion<T> quat);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Quaternion<T> operator*(const float &scalar, BwatEngine::Math::Internal::Quaternion<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Quaternion<T> Lerp(BwatEngine::Math::Internal::Quaternion<T> begin, BwatEngine::Math::Internal::Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Quaternion<T> NLerp(BwatEngine::Math::Internal::Quaternion<T> begin, BwatEngine::Math::Internal::Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Quaternion<T> SLerp(BwatEngine::Math::Internal::Quaternion<T> begin, BwatEngine::Math::Internal::Quaternion<T> end, float ratio);

#pragma endregion

#pragma region Definitions
namespace BwatEngine::Math
{
    template<typename T>
    ML_FUNC_DECL float Internal::Quaternion<T>::Amplitude() const
    {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Internal::Quaternion<T>::Norm() const
    {
        return Sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL float Internal::Quaternion<T>::DotProduct(const Internal::Quaternion<T> &q) const
    {
        return (X * q.X + Y * q.Y + Z * q.Z + W * q.W);
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Add(const Internal::Quaternion<T> &quat)
    {
        *this += quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Sub(const Internal::Quaternion<T> &quat)
    {
        *this -= quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Mul(const Internal::Quaternion<T> &quat)
    {
        *this *= quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Scale(const float &factor)
    {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::GetScaled(const float &factor) const
    {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Normalize()
    {
        *this /= Norm();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::GetNormalized() const
    {
        return Internal::Quaternion{*this} / Norm();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::SafeNormalize()
    {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::GetSafeNormalized() const
    {
        if (Amplitude() == 0) return Internal::Quaternion<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Conjugate()
    {
        X *= -1;
        Y *= -1;
        Z *= -1;

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::GetConjugate() const
    {
        return Internal::Quaternion<T>{W, -X, -Y, -Z};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::Invert()
    {
        *this = Conjugate() / Amplitude();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::GetInverted() const
    {
        *this = Conjugate() / Amplitude();
        return *this;
    }

    template <typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Vector3<T> Internal::Quaternion<T>::GetEulerAngles()
    {
        Normalize();
        float pitch;
        float yaw;
        float roll;
        // roll (x-axis rotation)
        T p0 = 2.0 * (Y * Z + W * X);
        T p1 = W*W - X*X - Y*Y + Z*Z;

        if (p0 == 0 && p1 == 0)
            pitch = 2 * Atan2(X, W);
        else
            pitch = Atan2(p0, p1);

        T y0 = -2 * (X*Z - W*Y);
        y0 = Clamp(y0, -1, 1);
        yaw = Asin(y0);

        T r0 = 2 * (X*Y + W*Z);
        T r1 = W*W + X*X - Y*Y - Z*Z;

        roll = Atan2(r0, r1);


        return {pitch, yaw, roll};
    }
    template <typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Vector3<T> Internal::Quaternion<T>::Rotate(Vector3<T> v)
    {
        return Vector3<T>{v.X*(X*X + W*W - Y*Y - Z*Z) + v.Y*(2*X*Y - 2*W*Z) + v.Z*(2*X*Z + 2*W*Y),
                          v.X*(2*W*Z + 2*X*Y) + v.Y*(W*W - X*X + Y*Y - Z*Z) + v.Z*(-2*W*X + 2*Y*Z),
                          v.X*(-2*W*Y + 2*X*Z) + v.Y*(2*W*X + 2*Y*Z)+ v.Z*(W*W - X*X - Y*Y + Z*Z)};
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Quaternion<T>::Equals(const Internal::Quaternion<T> &rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Quaternion<T>::IsZero() const
    {
        return *this == Internal::Quaternion<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator=(const Internal::Quaternion<T> &other)
    {
        W = other.W;
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Quaternion<T>::operator==(const Internal::Quaternion<T> &rhs) const
    {
        return (X == rhs.X &&
                Y == rhs.Y &&
                Z == rhs.Z &&
                W == rhs.W);
    }

    template<typename T>
    ML_FUNC_DECL bool Internal::Quaternion<T>::operator!=(const Internal::Quaternion<T> &rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T &Internal::Quaternion<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T &Internal::Quaternion<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::operator+(const Internal::Quaternion<T> &rhs) const
    {
        return Internal::Quaternion<T>{W + rhs.W,
                                       X + rhs.X,
                                       Y + rhs.Y,
                                       Z + rhs.Z
                                      };
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator+=(const Internal::Quaternion<T> &quat)
    {
        W += quat.W;
        X += quat.X;
        Y += quat.Y;
        Z += quat.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator++()
    {
        X++;
        Y++;
        Z++;
        W++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::operator-(const Internal::Quaternion<T> &rhs) const
    {
        return Internal::Quaternion<T>{X - rhs.W,
                                       X - rhs.X,
                                       Y - rhs.Y,
                                       Z - rhs.Z
                                      };
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator-=(const Internal::Quaternion<T> &quat)
    {
        W -= quat.W;
        X -= quat.X;
        Y -= quat.Y;
        Z -= quat.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator--()
    {
        W--;
        X--;
        Y--;
        Z--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Quaternion<T> operator-(Internal::Quaternion<T> quat)
    {
        return Internal::Quaternion<T>{-quat.W, -quat.X, -quat.Y, -quat.Z};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::operator*(const Internal::Quaternion<T> &quat) const
    {
        return Internal::Quaternion<T>{W * quat.W - X * quat.X - Y * quat.Y - Z * quat.Z,
                             W * quat.X + X * quat.W + Y * quat.Z - Z * quat.Y,
                             W * quat.Y + Y * quat.W + Z * quat.X - X * quat.Z,
                             W * quat.Z + Z * quat.W + X * quat.Y - Y * quat.X};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator*=(const Internal::Quaternion<T> &quat)
    {
        *this = *this * quat;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::operator*(const float &scalar) const
    {
        return Internal::Quaternion<T>{W * scalar,
                                       X * scalar,
                                       Y * scalar,
                                       Z * scalar
                                      };
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Quaternion<T> operator*(const float &scalar, Internal::Quaternion<T> rhs)
    {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator*=(const float &scalar)
    {
        W *= scalar;
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Internal::Quaternion<T>::operator/(const float &scalar) const
    {
        return Internal::Quaternion<T>{W / scalar,
                                       X / scalar,
                                       Y / scalar,
                                       Z / scalar
                                      };
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> &Internal::Quaternion<T>::operator/=(const float &scalar)
    {
        W /= scalar;
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> Lerp(Internal::Quaternion<T> begin, Internal::Quaternion<T> end, float ratio)
    {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> NLerp(Internal::Quaternion<T> begin, Internal::Quaternion<T> end, float ratio)
    {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
        return Internal::Quaternion<T>{(1 - ratio) * begin + ratio * end}.Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Quaternion<T> SLerp(Internal::Quaternion<T> begin, Internal::Quaternion<T> end, float ratio)
    {
        float cosHalfTheta = begin.X * end.X + begin.Y * end.Y + begin.Z * end.Z + begin.W * end.W;

        if (Abs(cosHalfTheta) >= 1.0) return begin;
        if (cosHalfTheta > 0.95) return NLerp(begin, end, ratio);

        float halfTheta = Acos(cosHalfTheta);
        float sinHalfTheta = Sqrt(1.0 - cosHalfTheta * cosHalfTheta);

        if (Abs(sinHalfTheta) < 0.001)
            return Internal::Quaternion<T>{
                    begin.X * 0.5 + end.X * 0.5,
                    begin.Y * 0.5 + end.Y * 0.5,
                    begin.Z * 0.5 + end.Z * 0.5,
                    begin.W * 0.5 + end.W * 0.5};
        float ratioA = Sin((1 - ratio) * halfTheta) / sinHalfTheta;
        float ratioB = Sin(ratio * halfTheta) / sinHalfTheta;

        return Internal::Quaternion<T>{(begin.W * ratioA + end.W * ratioB),
                                       (begin.X * ratioA + end.X * ratioB),
                                       (begin.Y * ratioA + end.Y * ratioB),
                                       (begin.Z * ratioA + end.Z * ratioB),
                                      };
    }

#pragma endregion

}

#endif //MATH_QUATERNION_HPP