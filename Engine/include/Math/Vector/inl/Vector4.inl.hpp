#ifndef MATH_VECTOR4_INL
#define MATH_VECTOR4_INL


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

#endif //MATH_VECTOR4_INL
