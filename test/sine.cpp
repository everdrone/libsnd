#include <gtest/gtest.h>
#include <snd.h>

TEST(Sine, canSetFrequency) {
  snd::Sine<float> osc(44100);
  osc.setFrequency(440.f);
  EXPECT_NEAR(0, osc.tick(), 1e-06f);
}

// TEST(Sine, canSetPhase) {
//   snd::Sine<float> osc(44100);
//   osc.setFrequency(0.f);
//   osc.setPhase(0.f);
//   EXPECT_NEAR(0.f, osc.tick(), 1e-06f);
//   osc.setPhase(0.5f);
//   EXPECT_NEAR(0.5f, osc.tick(), 1e-06f);
// }
