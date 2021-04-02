//
// Created by lama on 18/01/2021.
//

#include <gtest/gtest.h>
#include <Math/Math.hpp>

using namespace BMath;

TEST(Noise, uint) {
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(Get1dNoiseUint(i), Get2dNoiseUint(i, 0));
        ASSERT_EQ(Get1dNoiseUint(i), Get3dNoiseUint(i, 0, 0));
        ASSERT_EQ(Get1dNoiseUint(i), Get4dNoiseUint(i, 0, 0, 0));

        ASSERT_EQ(Get2dNoiseUint(i, i), Get3dNoiseUint(i, i, 0));
        ASSERT_EQ(Get2dNoiseUint(i, i), Get4dNoiseUint(i, i, 0, 0));

        ASSERT_EQ(Get3dNoiseUint(i, i, i), Get4dNoiseUint(i, i, i, 0));
    }
}

TEST(Noise, zeroToOne) {
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(Get1dNoiseZeroToOne(i), Get2dNoiseZeroToOne(i, 0));
        ASSERT_EQ(Get1dNoiseZeroToOne(i), Get3dNoiseZeroToOne(i, 0, 0));
        ASSERT_EQ(Get1dNoiseZeroToOne(i), Get4dNoiseZeroToOne(i, 0, 0, 0));

        ASSERT_EQ(Get2dNoiseZeroToOne(i, i), Get3dNoiseZeroToOne(i, i, 0));
        ASSERT_EQ(Get2dNoiseZeroToOne(i, i), Get4dNoiseZeroToOne(i, i, 0, 0));

        ASSERT_EQ(Get3dNoiseZeroToOne(i, i, i), Get4dNoiseZeroToOne(i, i, i, 0));
    }
}

TEST(Noise, negOneToOne) {
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(Get1dNoiseNegOneToOne(i), Get2dNoiseNegOneToOne(i, 0));
        ASSERT_EQ(Get1dNoiseNegOneToOne(i), Get3dNoiseNegOneToOne(i, 0, 0));
        ASSERT_EQ(Get1dNoiseNegOneToOne(i), Get4dNoiseNegOneToOne(i, 0, 0, 0));

        ASSERT_EQ(Get2dNoiseNegOneToOne(i, i), Get3dNoiseNegOneToOne(i, i, 0));
        ASSERT_EQ(Get2dNoiseNegOneToOne(i, i), Get4dNoiseNegOneToOne(i, i, 0, 0));

        ASSERT_EQ(Get3dNoiseNegOneToOne(i, i, i), Get4dNoiseNegOneToOne(i, i, i, 0));
    }
}