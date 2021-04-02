//
// Created by lama on 16/12/2020.
//

#include <gtest/gtest.h>
#include <Math/Math.hpp>

using BMath::vec4f;

TEST(Vector4, Constructors)
{
    vec4f vec{1, 0, 1, 0};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 0);
    ASSERT_EQ(vec.Z, 1);
    ASSERT_EQ(vec.W, 0);
    vec = {1};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 1);
    ASSERT_EQ(vec.Z, 1);
    ASSERT_EQ(vec.W, 1);
    vec = {0, 1, 0, 1};
    ASSERT_EQ(vec.X, 0);
    ASSERT_EQ(vec.Y, 1);
    ASSERT_EQ(vec.Z, 0);
    ASSERT_EQ(vec.W, 1);
    vec4f vec2 = vec;
    ASSERT_EQ(vec2.X, vec.X);
    ASSERT_EQ(vec2.Y, vec.Y);
    ASSERT_EQ(vec2.Z, vec.Z);
    ASSERT_EQ(vec2.W, vec.W);
}

TEST(Vector4, Addition)
{
    vec4f vec1{1, 0, 2, 3};
    vec4f vec2{2, 1, 3, 4};
    vec4f checkVec{3, 1, 5, 7};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {-1, 0, -2, -3};
    checkVec = {0};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {0, -1, 1, 2};
    checkVec = {1, -1, 3, 5};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec1 += {1};
    checkVec = {2, 1, 3, 4};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    vec1.Add({1});
    checkVec = {1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    checkVec = {1};
    ASSERT_EQ(++vec1, checkVec);
}

TEST(Vector4, Substraction)
{
    vec4f vec1{1, 0, 1, 0};
    vec4f vec2{2, 1, 0, 3};
    vec4f checkVec{-1, -1, 1, -3};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {-1, 0, -2, 2};
    checkVec = {2, 0, 3, -2};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {0, -1, -1, 5};
    checkVec = {1, 1, 2, -5};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec1 -= {1};
    checkVec = {0, -1, 0, -1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {1};
    checkVec = {0};
    ASSERT_EQ(--vec1, checkVec);

    vec1 = {0};
    vec1.Sub({1});
    checkVec = {-1};
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector4, Multiplication)
{
    vec4f vec1{1, 0, 1, 2};
    vec4f checkVec{2, 0, 2, 4};
    ASSERT_EQ(vec1 * 2, checkVec);
    ASSERT_EQ(2 * vec1, checkVec);

    vec1 = -vec1;
    checkVec = {-1, 0, -1, -2};
    ASSERT_EQ(vec1, checkVec);

    vec1 *= 2;
    checkVec = {-2, 0, -2, -4};
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

TEST(Vector4, Division)
{
    vec4f vec1{2, 0, 2, -2};
    vec4f checkVec{1, 0, 1, -1};
    ASSERT_EQ(vec1 / 2, checkVec);
    ASSERT_EQ(vec1 / -2, -checkVec);

    vec1 /= 2;
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector4, DotProduct)
{
    vec4f vec1 = {3, 4, 5, -6};
    ASSERT_EQ(vec1.DotProduct(vec1), 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6);
    vec4f vec2 = {2, 5, -3, 2};
    ASSERT_EQ(vec1.DotProduct(vec2), 3 * 2 + 4 * 5 - 5 * 3 - 6 * 2);

}

TEST(Vector4, Length)
{
    vec4f vec1 = {3, 4, 5, 6};
    float memSquared = 3 * 3 + 4 * 4 + 5 * 5 + 6 * 6;
    ASSERT_LE(vec1.Length() - std::sqrt(memSquared), BMath::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), memSquared);
    vec1 = {-3, 4, 5, 6};
    ASSERT_LE(vec1.Length() - std::sqrt(memSquared), BMath::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), memSquared);
    vec1 = {-3, -4, 5, 6};
    ASSERT_LE(vec1.Length() - std::sqrt(memSquared), BMath::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), memSquared);
    vec1 = {-3, -4, 5, 6};
    ASSERT_LE(vec1.Length() - std::sqrt(memSquared), BMath::EPSILON);
    ASSERT_EQ(vec1.Amplitude(), memSquared);

    vec1 = {0};
    ASSERT_EQ(vec1.Length(), 0);
    ASSERT_EQ(vec1.Amplitude(), 0);
}

TEST(Vector4, Normalize)
{
    vec4f vec1 = {3, 4, 5, 6};
    vec4f checkVec = vec1;
    ASSERT_LE(vec1.GetNormalized().Length() - 1, BMath::EPSILON);
    ASSERT_EQ(vec1, checkVec);
    ASSERT_LE(vec1.Normalize().Length() - 1, BMath::EPSILON);
    ASSERT_NE(vec1, checkVec);

    vec1 = {0};
    ASSERT_EQ(vec1.SafeNormalize().Length(), 0);
    ASSERT_EQ(vec1.GetSafeNormalized().Length(), 0);
    ASSERT_NE(vec1.Normalize(), 0);
}

TEST(Vector4, Comparison)
{
    vec4f vec1{1};
    ASSERT_TRUE(vec1.Equals(vec1));
    ASSERT_TRUE(vec1 == vec1);
    ASSERT_FALSE(vec1 != vec1);

    vec4f vec2{1};
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

TEST(Vector4, Lerp)
{
    vec4f vec1{0};
    vec4f vec2{2};
    vec4f checkVec{1};
    ASSERT_EQ(Lerp(vec1, vec2, 0.5), checkVec);
    ASSERT_EQ(Lerp(vec1, vec2, 0), vec1);
    ASSERT_EQ(Lerp(vec1, vec2, 1), vec2);
}