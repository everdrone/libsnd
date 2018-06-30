#ifndef SAWTOOTH_H_
#define SAWTOOTH_H_

#include <stdint.h>
#include <cmath>
#include "utils.h"

namespace snd {

template <class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sampleRate, fp_t initialFrequency = 0) {
    SR = sampleRate;
    frequencyState = initialFrequency;
    out = latency = 0;
    frequency = increment = 0;
    // wave specific
    flipFlop.state = false;
    flipFlop_old = !flipFlop.state;
    phaseState = snc = phaseSign = 0;
    for (uint8_t i = 0; i < 2; i++) {
      state[i] = 0;
      sign[i] = 1;
      temp[i] = 0;
      inject[i] = 0;
    }
    this->setPhase();
  }
  ~Sawtooth() {}

  fp_t tick() {
    this->_interpolateFrequency();
    phaseState = phase;
    phase -= increment;
    if (0.5 < std::abs(phase)) {
      phaseSign = phase < 0 ? -1 : 1;
      phase -= phaseSign;
      snc = (phase + (-phaseSign * -0.5)) / -increment;
      inject[0] = phaseSign;
      inject[1] = phaseSign;
      if (flipFlop.state && flipFlop.state != flipFlop_old) {
        state[0] = -2;
      } else if ((!flipFlop.state) && flipFlop.state != flipFlop_old) {
        state[1] = -2;
      }
      flipFlop_old = flipFlop.state;
      flipFlop.tick();
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
    out = phaseState;
    latency += blep;
    latency += latency;
    return latency;
  }

  void setFrequency(fp_t frequency) {
    this->frequency = frequency;
    frequencyState = frequency;
  }

  void setPhase(fp_t phase) {
    fp_t phs = phase;
    phs -= 0.5;
    phs -= std::round(phs);
    this->phase = phs;
  }

 private:
  fp_t SR;
  fp_t phase, frequency, frequencyState;
  fp_t increment, latency, out;
  fp_t phaseSign, snc, phaseState;
  FlipFlop flipFlop;
  bool flipFlop_old;
  int8_t state[2];
  fp_t temp[2];
  fp_t sign[2];
  fp_t inject[2];
  fp_t blep;

  void _interpolateFrequency() {
    increment = frequency / SR;
    increment = increment > 0.5 ? 0.5 : (increment < -0.5 ? -0.5 : increment);
  }
};

}; // !snd

#endif // !SAWTOOTH_H_
