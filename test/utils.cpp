#include <gtest/gtest.h>
#include <snd.h>

TEST(FlipFlop, tick_flips) {
  snd::FlipFlop flip_flop;
  flip_flop.tick();
  EXPECT_TRUE(flip_flop.state);
}

TEST(FlipFlop, FlipFlop_initial_state) {
  snd::FlipFlop flip_flop(true);
  flip_flop.tick();
  EXPECT_FALSE(flip_flop.state);
}
