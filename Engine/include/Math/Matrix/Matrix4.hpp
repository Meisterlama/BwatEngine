#ifndef MATH_MATRIX4_HPP
#define MATH_MATRIX4_HPP

#include "Math/Meta.hpp"
#include "Math/Vector/Vector3.hpp"
#include "Math/Common.hpp"

#pragma region Declarations
namespace BwatEngine::Math
{
    namespace Internal
    {
        template<typename T>
        class Vector3;
        template<typename T>
        class Vector4;
        template<typename T>
        class Matrix4
        {
        public:
            union
            {
                // Column Major
                struct
                {
                    T v0;
                    T v4;
                    T v8;
                    T v12; // a, b, c, d
                    T v1;
                    T v5;
                    T v9;
                    T v13; // e, f, g, h
                    T v2;
                    T v6;
                    T v10;
                    T v14; // i, j, k, l
                    T v3;
                    T v7;
                    T v11;
                    T v15; // m, n, o, p
                };
                T values[4 * 4]{0};
            };

            // Initialize the diagonal of the matrix
            ML_FUNC_DECL Matrix4(T x = 0)
            {
                values[0 * 4 + 0] = x;
                values[1 * 4 + 1] = x;
                values[2 * 4 + 2] = x;
                values[3 * 4 + 3] = x;
            }

            // Initialize the diagonal of the matrix
            ML_FUNC_DECL Matrix4(T x0, T x5, T x10, T x15)
            {
                values[0 * 4 + 0] = x0;
                values[1 * 4 + 1] = x5;
                values[2 * 4 + 2] = x10;
                values[3 * 4 + 3] = x15;
            }

            ML_FUNC_DECL Matrix4(T x0, T x1, T x2, T x3,
                                 T x4, T x5, T x6, T x7,
                                 T x8, T x9, T x10, T x11,
                                 T x12, T x13, T x14, T x15)
            {
                v0 = x0;
                v1 = x1;
                v2 = x2;
                v3 = x3;
                v4 = x4;
                v5 = x5;
                v6 = x6;
                v7 = x7;
                v8 = x8;
                v9 = x9;
                v10 = x10;
                v11 = x11;
                v12 = x12;
                v13 = x13;
                v14 = x14;
                v15 = x15;
            }

            ML_FUNC_DECL Matrix4(const Matrix4 &mat) = default;
            ML_FUNC_DECL Matrix4(Matrix4 &&mat) noexcept = default;
            ~Matrix4() = default;

            ML_FUNC_DECL Matrix4 &Transpose();
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetTranspose() const;

            [[nodiscard]] ML_FUNC_DECL T GetDeterminant();

            ML_FUNC_DECL Matrix4 &Invert();
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetInverted() const;

            ML_FUNC_DECL Matrix4 &Normalize();
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetNormalized() const;

            ML_FUNC_DECL Vector4<T> &RotateVector(Vector4<T> &vec) const;
            [[nodiscard]] ML_FUNC_DECL Vector4<T> GetRotatedVector(const Vector4<T> &vec) const;

            ML_FUNC_DECL Vector4<T> &RotateVector(Internal::Vector3<T> &vec) const;
            [[nodiscard]] ML_FUNC_DECL Vector4<T> GetRotatedVector(const Internal::Vector3<T> &vec) const;

            static ML_FUNC_DECL Matrix4 CreatePerspective(T left, T right, T bottom, T top, T near, T far);
            static ML_FUNC_DECL Matrix4 CreatePerspective(T fovy, T aspect, T near, T far);
            static ML_FUNC_DECL Matrix4 CreateOrtho(T left, T right, T bottom, T top, T near, T far);
            static ML_FUNC_DECL Matrix4 CreateTranslationMat(Internal::Vector3<T> translation);
            static ML_FUNC_DECL Matrix4 CreateRotationMat(Internal::Vector3<T> axis, T angle);
            static ML_FUNC_DECL Matrix4 CreateXRotationMat(T angle);
            static ML_FUNC_DECL Matrix4 CreateYRotationMat(T angle);
            static ML_FUNC_DECL Matrix4 CreateZRotationMat(T angle);
            static ML_FUNC_DECL Matrix4 CreateXYZRotationMat(Internal::Vector3<T> angles);
            static ML_FUNC_DECL Matrix4 CreateScaleMat(Internal::Vector3<T> scale);
            static ML_FUNC_DECL Matrix4
            CreateTRSMat(Internal::Vector3<T> translation, Internal::Vector3<T> rotation, Internal::Vector3<T> scale);
            static ML_FUNC_DECL Matrix4
            LookAt(Internal::Vector3<T> origin, Internal::Vector3<T> target, Internal::Vector3<T> upDir);

            [[nodiscard]] ML_FUNC_DECL bool Equals(const Matrix4 &rhs) const;
            [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

            ML_FUNC_DECL Matrix4 &operator=(const Matrix4 &other);

            [[nodiscard]] ML_FUNC_DECL bool operator==(const Matrix4 &other) const;

            [[nodiscard]] ML_FUNC_DECL bool operator!=(const Matrix4 &other) const;

            [[nodiscard]] ML_FUNC_DECL const T &operator[](int idx) const;
            [[nodiscard]] ML_FUNC_DECL T &operator[](int idx);

            ML_FUNC_DECL Matrix4 &Add(const Matrix4 &other);
            [[nodiscard]] ML_FUNC_DECL Matrix4 operator+(const Matrix4 &other) const;
            ML_FUNC_DECL Matrix4 &operator+=(const Matrix4 &other);
            ML_FUNC_DECL Matrix4 &operator++();

            ML_FUNC_DECL Matrix4 &Sub(const Matrix4 &other);
            [[nodiscard]] ML_FUNC_DECL Matrix4 operator-(const Matrix4 &other) const;
            ML_FUNC_DECL Matrix4 &operator-=(const Matrix4 &other);
            ML_FUNC_DECL Matrix4 &operator--();

            ML_FUNC_DECL Matrix4 &Mult(const Matrix4 &other);
            [[nodiscard]] ML_FUNC_DECL Matrix4 operator*(const Matrix4 &other) const;
            ML_FUNC_DECL Matrix4 &operator*=(const Matrix4 &other);

            ML_FUNC_DECL Vector4<T> &Mult(const Vector4<T> &other);
            [[nodiscard]] ML_FUNC_DECL Vector4<T> operator*(const Vector4<T> &other) const;

            ML_FUNC_DECL Vector4<T> &Mult(const Internal::Vector3<T> &other);
            [[nodiscard]] ML_FUNC_DECL Vector4<T> operator*(const Internal::Vector3<T> &other) const;

            [[nodiscard]] ML_FUNC_DECL Matrix4 operator*(const T &scalar) const;
            ML_FUNC_DECL Matrix4 &operator*=(const T &scalar);

            [[nodiscard]] ML_FUNC_DECL Matrix4 operator/(const T &scalar) const;
            ML_FUNC_DECL Matrix4 &operator/=(const T &scalar);
        };
    }

    typedef Internal::Matrix4<float> Mat4f;
    typedef Internal::Matrix4<double> Mat4d;
}

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> operator-(BwatEngine::Math::Internal::Matrix4<T> mat);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> operator*(const T& scalar, BwatEngine::Math::Internal::Matrix4<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> Lerp(BwatEngine::Math::Internal::Matrix4<T> begin,
                                                                           BwatEngine::Math::Internal::Matrix4<T> end,
                                                                           T ratio);

#pragma endregion

#pragma region Definitions
namespace BwatEngine::Math
{
    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Transpose()
    {
        T tmp = values[0*4 + 1];
        values[0*4 + 1] = values[1*4 + 0];
        values[1*4 + 0] = tmp;

        tmp = values[0*4 + 2];
        values[0*4 + 2] = values[2*4 + 0];
        values[2*4 + 0] = tmp;

        tmp = values[0*4 + 3];
        values[0*4 + 3] = values[3*4 + 0];
        values[3*4 + 0] = tmp;

        tmp = values[1*4 + 2];
        values[1*4 + 2] = values[2*4 + 1];
        values[2*4 + 1] = tmp;

        tmp = values[1*4 + 3];
        values[1*4 + 3] = values[3*4 + 1];
        values[3*4 + 1] = tmp;

        tmp = values[2*4 + 3];
        values[2*4 + 3] = values[3*4 + 2];
        values[3*4 + 2] = tmp;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::GetTranspose() const
    {
        return Internal::Matrix4<T>{*this}.Transpose();
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL T Internal::Matrix4<T>::GetDeterminant()
    {
        T af = values[0*4 + 0]  * values[1*4 + 1];  T ag = values[0*4 + 0]  * values[2*4 + 1];  T ah = values[0*4 + 0]  * values[3*4 + 1]; T be = values[0*4 + 1]  * values[0*4 + 1];
        T bg = values[1*4 + 0]  * values[2*4 + 1];  T bh = values[1*4 + 0]  * values[3*4 + 1];  T ce = values[2*4 + 0]  * values[0*4 + 1];  T cf = values[2*4 + 0]  * values[1*4 + 1];
        T ch = values[2*4 + 0]  * values[3*4 + 1];  T de = values[3*4 + 0]  * values[0*4 + 1];  T df = values[3*4 + 0]  * values[1*4 + 1];  T dg = values[3*4 + 0]  * values[2*4 + 1];
        T in = values[0*4 + 2]  * values[1*4 + 3]; T io = values[0*4 + 2]  * values[2*4 + 3]; T ip = values[0*4 + 2]  * values[3*4 + 3]; T jm = values[1*4 + 2]  * values[0*4 + 3];
        T jo = values[1*4 + 2]  * values[2*4 + 3]; T jp = values[1*4 + 2]  * values[3*4 + 3]; T km = values[2*4 + 2] * values[0*4 + 3]; T kn = values[2*4 + 2] * values[1*4 + 3];
        T kp = values[2*4 + 2] * values[3*4 + 3]; T lm = values[3*4 + 2] * values[0*4 + 3]; T ln = values[3*4 + 2] * values[1*4 + 3]; T lo = values[3*4 + 2] * values[2*4 + 3];

        return (af*kp - af*lo - ag*jp + ag*ln + ah*jo - ah*kn - be*kp + be*lo +
                bg*ip - bg*lm - bh*io + bh*km + ce*jp - ce*ln - cf*ip + cf*lm +
                ch*in - ch*jm - de*jo + de*kn + df*io - df*km - dg*in + dg*jm);
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Invert()
    {
        T a00 = values[0*4 + 0];  T a01 = values[0*4 + 1];  T a02 = values[0*4 + 2];  T a03 = values[0*4 + 3];
        T a10 = values[1*4 + 0];  T a11 = values[1*4 + 1];  T a12 = values[1*4 + 2];  T a13 = values[1*4 + 3];
        T a20 = values[2*4 + 0];  T a21 = values[2*4 + 1];  T a22 = values[2*4 + 2]; T a23 = values[2*4 + 3];
        T a30 = values[3*4 + 0]; T a31 = values[3*4 + 1]; T a32 = values[3*4 + 2]; T a33 = values[3*4 + 3];

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

        values[0*4 + 0] = (a11*b11 - a12*b10 + a13*b09)*invDet;
        values[0*4 + 1] = (-a01*b11 + a02*b10 - a03*b09)*invDet;
        values[0*4 + 2] = (a31*b05 - a32*b04 + a33*b03)*invDet;
        values[0*4 + 3] = (-a21*b05 + a22*b04 - a23*b03)*invDet;
        values[1*4 + 0] = (-a10*b11 + a12*b08 - a13*b07)*invDet;
        values[1*4 + 1] = (a00*b11 - a02*b08 + a03*b07)*invDet;
        values[1*4 + 2] = (-a30*b05 + a32*b02 - a33*b01)*invDet;
        values[1*4 + 3] = (a20*b05 - a22*b02 + a23*b01)*invDet;
        values[2*4 + 0] = (a10*b10 - a11*b08 + a13*b06)*invDet;
        values[2*4 + 1] = (-a00*b10 + a01*b08 - a03*b06)*invDet;
        values[2*4 + 2] = (a30*b04 - a31*b02 + a33*b00)*invDet;
        values[2*4 + 3] = (-a20*b04 + a21*b02 - a23*b00)*invDet;
        values[3*4 + 0] = (-a10*b09 + a11*b07 - a12*b06)*invDet;
        values[3*4 + 1] = (a00*b09 - a01*b07 + a02*b06)*invDet;
        values[3*4 + 2] = (-a30*b03 + a31*b01 - a32*b00)*invDet;
        values[3*4 + 3] = (a20*b03 - a21*b01 + a22*b00)*invDet;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::GetInverted() const
    {
        return Internal::Matrix4<T>{*this}.Invert();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Normalize()
    {
        T det = GetDeterminant();
        values[0*4 + 0]  /= det;
        values[0*4 + 1]  /= det;
        values[0*4 + 2]  /= det;
        values[0*4 + 3]  /= det;
        values[1*4 + 0]  /= det;
        values[1*4 + 1]  /= det;
        values[1*4 + 2]  /= det;
        values[1*4 + 3]  /= det;
        values[2*4 + 0]  /= det;
        values[2*4 + 1]  /= det;
        values[2*4 + 2] /= det;
        values[2*4 + 3] /= det;
        values[3*4 + 0] /= det;
        values[3*4 + 1] /= det;
        values[3*4 + 2] /= det;
        values[3*4 + 3] /= det;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::GetNormalized() const
    {
        return Internal::Matrix4<T>{*this}.Normalize();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector4<T>& Internal::Matrix4<T>::RotateVector(Vector4<T>& vec) const
    {
        vec = Vector4<T>{
            vec.X * values[0*4 + 0] + vec.Y * values[1*4 + 0] + vec.Z * values[2*4 + 0]  + vec.W * values[3*4 + 0],
            vec.X * values[0*4 + 1] + vec.Y * values[1*4 + 1] + vec.Z * values[2*4 + 1]  + vec.W * values[3*4 + 1],
            vec.X * values[0*4 + 2] + vec.Y * values[1*4 + 2] + vec.Z * values[2*4 + 2] + vec.W * values[3*4 + 2],
            vec.X * values[0*4 + 3] + vec.Y * values[1*4 + 3] + vec.Z * values[2*4 + 3] + vec.W * values[3*4 + 3],};

        return vec;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Vector4<T> Internal::Matrix4<T>::GetRotatedVector(const Vector4<T>& vec) const
    {
        return Vector4<T>{
                vec.X * values[0*4 + 0] + vec.Y * values[1*4 + 0] + vec.Z * values[2*4 + 0]  + vec.W * values[3*4 + 0],
                vec.X * values[0*4 + 1] + vec.Y * values[1*4 + 1] + vec.Z * values[2*4 + 1]  + vec.W * values[3*4 + 1],
                vec.X * values[0*4 + 2] + vec.Y * values[1*4 + 2] + vec.Z * values[2*4 + 2] + vec.W * values[3*4 + 2],
                vec.X * values[0*4 + 3] + vec.Y * values[1*4 + 3] + vec.Z * values[2*4 + 3] + vec.W * values[3*4 + 3],};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Vector4<T>& Internal::Matrix4<T>::RotateVector(Internal::Vector3<T>& vec) const
    {
        vec = Internal::Vector3<T>{
                vec.X * values[0*4 + 0] + vec.Y * values[1*4 + 0] + vec.Z * values[2*4 + 0]  + vec.W * values[3*4 + 0],
                vec.X * values[0*4 + 1] + vec.Y * values[1*4 + 1] + vec.Z * values[2*4 + 1]  + vec.W * values[3*4 + 1],
                vec.X * values[0*4 + 2] + vec.Y * values[1*4 + 2] + vec.Z * values[2*4 + 2] + vec.W * values[3*4 + 2]};

        return vec;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Vector4<T> Internal::Matrix4<T>::GetRotatedVector(const Internal::Vector3<T>& vec) const
    {
        return Internal::Vector3<T>{
                vec.X * values[0*4 + 0] + vec.Y * values[1*4 + 0] + vec.Z * values[2*4 + 0]  + vec.W * values[3*4 + 0],
                vec.X * values[0*4 + 1] + vec.Y * values[1*4 + 1] + vec.Z * values[2*4 + 1]  + vec.W * values[3*4 + 1],
                vec.X * values[0*4 + 2] + vec.Y * values[1*4 + 2] + vec.Z * values[2*4 + 2] + vec.W * values[3*4 + 2]};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreatePerspective(T left, T right, T bottom, T top, T near, T far)
    {
        return Internal::Matrix4<T>{(near*2)/(right-left), 0                    , (right+left)/(right-left) , 0,
                          0                    , (near*2)/(top-bottom), (top+bottom)/(top-bottom) , 0,
                          0                    , 0                    , -(far+near)/(far-near)    ,-(far * near*2)/(far - near),
                          0                    , 0                    , -1                        , 0};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreatePerspective(T fovy, T aspect, T near, T far)
    {
        T top = near*tan(Math::ToRads(fovy)*0.5);
        T right = top*aspect;

        return CreatePerspective(-right, right, -top, top, near, far);
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateOrtho(T left, T right, T bottom, T top, T near, T far)
    {
        return Internal::Matrix4<T>{2/(right-left), 0             , 0             , -(right+left)/(right-left),
                          0             , 2/(top-bottom), 0             , -(top+bottom)/(top-bottom),
                          0             , 0             ,-2/(far-near)  , -(far+near)/(far-near),
                          0             , 0             , 0             , 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateTranslationMat(Internal::Vector3<T> translation)
    {
        return Internal::Matrix4<T>{1, 0, 0, translation.X,
                          0, 1, 0, translation.Y,
                          0, 0, 1, translation.Z,
                          0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateRotationMat(Internal::Vector3<T> axis, T angle)
    {
        axis.Normalize();
        T sa = Sin(angle);
        T ca = Cos(angle);
        T t = 1.0f - ca;

        T x = axis.X;
        T y = axis.Y;
        T z = axis.Z;

        return Internal::Matrix4<T>{  x*x*t + ca  , y*x*t + z*sa, z*x*t - y*sa, 0.0f,
                            x*y*t - z*sa, y*y*t + ca  , z*y*t + x*sa, 0.0f,
                            x*z*t + y*sa, y*z*t - x*sa, z*z*t + ca  , 0.0f,
                            0.0f        , 0.0f        , 0.0f        , 1.0f};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateXRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Internal::Matrix4<T>{1, 0, 0, 0,
                          0, c, s, 0,
                          0,-s, c, 0,
                          0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateYRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Internal::Matrix4<T>{ c, 0,-s, 0,
                           0, 1, 0, 0,
                           s, 0, c, 0,
                           0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateZRotationMat(T angle)
    {
        T c = Cos(angle);
        T s = Sin(angle);
        return Internal::Matrix4<T>{ c, s, 0, 0,
                           -s, c, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateXYZRotationMat(Internal::Vector3<T> angles)
    {
        float cz = Cos(angles.Z);
        float sz = Sin(angles.Z);
        float cy = Cos(angles.Y);
        float sy = Sin(angles.Y);
        float cx = Cos(angles.X);
        float sx = Sin(angles.X);

        return Internal::Matrix4<T>{cz * cy, (cz * sy * sx) - (sz * cx), (cz * sy * cx) + (sz * sx), 0,
                          sz * cy, (sz * sy * sx) + (cz * cx), (sz * sy * cx) - (cz * sx), 0,
                          -sy    , cy * sx                   , cy * cx                   , 0,
                          0      , 0                         , 0                          , 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateScaleMat(Internal::Vector3<T> scale)
    {
        return Internal::Matrix4<T>{scale.X, 0      , 0      , 0,
                          0      , scale.Y, 0      , 0,
                          0      , 0      , scale.Z, 0,
                          0      , 0      , 0      , 1};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateTRSMat(Internal::Vector3<T> translation, Internal::Vector3<T> rotation, Internal::Vector3<T> scale)
    {
        return CreateTranslationMat(translation) * CreateXYZRotationMat(rotation) * CreateScaleMat(scale);
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::LookAt(Internal::Vector3<T> origin, Internal::Vector3<T> target, Internal::Vector3<T> upDir)
    {
        Internal::Vector3<T> forward{origin - target};
        forward.SafeNormalize();

        Internal::Vector3<T> left{upDir.CrossProduct(forward)};
        left.Normalize();

        Internal::Vector3<T> up = forward.CrossProduct(left);

        T m12 = -left.x * origin.X - left.Y * origin.Y - left.Z * origin.Z;
        T m13 = -up.X * origin.X - up.Y * origin.Y - up.Z * origin.Z;
        T m14 = -forward.X * origin.X - forward.Y * origin.Y - forward.Z * origin.Z;

        return Internal::Matrix4<T>{left.X   , left.Y   , left.Z   , m12,
                          up.X     , up.Y     , up.Z     , m13,
                          forward.X, forward.Y, forward.Z, m14,
                          0        , 0        ,0         , 1   };
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL bool Internal::Matrix4<T>::Equals(const Internal::Matrix4<T>& rhs) const
    {
        return *this == rhs;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL bool Internal::Matrix4<T>::IsZero() const
    {
        return *this == Internal::Matrix4<T>{0};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator=(const Internal::Matrix4<T>& other)
    {
        values[0*4 + 0] = other.values[0*4 + 0];
        values[0*4 + 1] = other.values[0*4 + 1];
        values[0*4 + 2] = other.values[0*4 + 2];
        values[0*4 + 3] = other.values[0*4 + 3];
        values[1*4 + 0] = other.values[1*4 + 0];
        values[1*4 + 1] = other.values[1*4 + 1];
        values[1*4 + 2] = other.values[1*4 + 2];
        values[1*4 + 3] = other.values[1*4 + 3];
        values[2*4 + 0] = other.values[2*4 + 0];
        values[2*4 + 1] = other.values[2*4 + 1];
        values[2*4 + 2] = other.values[2*4 + 2];
        values[2*4 + 3] = other.values[2*4 + 3];
        values[3*4 + 0] = other.values[3*4 + 0];
        values[3*4 + 1] = other.values[3*4 + 1];
        values[3*4 + 2] = other.values[3*4 + 2];
        values[3*4 + 3] = other.values[3*4 + 3];

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL bool Internal::Matrix4<T>::operator==(const Internal::Matrix4<T>& other) const
    {
        return (values[0*4 + 0] == other.values[0*4 + 0] &&
                values[0*4 + 1] == other.values[0*4 + 1] &&
                values[0*4 + 2] == other.values[0*4 + 2] &&
                values[0*4 + 3] == other.values[0*4 + 3] &&
                values[1*4 + 0] == other.values[1*4 + 0] &&
                values[1*4 + 1] == other.values[1*4 + 1] &&
                values[1*4 + 2] == other.values[1*4 + 2] &&
                values[1*4 + 3] == other.values[1*4 + 3] &&
                values[2*4 + 0] == other.values[2*4 + 0] &&
                values[2*4 + 1] == other.values[2*4 + 1] &&
                values[2*4 + 2] == other.values[2*4 + 2] &&
                values[2*4 + 3] == other.values[2*4 + 3] &&
                values[3*4 + 0] == other.values[3*4 + 0] &&
                values[3*4 + 1] == other.values[3*4 + 1] &&
                values[3*4 + 2] == other.values[3*4 + 2] &&
                values[3*4 + 3] == other.values[3*4 + 3]);
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL bool Internal::Matrix4<T>::operator!=(const Internal::Matrix4<T>& other) const
    {
        return !(*this == other);
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL const T& Internal::Matrix4<T>::operator[](int idx) const
    {
        return values[idx];
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL T& Internal::Matrix4<T>::operator[](int idx)
    {
        return values[idx];
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Add(const Internal::Matrix4<T>& other)
    {
        *this += other;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator+(const Internal::Matrix4<T>& other) const
    {
        return  Internal::Matrix4<T> {values[0*4 + 0] + other.values[0*4 + 0],
                            values[0*4 + 1] + other.values[0*4 + 1],
                            values[0*4 + 2] + other.values[0*4 + 2],
                            values[0*4 + 3] + other.values[0*4 + 3],
                            values[1*4 + 0] + other.values[1*4 + 0],
                            values[1*4 + 1] + other.values[1*4 + 1],
                            values[1*4 + 2] + other.values[1*4 + 2],
                            values[1*4 + 3] + other.values[1*4 + 3],
                            values[2*4 + 0] + other.values[2*4 + 0],
                            values[2*4 + 1] + other.values[2*4 + 1],
                            values[2*4 + 2] + other.values[2*4 + 2],
                            values[2*4 + 3] + other.values[2*4 + 3],
                            values[3*4 + 0] + other.values[3*4 + 0],
                            values[3*4 + 1] + other.values[3*4 + 1],
                            values[3*4 + 2] + other.values[3*4 + 2],
                            values[3*4 + 3] + other.values[3*4 + 3]};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator+=(const Internal::Matrix4<T>& other)
    {
        values[0*4 + 0] += other.values[0*4 + 0];
        values[0*4 + 1] += other.values[0*4 + 1];
        values[0*4 + 2] += other.values[0*4 + 2];
        values[0*4 + 3] += other.values[0*4 + 3];
        values[1*4 + 0] += other.values[1*4 + 0];
        values[1*4 + 1] += other.values[1*4 + 1];
        values[1*4 + 2] += other.values[1*4 + 2];
        values[1*4 + 3] += other.values[1*4 + 3];
        values[2*4 + 0] += other.values[2*4 + 0];
        values[2*4 + 1] += other.values[2*4 + 1];
        values[2*4 + 2] += other.values[2*4 + 2];
        values[2*4 + 3] += other.values[2*4 + 3];
        values[3*4 + 0] += other.values[3*4 + 0];
        values[3*4 + 1] += other.values[3*4 + 1];
        values[3*4 + 2] += other.values[3*4 + 2];
        values[3*4 + 3] += other.values[3*4 + 3];

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator++()
    {
        values[0*4 + 0]++;
        values[0*4 + 1]++;
        values[0*4 + 2]++;
        values[0*4 + 3]++;
        values[1*4 + 0]++;
        values[1*4 + 1]++;
        values[1*4 + 2]++;
        values[1*4 + 3]++;
        values[2*4 + 0]++;
        values[2*4 + 1]++;
        values[2*4 + 2]++;
        values[2*4 + 3]++;
        values[3*4 + 0]++;
        values[3*4 + 1]++;
        values[3*4 + 2]++;
        values[3*4 + 3]++;

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Sub(const Internal::Matrix4<T>& other)
    {
        *this -= other;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator-(const Internal::Matrix4<T>& other) const
    {
        return  Internal::Matrix4<T> {values[0*4 + 0] - other.values[0*4 + 0],
                            values[0*4 + 1] - other.values[0*4 + 1],
                            values[0*4 + 2] - other.values[0*4 + 2],
                            values[0*4 + 3] - other.values[0*4 + 3],
                            values[1*4 + 0] - other.values[1*4 + 0],
                            values[1*4 + 1] - other.values[1*4 + 1],
                            values[1*4 + 2] - other.values[1*4 + 2],
                            values[1*4 + 3] - other.values[1*4 + 3],
                            values[2*4 + 0] - other.values[2*4 + 0],
                            values[2*4 + 1] - other.values[2*4 + 1],
                            values[2*4 + 2] - other.values[2*4 + 2],
                            values[2*4 + 3] - other.values[2*4 + 3],
                            values[3*4 + 0] - other.values[3*4 + 0],
                            values[3*4 + 1] - other.values[3*4 + 1],
                            values[3*4 + 2] - other.values[3*4 + 2],
                            values[3*4 + 3] - other.values[3*4 + 3]};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator-=(const Internal::Matrix4<T>& other)
    {
        values[0*4 + 0] -= other.values[0*4 + 0];
        values[0*4 + 1] -= other.values[0*4 + 1];
        values[0*4 + 2] -= other.values[0*4 + 2];
        values[0*4 + 3] -= other.values[0*4 + 3];
        values[1*4 + 0] -= other.values[1*4 + 0];
        values[1*4 + 1] -= other.values[1*4 + 1];
        values[1*4 + 2] -= other.values[1*4 + 2];
        values[1*4 + 3] -= other.values[1*4 + 3];
        values[2*4 + 0] -= other.values[2*4 + 0];
        values[2*4 + 1] -= other.values[2*4 + 1];
        values[2*4 + 2] -= other.values[2*4 + 2];
        values[2*4 + 3] -= other.values[2*4 + 3];
        values[3*4 + 0] -= other.values[3*4 + 0];
        values[3*4 + 1] -= other.values[3*4 + 1];
        values[3*4 + 2] -= other.values[3*4 + 2];
        values[3*4 + 3] -= other.values[3*4 + 3];

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator--()
    {
        values[0*4 + 0]--;
        values[0*4 + 1]--;
        values[0*4 + 2]--;
        values[0*4 + 3]--;
        values[1*4 + 0]--;
        values[1*4 + 1]--;
        values[1*4 + 2]--;
        values[1*4 + 3]--;
        values[2*4 + 0]--;
        values[2*4 + 1]--;
        values[2*4 + 2]--;
        values[2*4 + 3]--;
        values[3*4 + 0]--;
        values[3*4 + 1]--;
        values[3*4 + 2]--;
        values[3*4 + 3]--;

        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::Mult(const Internal::Matrix4<T>& other)
    {
        *this *= other;
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator*(const Internal::Matrix4<T>& other) const
    {
        return Internal::Matrix4<T> {values[0*4 + 0] * other.values[0*4 + 0] + values[0*4 + 1] * other.values[1*4 + 0]  + values[0*4 + 2] * other.values[2*4 + 0] + values[0*4 + 3] * other.values[3*4 + 0],
                           values[0*4 + 0] * other.values[0*4 + 1] + values[0*4 + 1] * other.values[1*4 + 1]  + values[0*4 + 2] * other.values[2*4 + 1] + values[0*4 + 3] * other.values[3*4 + 1],
                           values[0*4 + 0] * other.values[0*4 + 2] + values[0*4 + 1] * other.values[1*4 + 2]  + values[0*4 + 2] * other.values[2*4 + 2] + values[0*4 + 3] * other.values[3*4 + 2],
                           values[0*4 + 0] * other.values[0*4 + 3] + values[0*4 + 1] * other.values[1*4 + 3]  + values[0*4 + 2] * other.values[2*4 + 3] + values[0*4 + 3] * other.values[3*4 + 3],
                           values[1*4 + 0] * other.values[0*4 + 0] + values[1*4 + 1] * other.values[1*4 + 0]  + values[1*4 + 2] * other.values[2*4 + 0] + values[1*4 + 3] * other.values[3*4 + 0],
                           values[1*4 + 0] * other.values[0*4 + 1] + values[1*4 + 1] * other.values[1*4 + 1]  + values[1*4 + 2] * other.values[2*4 + 1] + values[1*4 + 3] * other.values[3*4 + 1],
                           values[1*4 + 0] * other.values[0*4 + 2] + values[1*4 + 1] * other.values[1*4 + 2]  + values[1*4 + 2] * other.values[2*4 + 2] + values[1*4 + 3] * other.values[3*4 + 2],
                           values[1*4 + 0] * other.values[0*4 + 3] + values[1*4 + 1] * other.values[1*4 + 3]  + values[1*4 + 2] * other.values[2*4 + 3] + values[1*4 + 3] * other.values[3*4 + 3],
                           values[2*4 + 0] * other.values[0*4 + 0] + values[2*4 + 1] * other.values[1*4 + 0]  + values[2*4 + 2] * other.values[2*4 + 0] + values[2*4 + 3] * other.values[3*4 + 0],
                           values[2*4 + 0] * other.values[0*4 + 1] + values[2*4 + 1] * other.values[1*4 + 1]  + values[2*4 + 2] * other.values[2*4 + 1] + values[2*4 + 3] * other.values[3*4 + 1],
                           values[2*4 + 0] * other.values[0*4 + 2] + values[2*4 + 1] * other.values[1*4 + 2]  + values[2*4 + 2] * other.values[2*4 + 2] + values[2*4 + 3] * other.values[3*4 + 2],
                           values[2*4 + 0] * other.values[0*4 + 3] + values[2*4 + 1] * other.values[1*4 + 3]  + values[2*4 + 2] * other.values[2*4 + 3] + values[2*4 + 3] * other.values[3*4 + 3],
                           values[3*4 + 0] * other.values[0*4 + 0] + values[3*4 + 1] * other.values[1*4 + 0]  + values[3*4 + 2] * other.values[2*4 + 0] + values[3*4 + 3] * other.values[3*4 + 0],
                           values[3*4 + 0] * other.values[0*4 + 1] + values[3*4 + 1] * other.values[1*4 + 1]  + values[3*4 + 2] * other.values[2*4 + 1] + values[3*4 + 3] * other.values[3*4 + 1],
                           values[3*4 + 0] * other.values[0*4 + 2] + values[3*4 + 1] * other.values[1*4 + 2]  + values[3*4 + 2] * other.values[2*4 + 2] + values[3*4 + 3] * other.values[3*4 + 2],
                           values[3*4 + 0] * other.values[0*4 + 3] + values[3*4 + 1] * other.values[1*4 + 3]  + values[3*4 + 2] * other.values[2*4 + 3] + values[3*4 + 3] * other.values[3*4 + 3]
        };
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator*=(const Internal::Matrix4<T>& other)
    {
        T tmpV0  = values[0*4 + 0] * other.values[0*4 + 0] + values[0*4 + 1] * other.values[1*4 + 0]  + values[0*4 + 2] * other.values[2*4 + 0] + values[0*4 + 3] * other.values[3*4 + 0];
        T tmpV1  = values[0*4 + 0] * other.values[0*4 + 1] + values[0*4 + 1] * other.values[1*4 + 1]  + values[0*4 + 2] * other.values[2*4 + 1] + values[0*4 + 3] * other.values[3*4 + 1];
        T tmpV2  = values[0*4 + 0] * other.values[0*4 + 2] + values[0*4 + 1] * other.values[1*4 + 2]  + values[0*4 + 2] * other.values[2*4 + 2] + values[0*4 + 3] * other.values[3*4 + 2];
        T tmpV3  = values[0*4 + 0] * other.values[0*4 + 3] + values[0*4 + 1] * other.values[1*4 + 3]  + values[0*4 + 2] * other.values[2*4 + 3] + values[0*4 + 3] * other.values[3*4 + 3];
        T tmpV4  = values[1*4 + 0] * other.values[0*4 + 0] + values[1*4 + 1] * other.values[1*4 + 0]  + values[1*4 + 2] * other.values[2*4 + 0] + values[1*4 + 3] * other.values[3*4 + 0];
        T tmpV5  = values[1*4 + 0] * other.values[0*4 + 1] + values[1*4 + 1] * other.values[1*4 + 1]  + values[1*4 + 2] * other.values[2*4 + 1] + values[1*4 + 3] * other.values[3*4 + 1];
        T tmpV6  = values[1*4 + 0] * other.values[0*4 + 2] + values[1*4 + 1] * other.values[1*4 + 2]  + values[1*4 + 2] * other.values[2*4 + 2] + values[1*4 + 3] * other.values[3*4 + 2];
        T tmpV7  = values[1*4 + 0] * other.values[0*4 + 3] + values[1*4 + 1] * other.values[1*4 + 3]  + values[1*4 + 2] * other.values[2*4 + 3] + values[1*4 + 3] * other.values[3*4 + 3];
        T tmpV8  = values[2*4 + 0] * other.values[0*4 + 0] + values[2*4 + 1] * other.values[1*4 + 0]  + values[2*4 + 2] * other.values[2*4 + 0] + values[2*4 + 3] * other.values[3*4 + 0];
        T tmpV9  = values[2*4 + 0] * other.values[0*4 + 1] + values[2*4 + 1] * other.values[1*4 + 1]  + values[2*4 + 2] * other.values[2*4 + 1] + values[2*4 + 3] * other.values[3*4 + 1];
        T tmpV10 = values[2*4 + 0] * other.values[0*4 + 2] + values[2*4 + 1] * other.values[1*4 + 2]  + values[2*4 + 2] * other.values[2*4 + 2] + values[2*4 + 3] * other.values[3*4 + 2];
        T tmpV11 = values[2*4 + 0] * other.values[0*4 + 3] + values[2*4 + 1] * other.values[1*4 + 3]  + values[2*4 + 2] * other.values[2*4 + 3] + values[2*4 + 3] * other.values[3*4 + 3];
        T tmpV12 = values[3*4 + 0] * other.values[0*4 + 0] + values[3*4 + 1] * other.values[1*4 + 0]  + values[3*4 + 2] * other.values[2*4 + 0] + values[3*4 + 3] * other.values[3*4 + 0];
        T tmpV13 = values[3*4 + 0] * other.values[0*4 + 1] + values[3*4 + 1] * other.values[1*4 + 1]  + values[3*4 + 2] * other.values[2*4 + 1] + values[3*4 + 3] * other.values[3*4 + 1];
        T tmpV14 = values[3*4 + 0] * other.values[0*4 + 2] + values[3*4 + 1] * other.values[1*4 + 2]  + values[3*4 + 2] * other.values[2*4 + 2] + values[3*4 + 3] * other.values[3*4 + 2];
        T tmpV15 = values[3*4 + 0] * other.values[0*4 + 3] + values[3*4 + 1] * other.values[1*4 + 3]  + values[3*4 + 2] * other.values[2*4 + 3] + values[3*4 + 3] * other.values[3*4 + 3];

        values[0*4 + 0]  = tmpV0;
        values[0*4 + 1]  = tmpV1;
        values[0*4 + 2]  = tmpV2;
        values[0*4 + 3]  = tmpV3;
        values[1*4 + 0]  = tmpV4;
        values[1*4 + 1]  = tmpV5;
        values[1*4 + 2]  = tmpV6;
        values[1*4 + 3]  = tmpV7;
        values[2*4 + 0]  = tmpV8;
        values[2*4 + 1]  = tmpV9;
        values[2*4 + 2] = tmpV10;
        values[2*4 + 3] = tmpV11;
        values[3*4 + 0] = tmpV12;
        values[3*4 + 1] = tmpV13;
        values[3*4 + 2] = tmpV14;
        values[3*4 + 3] = tmpV15;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator*(const T& scalar) const
    {
        return  Internal::Matrix4<T> {values[0*4 + 0]  * scalar,
                            values[0*4 + 1]  * scalar,
                            values[0*4 + 2]  * scalar,
                            values[0*4 + 3]  * scalar,
                            values[1*4 + 0]  * scalar,
                            values[1*4 + 1]  * scalar,
                            values[1*4 + 2]  * scalar,
                            values[1*4 + 3]  * scalar,
                            values[2*4 + 0]  * scalar,
                            values[2*4 + 1]  * scalar,
                            values[2*4 + 2] * scalar,
                            values[2*4 + 3] * scalar,
                            values[3*4 + 0] * scalar,
                            values[3*4 + 1] * scalar,
                            values[3*4 + 2] * scalar,
                            values[3*4 + 3] * scalar};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator*=(const T& scalar)
    {
        values[0*4 + 0]  *= scalar;
        values[0*4 + 1]  *= scalar;
        values[0*4 + 2]  *= scalar;
        values[0*4 + 3]  *= scalar;
        values[1*4 + 0]  *= scalar;
        values[1*4 + 1]  *= scalar;
        values[1*4 + 2]  *= scalar;
        values[1*4 + 3]  *= scalar;
        values[2*4 + 0]  *= scalar;
        values[2*4 + 1]  *= scalar;
        values[2*4 + 2] *= scalar;
        values[2*4 + 3] *= scalar;
        values[3*4 + 0] *= scalar;
        values[3*4 + 1] *= scalar;
        values[3*4 + 2] *= scalar;
        values[3*4 + 3] *= scalar;

        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator/(const T& scalar) const
    {
        return  Internal::Matrix4<T> {values[0*4 + 0]  / scalar,
                            values[0*4 + 1]  / scalar,
                            values[0*4 + 2]  / scalar,
                            values[0*4 + 3]  / scalar,
                            values[1*4 + 0]  / scalar,
                            values[1*4 + 1]  / scalar,
                            values[1*4 + 2]  / scalar,
                            values[1*4 + 3]  / scalar,
                            values[2*4 + 0]  / scalar,
                            values[2*4 + 1]  / scalar,
                            values[2*4 + 2] / scalar,
                            values[2*4 + 3] / scalar,
                            values[3*4 + 0] / scalar,
                            values[3*4 + 1] / scalar,
                            values[3*4 + 2] / scalar,
                            values[3*4 + 3] / scalar};
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator/=(const T& scalar)
    {
        values[0*4 + 0]  /= scalar;
        values[0*4 + 1]  /= scalar;
        values[0*4 + 2]  /= scalar;
        values[0*4 + 3]  /= scalar;
        values[1*4 + 0]  /= scalar;
        values[1*4 + 1]  /= scalar;
        values[1*4 + 2]  /= scalar;
        values[1*4 + 3]  /= scalar;
        values[2*4 + 0]  /= scalar;
        values[2*4 + 1]  /= scalar;
        values[2*4 + 2] /= scalar;
        values[2*4 + 3] /= scalar;
        values[3*4 + 0] /= scalar;
        values[3*4 + 1] /= scalar;
        values[3*4 + 2] /= scalar;
        values[3*4 + 3] /= scalar;

        return *this;
    }




}
template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> operator-(BwatEngine::Math::Internal::Matrix4<T> mat)
{
    return  BwatEngine::Math::Internal::Matrix4<T> {-mat.values[0*4 + 0],
                                  -mat.values[0*4 + 1],
                                  -mat.values[0*4 + 2],
                                  -mat.values[0*4 + 3],
                                  -mat.values[1*4 + 0],
                                  -mat.values[1*4 + 1],
                                  -mat.values[1*4 + 2],
                                  -mat.values[1*4 + 3],
                                  -mat.values[2*4 + 0],
                                  -mat.values[2*4 + 1],
                                  -mat.values[2*4 + 2],
                                  -mat.values[2*4 + 3],
                                  -mat.values[3*4 + 0],
                                  -mat.values[3*4 + 1],
                                  -mat.values[3*4 + 2],
                                  -mat.values[3*4 + 3]};
}


template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> operator*(const T& scalar, BwatEngine::Math::Internal::Matrix4<T> rhs)
{
    return rhs * scalar;
}

template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> Lerp(BwatEngine::Math::Internal::Matrix4<T> begin, BwatEngine::Math::Internal::Matrix4<T> end, T ratio)
{
    ratio = (ratio > 1) ? 1 : (ratio < 0) ?  0 : ratio;
    return (1 - ratio) * begin + ratio * end;
}
#pragma endregion

#endif //MATH_MATRIX4_HPP