#ifndef MATH_MATRIX4_HPP
#define MATH_MATRIX4_HPP

#include "Math/Meta.hpp"
#include "Math/Vector/Vector3.hpp"
#include "Math/Quaternion.hpp"
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
                     T v0; T v1; T v2; T v3;     // a, b, c, d
                     T v4; T v5; T v6; T v7;     // e, f, g, h
                     T v8; T v9; T v10; T v11;   // i, j, k, l
                     T v12; T v13; T v14; T v15; // m, n, o, p
                };
                T values[4 * 4]{0};
            };

            /**
             * @brief Initialize the diagonal of the matrix
             * @param x value of the diagonal
             */
            ML_FUNC_DECL Matrix4(T x = 0)
            {
                v0  = x;
                v5  = x;
                v10 = x;
                v15 = x;
            }

            /**
             * @brief Initialize the diagonal of the matrix
             * @param x0
             * @param x5
             * @param x10
             * @param x15
             */
            ML_FUNC_DECL Matrix4(T x0, T x5, T x10, T x15)
            {
                v0  = x0;
                v5  = x5;
                v10 = x10;
                v15 = x15;
            }

            /**
             * @brief Initialize the whole matrix
             */
            ML_FUNC_DECL Matrix4( T x0, T x1, T x2, T x3,
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

            /**
             * @brief Transpose the matrix in place
             * @return A reference to self
             */
            ML_FUNC_DECL Matrix4 &Transpose();

            /**
             * @return A transposed copy of the matrix
             */
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetTransposed() const;

            /**
             *
             * @return The determinant of the matrix
             */
            [[nodiscard]] ML_FUNC_DECL T GetDeterminant();

            /**
             * @brief Invert the matrix in place
             * @return A reference to self
             */
            ML_FUNC_DECL Matrix4 &Invert();

            /**
             * @return An inverted copy of the matrix
             */
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetInverted() const;

            /**
             * @brief Normalize the matrix in place
             * @return A reference to self
             */
            ML_FUNC_DECL Matrix4 &Normalize();

            /**
             * @return An inverted copy of the matrix
             */
            [[nodiscard]] ML_FUNC_DECL Matrix4 GetNormalized() const;

            // TODO: Implement Properly
            ML_FUNC_DECL Vector4<T> &RotateVector(Vector4<T> &vec) const;
            [[nodiscard]] ML_FUNC_DECL Vector4<T> GetRotatedVector(const Vector4<T> &vec) const;

            // TODO: Implement properly
            ML_FUNC_DECL Vector4<T> &RotateVector(Internal::Vector3<T> &vec) const;
            [[nodiscard]] ML_FUNC_DECL Vector4<T> GetRotatedVector(const Internal::Vector3<T> &vec) const;

            /**
             * @return A perspective projection matrix
             */
            static ML_FUNC_DECL Matrix4 CreatePerspective(T left, T right, T bottom, T top, T near, T far);

            /**
             * @param fovy   Vertical fov of the perspective (in degrees)
             * @param aspect Aspect ratio (width / height)
             * @param near   Clipping the objects closer than this
             * @param far    Clipping the objects farther than this
             * @return A perspective projection matrix
             */
            static ML_FUNC_DECL Matrix4 CreatePerspective(T fovy, T aspect, T near, T far);

            /**
             * @param left   Leftmost of the projection
             * @param right  Rightmost coordinate of the projection
             * @param bottom Lowest coordinate of the projection
             * @param top    Highest coordinate of the projection
             * @param near   Clipping the objects closer than this
             * @param far    Clipping the objects farther than this
             * @return A orthographic projection matrix
             */
            static ML_FUNC_DECL Matrix4 CreateOrtho(T left, T right, T bottom, T top, T near, T far);

            /**
             * @param translation Translation vector in XYZ coordinates
             * @return A matrix that represent the translation given
             */
            static ML_FUNC_DECL Matrix4 CreateTranslationMat(Internal::Vector3<T> translation);

            /**
             * @param axis  Axis of the rotation
             * @param angle Angle of the rotation (in radians)
             * @return A matrix that represent the rotation of \p angle around the \p axis
             */
            static ML_FUNC_DECL Matrix4 CreateRotationMat(Internal::Vector3<T> axis, T angle);

            /**
             * @param rotation Quaternion representing the rotation (Should be normalized before)
             * @return A matrix that represent the \p rotation given
             */
            static ML_FUNC_DECL Matrix4 CreateRotationMat(Internal::Quaternion<T> rotation);

            /**
             * @param angle Euler angle of the rotation (in radians)
             * @return A matrix that represent a rotation of \p angle around the X axis
             */
            static ML_FUNC_DECL Matrix4 CreateXRotationMat(T angle);

            /**
             * @param angle Euler angle of the rotation (in radians)
             * @return A matrix that represent a rotation of \p angle around the Y axis
             */
            static ML_FUNC_DECL Matrix4 CreateYRotationMat(T angle);

            /**
             * @param angle Euler angle of the rotation (in radians)
             * @return A matrix that represent a rotation of \p angle around the Z axis
             */
            static ML_FUNC_DECL Matrix4 CreateZRotationMat(T angle);

            /**
             * @param angles Euler angles of the rotation (in radians)
             * @return A matrix that represent a rotation given by the Euler angles
             */
            static ML_FUNC_DECL Matrix4 CreateXYZRotationMat(Internal::Vector3<T> angles);

            /**
             * @param scale Scale vector in XYZ coordinates
             * @return A matrix that represent the scale given
             */
            static ML_FUNC_DECL Matrix4 CreateScaleMat(Internal::Vector3<T> scale);

            /**
             * @param translation Translation vector in XYZ coordinates
             * @param rotation Euler angles of the rotation (in radians)
             * @param scale Scale vector in XYZ coordinates
             * @return A matrix representing the combination of Translation, RotationXYZ and Scale (in this order)
             */
            static ML_FUNC_DECL Matrix4 CreateTRSMat(Internal::Vector3<T> translation,
                                                    Internal::Vector3<T> rotation,
                                                    Internal::Vector3<T> scale);

            /**
             * @param translation Translation vector in XYZ coordinates
             * @param rotation Euler angles of the rotation (in radians)
             * @param scale Scale vector in XYZ coordinates
             * @return A matrix representing the combination of Scale, RotationXYZ and Translation (in this order)
             */
            static ML_FUNC_DECL Matrix4 CreateSRTMat(Internal::Vector3<T> translation,
                                                     Internal::Vector3<T> rotation,
                                                     Internal::Vector3<T> scale);

            /**
             * @param translation Translation vector in XYZ coordinates
             * @param rotation Quaternion representing the rotation
             * @param scale Scale vector in XYZ coordinates
             * @return A matrix representing the combination of Translation, RotationXYZ and Scale (in this order)
             */
            static ML_FUNC_DECL Matrix4 CreateTRSMat(Internal::Vector3<T> translation,
                                                     Internal::Quaternion<T> rotation,
                                                     Internal::Vector3<T> scale);

            /**
             * @param translation Translation vector in XYZ coordinates
             * @param rotation Quaternion representing the rotation
             * @param scale Scale vector in XYZ coordinates
             * @return A matrix representing the combination of Scale, RotationXYZ and Translation (in this order)
             */
            static ML_FUNC_DECL Matrix4 CreateSRTMat(Internal::Vector3<T> translation,
                                                     Internal::Quaternion<T> rotation,
                                                     Internal::Vector3<T> scale);

            /**
             * @param origin Origin (eye) of the viewer
             * @param target Focus point of the viewer
             * @param upDir Up vector of the viewer
             * @return A matrix corresponding to the orientation required for \p origin to look at \p target
             */
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

            // TODO: Implement properly
            ML_FUNC_DECL Vector4<T> &Mult(const Vector4<T> &other);
            [[nodiscard]] ML_FUNC_DECL Vector4<T> operator*(const Vector4<T> &other) const;

            // TODO: Implement properly
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

    /**
     * @param ratio percentage of the lerp (between 0 and 1)
     * @return The linear interpolation between \p begin and \p end
     */
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
        for (int i = 0; i < 4; i++)
        {
            for (int j = (i+1); j < 4; j++)
            {
                const T tmp = values[i*4 + j];
                values[i*4 + j] = values[j*4 + i];
                values[j*4 + i] = tmp;
            }
        }
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::GetTransposed() const
    {
        return Internal::Matrix4<T>{*this}.Transpose();
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL T Internal::Matrix4<T>::GetDeterminant()
    {
        T af = values[0*4 + 0] * values[1*4 + 1]; T ag = values[0*4 + 0] * values[1*4 + 2]; T ah = values[0*4 + 0] * values[1*4 + 3];
        T be = values[0*4 + 1] * values[1*4 + 0]; T bg = values[0*4 + 1] * values[1*4 + 2]; T bh = values[0*4 + 1] * values[1*4 + 3];
        T ce = values[0*4 + 2] * values[1*4 + 0]; T cf = values[0*4 + 2] * values[1*4 + 1]; T ch = values[0*4 + 2] * values[1*4 + 3];
        T de = values[0*4 + 3] * values[1*4 + 0]; T df = values[0*4 + 3] * values[1*4 + 1]; T dg = values[0*4 + 3] * values[1*4 + 2];
        T in = values[2*4 + 0] * values[3*4 + 1]; T io = values[2*4 + 0] * values[3*4 + 2]; T ip = values[2*4 + 0] * values[3*4 + 3];
        T jm = values[2*4 + 1] * values[3*4 + 0]; T jo = values[2*4 + 1] * values[3*4 + 2]; T jp = values[2*4 + 1] * values[3*4 + 3];
        T km = values[2*4 + 2] * values[3*4 + 0]; T kn = values[2*4 + 2] * values[3*4 + 1]; T kp = values[2*4 + 2] * values[3*4 + 3];
        T lm = values[2*4 + 3] * values[3*4 + 0]; T ln = values[2*4 + 3] * values[3*4 + 1]; T lo = values[2*4 + 3] * values[3*4 + 2];

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
        for (int i = 0; i < 16; i++)
        {
            values[i] /= det;
        }

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
                          0                    , 0                    , -1                        , 0}.Transpose();
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
                          0             , 0             , 0             , 1}.Transpose();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateTranslationMat(Internal::Vector3<T> translation)
    {
        return Internal::Matrix4<T>{1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          translation.X, translation.Y, translation.Z, 1};
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
                            0.0f        , 0.0f        , 0.0f        , 1.0f};//.Transpose();
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateRotationMat(Internal::Quaternion<T> rotation)
    {
        rotation.Normalize();
        float x2 = 2 * (rotation.X * rotation.X), y2 = 2 * (rotation.Y * rotation.Y), z2 = 2 * (rotation.Z * rotation.Z);
        float xy = 2 * (rotation.X * rotation.Y), xz = 2 * (rotation.X * rotation.Z), yz = 2 * (rotation.Y * rotation.Z);
        float xw = 2 * (rotation.X * rotation.W), yw = 2 * (rotation.Y * rotation.W), zw = 2 * (rotation.Z * rotation.W);


        return Internal::Matrix4<T>{1 - y2 - z2, xy - zw    , xz + yw    , 0,
                                    xy + zw    , 1 - x2 - z2, yz - xw    , 0,
                                    xz - yw    , yz + xw    , 1 - x2 - y2, 0,
                                    0          , 0          , 0          , 1}.Transpose();
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
        return CreateYRotationMat(angles.Y) * CreateXRotationMat(angles.X) * CreateZRotationMat(angles.Z);
//        return Internal::Matrix4<T>{cz * cy, (cz * sy * sx) - (sz * cx), (cz * sy * cx) + (sz * sx), 0,
//                          sz * cy, (sz * sy * sx) + (cz * cx), (sz * sy * cx) - (cz * sx), 0,
//                          -sy    , cy * sx                   , cy * cx                   , 0,
//                          0      , 0                         , 0                          , 1};
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
        return (CreateTranslationMat(translation) * CreateXYZRotationMat(rotation) * CreateScaleMat(scale));
    }


    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateSRTMat(Internal::Vector3<T> translation, Internal::Vector3<T> rotation, Internal::Vector3<T> scale)
    {
        return (CreateScaleMat(scale) * CreateXYZRotationMat(rotation) * CreateTranslationMat(translation));
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateTRSMat(Internal::Vector3<T> translation, Internal::Quaternion<T> rotation, Internal::Vector3<T> scale)
    {
        return (CreateTranslationMat(translation) * CreateRotationMat(rotation) * CreateScaleMat(scale));
    }


    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::CreateSRTMat(Internal::Vector3<T> translation, Internal::Quaternion<T> rotation, Internal::Vector3<T> scale)
    {
        return (CreateScaleMat(scale) * CreateRotationMat(rotation) * CreateTranslationMat(translation));
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
        for (int i = 0; i < 16; i++)
        {
            values[i] = other.values[i];
        }
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL bool Internal::Matrix4<T>::operator==(const Internal::Matrix4<T>& other) const
    {
        for (int i = 0; i < 16; i++)
        {
            if (values[i] != other.values[i])
                return false;
        }
        return true;
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
        Internal::Matrix4<T> retMat = *this;
        retMat += other;
        return retMat;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator+=(const Internal::Matrix4<T>& other)
    {
        for (int i = 0; i < 16; i++)
        {
            values[i] += other.values[i];
        }
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator++()
    {
        for (int i = 0; i < 16; i++)
        {
            values[i]++;
        }
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
        Internal::Matrix4<T> retMat = *this;
        retMat -= other;
        return retMat;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator-=(const Internal::Matrix4<T>& other)
    {
        for (int i = 0; i < 16; i++)
        {
            values[i] -= other.values[i];
        }
        return *this;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator--()
    {
        for(int i = 0; i < 16; i++)
        {
            values[i]--;
        }
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
        Internal::Matrix4<T> retMat = *this;
        retMat *= other;
        return retMat;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator*=(const Internal::Matrix4<T>& other)
    {
        const Internal::Matrix4<T> oldMat{*this};
//        for (int i = 0; i < 16; i++)
//        {
//            values[(i%4) * 4 + (i/4)] = other.values[(i%4) * 4 + 0] * oldMat.values[0 * 4 + (i/4)]
//                      + other.values[(i%4) * 4 + 1] * oldMat.values[1 * 4 + (i/4)]
//                      + other.values[(i%4) * 4 + 2] * oldMat.values[2 * 4 + (i/4)]
//                      + other.values[(i%4) * 4 + 3] * oldMat.values[3 * 4 + (i/4)];
//        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                values[j * 4 + i] = other.values[j * 4 + 0] * oldMat.values[0 * 4 + i]
                                  + other.values[j * 4 + 1] * oldMat.values[1 * 4 + i]
                                  + other.values[j * 4 + 2] * oldMat.values[2 * 4 + i]
                                  + other.values[j * 4 + 3] * oldMat.values[3 * 4 + i];
            }
        }
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator*(const T& scalar) const
    {
        Internal::Matrix4<T> retMat = *this;
        retMat *= scalar;
        return retMat;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator*=(const T& scalar)
    {
        for (int i = 0; i < 16; i++)
        {
            values[i] *= scalar;
        }
        return *this;
    }

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Internal::Matrix4<T> Internal::Matrix4<T>::operator/(const T& scalar) const
    {
        Internal::Matrix4<T> retMat = *this;
        retMat *= scalar;
        return retMat;
    }

    template<typename T>
    ML_FUNC_DECL Internal::Matrix4<T>& Internal::Matrix4<T>::operator/=(const T& scalar)
    {
        for (int i = 0; i < 16; i++)
        {
            values[i] /= scalar;
        }
        return *this;
    }

}
template<typename T>
[[nodiscard]] ML_FUNC_DECL BwatEngine::Math::Internal::Matrix4<T> operator-(BwatEngine::Math::Internal::Matrix4<T> mat)
{
    mat *= -1;
    return mat;
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