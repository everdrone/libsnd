#ifndef SINE_H_
#define SINE_H_

#include <cmath>
#include "approx.h"

namespace snd {

template <class fp_t>
class Sine {
 public:
  Sine(fp_t sample_rate, fp_t initial_frequency = 0) {
    this->sample_rate = sample_rate;
    frequency_state = initial_frequency;
    frequency = initial_frequency;
    increment = sine_step = out = latency = 0;
    // TODO(everdrone): set initial phase to 0
    this->setPhase(0.5);
  };
  ~Sine() {};

  fp_t tick() {
    this->_interpolateFrequency();
    latency = out;
    this->_triangularDriver();
    out = sineApprox7odd<fp_t>(sine_step);
    phase -= increment;
    fp_t sign = -1;
    if (0.5 < std::abs(phase)) {
      if (phase > 0) {
        sign = 1;
      }
      phase -= sign;
    }
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
  fp_t frequency;
  fp_t phase, frequency_state, frequency_input,
       increment, latency, sine_step,
       out;

  void _interpolateFrequency() {
    this->frequency = (frequency_input + frequency_state) * 0.5;
    frequency_state = frequency_input;
    increment = frequency / sample_rate;
    increment = increment > 0.5 ? 0.5 : (increment < -0.5 ? -0.5 : increment);
  }

  void _triangularDriver() {
    sine_step = phase - 0.25;
    sine_step -= std::round(sine_step);
    sine_step += sine_step;
    sine_step = std::abs(sine_step);
    sine_step = 0.5 - sine_step;
  }
};

}; // !snd

#endif // !SINE_H
