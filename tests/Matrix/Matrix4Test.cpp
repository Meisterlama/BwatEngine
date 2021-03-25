#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Math/Math.hpp"

#include "../GlmBwatComparison.hpp"

using namespace BwatEngine::Math;

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

    ASSERT_MAT_EQ(mat3, bgmat3);

    gmat3 = gmat2 * gmat3;
    bgmat3 = GMatToBMat(gmat3);
    mat3 = mat2 * mat3;

    ASSERT_MAT_EQ(mat3, bgmat3);
}


TEST(Matrix4, TRS)
{
    float Tx = 1; float Ty = 2; float Tz = 3;
    float Rx = 4; float Ry = 5; float Rz = 6;
    float Sx = 1; float Sy = 1; float Sz = 1;

    Mat4f mat;
    glm::mat4 gmatT;
    glm::mat4 gmatR;
    glm::mat4 gmatS;
    glm::mat4 gmat;
    Mat4f bgmat;

    Tx = 1; Ty = 2; Tz = 3;
    Rx = 4; Ry = 5; Rz = 6;
    Sx = 1; Sy = 1; Sz = 1;

    mat = Mat4f::CreateTRSMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
                      glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
                      glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatT * gmatR * gmatS;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    Tx = 4; Ty = 1; Tz = 7;
    Rx = 7; Ry = 4; Rz = 12;
    Sx = 3; Sy = 9; Sz = 2;

    mat = Mat4f::CreateTRSMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
            glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
            glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatT * gmatR * gmatS;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    Tx = 2; Ty = 3; Tz = 8;
    Rx = 3; Ry = 1; Rz = 6;
    Sx = 6; Sy = 7; Sz = 5;

    mat = Mat4f::CreateTRSMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
            glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
            glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatT * gmatR * gmatS;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, SRT)
{
    float Tx = 1; float Ty = 2; float Tz = 3;
    float Rx = 4; float Ry = 5; float Rz = 6;
    float Sx = 1; float Sy = 1; float Sz = 1;

    Mat4f mat;
    glm::mat4 gmatT;
    glm::mat4 gmatR;
    glm::mat4 gmatS;
    glm::mat4 gmat;
    Mat4f bgmat;

    Tx = 1; Ty = 2; Tz = 3;
    Rx = 4; Ry = 5; Rz = 6;
    Sx = 1; Sy = 1; Sz = 1;

    mat = Mat4f::CreateSRTMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
            glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
            glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatS * gmatR * gmatT;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    Tx = 4; Ty = 1; Tz = 7;
    Rx = 7; Ry = 4; Rz = 12;
    Sx = 3; Sy = 9; Sz = 2;

    mat = Mat4f::CreateSRTMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
            glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
            glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatS * gmatR * gmatT;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    Tx = 2; Ty = 3; Tz = 8;
    Rx = 3; Ry = 1; Rz = 6;
    Sx = 6; Sy = 7; Sz = 5;

    mat = Mat4f::CreateSRTMat({Tx, Ty, Tz}, Vec3f{Rx, Ry, Rz}, {Sx, Sy, Sz});

    gmatT = glm::translate(glm::mat4(1), {Tx, Ty, Tz});
    gmatR = glm::rotate(glm::mat4{1}, Ry, {0, 1, 0}) *
            glm::rotate(glm::mat4{1}, Rx, {1, 0, 0}) *
            glm::rotate(glm::mat4{1}, Rz, {0, 0, 1});
    gmatS = glm::scale(glm::mat4{1}, {Sx, Sy, Sz});

    gmat = gmatS * gmatR * gmatT;
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, Perspective)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;

    mat = Mat4f::CreatePerspective(60, 800.f / 600.f, 0.01f, 100.f);
    gmat = glm::perspective(BwatEngine::Math::ToRads(60), 800.f / 600.f, 0.01f, 100.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreatePerspective(90, 200.f / 600.f, 0.06f, 100.f);
    gmat = glm::perspective(BwatEngine::Math::ToRads(90), 200.f / 600.f, 0.06f, 100.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreatePerspective(120, 350.f / 600.f, 0.03f, 100.f);
    gmat = glm::perspective(BwatEngine::Math::ToRads(120), 350.f / 600.f, 0.03f, 100.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, Orthographic)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;

    mat = Mat4f::CreateOrtho(-400.f, 400.f, -400.f, 400.f, 0.01f, 100.f);
    gmat = glm::ortho(-400.f, 400.f, -400.f, 400.f, 0.01f, 100.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreateOrtho(-800.f, 400.f, 200.f, 400.f, 0.01f, 100.f);
    gmat = glm::ortho(-800.f, 400.f, 200.f, 400.f, 0.01f, 100.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreateOrtho(-534.f, 400.f, -145.f, 400.f, 1.f, 130.f);
    gmat = glm::ortho(-534.f, 400.f, -145.f, 400.f, 1.f, 130.f);
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, Determinant)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;
    float det;
    float gdet;

    mat = {1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10, 11, 12,
           13, 14, 15, 16};

    gmat = {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16};

    det = mat.GetDeterminant();
    gdet = glm::determinant(gmat);

    ASSERT_EQ(det, gdet);

    mat = {6, 3, 3, 4,
           5, 2, 2, 7,
           2, 2, 6, 12,
           1, 3, 4, 8};

    gmat = {6, 3, 3, 4,
            5, 2, 2, 7,
            2, 2, 6, 12,
            1, 3, 4, 8};

    det = mat.GetDeterminant();
    gdet = glm::determinant(gmat);

    ASSERT_EQ(det, gdet);
}

TEST(Matrix4, Inverse)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;

    mat = {6, 3, 3, 4,
           5, 2, 2, 7,
           2, 2, 6, 12,
           1, 3, 4, 8};

    gmat = {6, 3, 3, 4,
            5, 2, 2, 7,
            2, 2, 6, 12,
            1, 3, 4, 8};

    mat.Invert();
    gmat = glm::inverse(gmat);
    bgmat = GMatToBMat(gmat);

    ASSERT_MAT_EQ(mat, bgmat);

    mat = {12, 2, 3, 4,
           5, 7, 7, 8,
           9, 10, 11, 12,
           13, 14, 15, 16};

    gmat = {12, 2, 3, 4,
            5, 7, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16};

    mat.Invert();
    gmat = glm::inverse(gmat);
    bgmat = GMatToBMat(gmat);

    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, Normalize)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;

    mat = {6, 3, 3, 4,
           5, 2, 2, 7,
           2, 2, 6, 12,
           1, 3, 4, 8};

    gmat = {6, 3, 3, 4,
            5, 2, 2, 7,
            2, 2, 6, 12,
            1, 3, 4, 8};

    mat = mat.GetNormalized();
    gmat = gmat / glm::determinant(gmat);
    bgmat = GMatToBMat(gmat);

    ASSERT_MAT_EQ(mat, bgmat);

    mat = {12, 2, 3, 4,
           5, 7, 7, 8,
           9, 10, 11, 12,
           13, 14, 15, 16};

    gmat = {12, 2, 3, 4,
            5, 7, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16};

    mat = mat.GetNormalized();
    gmat = gmat / glm::determinant(gmat);
    bgmat = GMatToBMat(gmat);

    ASSERT_MAT_EQ(mat, bgmat);
}

TEST(Matrix4, RotationMatrix)
{
    Mat4f mat;
    glm::mat4 gmat;
    Mat4f bgmat;

    mat = {1};

    mat = Mat4f::CreateXRotationMat(5.f);
    gmat = glm::rotate(glm::mat4(1), 5.f, {1.f, 0.f, 0.f});
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreateYRotationMat(5.f);
    gmat = glm::rotate(glm::mat4(1), 5.f, {0.f, 1.f, 0.f});
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreateZRotationMat(5.f);
    gmat = glm::rotate(glm::mat4(1), 5.f, {0.f, 0.f, 1.f});
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);

    mat = Mat4f::CreateXYZRotationMat({5.f});
    gmat = glm::rotate(glm::mat4(1), 5.f, {0.f, 1.f, 0.f}) *
           glm::rotate(glm::mat4(1), 5.f, {1.f, 0.f, 0.f}) *
           glm::rotate(glm::mat4(1), 5.f, {0.f, 0.f, 1.f});
    bgmat = GMatToBMat(gmat);
    ASSERT_MAT_EQ(mat, bgmat);
}