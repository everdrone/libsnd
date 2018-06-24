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
  }
}

TEST_CASE("lfo") {
  SECTION("instantiate") {
    snd::LFO::Sine<double> ls(SRR);
    snd::LFO::Sine<double> *lsp;
    lsp = new snd::LFO::Sine<double>(SRR);
    REQUIRE(sizeof(ls) == sizeof(snd::LFO::Sine<double>));
  }
}
