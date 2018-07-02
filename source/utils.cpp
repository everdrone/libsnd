#include "utils.h"

namespace snd {

FlipFlop::FlipFlop(bool initial_state) {
  state = initial_state;
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
