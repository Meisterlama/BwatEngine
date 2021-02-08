#ifndef MATH_MATRIX3_HPP
#define MATH_MATRIX3_HPP

#include "Math/Meta.hpp"

namespace Math
{
    template<typename T>
    class Matrix4
    {
    public:
        union{
            struct {
                T v0;  T v1;  T v2;  T v3;
                T v4;  T v5;  T v6;  T v7;
                T v8;  T v9;  T v10; T v11;
                T v12; T v13; T v14; T v15;
            };
            T values[4*4];
        };

        // Initialize the diagonal of the matrix
        ML_FUNC_DECL Matrix4(T x = 0)
        {
            v0  = x;
            v5  = x;
            v10 = x;
            v15 = x;
        }

        // Initialize the diagonal of the matrix
        ML_FUNC_DECL Matrix4(T x0, T x5, T x10, T x15)
        {
            v0  = x0;
            v5  = x5;
            v10 = x10;
            v15 = x15;
        }

        ML_FUNC_DECL Matrix4(T x0 , T x1 , T x2 , T x3,
                             T x4 , T x5 , T x6 , T x7,
                             T x8 , T x9 , T x10, T x11,
                             T x12, T x13, T x14, T x15)
        {
            v0  = x0;
            v1  = x1;
            v2  = x2;
            v3  = x3;
            v4  = x4;
            v5  = x5;
            v6  = x6;
            v7  = x7;
            v8  = x8;
            v9  = x9;
            v10 = x10;
            v11 = x11;
            v12 = x12;
            v13 = x13;
            v14 = x14;
            v15 = x15;
        }

        ML_FUNC_DECL Matrix4(const Matrix4& mat) = default;
        ML_FUNC_DECL Matrix4(Matrix4&& mat) noexcept = default;
        ~Matrix4() = default;

        ML_FUNC_DECL Matrix4& Transpose();
        [[nodiscard]] ML_FUNC_DECL Matrix4 GetTranspose() const;

        [[nodiscard]] ML_FUNC_DECL T GetDeterminant();

        ML_FUNC_DECL Matrix4& Invert();
        [[nodiscard]] ML_FUNC_DECL Matrix4 Invert() const;

        ML_FUNC_DECL Matrix4& Scale(float scaleX, float scaleY, float scaleZ);
        [[nodiscard]] ML_FUNC_DECL Matrix4 Scale(float scaleX, float scaleY, float scaleZ) const;

        ML_FUNC_DECL Matrix4& ScaleX(float scale);
        [[nodiscard]] ML_FUNC_DECL Matrix4 ScaleX(float scale) const;

        ML_FUNC_DECL Matrix4& ScaleY(float scale);
        [[nodiscard]] ML_FUNC_DECL Matrix4 ScaleY(float scale) const;

        ML_FUNC_DECL Matrix4& ScaleZ(float scale);
        [[nodiscard]] ML_FUNC_DECL Matrix4 ScaleZ(float scale) const;

        ML_FUNC_DECL Matrix4& Rotate(float axisX, float axisY, float axisZ, float angle);
        [[nodiscard]] ML_FUNC_DECL Matrix4 Rotate(float axisX, float axisY, float axisZ, float angle) const;

        ML_FUNC_DECL Matrix4& RotateX(float angle);
        [[nodiscard]] ML_FUNC_DECL Matrix4 RotateX(float angle) const;

        ML_FUNC_DECL Matrix4& RotateY(float angle);
        [[nodiscard]] ML_FUNC_DECL Matrix4 RotateY(float angle) const;

        ML_FUNC_DECL Matrix4& RotateZ(float angle);
        [[nodiscard]] ML_FUNC_DECL Matrix4 RotateZ(float angle) const;

        ML_FUNC_DECL Matrix4& Translate(float X, float Y, float Z);
        [[nodiscard]] ML_FUNC_DECL Matrix4 Translate(float X, float Y, float Z) const;

        ML_FUNC_DECL Matrix4& TranslateX(float X);
        [[nodiscard]] ML_FUNC_DECL Matrix4 TranslateX(float X) const;

        ML_FUNC_DECL Matrix4& TranslateY(float Y);
        [[nodiscard]] ML_FUNC_DECL Matrix4 TranslateY(float Y) const;

        ML_FUNC_DECL Matrix4& TranslateZ(float Y);
        [[nodiscard]] ML_FUNC_DECL Matrix4 TranslateZ(float Y) const;

        static ML_FUNC_DECL Matrix4 GetPerspective(float fovy, float aspect, float near, float far);
        static ML_FUNC_DECL Matrix4 GetOrtho(float left, float right, float bottom, float top, float near, float far);

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Matrix4& rhs) const;
        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Matrix4& operator=(const Matrix4& other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Matrix4& other) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Matrix4& other) const;

        [[nodiscard]] ML_FUNC_DECL const T& operator[](int idx) const;
        [[nodiscard]] ML_FUNC_DECL T& operator[](int idx);

        ML_FUNC_DECL Matrix4& Add(const Matrix4& other);
        [[nodiscard]] ML_FUNC_DECL Matrix4 operator+(const Matrix4& other) const;
        ML_FUNC_DECL Matrix4& operator+=(const Matrix4& other);
        ML_FUNC_DECL Matrix4& operator++();

        ML_FUNC_DECL Matrix4& Sub(const Matrix4& other);
        [[nodiscard]] ML_FUNC_DECL Matrix4 operator-(const Matrix4& other) const;
        ML_FUNC_DECL Matrix4& operator-=(const Matrix4& other);
        ML_FUNC_DECL Matrix4& operator--();

        ML_FUNC_DECL Matrix4& Mult(const Matrix4& other);
        [[nodiscard]] ML_FUNC_DECL Matrix4 operator*(const Matrix4& other) const;
        ML_FUNC_DECL Matrix4& operator*=(const Matrix4& other);

        [[nodiscard]] ML_FUNC_DECL Matrix4 operator*(const float& scalar) const;
        ML_FUNC_DECL Matrix4& operator*=(const float& scalar);

        [[nodiscard]] ML_FUNC_DECL Matrix4 operator/(const float& scalar) const;
        ML_FUNC_DECL Matrix4& operator/=(const float& scalar);
    };

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> operator-(Matrix4<T> mat);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> operator*(const float& scalar, Matrix4<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Lerp(Matrix4<T> begin, Matrix4<T> end, float ratio);

#include "inl/Matrix4.inl.hpp"
}

#endif //MATH_MATRIX3_HPP