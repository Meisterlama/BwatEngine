#ifndef MATH_MATRIX3_HPP
#define MATH_MATRIX3_HPP

#include "Math/Meta.hpp"
#include "Math/Vector/Vector3.hpp"

namespace BMath
{
    template<typename T>
    class Vector3;
    template<typename T>
    class Matrix4
    {
    public:
        union{
            // Column Major
            struct {
                T v0;  T v4;  T v8;  T v12; // a, b, c, d
                T v1;  T v5;  T v9;  T v13; // e, f, g, h
                T v2;  T v6;  T v10; T v14; // i, j, k, l
                T v3;  T v7;  T v11; T v15; // m, n, o, p
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

        ML_FUNC_DECL Matrix4(T x0 , T x4 , T x8 , T x12,
                             T x1 , T x5 , T x9 , T x13,
                             T x2 , T x6 , T x10, T x14,
                             T x3,  T x7, T x11, T x15)
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
        [[nodiscard]] ML_FUNC_DECL Matrix4 GetInverted() const;

        ML_FUNC_DECL Matrix4& Normalize();
        [[nodiscard]] ML_FUNC_DECL Matrix4 GetNormalized() const;

        static ML_FUNC_DECL Matrix4&& CreatePerspective(T fovy, T aspect, T near, T far);
        static ML_FUNC_DECL Matrix4&& CreateOrtho(T left, T right, T bottom, T top, T near, T far);
        static ML_FUNC_DECL Matrix4&& CreateTranslationMat(Vector3<T> translation);
        static ML_FUNC_DECL Matrix4&& CreateRotationMat(Vector3<T> axis, T angle);
        static ML_FUNC_DECL Matrix4&& CreateXRotationMat(T angle);
        static ML_FUNC_DECL Matrix4&& CreateYRotationMat(T angle);
        static ML_FUNC_DECL Matrix4&& CreateZRotationMat(T angle);
        static ML_FUNC_DECL Matrix4&& CreateXYZRotationMat(Vector3<T> angles);
        static ML_FUNC_DECL Matrix4&& CreateScaleMat(Vector3<T> scale);
        static ML_FUNC_DECL Matrix4&& CreateTRSMat(Vector3<T> translation, Vector3<T> rotation, Vector3<T> scale);

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

        [[nodiscard]] ML_FUNC_DECL Matrix4 operator*(const T& scalar) const;
        ML_FUNC_DECL Matrix4& operator*=(const T& scalar);

        [[nodiscard]] ML_FUNC_DECL Matrix4 operator/(const T& scalar) const;
        ML_FUNC_DECL Matrix4& operator/=(const T& scalar);
    };

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> operator-(Matrix4<T> mat);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> operator*(const T& scalar, Matrix4<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Lerp(Matrix4<T> begin, Matrix4<T> end, T ratio);

#include "inl/Matrix4.inl.hpp"
}

#endif //MATH_MATRIX3_HPP