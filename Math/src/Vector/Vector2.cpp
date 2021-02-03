#include "Meta.hpp"
#include "Vector/Vector2.hpp"

namespace Math {
    template<typename T>
    ML_FUNC_DECL float Vector2<T>::DotProduct(const Vector2 &v) const {
        return (X * v.X + Y * v.Y);
    }

    template<typename T>
    ML_FUNC_DECL float Vector2<T>::Amplitude() const {
        return DotProduct(*this);
    }

    template<typename T>
    ML_FUNC_DECL float Vector2<T>::Length() const {
        return std::sqrt(Amplitude());
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::Add(const Vector2 &vec) {
        *this += vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::Sub(const Vector2 &vec) {
        *this -= vec;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::Scale(const float &factor) {
        *this *= factor;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetScaled(const float &factor) const {
        return *this * factor;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::Normalize() {
        *this /= Length();
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetNormalized() const {
        return Vector2{*this} / Length();
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::SafeNormalize() {
        if (Amplitude() == 0) return *this;
        return Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::GetSafeNormalized() const {
        if (Amplitude() == 0) return Vector2<T>{0};
        return GetNormalized();
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::Equals(const Vector2 &rhs) const {
        return *this == rhs;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::IsZero() const {
        return *this == Vector2<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator=(const Vector2 &other) {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::operator==(const Vector2 &rhs) const {
        return (X == rhs.X &&
                Y == rhs.Y);
    }

    template<typename T>
    ML_FUNC_DECL bool Vector2<T>::operator!=(const Vector2 &rhs) const {
        return !(*this == rhs);
    }

    template<typename T>
    ML_FUNC_DECL const T &Vector2<T>::operator[](int idx) const {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL T &Vector2<T>::operator[](int idx) {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator+(const Vector2 &rhs) const {
        return Vector2<T>{X + rhs.X,
                          Y + rhs.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator+=(const Vector2 &vec) {
        X += vec.X;
        Y += vec.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator++() {
        X++;
        Y++;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator-(const Vector2 &rhs) const {
        return Vector2<T>{X - rhs.X,
                          Y - rhs.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator-=(const Vector2 &vec) {
        X -= vec.X;
        Y -= vec.Y;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator--() {
        X--;
        Y--;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator-(Vector2<T> vec) {
        return Vector2<T>{-vec.X, -vec.Y};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator*(const float &scalar) const {
        return Vector2<T>{X * scalar,
                          Y * scalar};
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Vector2<T> operator*(const float &scalar, Vector2<T> rhs) {
        return rhs * scalar;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator*=(const float &scalar) {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Vector2<T>::operator/(const float &scalar) const {
        return Vector2<T>{X / scalar,
                          Y / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> &Vector2<T>::operator/=(const float &scalar) {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Vector2<T> Lerp(Vector2<T> begin, Vector2<T> end, float ratio) {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ? 0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }
}