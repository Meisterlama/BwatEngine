//
// Created by lama on 16/12/2020.
//

#include <gtest/gtest.h>
#include "Math/Math.hpp"

using BMath::vec2f;

TEST(Vector2, Constructors)
{
    vec2f vec{1, 0};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 0);
    vec = {1};
    ASSERT_EQ(vec.X, 1);
    ASSERT_EQ(vec.Y, 1);
    vec = {0, 1};
    ASSERT_EQ(vec.X, 0);
    ASSERT_EQ(vec.Y, 1);
    vec2f vec2 = vec;
    ASSERT_EQ(vec2.X, vec.X);
    ASSERT_EQ(vec2.Y, vec.Y);
}

TEST(Vector2, Addition)
{
    vec2f vec1{1, 0};
    vec2f vec2{2, 1};
    vec2f checkVec{3, 1};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {-1, 0};
    checkVec = {0};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec2 = {0, -1};
    checkVec = {1, -1};
    ASSERT_EQ(vec1 + vec2, checkVec);

    vec1 += {1};
    checkVec = {2, 1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    vec1.Add({1});
    checkVec = {1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {0};
    checkVec = {1};
    ASSERT_EQ(++vec1, checkVec);
}

TEST(Vector2, Substraction)
{
    vec2f vec1{1, 0};
    vec2f vec2{2, 1};
    vec2f checkVec{-1, -1};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {-1, 0};
    checkVec = {2, 0};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec2 = {0, -1};
    checkVec = {1, 1};
    ASSERT_EQ(vec1 - vec2, checkVec);

    vec1 -= {1};
    checkVec = {0, -1};
    ASSERT_EQ(vec1, checkVec);

    vec1 = {1};
    checkVec = {0};
    ASSERT_EQ(--vec1, checkVec);

    vec1 = {0};
    vec1.Sub({1});
    checkVec = {-1};
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector2, Multiplication)
{
    vec2f vec1{1, 0};
    vec2f checkVec{2,0};
    ASSERT_EQ(vec1 * 2, checkVec);
    ASSERT_EQ(2 * vec1, checkVec);

    vec1 = -vec1;
    checkVec = {-1, 0};
    ASSERT_EQ(vec1, checkVec);

    vec1 *= 2;
    checkVec = {-2, 0};
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

TEST(Vector2, Division)
{
    vec2f vec1{2, 0};
    vec2f checkVec{1,0};
    ASSERT_EQ(vec1 / 2, checkVec);
    ASSERT_EQ(vec1 / -2, -checkVec);

    vec1 /= 2;
    ASSERT_EQ(vec1, checkVec);
}

TEST(Vector2, DotProduct)
{
    vec2f vec1 = {3,4};
    ASSERT_EQ(vec1.DotProduct(vec1), 3 * 3 + 4 * 4);
    vec2f vec2 = {2,5};
    ASSERT_EQ(vec1.DotProduct(vec2), vec1.X * vec2.X + vec1.Y * vec2.Y);


}

TEST(Vector2, Length)
{
    vec2f vec1 = {3,4};
    ASSERT_EQ(vec1.Length(), 5);
    ASSERT_EQ(vec1.Amplitude(), 25);
    vec1 = {-3,4};
    ASSERT_EQ(vec1.Length(), 5);
    ASSERT_EQ(vec1.Amplitude(), 25);
    vec1 = {-3, -4};
    ASSERT_EQ(vec1.Length(), 5);
    ASSERT_EQ(vec1.Amplitude(), 25);

    vec1 = {0};
    ASSERT_EQ(vec1.Length(), 0);
    ASSERT_EQ(vec1.Amplitude(), 0);
}

TEST(Vector2, Normalize)
{
    vec2f vec1 = {3,4};
    vec2f checkVec = vec1;
    ASSERT_EQ(vec1.GetNormalized().Length(), 1);
    ASSERT_EQ(vec1, checkVec);
    ASSERT_EQ(vec1.Normalize().Length(), 1);
    ASSERT_NE(vec1, checkVec);

    vec1 = {0};
    ASSERT_EQ(vec1.SafeNormalize().Length(), 0);
    ASSERT_EQ(vec1.GetSafeNormalized().Length(), 0);
    ASSERT_NE(vec1.Normalize(), 0);
}

TEST(Vector2, Comparison)
{
    vec2f vec1{1};
    ASSERT_TRUE(vec1.Equals(vec1));
    ASSERT_TRUE(vec1 == vec1);
    ASSERT_FALSE(vec1 != vec1);

    vec2f vec2{1};
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

TEST(Vector2, Lerp)
{
    vec2f vec1{0};
    vec2f vec2{2};
    vec2f checkVec{1};
    ASSERT_EQ(Lerp(vec1, vec2, 0.5), checkVec);
    ASSERT_EQ(Lerp(vec1, vec2, 0), vec1);
    ASSERT_EQ(Lerp(vec1, vec2, 1), vec2);

}