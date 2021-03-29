#include "GlmBwatComparison.hpp"

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