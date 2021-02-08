#ifndef MATH_MATRIX3_INL_HPP
#define MATH_MATRIX3_INL_HPP

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Transpose()
{
    T tmp = v1;
    v1 = v4;
    v4 = tmp;

    tmp = v2;
    v2 = v8;
    v8 = tmp;

    tmp = v3;
    v3 = v12;
    v12 = tmp;

    tmp = v6;
    v6 = v9;
    v9 = tmp;

    tmp = v7;
    v7 = v13;
    v13 = tmp;

    tmp = v11;
    v11 = v14;
    v14 = tmp;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetTranspose() const
{
    return Matrix4{*this}.Transpose();
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL T Matrix4<T>::GetDeterminant();

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Invert();

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::Invert() const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Scale(float scaleX, float scaleY, float scaleZ);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::Scale(float scaleX, float scaleY, float scaleZ) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::ScaleX(float scale);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::ScaleX(float scale) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::ScaleY(float scale);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::ScaleY(float scale) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::ScaleZ(float scale);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::ScaleZ(float scale) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Rotate(float axisX, float axisY, float axisZ, float angle);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::Rotate(float axisX, float axisY, float axisZ, float angle) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::RotateX(float angle);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::RotateX(float angle) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::RotateY(float angle);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::RotateY(float angle) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::RotateZ(float angle);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::RotateZ(float angle) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Translate(float X, float Y, float Z);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::Translate(float X, float Y, float Z) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::TranslateX(float X);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::TranslateX(float X) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::TranslateY(float Y);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::TranslateY(float Y) const;

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::TranslateZ(float Y);

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::TranslateZ(float Y) const;

template<typename T>
ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetPerspective(float fovy, float aspect, float near, float far);

template<typename T>
ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetOrtho(float left, float right, float bottom, float top, float near, float far);

template<typename T>
[[nodiscard]] ML_FUNC_DECL bool Matrix4<T>::Equals(const Matrix4<T>& rhs) const
{
    return *this == rhs;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL bool Matrix4<T>::IsZero() const
{
    return *this == Matrix4<T>{0};
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& other)
{
    v0  = other.v0;
    v1  = other.v1;
    v2  = other.v2;
    v3  = other.v3;
    v4  = other.v4;
    v5  = other.v5;
    v6  = other.v6;
    v7  = other.v7;
    v8  = other.v8;
    v9  = other.v9;
    v10 = other.v10;
    v11 = other.v11;
    v12 = other.v12;
    v13 = other.v13;
    v14 = other.v14;
    v15 = other.v15;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL bool Matrix4<T>::operator==(const Matrix4<T>& other) const
{
    return (v0  == other.v0  &&
            v1  == other.v1  &&
            v2  == other.v2  &&
            v3  == other.v3  &&
            v4  == other.v4  &&
            v5  == other.v5  &&
            v6  == other.v6  &&
            v7  == other.v7  &&
            v8  == other.v8  &&
            v9  == other.v9  &&
            v10 == other.v10 &&
            v11 == other.v11 &&
            v12 == other.v12 &&
            v13 == other.v13 &&
            v14 == other.v14 &&
            v15 == other.v15);
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL bool Matrix4<T>::operator!=(const Matrix4<T>& other) const
{
    return !(*this == other);
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL const T& Matrix4<T>::operator[](int idx) const
{
    return values[idx];
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL T& Matrix4<T>::operator[](int idx)
{
    return values[idx];
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Add(const Matrix4<T>& other)
{
    *this += other;
    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& other) const
{
    return  Matrix4<T> {v0  + other.v0,
                        v1  + other.v1,
                        v2  + other.v2,
                        v3  + other.v3,
                        v4  + other.v4,
                        v5  + other.v5,
                        v6  + other.v6,
                        v7  + other.v7,
                        v8  + other.v8,
                        v9  + other.v9,
                        v10 + other.v10,
                        v11 + other.v11,
                        v12 + other.v12,
                        v13 + other.v13,
                        v14 + other.v14,
                        v15 + other.v15};
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& other)
{
    v0  += other.v0;
    v1  += other.v1;
    v2  += other.v2;
    v3  += other.v3;
    v4  += other.v4;
    v5  += other.v5;
    v6  += other.v6;
    v7  += other.v7;
    v8  += other.v8;
    v9  += other.v9;
    v10 += other.v10;
    v11 += other.v11;
    v12 += other.v12;
    v13 += other.v13;
    v14 += other.v14;
    v15 += other.v15;

    return *this;
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator++()
{
    v0++;
    v1++;
    v2++;
    v3++;
    v4++;
    v5++;
    v6++;
    v7++;
    v8++;
    v9++;
    v10++;
    v11++;
    v12++;
    v13++;
    v14++;
    v15++;

    return *this;
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Sub(const Matrix4<T>& other)
{
    *this -= other;
    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& other) const
{
    return  Matrix4<T> {v0  - other.v0,
                        v1  - other.v1,
                        v2  - other.v2,
                        v3  - other.v3,
                        v4  - other.v4,
                        v5  - other.v5,
                        v6  - other.v6,
                        v7  - other.v7,
                        v8  - other.v8,
                        v9  - other.v9,
                        v10 - other.v10,
                        v11 - other.v11,
                        v12 - other.v12,
                        v13 - other.v13,
                        v14 - other.v14,
                        v15 - other.v15};
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& other)
{
    v0  -= other.v0;
    v1  -= other.v1;
    v2  -= other.v2;
    v3  -= other.v3;
    v4  -= other.v4;
    v5  -= other.v5;
    v6  -= other.v6;
    v7  -= other.v7;
    v8  -= other.v8;
    v9  -= other.v9;
    v10 -= other.v10;
    v11 -= other.v11;
    v12 -= other.v12;
    v13 -= other.v13;
    v14 -= other.v14;
    v15 -= other.v15;

    return *this;
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator--()
{
    v0--;
    v1--;
    v2--;
    v3--;
    v4--;
    v5--;
    v6--;
    v7--;
    v8--;
    v9--;
    v10--;
    v11--;
    v12--;
    v13--;
    v14--;
    v15--;

    return *this;
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Mult(const Matrix4& other)
{
    *this *= other;
    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& other) const
{
    return Matrix4<T> {v0  * other.v0 + v1  * other.v4  + v2  * other.v8  + v3  * other.v12,
                       v0  * other.v1 + v1  * other.v5  + v2  * other.v9  + v3  * other.v13,
                       v0  * other.v2 + v1  * other.v6  + v2  * other.v10 + v3  * other.v14,
                       v0  * other.v3 + v1  * other.v7  + v2  * other.v11 + v3  * other.v15,
                       v4  * other.v0 + v5  * other.v4  + v6  * other.v8  + v7  * other.v12,
                       v4  * other.v1 + v5  * other.v5  + v6  * other.v9  + v7  * other.v13,
                       v4  * other.v2 + v5  * other.v6  + v6  * other.v10 + v7  * other.v14,
                       v4  * other.v3 + v5  * other.v7  + v6  * other.v11 + v7  * other.v15,
                       v8  * other.v0 + v9  * other.v4  + v10 * other.v8  + v11 * other.v12,
                       v8  * other.v1 + v9  * other.v5  + v10 * other.v9  + v11 * other.v13,
                       v8  * other.v2 + v9  * other.v6  + v10 * other.v10 + v11 * other.v14,
                       v8  * other.v3 + v9  * other.v7  + v10 * other.v11 + v11 * other.v15,
                       v12 * other.v0 + v13 * other.v4  + v14 * other.v8  + v15 * other.v12,
                       v12 * other.v1 + v13 * other.v5  + v14 * other.v9  + v15 * other.v13,
                       v12 * other.v2 + v13 * other.v6  + v14 * other.v10 + v15 * other.v14,
                       v12 * other.v3 + v13 * other.v7  + v14 * other.v11 + v15 * other.v15
                       };
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& other)
{
    v0  = v0  * other.v0 + v1  * other.v4  + v2  * other.v8  + v3  * other.v12;
    v1  = v0  * other.v1 + v1  * other.v5  + v2  * other.v9  + v3  * other.v13;
    v2  = v0  * other.v2 + v1  * other.v6  + v2  * other.v10 + v3  * other.v14;
    v3  = v0  * other.v3 + v1  * other.v7  + v2  * other.v11 + v3  * other.v15;
    v4  = v4  * other.v0 + v5  * other.v4  + v6  * other.v8  + v7  * other.v12;
    v5  = v4  * other.v1 + v5  * other.v5  + v6  * other.v9  + v7  * other.v13;
    v6  = v4  * other.v2 + v5  * other.v6  + v6  * other.v10 + v7  * other.v14;
    v7  = v4  * other.v3 + v5  * other.v7  + v6  * other.v11 + v7  * other.v15;
    v8  = v8  * other.v0 + v9  * other.v4  + v10 * other.v8  + v11 * other.v12;
    v9  = v8  * other.v1 + v9  * other.v5  + v10 * other.v9  + v11 * other.v13;
    v10 = v8  * other.v2 + v9  * other.v6  + v10 * other.v10 + v11 * other.v14;
    v11 = v8  * other.v3 + v9  * other.v7  + v10 * other.v11 + v11 * other.v15;
    v12 = v12 * other.v0 + v13 * other.v4  + v14 * other.v8  + v15 * other.v12;
    v13 = v12 * other.v1 + v13 * other.v5  + v14 * other.v9  + v15 * other.v13;
    v14 = v12 * other.v2 + v13 * other.v6  + v14 * other.v10 + v15 * other.v14;
    v15 = v12 * other.v3 + v13 * other.v7  + v14 * other.v11 + v15 * other.v15;

    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator*(const float& scalar) const
{
    return  Matrix4<T> {v0  * scalar,
                        v1  * scalar,
                        v2  * scalar,
                        v3  * scalar,
                        v4  * scalar,
                        v5  * scalar,
                        v6  * scalar,
                        v7  * scalar,
                        v8  * scalar,
                        v9  * scalar,
                        v10 * scalar,
                        v11 * scalar,
                        v12 * scalar,
                        v13 * scalar,
                        v14 * scalar,
                        v15 * scalar};
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator*=(const float& scalar)
{
    v0  *= scalar;
    v1  *= scalar;
    v2  *= scalar;
    v3  *= scalar;
    v4  *= scalar;
    v5  *= scalar;
    v6  *= scalar;
    v7  *= scalar;
    v8  *= scalar;
    v9  *= scalar;
    v10 *= scalar;
    v11 *= scalar;
    v12 *= scalar;
    v13 *= scalar;
    v14 *= scalar;
    v15 *= scalar;

    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator/(const float& scalar) const
{
    return  Matrix4<T> {v0  / scalar,
                        v1  / scalar,
                        v2  / scalar,
                        v3  / scalar,
                        v4  / scalar,
                        v5  / scalar,
                        v6  / scalar,
                        v7  / scalar,
                        v8  / scalar,
                        v9  / scalar,
                        v10 / scalar,
                        v11 / scalar,
                        v12 / scalar,
                        v13 / scalar,
                        v14 / scalar,
                        v15 / scalar};
}

template<typename T>
ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator/=(const float& scalar)
{
    v0  /= scalar;
    v1  /= scalar;
    v2  /= scalar;
    v3  /= scalar;
    v4  /= scalar;
    v5  /= scalar;
    v6  /= scalar;
    v7  /= scalar;
    v8  /= scalar;
    v9  /= scalar;
    v10 /= scalar;
    v11 /= scalar;
    v12 /= scalar;
    v13 /= scalar;
    v14 /= scalar;
    v15 /= scalar;

    return *this;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> operator-(Matrix4<T> mat)
{
    return  Matrix4<T> {-mat.v0,
                        -mat.v1,
                        -mat.v2,
                        -mat.v3,
                        -mat.v4,
                        -mat.v5,
                        -mat.v6,
                        -mat.v7,
                        -mat.v8,
                        -mat.v9,
                        -mat.v10,
                        -mat.v11,
                        -mat.v12,
                        -mat.v13,
                        -mat.v14,
                        -mat.v15};
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> operator*(const float& scalar, Matrix4<T> rhs)
{
    return rhs * scalar;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL Matrix4<T> Lerp(Matrix4<T> begin, Matrix4<T> end, float ratio)
{
    ratio = (ratio > 1) ? 1 : (ratio < 0) ?  0 : ratio;
    return (1 - ratio) * begin + ratio * end;
}

#endif //MATH_MATRIX3_INL_HPP
