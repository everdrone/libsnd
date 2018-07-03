#ifndef SAWTOOTH_H_
#define SAWTOOTH_H_

#include <stdint.h>
#include <cmath>
#include "utils.h"

namespace snd {

template <class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sample_rate, fp_t initial_frequency = 0) {
    sample_rate = sample_rate;
    frequency_state = initial_frequency;
    frequency = initial_frequency;
    out = latency = 0;
    increment = 0;
    // wave specific
    flip_flop.state = false;
    flip_flop_state = !flip_flop.state;
    phase_state = snc = phase_sign = 0;
    for (uint8_t i = 0; i < 2; i++) {
      state[i] = 0;
      sign[i] = 1;
      temp[i] = 0;
      inject[i] = 0;
    }
    this->setPhase(0);
  }
  ~Sawtooth() {}

  fp_t tick() {
    this->_interpolateFrequency();
    phase_state = phase;
    phase -= increment;
    if (0.5 < std::abs(phase)) {
      phase_sign = phase < 0 ? -1 : 1;
      phase -= phase_sign;
      snc = (phase + (-phase_sign * -0.5)) / -increment;
      inject[0] = phase_sign;
      inject[1] = phase_sign;
      if (flip_flop.state && flip_flop.state != flip_flop_state) {
        state[0] = -2;
      } else if ((!flip_flop.state) && flip_flop.state != flip_flop_state) {
        state[1] = -2;
      }
      flip_flop_state = flip_flop.state;
      flip_flop.tick();
    }
    for (uint8_t i = 0; i < 2; i++) {
      if (state[i] < 2) {
        temp[i] = static_cast<fp_t>(state[i]) + snc;
        temp[i] *= -0.5;
        sign[i] = state[i] < 0 ? -1 : 1;
        temp[i] = computeBLEP(std::abs(temp[i]));
        temp[i] *= sign[i] * inject[i];
        state[i]++;
      } else {
        temp[i] = 0;
      }
    }
    blep = temp[0] + temp[1];
    latency = out;
    out = phase_state;
    latency += blep;
    latency += latency;
    return latency;
  }

  void setFrequency(fp_t freq) {
    frequency_input = freq;
  }

  void setPhase(fp_t phase) {
    fp_t phs = phase;
    phs -= 0.5;
    phs -= std::round(phs);
    this->phase = phs;
  }

 private:
  fp_t sample_rate;
  fp_t phase, frequency, frequency_state, frequency_input;
  fp_t increment, latency, out;
  fp_t phase_sign, snc, phase_state;
  FlipFlop flip_flop;
  bool flip_flop_state;
  int8_t state[2];
  fp_t temp[2];
  fp_t sign[2];
  fp_t inject[2];
  fp_t blep;

  void _interpolateFrequency() {
    this->frequency = (frequency_input + frequency_state) * 0.5;
    frequency_state = frequency_input;
    increment = frequency / sample_rate;
    increment = increment > 0.5 ? 0.5 : (increment < -0.5 ? -0.5 : increment);
  }
};

}; // !snd

#endif // !SAWTOOTH_H_
