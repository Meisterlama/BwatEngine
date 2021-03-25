#include <gtest/gtest.h>
#include "Math/Math.hpp"

using namespace BwatEngine::Math;

TEST(Common, RadiansToDegs)
{
    ASSERT_FLOAT_EQ(ToDegs(PI), 180.f);
    ASSERT_FLOAT_EQ(ToRads(180.f), PI);
}