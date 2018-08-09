#ifndef LFO_H_
#define LFO_H_

#include <cmath>
#include <memory>

#include "approx.h"

namespace snd {
namespace lfo {

template <class fp_t>
class LFOBase {
 public:
  LFOBase(fp_t sampleRate) {
    this->SR = sampleRate;
    freq = 0;
    this->setPhase(0);
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

  fp_t process() {
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
class Sine : public LFOBase<fp_t> {
 public:
  Sine(fp_t sampleRate) : LFOBase<fp_t>(sampleRate) {
    out = 0.0;
  };
  ~Sine() {};

  void setFrequency(fp_t frequency) {
    LFOBase<fp_t>::setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    LFOBase<fp_t>::setPhase(phase);
  }

  fp_t tick() {
    out = this->process();
    // triangular driver
    out = std::abs(out + out);
    out = 0.5 - out;
    // sine approx
    return sineApprox7odd(out);
  }

 private:
  fp_t out;
};

template <class fp_t>
class Parabolic : public LFOBase<fp_t> {
 public:
  Parabolic(fp_t sampleRate) : LFOBase<fp_t>(sampleRate) {
    out = 0.0;
  };
  ~Parabolic() {};

  void setFrequency(fp_t frequency) {
    LFOBase<fp_t>::setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    LFOBase<fp_t>::setPhase(phase);
  }

  fp_t tick() {
    out = this->process();
    out = 0.25 - std::abs(out);
    return (8.0 * out) * (1.0 - (2.0 * std::abs(out)));
  }

 private:
  fp_t out;
};

template <class fp_t>
class Triangle : public LFOBase<fp_t> {
 public:
  Triangle(fp_t sampleRate) : LFOBase<fp_t>(sampleRate) {
    out = 0.0;
  };
  ~Triangle() {};

  void setFrequency(fp_t frequency) {
    LFOBase<fp_t>::setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    LFOBase<fp_t>::setPhase(phase);
  }

  fp_t tick() {
    out = this->process();
    // triangular driver
    out = std::abs(out) * 4.0;
    return out - 1.0;
  }

 private:
  fp_t out;
};

template <class fp_t>
class Sawtooth : public LFOBase<fp_t> {
 public:
  Sawtooth(fp_t sampleRate) : LFOBase<fp_t>(sampleRate) {
    out = 0.0;
  }
  ~Sawtooth() {}

  void setFrequency(fp_t frequency) {
    LFOBase<fp_t>::setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    LFOBase<fp_t>::setPhase(phase);
  }

  fp_t tick() {
    out = this->process();
    return out + out;
  }

 private:
  fp_t out;
};

template <class fp_t>
class Square : public LFOBase<fp_t> {
 public:
  Square(fp_t sampleRate) : LFOBase<fp_t>(sampleRate) {
    out = 0.0;
    pulseWidth = 0.5;
  }
  ~Square() {}

  void setFrequency(fp_t frequency) {
    LFOBase<fp_t>::setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    LFOBase<fp_t>::setPhase(phase);
  }

  void setPulseWidth(fp_t pw) {
    pulseWidth = pw;
  }

  fp_t tick() {
    out = this->process();
    if (out > pulseWidth - 0.5) {
      return -1.0;
    }
    return 1.0;
  }

 private:
  fp_t out;
  fp_t pulseWidth;
};

}; // !lfo
}; // !snd

#endif // !LFO_H_
