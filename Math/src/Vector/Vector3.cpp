#include "Vector/Vector3.hpp"

namespace Math
{
    template<typename T>
    ML_FUNC_DECL float Vector3<T>::DotProduct(const Vector3 &v) const {
        return (X * v.X + Y * v.Y + Z * v.Z);
    }

    template<typename T>
    ML_FUNC_DECL float Vector3<T>::Amplitude() const {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Vector3<T>::Length() const {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::Add(const Vector3 &vec) {
        *this += vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::Sub(const Vector3 &vec) {
        *this -= vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::Scale(const float &factor) {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::GetScaled(const float &factor) const {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::Normalize() {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::GetNormalized() const {
        return Vector3{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::SafeNormalize() {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::GetSafeNormalized() const {
        if (Amplitude() == 0) return Vector3<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL bool Vector3<T>::Equals(const Vector3 &rhs) const {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector3<T>::IsZero() const {
        return *this == Vector3<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator=(const Vector3 &other) {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector3<T>::operator==(const Vector3 &rhs) const {
        return (X == rhs.X &&
                Y == rhs.Y &&
                Z == rhs.Z);
    }

    template<typename T>
    ML_FUNC_DECL bool Vector3<T>::operator!=(const Vector3 &rhs) const {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T &Vector3<T>::operator[](int idx) const {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T &Vector3<T>::operator[](int idx) {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::operator+(const Vector3 &rhs) const {
        return Vector3<T>{X + rhs.X,
                          Y + rhs.Y,
                          Z + rhs.Z};
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator+=(const Vector3 &vec) {
        X += vec.X;
        Y += vec.Y;
        Z += vec.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator++() {
        X++;
        Y++;
        Z++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::operator-(const Vector3 &rhs) const {
        return Vector3<T>{X - rhs.X,
                          Y - rhs.Y,
                          Z - rhs.Z};
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator-=(const Vector3 &vec) {
        X -= vec.X;
        Y -= vec.Y;
        Z -= vec.Z;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator--() {
        X--;
        Y--;
        Z--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector3<T> operator-(Vector3<T> vec) {
        return Vector3<T>{-vec.X, -vec.Y, -vec.Z};
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::operator*(const float &scalar) const {
        return Vector3<T>{X * scalar,
                          Y * scalar,
                          Z * scalar};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector3<T> operator*(const float &scalar, Vector3<T> rhs) {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator*=(const float &scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Vector3<T>::operator/(const float &scalar) const {
        return Vector3<T>{X / scalar,
                          Y / scalar,
                          Z / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> &Vector3<T>::operator/=(const float &scalar) {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector3<T> Lerp(Vector3<T> begin, Vector3<T> end, float ratio) {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }
}