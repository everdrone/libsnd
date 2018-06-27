#include <gtest/gtest.h>
#include <snd.h>

TEST(FlipFlop, canFlip) {
  snd::FlipFlop flip_flop;
  flip_flop.tick();
  EXPECT_TRUE(flip_flop.state);
}

TEST(FlipFlop, canGetInitialState) {
  snd::FlipFlop flip_flop(true);
  flip_flop.tick();
  EXPECT_FALSE(flip_flop.state);
}
