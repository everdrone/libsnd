#include <gtest/gtest.h>
#include "../include/snd.h"

TEST(Denormal, CanCancel) {
  float a = snd::denormalCancel<float>(static_cast<float>(1e-40f));
  EXPECT_FLOAT_EQ(0, a);
}

TEST(Denormal, CanTest) {
  float a = snd::isDenormal<float>(static_cast<float>(1e-40f));
  EXPECT_TRUE(a);
}
