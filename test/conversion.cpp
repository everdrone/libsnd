#include <gtest/gtest.h>
#include <cmath>
#include <snd.h>

#include <iostream>

TEST(Conversion, pitchToFrequency_base) {
  uint8_t pitch = 60;
  EXPECT_NEAR(
    261.6256,
    snd::pitchToFrequency<double>(pitch),
    1e-5
  );
}

TEST(Conversion, pitchToFrequency_zero) {
  uint8_t pitch = 0;
  EXPECT_NEAR(
    8.1758,
    snd::pitchToFrequency<double>(pitch),
    1e-5
  );
}

TEST(Conversion, pitchToFrequency_negative) {
  int pitch = -12;
  EXPECT_NEAR(
    4.0879,
    snd::pitchToFrequency<double>(pitch),
    1e-5
  );
}

TEST(Conversion, pitchToFrequency_floating) {
  double pitch = -7.4545;
  EXPECT_NEAR(
    5.3153,
    snd::pitchToFrequency<double>(pitch),
    1e-5
  );
}

TEST(Conversion, frequencyToPitch_base) {
  int freq = 440;
  EXPECT_NEAR(
    69,
    snd::frequencyToPitch<double>(freq),
    1e-4
  );
}

TEST(Conversion, frequencyToPitch_floating) {
  double freq = 440.01;
  EXPECT_NEAR(
    69.0004,
    snd::frequencyToPitch<double>(freq),
    1e-4
  );
}

TEST(Conversion, ampFactorToDeciBel_zero) {
  double amp = 1;
  EXPECT_DOUBLE_EQ(
    0,
    snd::ampFactorToDeciBel(amp)
  );
}

TEST(Conversion, ampFactorToDeciBel_ratio) {
  double amp = 2;
  EXPECT_NEAR(
    6.0205,
    snd::ampFactorToDeciBel(amp),
    1e-4
  );
}

TEST(Conversion, ampFactorToDeciBel_halfRatio) {
  double amp = 0.5;
  EXPECT_NEAR(
    -6.0205,
    snd::ampFactorToDeciBel(amp),
    1e-4
  );
}

TEST(Conversion, ampFactorToDeciBel_floating) {
  double amp = 0.33;
  EXPECT_NEAR(
    -9.6297,
    snd::ampFactorToDeciBel(amp),
    1e-4
  );
}

TEST(Conversion, decibelToAmpFactor_ratio) {
  double db = 1;
  EXPECT_NEAR(
    1.1220,
    snd::deciBelToAmpFactor(db),
    1e-4
  );
}

TEST(Conversion, decibelToAmpFactor_zero) {
  double db = 0;
  EXPECT_DOUBLE_EQ(
    1,
    snd::deciBelToAmpFactor(db)
  );
}

TEST(Conversion, decibelToAmpFactor_negative) {
  double db = -12;
  EXPECT_NEAR(
    0.2512,
    snd::deciBelToAmpFactor(db),
    1e-4
  );
}
