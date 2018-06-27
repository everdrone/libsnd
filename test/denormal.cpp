#include <gtest/gtest.h>
#include <snd.h>

TEST(Denormal, canCancel) {
  float a = snd::denormalCancel<float>(static_cast<float>(1e-40f));
  EXPECT_FLOAT_EQ(0, a);
}

TEST(Denormal, canTest) {
  float a = snd::isDenormal<float>(static_cast<float>(1e-40f));
  EXPECT_TRUE(a);
}
