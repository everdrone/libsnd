#ifndef LFO_H_
#define LFO_H_

#include <cmath>
#include "approx.hh"

namespace snd {
namespace LFO {

template <class fp_t>
class LFOBase {
 public:
  LFOBase(fp_t sampleRate) {
    this->SR = sampleRate;
    freq = 0;
  }
  ~LFOBase() {}

  void setFrequency(fp_t frequency) {
    freq = frequency / SR;
  }

  void setPhase(fp_t phase) {
    fp_t ph = phase;
    ph -= 0.25;
    ph -= std::round(ph);
    this->state = ph;
  }

  fp_t tick() {
    state += freq;
    state -= std::round(state);
    return state;
  }

 private:
  fp_t SR;
  fp_t state;
  fp_t freq;
};

template <class fp_t>
class Sine {
 public:
  Sine(fp_t sampleRate) {
    phaseDriver = new LFOBase<fp_t>(sampleRate);
  }
  ~Sine() {}

  void setFrequency(fp_t frequency) {
    phaseDriver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phaseDriver->setPhase(phase);
  }

  fp_t tick() {
    out = phaseDriver->tick();
    // triangular driver
    out = std::abs(out + out);
    out = 0.5 - out;
    // sine approx
    return sineApprox7odd(out);
  }

 private:
  fp_t out;
  LFOBase<fp_t>* phaseDriver;
};

}; // !LFO
}; // !snd

#endif // !LFO_H_
