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
  LFOBase(fp_t sample_rate) {
    this->sample_rate = sample_rate;
    freq = 0;
    this->setPhase(0);
  }
  ~LFOBase() {}

  void setFrequency(fp_t frequency) {
    freq = frequency / sample_rate;
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
  fp_t sample_rate;
  fp_t state;
  fp_t freq;
};

template <class fp_t>
class Sine {
 public:
  Sine(fp_t sample_rate) {
    phase_driver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sample_rate));
  };
  ~Sine() {};

  void setFrequency(fp_t frequency) {
    phase_driver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phase_driver->setPhase(phase);
  }

  fp_t tick() {
    out = phase_driver->tick();
    // triangular driver
    out = std::abs(out + out);
    out = 0.5 - out;
    // sine approx
    return sineApprox7odd(out);
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phase_driver;
};

template <class fp_t>
class Parabolic {
 public:
  Parabolic(fp_t sample_rate) {
    phase_driver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sample_rate));
  };
  ~Parabolic() {};

  void setFrequency(fp_t frequency) {
    phase_driver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phase_driver->setPhase(phase);
  }

  fp_t tick() {
    out = phase_driver->tick();
    out = 0.25 - std::abs(out);
    return (8.0 * out) * (1.0 - (2.0 * std::abs(out)));
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phase_driver;
};

template <class fp_t>
class Triangle {
 public:
  Triangle(fp_t sample_rate) {
    phase_driver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sample_rate));
  };
  ~Triangle() {};

  void setFrequency(fp_t frequency) {
    phase_driver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phase_driver->setPhase(phase);
  }

  fp_t tick() {
    out = phase_driver->tick();
    // triangular driver
    out = std::abs(out) * 4.0;
    return out - 1.0;
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phase_driver;
};

template <class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sample_rate) {
    phase_driver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sample_rate));
  }
  ~Sawtooth() {}

  void setFrequency(fp_t frequency) {
    phase_driver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phase_driver->setPhase(phase);
  }

  fp_t tick() {
    out = phase_driver->tick();
    return out + out;
  }

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phase_driver;
};

template <class fp_t>
class Square {
 public:
  Square(fp_t sample_rate) {
    phase_driver = std::unique_ptr<LFOBase<fp_t>>(new LFOBase<fp_t>(sample_rate));
    pulse_width = 0.5;
  }
  ~Square() {}

  void setFrequency(fp_t frequency) {
    phase_driver->setFrequency(frequency);
  }

  void setPhase(fp_t phase) {
    phase_driver->setPhase(phase);
  }

  void setPulseWidth(fp_t pw) {
    pulse_width = pw;
  }

  fp_t tick() {
    out = phase_driver->tick();
    if (out > pulse_width - 0.5) {
      return -1.0;
    }
    return 1.0;
  }

 private:
  fp_t out;
  fp_t pulse_width;
  std::unique_ptr<LFOBase<fp_t>> phase_driver;
};

}; // !lfo
}; // !snd

#endif // !LFO_H_
