#pragma once

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
    phaseDriver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sampleRate));
  };
  ~Sine() {};

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
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template <class fp_t>
class Parabolic {
 public:
  Parabolic(fp_t sampleRate) {
    phaseDriver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sampleRate));
  };
  ~Parabolic() {};

  void setFrequency(fp_t frequency) {
    phaseDriver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phaseDriver->setPhase(phase);
  }

  fp_t tick() {
    out = phaseDriver->tick();
    out = 0.25 - std::abs(out);
    return (8.0 * out) * (1.0 - (2.0 * std::abs(out)));
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template <class fp_t>
class Triangle {
 public:
  Triangle(fp_t sampleRate) {
    phaseDriver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sampleRate));
  };
  ~Triangle() {};

  void setFrequency(fp_t frequency) {
    phaseDriver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phaseDriver->setPhase(phase);
  }

  fp_t tick() {
    out = phaseDriver->tick();
    // triangular driver
    out = std::abs(out) * 4.0;
    return out - 1.0;
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template <class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sampleRate) {
    phaseDriver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sampleRate));
  }
  ~Sawtooth() {}

  void setFrequency(fp_t frequency) {
    phaseDriver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phaseDriver->setPhase(phase);
  }

  fp_t tick() {
    out = phaseDriver->tick();
    return out + out;
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template <class fp_t>
class Square {
 public:
  Square(fp_t sampleRate) {
    phaseDriver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sampleRate));
    pulseWidth = 0.5;
  }
  ~Square() {}

  void setFrequency(fp_t frequency) {
    phaseDriver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phaseDriver->setPhase(phase);
  }

  void setPulseWidth(fp_t pw) {
    pulseWidth = pw;
  }

  fp_t tick() {
    out = phaseDriver->tick();
    if (out > pulseWidth - 0.5) {
      return -1.0;
    }
    return 1.0;
  }

 private:
  fp_t out;
  fp_t pulseWidth;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

}; // !lfo
}; // !snd
