#ifndef MATH_MATRIX4_HPP
#define MATH_MATRIX4_HPP

#include "Math/Meta.hpp"
#include "Math/Vector/Vector3.hpp"

namespace BMath
{

#pragma region Declarations

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

#pragma endregion

#pragma region Definitions

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

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetTranspose() const
    {
        return Matrix4{*this}.Transpose();
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL T Matrix4<T>::GetDeterminant()
    {
        T af = v0  * v5;  T ag = v0  * v9;  T ah = v0  * v13; T be = v1  * v1;
        T bg = v4  * v9;  T bh = v4  * v13;  T ce = v8  * v1;  T cf = v8  * v5;
        T ch = v8  * v13;  T de = v12  * v1;  T df = v12  * v5;  T dg = v12  * v9;
        T in = v2  * v7; T io = v2  * v11; T ip = v2  * v15; T jm = v6  * v3;
        T jo = v6  * v11; T jp = v6  * v15; T km = v10 * v3; T kn = v10 * v7;
        T kp = v10 * v15; T lm = v14 * v3; T ln = v14 * v7; T lo = v14 * v11;

        return (af*kp - af*lo - ag*jp + ag*ln + ah*jo - ah*kn - be*kp + be*lo +
                bg*ip - bg*lm - bh*io + bh*km + ce*jp - ce*ln - cf*ip + cf*lm +
                ch*in - ch*jm - de*jo + de*kn + df*io - df*km - dg*in + dg*jm);
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Invert()
    {
        T a00 = v0;  T a01 = v1;  T a02 = v2;  T a03 = v3;
        T a10 = v4;  T a11 = v5;  T a12 = v6;  T a13 = v7;
        T a20 = v8;  T a21 = v9;  T a22 = v10; T a23 = v11;
        T a30 = v12; T a31 = v13; T a32 = v14; T a33 = v15;

        T b00 = a00*a11 - a01*a10;
        T b01 = a00*a12 - a02*a10;
        T b02 = a00*a13 - a03*a10;
        T b03 = a01*a12 - a02*a11;
        T b04 = a01*a13 - a03*a11;
        T b05 = a02*a13 - a03*a12;
        T b06 = a20*a31 - a21*a30;
        T b07 = a20*a32 - a22*a30;
        T b08 = a20*a33 - a23*a30;
        T b09 = a21*a32 - a22*a31;
        T b10 = a21*a33 - a23*a31;
        T b11 = a22*a33 - a23*a32;

        // Calculate the invert determinant (inlined to avoid double-caching)
        T invDet = 1.0f/(b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

        v0 = (a11*b11 - a12*b10 + a13*b09)*invDet;
        v1 = (-a01*b11 + a02*b10 - a03*b09)*invDet;
        v2 = (a31*b05 - a32*b04 + a33*b03)*invDet;
        v3 = (-a21*b05 + a22*b04 - a23*b03)*invDet;
        v4 = (-a10*b11 + a12*b08 - a13*b07)*invDet;
        v5 = (a00*b11 - a02*b08 + a03*b07)*invDet;
        v6 = (-a30*b05 + a32*b02 - a33*b01)*invDet;
        v7 = (a20*b05 - a22*b02 + a23*b01)*invDet;
        v8 = (a10*b10 - a11*b08 + a13*b06)*invDet;
        v9 = (-a00*b10 + a01*b08 - a03*b06)*invDet;
        v10 = (a30*b04 - a31*b02 + a33*b00)*invDet;
        v11 = (-a20*b04 + a21*b02 - a23*b00)*invDet;
        v12 = (-a10*b09 + a11*b07 - a12*b06)*invDet;
        v13 = (a00*b09 - a01*b07 + a02*b06)*invDet;
        v14 = (-a30*b03 + a31*b01 - a32*b00)*invDet;
        v15 = (a20*b03 - a21*b01 + a22*b00)*invDet;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetInverted() const
    {
        return Matrix4<T>{*this}.Invert();
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>& Matrix4<T>::Normalize()
    {
        T det = GetDeterminant();
        v0  /= det;
        v1  /= det;
        v2  /= det;
        v3  /= det;
        v4  /= det;
        v5  /= det;
        v6  /= det;
        v7  /= det;
        v8  /= det;
        v9  /= det;
        v10 /= det;
        v11 /= det;
        v12 /= det;
        v13 /= det;
        v14 /= det;
        v15 /= det;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::GetNormalized() const
    {
        return Matrix4<T>{*this}.Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreatePerspective(T fovy, T aspect, T near, T far)
    {
        T top = near*tan(fovy*0.5);
        T right = top*aspect;

        return Matrix4<T>{near/right, 0       , 0                          , 0,
                          0        , near/top, 0                          , 0,
                          0        , 0       ,-(far + near)/(far - near)  ,-(far*near*2)/(far - near),
                          0        , 0       ,-1                          , 0};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateOrtho(T left, T right, T bottom, T top, T near, T far)
    {
        return Matrix4<T>{1/right, 0    , 0             , 0,
                          0      , 1/top, 0             , 0,
                          0      , 0    ,-2/(far - near),-(far + near)/(far - near),
                          0      , 0    ,-1             , 0};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateTranslationMat(Vector3<T> translation)
    {
        return Matrix4<T>{1, 0, 0, translation.X,
                          0, 1, 0, translation.Y,
                          0, 0, 1, translation.Z,
                          0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateRotationMat(Vector3<T> axis, T angle)
    {
        axis.Normalize();
        T sa = Sin(angle);
        T ca = Cos(angle);
        T t = 1.0f - ca;

        T x = axis.X;
        T y = axis.Y;
        T z = axis.Z;

        return Matrix4<T>{  x*x*t + ca  , y*x*t + z*sa, z*x*t - y*sa, 0.0f,
                            x*y*t - z*sa, y*y*t + ca  , z*y*t + x*sa, 0.0f,
                            x*z*t + y*sa, y*z*t - x*sa, z*z*t + ca  , 0.0f,
                            0.0f        , 0.0f        , 0.0f        , 1.0f};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateXRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Matrix4<T>{1, 0, 0, 0,
                          0, c, s, 0,
                          0,-s, c, 0,
                          0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateYRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Matrix4<T>{ c, 0,-s, 0,
                           0, 1, 0, 0,
                           s, 0, c, 0,
                           0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateZRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Matrix4<T>{ c, s, 0, 0,
                           -s, c, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateXYZRotationMat(Vector3<T> angles)
    {
        float cz = Cos(-angles.Z);
        float sz = Sin(-angles.Z);
        float cy = Cos(-angles.Y);
        float sy = Sin(-angles.Y);
        float cx = Cos(-angles.X);
        float sx = Sin(-angles.X);

        return Matrix4<T>{cz * cy, (cz * sy * sx) - (sz * cx), (cz * sy * cx) + (sz * sx), 0,
                          sz * cy, (sz * sy * sx) + (cz * cx), (sz * sy * cx) - (cz * sx), 0,
                          -sy    , cy * sx                   , cy * cx                   , 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateScaleMat(Vector3<T> scale)
    {
        return Matrix4<T>{scale.X, 0      , 0      , 0,
                          0      , scale.Y, 0      , 0,
                          0      , 0      , scale.Z, 0,
                          0      , 0      , 0      , 1};
    }

    template<typename T>
    ML_FUNC_DECL Matrix4<T>&& Matrix4<T>::CreateTRSMat(Vector3<T> translation, Vector3<T> rotation, Vector3<T> scale)
    {
        return CreateTranslationMat(translation) * CreateXYZRotationMat(rotation) * CreateScaleMat(scale);
    }

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
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator*(const T& scalar) const
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
    ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator*=(const T& scalar)
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
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Matrix4<T>::operator/(const T& scalar) const
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
    ML_FUNC_DECL Matrix4<T>& Matrix4<T>::operator/=(const T& scalar)
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
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> operator*(const T& scalar, Matrix4<T> rhs)
    {
        return rhs * scalar;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Matrix4<T> Lerp(Matrix4<T> begin, Matrix4<T> end, T ratio)
    {
        ratio = (ratio > 1) ? 1 : (ratio < 0) ?  0 : ratio;
        return (1 - ratio) * begin + ratio * end;
    }

#pragma endregion

}
#endif //MATH_MATRIX4_HPP