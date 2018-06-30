#include <gtest/gtest.h>
#include <snd.h>

TEST(Approx, sineApprox7odd_zero) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::sineApprox7odd<double>(val));
}

TEST(Approx, sineApprox7odd_one) {
  double val = 1;
  EXPECT_NEAR(-0.0296, snd::sineApprox7odd<double>(val), 1e-4);
}

TEST(Approx, sineApprox7odd_half) {
  double val = 0.5;
  EXPECT_DOUBLE_EQ(1, snd::sineApprox7odd<double>(val));
}

TEST(Approx, sineApprox7odd_negative_half) {
  double val = -0.5;
  EXPECT_DOUBLE_EQ(-1, snd::sineApprox7odd<double>(val));
}

TEST(Approx, sineApprox7odd_negative) {
  double val = -1;
  EXPECT_NEAR(0.0296, snd::sineApprox7odd<double>(val), 1e-4);
}

TEST(Approx, sineApprox7odd_exceed) {
  double val = 2;
  EXPECT_NEAR(-23.0724, snd::sineApprox7odd<double>(val), 1e-4);
}

TEST(Approx, tanRatApprox0Pi2_zero) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::tanRatApprox0Pi2<double>(val));
}

TEST(Approx, tanRatApprox0Pi2_one) {
  double val = 1;
  EXPECT_NEAR(1.5572, snd::tanRatApprox0Pi2<double>(val), 1e-4);
}

TEST(Approx, tanRatApprox0Pi2_negative) {
  double val = -1;
  EXPECT_NEAR(-1.6485, snd::tanRatApprox0Pi2<double>(val), 1e-4);
}

TEST(Approx, tanRatApprox0Pi2_floating) {
  double val = 0.01;
  EXPECT_NEAR(0.01, snd::tanRatApprox0Pi2<double>(val), 1e-4);
}

TEST(Approx, tanRatApprox0Pi2_small) {
  double val = 1e-3;
  EXPECT_NEAR(1e-3, snd::tanRatApprox0Pi2<double>(val), 1e-6);
}

TEST(Approx, sin_zero) {
  double val = 0;
  EXPECT_NEAR(0, snd::sin<double>(val), 1e-6);
}

TEST(Approx, sin_one) {
  double val = 1;
  EXPECT_NEAR(0.8415, snd::sin<double>(val), 1e-4);
}

TEST(Approx, sin_negative) {
  double val = -1;
  EXPECT_NEAR(-0.8415, snd::sin<double>(val), 1e-4);
}

TEST(Approx, sin_floating) {
  double val = 12.44;
  EXPECT_NEAR(-0.126, snd::sin<double>(val), 1e-4);
}

TEST(Approx, sin_small) {
  double val = 0.001;
  EXPECT_NEAR(0.001, snd::sin<double>(val), 1e-4);
}

TEST(Approx, cos_zero) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::tanh<double>(val));
}

TEST(Approx, cos_one) {
  double val = 1;
  EXPECT_NEAR(0.7616, snd::tanh<double>(val), 1e-4);
}

TEST(Approx, cos_negative) {
  double val = -1;
  EXPECT_NEAR(-0.7616, snd::tanh<double>(val), 1e-4);
}

TEST(Approx, cos_floating) {
  double val = 9.333;
  EXPECT_NEAR(1, snd::tanh<double>(val), 1e-6);
}

TEST(Approx, cos_small) {
  double val = 0.0988;
  EXPECT_NEAR(0.0985, snd::tanh<double>(val), 1e-4);
}
