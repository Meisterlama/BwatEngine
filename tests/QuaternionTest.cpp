#include <gtest/gtest.h>
#include "Math/Math.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GlmBwatComparison.hpp"

using namespace BwatEngine::Math;

TEST(Quaternion, Constructor)
{
    Quatd quat{1,2,3,4};
    glm::quat gquat{1,2,3,4};
    ASSERT_EQ_QUAT(quat, gquat);

    quat = {{1, 2,3,0}};
    gquat = {0, 1, 2, 3};
    ASSERT_EQ_QUAT(quat, gquat);
}


TEST(Quaternion, Norm)
{
    Quatf quat {1, 0, 0, 0};
    ASSERT_FLOAT_EQ(quat.Norm(), 1.0f);

    quat = {3, 4, 0, 0};
    ASSERT_FLOAT_EQ(quat.Norm(), 5.0f);
    quat.Normalize();
    ASSERT_FLOAT_EQ(quat.Norm(), 1.f);

    quat = {0, 3, 4, 0};
    ASSERT_FLOAT_EQ(quat.Norm(), 5.0f);
    quat.Normalize();
    ASSERT_FLOAT_EQ(quat.Norm(), 1.f);

    Vec4f vec{12, 24, 3, 17};
    quat = {12, 24, 3, 17};

    ASSERT_FLOAT_EQ(quat.Norm(), vec.Length());
    ASSERT_FLOAT_EQ(quat.Amplitude(), vec.Amplitude());
    ASSERT_FLOAT_EQ(quat.Amplitude(), quat.Norm() * quat.Norm());

    quat.Normalize();
    vec.Normalize();

    ASSERT_FLOAT_EQ(quat.Norm(), vec.Length());
    ASSERT_FLOAT_EQ(quat.Norm(), 1);
}

TEST(Quaternion, DotProduct)
{
    Quatf quat1 {1,2,3,4};
    Quatf quat2 {4,5,6,7};
    Vec4f vec1  {2,3,4,1};
    Vec4f vec2  {5,6,7,4};

    ASSERT_FLOAT_EQ(quat1.DotProduct(quat1), quat1.Amplitude());
    ASSERT_FLOAT_EQ(quat1.DotProduct(quat2), vec1.DotProduct(vec2));
}

TEST(Quaternion, Conjugate)
{
    Quatf quat { 1, 2, 3, 4};
    Quatf quatC {1, -2, -3, -4};

    ASSERT_EQ((quat.GetConjugate()), quatC);
}

TEST(Quaternion, ScalarArithmetic)
{
    Quatf quat{1, 2, 3, 4};
    Quatf quat2{0};
    Quatf quatR;
    Quatf quatT;

    ASSERT_EQ((quat+quat2), quat);

    quatR = quat + quat;
    quatT = {2, 4, 6, 8};
    ASSERT_EQ(quatR, quatT);

    quatR -= quat;
    quatT = {1, 2, 3, 4};
    ASSERT_EQ(quatR, quatT);

    quatR *= 2;
    quatT = {2, 4, 6, 8};
    ASSERT_EQ(quatR, quatT);

    quatR /= 2;
    quatT = {1, 2, 3, 4};
    ASSERT_EQ(quatR, quatT);
}

TEST(Quaternion, Mult)
{
    Quatf quatR {1, 2, 3, 4};
    Quatf quatR2 {5, 6, 7, 8};
    glm::quat gquatT {1, 2, 3, 4};
    glm::quat gquatT2 {5, 6, 7, 8};

    quatR *= quatR;
    gquatT *= gquatT;
    ASSERT_EQ_QUAT(quatR, gquatT);

    quatR *= quatR;
    gquatT *= gquatT;
    ASSERT_EQ_QUAT(quatR, gquatT);

    quatR *= quatR;
    gquatT *= gquatT;
    ASSERT_EQ_QUAT(quatR, gquatT);

    quatR *= quatR2;
    gquatT *= gquatT2;
    ASSERT_EQ_QUAT(quatR, gquatT);
}


TEST(Quaternion, Rotation)
{
    Vec3f angles = {1, 2, 3};
    Quatf quatR{angles};
    glm::quat gquatT {glm::vec3{angles.X, angles.Y, angles.Z}};

    ASSERT_EQ_QUAT(quatR, gquatT);

    Vec3f vecR = quatR.Rotate({4, 5, 6});
    glm::vec3 gvec3T = glm::rotate(gquatT, glm::vec3{4,5,6});

    ASSERT_EQ_VEC(vecR, gvec3T);

    vecR = quatR.Rotate({2, 6, 4});
    gvec3T = glm::rotate(gquatT, glm::vec3{2, 6, 4});

    ASSERT_EQ_VEC(vecR, gvec3T);
}


TEST(Quaternion, EulerAngles)
{
    Quatf quatT{1.5, 2, 2.5};
    Vec3f vecT{1.5, 2, 2.5};
    Vec3f eulerAngles = quatT.GetEulerAngles();
    glm::quat quatG{glm::vec3{1.5, 2, 2.5}};
    glm::vec3 angleG = glm::eulerAngles(quatG);
    ASSERT_EQ_VEC(eulerAngles, angleG);
}

TEST(Quaternion, RotationMat)
{
    Vec3f angles = {1, 2, 3};
    Quatf quatR{angles};
    glm::quat gquatT {glm::vec3{angles.X, angles.Y, angles.Z}};

    Mat4f matR = Mat4f::CreateRotationMat(quatR);
    glm::mat4 matG = glm::toMat4(gquatT);

    Mat4f bgmat = GMatToBMat(matG);
    ASSERT_MAT_EQ(matR, bgmat);
}
