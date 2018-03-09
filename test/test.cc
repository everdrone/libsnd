#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "snd.h"

double SRR = 44100;

TEST_CASE("denormal cancel") {
  float a = snd::denormalCancel<float>(static_cast<float>(1e-40f));
  REQUIRE(a == 0);
}

TEST_CASE("sine oscillator") {
  SECTION("instantiate") {
    snd::Sine<float> s(SRR);
    REQUIRE(sizeof(s) == sizeof(snd::Sine<float>));
    SECTION("set frequency") {
      s.setFrequency(440);
      REQUIRE(s.frequency == 440);
    }
  }
}
