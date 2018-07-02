#include <gtest/gtest.h>
#include <snd.h>

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

TEST(Conversion, logTimeToSeconds_millisecond) {
  double num = 0;
  EXPECT_NEAR(
    0.001,
    snd::logTimeToSeconds(num),
    1e-7
  );
}

TEST(Conversion, logTimeToSeconds_one) {
  double num = 60;
  EXPECT_NEAR(
    1,
    snd::logTimeToSeconds(num),
    1e-7
  );
}

TEST(Conversion, logTimeToSeconds_ten) {
  double num = 80;
  EXPECT_NEAR(
    10,
    snd::logTimeToSeconds(num),
    1e-7
  );
}

TEST(Conversion, scale_base) {
  double x = 1;
  double a = 1;
  double b = 127;
  double c = 0;
  double d = 1;
  EXPECT_DOUBLE_EQ(
    0,
    snd::scale(x, a, b, c, d)
  );
}

TEST(Conversion, scale_half) {
  double x = 0.5;
  double a = 0;
  double b = 1;
  double c = 0;
  double d = 1;
  EXPECT_DOUBLE_EQ(
    0.5,
    snd::scale(x, a, b, c, d)
  );
}

TEST(Conversion, scale_negative) {
  double x = 50;
  double a = -100;
  double b = 100;
  double c = 0;
  double d = 100;
  EXPECT_DOUBLE_EQ(
    75,
    snd::scale(x, a, b, c, d)
  );
}

TEST(Conversion, BLTPrewarp_base) {
  double freq = 1;
  double sample_rate = 44100;
  EXPECT_NEAR(
    0.0001,
    snd::BLTPrewarp(freq, sample_rate),
    1e-4
  );
}

TEST(Conversion, BLTPrewarp_floating) {
  double freq = 440.998;
  double sample_rate = 44100;
  EXPECT_NEAR(
    0.0314,
    snd::BLTPrewarp(freq, sample_rate),
    1e-4
  );
}

TEST(Conversion, BLTPrewarp_high) {
  double freq = 2000.1;
  double sample_rate = 44100;
  EXPECT_NEAR(
    0.1435,
    snd::BLTPrewarp(freq, sample_rate),
    1e-4
  );
}

TEST(Conversion, BLTPrewarp_almost_nyquist) {
  double freq = 22000;
  double sample_rate = 44100;
  EXPECT_NEAR(
    15.9992,
    snd::BLTPrewarp(freq, sample_rate),
    1e-4
  );
}

TEST(Conversion, BLTPrewarp_aliasing) {
  double freq = 44100;
  double sample_rate = 44100;
  EXPECT_NEAR(
    15.9992,
    snd::BLTPrewarp(freq, sample_rate),
    1e-4
  );
}
