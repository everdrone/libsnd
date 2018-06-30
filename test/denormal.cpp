#include <gtest/gtest.h>
#include <snd.h>

TEST(Denormal, denormalCancel_will_cancel) {
  float a = 1e-40;
  EXPECT_FLOAT_EQ(
    0,
    snd::denormalCancel<float>(a)
  );
}

TEST(Denormal, denormalCancel_wont_cancel) {
  float a = 1e-12;
  EXPECT_FLOAT_EQ(
    a,
    snd::denormalCancel<float>(a)
  );
}

TEST(Denormal, denormalCancel_bignum) {
  float a = 1e+12;
  EXPECT_FLOAT_EQ(
    a,
    snd::denormalCancel<float>(a)
  );
}

TEST(Denormal, isDenormal_true) {
  float a = 1e-40;
  EXPECT_TRUE(
    snd::isDenormal<float>(a)
  );
}

TEST(Denormal, isDenormal_false) {
  float a = -1e-9;
  EXPECT_FALSE(
    snd::isDenormal<float>(a)
  );
}
