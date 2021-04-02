#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Math/Math.hpp"

using BMath::Matrix4;

typedef BMath::Matrix4<float> Mat4f;

bool operator==(Mat4f Bmat, glm::mat4 Gmat)
{
    for (int i = 0; i < 16; i++)
    {
        if (Bmat[i] != Gmat[i/4][i%4])
            return false;
    }
    return true;
}

glm::mat4 BMatToGMat(Mat4f bmat)
{
    return glm::mat4(
            bmat.v0, bmat.v4, bmat.v8,bmat.v12,
            bmat.v1, bmat.v5, bmat.v9,bmat.v13,
            bmat.v2, bmat.v6, bmat.v10,bmat.v14,
            bmat.v3, bmat.v7, bmat.v11,bmat.v15
            );
}

TEST(Matrix4, Constructors)
{
ASSERT_TRUE(Mat4f{0} == glm::mat4(0));
ASSERT_TRUE(Mat4f{1} == glm::mat4(1));

ASSERT_TRUE( Mat4f(1, 2, 3, 4) == glm::mat4(1, 0, 0, 0,
                                            0, 2, 0, 0,
                                            0, 0, 3, 0,
                                            0, 0, 0, 4));

Mat4f testMat{1, 2, 3, 4};
Mat4f mat = testMat;

ASSERT_TRUE(testMat == mat);

testMat = {1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10, 11, 12,
           13, 14, 15, 16};

ASSERT_TRUE(testMat == BMatToGMat(testMat));
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

glm::mat4 gmat2 {1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16};

glm::mat4 gmat3 {6, 3, 3, 4,
                 5, 2, 2, 7,
                 2, 2, 6, 12,
                 1, 3, 4, 8};

ASSERT_NE(mat2 * mat3, mat3 * mat2);

gmat3 = gmat2 * gmat3;
mat3 = mat2 * mat3;

ASSERT_TRUE(mat3 == gmat3);
}


TEST(Matrix4, TRS)
{
Mat4f mat = Mat4f::CreateTRSMat({0}, {0}, {1});
Mat4f testMat{1};

ASSERT_EQ(mat, testMat);

Mat4f mat2 = Mat4f::CreateTRSMat({1, 2, 3}, {0}, {1});
testMat = {1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           1, 2, 3, 1};

ASSERT_EQ(mat2, testMat);

}


TEST(Matrix4, Perspective)
{
    Mat4f mat = Mat4f::CreatePerspective(BMath::ToRads(60), 800.f/600.f, 0.01f, 100.f);
    glm::mat4 gmat = glm::perspective(BMath::ToRads(60), 800.f/600.f, 0.01f, 100.f);

    ASSERT_TRUE(mat == gmat);
}
