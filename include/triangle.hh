#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cmath>
#include "utils.hh"

namespace snd {

template <class fp_t>
class Triangle {
 public:
  Triangle(fp_t sampleRate) {
    SR = sampleRate;
    phase = frequency = phaseState = 0;
    frequencyState = increment = 0;
    out = latency = 0;
    sincA = sincB = 0;
    sign = -1;
    for (int i = 0; i < 4; i++) {
      if (i < 2) {
        flipFlop[i].state = false;
      }
      counter[i] = 0;
      incrementState[i] = 0;
      signState[i] = -1;
      AASState[i] = 0;
    }
  }
  ~Triangle() {}

  fp_t tick() {
    // ramp driver
    phaseState = phase;
    phase -= increment;
    sign = -1;
    if (0.5 < std::abs(phase)) {
      if (phase > 0) {
        sign = 1;
      }
      phase -= sign;
    }
    // sign compare
    if (((phase - phaseState) * static_cast<fp_t>(sign)) < -0.5) {
      // trigger BLAMP B
      sincA = (phase + (singn * 0.5)) / increment;
      if (!flipFlop[0].tick()) {
        counter[0] = -2;
      } else {
        counter[1] = -2;
      }
    }
    if (this->_compareSignGT(phase * static_cast<fp_t>(sign),
                             phaseState * static_cast<fp_t>(sign))) {
      // trigger BLAMP B
      sincB = phase / increment;
      if (!flipFlop[1].tick()) {
        counter[2] = -2;
      } else {
        counter[3] = -2;
      }
    }
    // compute + counter
  }

  void setFrequency(fp_t frequency) {
    this->frequency = frequency;
  }

  void setPhase(fp_t phase) {
    fp_t phs = phase;
    phs -= 0.5;
    phs -= std::round(phs);
    this->phase = phs;
  }

 private:
  fp_t SR;
  fp_t out, latency;
  fp_t sincA, sincB;
  int8_t sign;
  fp_t frequency, phase, phaseState;
  fp_t increment, frequencyState;
  int8_t counter[4];
  fp_t AASState[4];
  fp_t incrementState[4];
  int8_t signState[4];
  FlipFlop flipFlop[2];

  void _interpolateFrequency() {
    increment = frequency / SR;
    increment = increment > 0.5 ? 0.5 : (increment < -0.5 ? -0.5 : increment);
    frequencyState = frequency;
  }

  bool _compareSignGT(fp_t a, fp_t b) {
    uint8_t signA = a < 0 ? -1 : 1;
    uint8_t signB = b < 0 ? -1 : 1;
    return signA < signB ? false : true;
  }

  void _computeAAS(uint8_t index, fp_t& sincSrc) {
    if (counter[index] < 2) {
      AASState[index] = sincSrc + static_cast<fp_t>(counter[index]);
      AASState[index] *= -0.5;
    } else {
      AASState[index] = 0;
    }
    fp_t value = std::abs(AASState[index]);
    value = this->_doBLAMP(AASState[index]);
    value *= incrementState[index];

  }

  fp_t polyBLAMP(fp_t& sinc) {

  }
};

}; // !snd

#endif // !TRIANGLE_H_
