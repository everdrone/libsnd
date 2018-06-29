#include <gtest/gtest.h>
#include <snd.h>

TEST(Saturator, tanhSaturator_base) {
  double val = 1;
  EXPECT_NEAR(
    0.7616,
    snd::tanhSaturator<double>(val, 1),
    1e-4
  );
}

TEST(Saturator, tanhSaturator_level) {
  double val = 1;
  double level = 2;
  EXPECT_NEAR(
    0.9242,
    snd::tanhSaturator<double>(val, level),
    1e-4
  );
}

TEST(Saturator, tanhSaturator_negative) {
  double val = 0.1112;
  double level = -12;
  EXPECT_NEAR(
    val,
    snd::tanhSaturator<double>(val, level),
    1e-4
  );
}

TEST(Saturator, tanhSaturator_saturation) {
  double val = 9.3;
  double level = 1.1;
  EXPECT_NEAR(
    level,
    snd::tanhSaturator<double>(val, level),
    1e-4
  );
}
