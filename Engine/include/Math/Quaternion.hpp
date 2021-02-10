#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP

namespace BMath
{

#pragma region Declarations

    template <typename T>
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
        : X(x), Y(x), Z(x), W(x)
        {}

        ML_FUNC_DECL Quaternion(T x, T y, T z, T w)
        : X(x), Y(y), Z(z), W(w)
        {}

        ML_FUNC_DECL Quaternion(T roll, T pitch, T yaw)
        {
            T x0 = Cos(roll/2);
            T x1 = Sin(roll/2);
            T y0 = Cos(pitch/2);
            T y1 = Sin(pitch/2);
            T z0 = Cos(yaw/2);
            T z1 = Sin(yaw/2);

            X = x1*y0*z0 - x0*y1*z1;
            Y = x0*y1*z0 - x1*y0*z1;
            Z = x0*y0*z1 - x1*y1*z0;
            W = x0*y0*z0 - x1*y1*z1;
        }

        ML_FUNC_DECL Quaternion(const Quaternion& vec) = default;
        ML_FUNC_DECL Quaternion(Quaternion&& vec) noexcept = default;
        ~Quaternion() = default;

        // Compute the amplitude without computing the sqrt
        // Valid for comparisons, but actually equals to length squared
        [[nodiscard]] ML_FUNC_DECL float Amplitude() const;

        // Return the length of the vector
        // If you only need it for comparison consider using Amplitude()
        [[nodiscard]] ML_FUNC_DECL float Length() const;

        // Scale in place
        ML_FUNC_DECL Quaternion& Scale(const float& factor);

        // Get a scaled copy of the vector
        [[nodiscard]] ML_FUNC_DECL Quaternion GetScaled(const float& factor) const;

        // Normalize in place
        ML_FUNC_DECL Quaternion& Normalize();

        // Get a normalized copy of the vector
        [[nodiscard]] ML_FUNC_DECL Quaternion GetNormalized() const;

        // Normalize in place.
        // Check for length != 0
        ML_FUNC_DECL Quaternion& SafeNormalize();

        // Get a normalized copy of the vector
        // If vector length == 0, return Vector{0}
        [[nodiscard]] ML_FUNC_DECL Quaternion GetSafeNormalized() const;

        // Conjugate in place
        ML_FUNC_DECL Quaternion& Conjugate();

        // Get a conjugate copy of the vector
        [[nodiscard]] ML_FUNC_DECL Quaternion GetConjugate() const;

        [[nodiscard]] ML_FUNC_DECL Matrix4<T> GetRotationMatrix();

        [[nodiscard]] ML_FUNC_DECL bool Equals(const Quaternion& rhs) const;
        [[nodiscard]] ML_FUNC_DECL bool IsZero() const;

        ML_FUNC_DECL Quaternion& operator=(const Quaternion& other);

        [[nodiscard]] ML_FUNC_DECL bool operator==(const Quaternion& rhs) const;

        [[nodiscard]] ML_FUNC_DECL bool operator!=(const Quaternion& rhs) const;

        [[nodiscard]] ML_FUNC_DECL const T& operator[](int idx) const;
        [[nodiscard]] ML_FUNC_DECL T& operator[](int idx);

        ML_FUNC_DECL Quaternion& Add(const Quaternion& vec);
        [[nodiscard]] ML_FUNC_DECL Quaternion operator+(const Quaternion& rhs) const;
        ML_FUNC_DECL Quaternion& operator+=(const Quaternion& vec);
        ML_FUNC_DECL Quaternion& operator++();

        ML_FUNC_DECL Quaternion& Sub(const Quaternion& vec);
        [[nodiscard]] ML_FUNC_DECL Quaternion operator-(const Quaternion& rhs) const;
        ML_FUNC_DECL Quaternion& operator-=(const Quaternion& vec);
        ML_FUNC_DECL Quaternion& operator--();

        [[nodiscard]] ML_FUNC_DECL Quaternion operator*(const float& scalar) const;
        ML_FUNC_DECL Quaternion& operator*=(const float& scalar);

        [[nodiscard]] ML_FUNC_DECL Quaternion operator/(const float& scalar) const;
        ML_FUNC_DECL Quaternion& operator/=(const float& scalar);

    };
    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator-(Quaternion<T> vec);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> operator*(const float& scalar, Quaternion<T> rhs);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> Lerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> NLerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

    template<typename T>
    [[nodiscard]] ML_FUNC_DECL Quaternion<T> SLerp(Quaternion<T> begin, Quaternion<T> end, float ratio);

#pragma endregion

#pragma region Definitions

#pragma endregion

}

#endif //MATH_QUATERNION_HPP