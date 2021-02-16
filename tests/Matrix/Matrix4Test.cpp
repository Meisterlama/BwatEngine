#include <gtest/gtest.h>
#include "Math/Math.hpp"

using BMath::Matrix4;

typedef BMath::Matrix4<float> Mat4f;

TEST(Matrix4, Constructors)
{
Mat4f testMat{0};

ASSERT_EQ(testMat.v0 , 0);
ASSERT_EQ(testMat.v1 , 0);
ASSERT_EQ(testMat.v2 , 0);
ASSERT_EQ(testMat.v3 , 0);
ASSERT_EQ(testMat.v4 , 0);
ASSERT_EQ(testMat.v5 , 0);
ASSERT_EQ(testMat.v6 , 0);
ASSERT_EQ(testMat.v7 , 0);
ASSERT_EQ(testMat.v8 , 0);
ASSERT_EQ(testMat.v9 , 0);
ASSERT_EQ(testMat.v10, 0);
ASSERT_EQ(testMat.v11, 0);
ASSERT_EQ(testMat.v12, 0);
ASSERT_EQ(testMat.v13, 0);
ASSERT_EQ(testMat.v14, 0);
ASSERT_EQ(testMat.v15, 0);

Mat4f mat{1};

testMat.v0 = 1;
testMat.v5 = 1;
testMat.v10 = 1;
testMat.v15 = 1;

ASSERT_EQ(mat, testMat);

mat = {1, 2, 3, 4};

testMat.v0 = 1;
testMat.v5 = 2;
testMat.v10 = 3;
testMat.v15 = 4;

ASSERT_EQ(mat, testMat);

Mat4f mat2 = mat;

ASSERT_EQ(mat2, testMat);

Mat4f mat3 {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16};

testMat.v0  = 1;
testMat.v1  = 2;
testMat.v2  = 3;
testMat.v3  = 4;
testMat.v4  = 5;
testMat.v5  = 6;
testMat.v6  = 7;
testMat.v7  = 8;
testMat.v8  = 9;
testMat.v9  = 10;
testMat.v10 = 11;
testMat.v11 = 12;
testMat.v12 = 13;
testMat.v13 = 14;
testMat.v14 = 15;
testMat.v15 = 16;

ASSERT_EQ(mat3, testMat);
}

TEST(Matrix4, Mult)
{
Mat4f testMat{0};
Mat4f mat{1};

ASSERT_EQ(testMat * mat, testMat);

testMat = {1};

ASSERT_EQ(testMat * mat, testMat);
ASSERT_EQ(mat * testMat, testMat);

Mat4f mat2 {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16};

Mat4f mat3 {6, 3, 3, 4,
            5, 2, 2, 7,
            2, 2, 6, 12,
            1, 3, 4, 8};

ASSERT_NE(mat2 * mat3, mat3 * mat2);

testMat = {26, 25, 41, 86,
           82, 65, 101, 210,
           138, 105, 161, 334,
           194, 145, 221, 458};
ASSERT_EQ(mat2 * mat3, testMat);
}


TEST(Matrix4, TRS)
{
Mat4f mat = Mat4f::CreateTRSMat({0}, {0}, {1});
Mat4f testMat{1};

ASSERT_EQ(mat, testMat);

Mat4f mat2 = Mat4f::CreateTRSMat({1, 2, 3}, {0}, {1});
testMat = {1, 0, 0, 1,
           0, 1, 0, 2,
           0, 0, 1, 3,
           0, 0, 0, 1};

ASSERT_EQ(mat2, testMat);

}
