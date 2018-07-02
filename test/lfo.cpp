#include <gtest/gtest.h>
#include <snd.h>

TEST(LFO, LFOBase) {
  snd::lfo::LFOBase<double> ramp(44100);
  ramp.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = ramp.tick();
    EXPECT_LE(value, 0.5);
    EXPECT_GE(value, -0.5);
    switch (i) {
    case 0:
      EXPECT_NEAR(-0.24, value, 1e-4);
      break;
    case 1:
      EXPECT_NEAR(-0.23, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(-0.0604, value, 1e-4);
      break;
    case 25:
      EXPECT_NEAR(0.0094, value, 1e-4);
      break;
    }
  }
}

TEST(LFO, Sine) {
  snd::lfo::Sine<double> lfo(44100);
  lfo.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = lfo.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_NEAR(0.0626, value, 1e-4);
      break;
    case 1:
      EXPECT_NEAR(0.1251, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(0.9288, value, 1e-4);
      break;
    case 24:
      EXPECT_NEAR(1, value, 1e-4);
      break;
    case 25:
      EXPECT_NEAR(0.9983, value, 1e-4);
      break;
    }
  }
}

TEST(LFO, Triangle) {
  snd::lfo::Triangle<double> lfo(44100);
  lfo.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = lfo.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_NEAR(-0.0399, value, 1e-4);
      break;
    case 1:
      EXPECT_NEAR(-0.0798, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(-0.7583, value, 1e-4);
      break;
    case 24:
      EXPECT_NEAR(-0.9977, value, 1e-4);
      break;
    case 25:
      EXPECT_NEAR(-0.9624, value, 1e-4);
      break;
    }
  }
}

TEST(LFO, Parabolic) {
  snd::lfo::Parabolic<double> lfo(44100);
  lfo.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = lfo.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_NEAR(0.0782, value, 1e-4);
      break;
    case 1:
      EXPECT_NEAR(0.1533, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(0.9416, value, 1e-4);
      break;
    case 24:
      EXPECT_NEAR(1, value, 1e-4);
      break;
    case 25:
      EXPECT_NEAR(0.9986, value, 1e-4);
      break;
    }
  }
}

TEST(LFO, Sawtooth) {
  snd::lfo::Sawtooth<double> lfo(44100);
  lfo.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = lfo.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_NEAR(-0.48, value, 1e-4);
      break;
    case 1:
      EXPECT_NEAR(-0.4601, value, 1e-4);
      break;
    case 18:
      EXPECT_NEAR(-0.1209, value, 1e-4);
      break;
    case 24:
      EXPECT_NEAR(-0.0011, value, 1e-4);
      break;
    case 25:
      EXPECT_NEAR(0.0188, value, 1e-4);
      break;
    }
  }
}

TEST(LFO, Square) {
  snd::lfo::Square<double> lfo(44100);
  lfo.setFrequency(440);
  double value = 0;
  for (int i = 0; i < 100; i++) {
    value = lfo.tick();
    EXPECT_LE(value, 1);
    EXPECT_GE(value, -1);
    switch (i) {
    case 0:
      EXPECT_DOUBLE_EQ(1, value);
      break;
    case 24:
      EXPECT_DOUBLE_EQ(1, value);
      break;
    case 25:
      EXPECT_DOUBLE_EQ(-1, value);
      break;
    case 74:
      EXPECT_DOUBLE_EQ(-1, value);
      break;
    case 75:
      EXPECT_DOUBLE_EQ(1, value);
      break;
    }
  }
}
