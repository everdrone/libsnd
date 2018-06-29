#include <gtest/gtest.h>
#include <snd.h>

TEST(Approx, sineApprox7odd) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::sineApprox7odd<double>(val));
  val = 1;
  EXPECT_NEAR(-0.0296, snd::sineApprox7odd<double>(val), 1e-4);
  val = 0.5;
  EXPECT_DOUBLE_EQ(1, snd::sineApprox7odd<double>(val));
  val = -0.5;
  EXPECT_DOUBLE_EQ(-1, snd::sineApprox7odd<double>(val));
  val = -1;
  EXPECT_NEAR(0.0296, snd::sineApprox7odd<double>(val), 1e-4);
  val = 2;
  EXPECT_NEAR(-23.0724, snd::sineApprox7odd<double>(val), 1e-4);
}

TEST(Approx, tanRatApprox0Pi2) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::tanRatApprox0Pi2<double>(val));
  val = -1;
  EXPECT_NEAR(-1.6485, snd::tanRatApprox0Pi2<double>(val), 1e-4);
  val = 1;
  EXPECT_NEAR(1.5572, snd::tanRatApprox0Pi2<double>(val), 1e-4);
  val = 0.01;
  EXPECT_NEAR(0.01, snd::tanRatApprox0Pi2<double>(val), 1e-4);
  val = 1e-3;
  EXPECT_NEAR(1e-3, snd::tanRatApprox0Pi2<double>(val), 1e-6);
}

TEST(Approx, sin) {
  double val = 0;
  EXPECT_NEAR(0, snd::sin<double>(val), 1e-6);
  val = 1;
  EXPECT_NEAR(0.8415, snd::sin<double>(val), 1e-4);
  val = -1;
  EXPECT_NEAR(-0.8415, snd::sin<double>(val), 1e-4);
  val = 12.44;
  EXPECT_NEAR(-0.126, snd::sin<double>(val), 1e-4);
  val = 0.001;
  EXPECT_NEAR(0.001, snd::sin<double>(val), 1e-4);
}

TEST(Approx, cos) {
  double val = 0;
  EXPECT_DOUBLE_EQ(0, snd::tanh<double>(val));
  val = 1;
  EXPECT_NEAR(0.7616, snd::tanh<double>(val), 1e-4);
  val = -1;
  EXPECT_NEAR(-0.7616, snd::tanh<double>(val), 1e-4);
  val = 9.333;
  EXPECT_NEAR(1, snd::tanh<double>(val), 1e-6);
  val = 0.0988;
  EXPECT_NEAR(0.0985, snd::tanh<double>(val), 1e-4);
}
