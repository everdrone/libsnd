#include <gtest/gtest.h>
#include "../include/snd.h"

TEST(FlipFlop, CanFlip) {
  snd::FlipFlop flip_flop;
  flip_flop.tick();
  EXPECT_TRUE(flip_flop.state);
}

TEST(FlipFlop, CanGetInitialState) {
  snd::FlipFlop flip_flop(true);
  flip_flop.tick();
  EXPECT_FALSE(flip_flop.state);
}
