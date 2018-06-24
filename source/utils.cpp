#include "utils.h"

namespace snd {

FlipFlop::FlipFlop(bool initialState) {
  state = initialState;
}
FlipFlop::FlipFlop() {
  state = false;
}
FlipFlop::~FlipFlop() {}
bool FlipFlop::tick() {
  state ^= true;
  return state;
}

} // !snd
