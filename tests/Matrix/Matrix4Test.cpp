#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Math/Math.hpp"

using namespace BwatEngine::Math;

bool operator==(Mat4f Bmat, glm::mat4 Gmat)
{
    for (int i = 0; i < 16; i++) {
        if (Bmat[i] != Gmat[i / 4][i % 4])
            return false;
    }
    return true;
}

glm::mat4 BMatToGMat(Mat4f bmat)
{
    return glm::mat4(
        bmat.v0, bmat.v1, bmat.v2, bmat.v3,
        bmat.v4, bmat.v5, bmat.v6, bmat.v7,
        bmat.v8, bmat.v9, bmat.v10, bmat.v11,
        bmat.v12, bmat.v13, bmat.v14, bmat.v15
    );
}
Mat4f GMatToBMat(glm::mat4 gmat)
{
    Mat4f retMat{0};
    for (int i = 0; i < 16; i++) {
        retMat[i] = gmat[i / 4][i % 4];
    }
    return retMat;
}

#define ASSERT_MAT_EQ(mat1, mat2) \
    for (int i = 0; i < 16; i++){ \
    ASSERT_FLOAT_EQ(mat1[i], mat2[i]);}


const Mat4f MatEPS = {EPSILON};

TEST(Matrix4, Constructors)
{
    ASSERT_TRUE(Mat4f{0} == glm::mat4(0));
    ASSERT_TRUE(Mat4f{1} == glm::mat4(1));

    ASSERT_TRUE(Mat4f(1, 2, 3, 4) == glm::mat4(1, 0, 0, 0,
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

    ASSERT_MAT_EQ((testMat * mat), testMat);

    testMat = {1};
    auto tmpMat = (testMat * mat);
    ASSERT_MAT_EQ(tmpMat, testMat);
    ASSERT_MAT_EQ((mat * testMat), testMat);

    Mat4f mat2{1, 2, 3, 4,
               5, 6, 7, 8,
               9, 10, 11, 12,
               13, 14, 15, 16};

    Mat4f mat3{6, 3, 3, 4,
               5, 2, 2, 7,
               2, 2, 6, 12,
               1, 3, 4, 8};

    glm::mat4 gmat2{1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16};

    glm::mat4 gmat3{6, 3, 3, 4,
                    5, 2, 2, 7,
                    2, 2, 6, 12,
                    1, 3, 4, 8};

    ASSERT_NE(mat2 * mat3, mat3 * mat2);

    gmat3 = gmat2 * gmat3;
    auto bgmat3 = GMatToBMat(gmat3);
    mat3 = mat2 * mat3;
//
    ASSERT_MAT_EQ(mat3, bgmat3);
}


TEST(Matrix4, TRS)
{
    Mat4f mat = Mat4f::CreateTRSMat({0}, {0}, {1});
    Mat4f testMat{1};

    ASSERT_MAT_EQ(mat, testMat);

    Mat4f mat2 = Mat4f::CreateTRSMat({1, 2, 3}, {0}, {1});
    testMat = {1, 0, 0, 1,
               0, 1, 0, 2,
               0, 0, 1, 3,
               0, 0, 0, 1};

    ASSERT_MAT_EQ(mat2, testMat);

}


TEST(Matrix4, Perspective)
{
    Mat4d mat = Mat4d::CreatePerspective(60, 800.f / 600.f, 0.01f, 100.f);
    glm::mat4 gmat = glm::perspective(BwatEngine::Math::ToRads(60), 800.f / 600.f, 0.01f, 100.f);

    auto bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}
