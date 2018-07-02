#include <gtest/gtest.h>
#include <snd.h>

TEST(Oscillator, Sine) {
  snd::Sine<double> osc(44100, 440);
  osc.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = osc.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_DOUBLE_EQ(0, value);
      break;
    case 1:
      EXPECT_DOUBLE_EQ(0, value);
      break;
    case 2:
      EXPECT_NEAR(-0.0626, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(-0.8751, value, 1e-4);
      break;
    case 26:
      EXPECT_NEAR(-1, value, 1e-4);
      break;
    case 40:
      EXPECT_NEAR(-0.6417, value, 1e-4);
      break;
    case 50:
      EXPECT_NEAR(-0.0698, value, 1e-4);
      break;
    case 51:
      osc.setFrequency(900);
      EXPECT_NEAR(-0.0071, value, 1e-4);
      break;
    case 52:
      EXPECT_NEAR(0.0555, value, 1e-4);
      break;
    }
  }
}
