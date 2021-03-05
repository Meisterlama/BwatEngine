//
// Created by lama on 16/12/2020.
//

#include <gtest/gtest.h>
#include <Math/Math.hpp>

using BwatEngine::Math::Vec3f;

TEST(Vector3, Constructors)
{
    Vec3f vec{1, 0, 1};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 0);
    ASSERT_EQ(vec.Z, 1);
    vec = {1};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 1);
    ASSERT_EQ(vec.Z, 1);
    vec = {0, 1, 0};
    ASSERT_EQ(vec.X, 0);
    ASSERT_EQ(vec.Y, 1);
    ASSERT_EQ(vec.Z, 0);
    Vec3f vec2 = vec;
    ASSERT_EQ(vec2.X, vec.X);
    ASSERT_EQ(vec2.Y, vec.Y);
    ASSERT_EQ(vec2.Z, vec.Z);
}

TEST(Vector3, Addition)
{
    Vec3f vec1{1, 0, 2};
    Vec3f vec2{2, 1, 3};
    Vec3f checkVec{3, 1, 5};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {-1, 0, -2};
    checkVec = {0};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {0, -1, 1};
    checkVec = {1, -1, 3};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec1 += {1};
    checkVec = {2, 1, 3};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    vec1.Add({1});
    checkVec = {1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    checkVec = {1};
    ASSERT_EQ(++vec1, checkVec);
}

TEST(Vector3, Substraction)
{
    Vec3f vec1{1, 0, 1};
    Vec3f vec2{2, 1, 0};
    Vec3f checkVec{-1, -1, 1};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {-1, 0, -2};
    checkVec = {2, 0, 3};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {0, -1, -1};
    checkVec = {1, 1, 2};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec1 -= {1};
    checkVec = {0, -1, 0};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {1};
    checkVec = {0};
    ASSERT_EQ(--vec1, checkVec);

    vec1 = {0};
    vec1.Sub({1});
    checkVec = {-1};
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector3, Multiplication)
{
    Vec3f vec1{1, 0, 1};
    Vec3f checkVec{2, 0, 2};
    ASSERT_EQ(vec1 * 2, checkVec);
    ASSERT_EQ(2 * vec1, checkVec);

    vec1 = -vec1;
    checkVec = {-1, 0, -1};
    ASSERT_EQ(vec1, checkVec);

    vec1 *= 2;
    checkVec = {-2, 0, -2};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {2};
    checkVec = {-2};
    ASSERT_EQ(-vec1, checkVec);

    checkVec = {1};
    ASSERT_EQ(vec1.Scale(0.5), checkVec);
    checkVec = {2};
    ASSERT_EQ(vec1.GetScaled(2), checkVec);
    checkVec = {1};
    ASSERT_EQ(vec1, checkVec);

}

TEST(Vector3, Division)
{
    Vec3f vec1{2, 0, 2};
    Vec3f checkVec{1, 0, 1};
    ASSERT_EQ(vec1 / 2, checkVec);
    ASSERT_EQ(vec1 / -2, -checkVec);

    vec1 /= 2;
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector3, DotProduct)
{
    Vec3f vec1 = {3, 4, 5};
    ASSERT_EQ(vec1.DotProduct(vec1), 3 * 3 + 4 * 4 + 5 * 5);
    Vec3f vec2 = {2, 5, -3};
    ASSERT_EQ(vec1.DotProduct(vec2), vec1.X * vec2.X + vec1.Y * vec2.Y + vec1.Z * vec2.Z);

}

TEST(Vector3, Length)
{
    Vec3f vec1 = {3, 4, 5};
    ASSERT_LE(vec1.Length() - std::sqrt(50), BwatEngine::Math::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), 50);
    vec1 = {-3, 4, 5};
    ASSERT_LE(vec1.Length() - std::sqrt(50), BwatEngine::Math::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), 50);
    vec1 = {-3, -4, 5};
    ASSERT_LE(vec1.Length() - std::sqrt(50), BwatEngine::Math::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), 50);

    vec1 = {0};
    ASSERT_EQ(vec1.Length(), 0);
    ASSERT_EQ(vec1.Amplitude(), 0);
}

TEST(Vector3, Normalize)
{
    Vec3f vec1 = {3, 4, 5};
    Vec3f checkVec = vec1;
    ASSERT_EQ(vec1.GetNormalized().Length(), 1);
    ASSERT_EQ(vec1, checkVec);
    ASSERT_EQ(vec1.Normalize().Length(), 1);
    ASSERT_NE(vec1, checkVec);

    vec1 = {0};
    ASSERT_EQ(vec1.SafeNormalize().Length(), 0);
    ASSERT_EQ(vec1.GetSafeNormalized().Length(), 0);
    ASSERT_NE(vec1.Normalize(), 0);
}

TEST(Vector3, Comparison)
{
    Vec3f vec1{1};
    ASSERT_TRUE(vec1.Equals(vec1));
    ASSERT_TRUE(vec1 == vec1);
    ASSERT_FALSE(vec1 != vec1);

    Vec3f vec2{1};
    ASSERT_FALSE(vec2.IsZero());
    ASSERT_TRUE(vec1.Equals(vec2));
    ASSERT_TRUE(vec1 == vec2);
    ASSERT_FALSE(vec1 != vec2);
    vec2 = {0};
    ASSERT_TRUE(vec2.IsZero());
    ASSERT_FALSE(vec1.Equals(vec2));
    ASSERT_FALSE(vec1 == vec2);
    ASSERT_TRUE(vec1 != vec2);
    vec2 = {-1};
    ASSERT_FALSE(vec1.Equals(vec2));
    ASSERT_FALSE(vec1 == vec2);

}

TEST(Vector3, Lerp)
{
    Vec3f vec1{0};
    Vec3f vec2{2};
    Vec3f checkVec{1};
    ASSERT_EQ(Lerp(vec1, vec2, 0.5), checkVec);
    ASSERT_EQ(Lerp(vec1, vec2, 0), vec1);
    ASSERT_EQ(Lerp(vec1, vec2, 1), vec2);
}