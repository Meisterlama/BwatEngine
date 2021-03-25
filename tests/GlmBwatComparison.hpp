#include "Math/Math.hpp"
#include "gtest/gtest.h"
#include "glm/matrix.hpp"
#include "glm/glm.hpp"

using namespace BwatEngine::Math;

bool operator==(Mat4f Bmat, glm::mat4 Gmat);

glm::mat4 BMatToGMat(Mat4f bmat);
Mat4f GMatToBMat(glm::mat4 gmat);

#define ASSERT_MAT_EQ(mat1, mat2) \
    for (int i = 0; i < 16; i++){ \
    ASSERT_FLOAT_EQ(mat1[i], mat2[i]);}

#define ASSERT_EQ_QUAT(bquat, gquat) \
    ASSERT_FLOAT_EQ(bquat.W, gquat.w); \
    ASSERT_FLOAT_EQ(bquat.X, gquat.x); \
    ASSERT_FLOAT_EQ(bquat.Y, gquat.y); \
    ASSERT_FLOAT_EQ(bquat.Z, gquat.z);

#define ASSERT_EQ_VEC(bvec, gvec) \
    ASSERT_FLOAT_EQ(bvec.X, gvec.x); \
    ASSERT_FLOAT_EQ(bvec.Y, gvec.y); \
    ASSERT_FLOAT_EQ(bvec.Z, gvec.z);

//