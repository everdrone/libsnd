#ifndef BILINEAR_H_
#define BILINEAR_H_

/**
 * TODO:
 * - test
 *  * - write explicit instances into *.cc file
 * - add to header file
 */

#include <cmath>
#include <stdint.h>
#include "conversion.h"

namespace snd {
namespace bilin {

template <class fp_t>
class BilinearFilterBase {
 public:
  BilinearFilterBase(fp_t sampleRate) {
    SR = sampleRate;
    out = amplitude = 0;
    for (uint8_t i = 0; i < 3; i++) {
      if (i < 2) {
        state[i] = 0;
      }
      coeff[i] = 0;
    }
  }
  ~BilinearFilterBase() {}

  virtual void setFrequency(fp_t frequency) {}
  void setGain(fp_t gain) {
    amplitude = std::powf(1.059253692626953, gain);
    amplitude *= amplitude;
  }

  fp_t tick(fp_t input) {
    this->computeBilinear(input);
  }

 protected:
  fp_t SR;
  fp_t coeff[3];
  fp_t state[2];
  fp_t amplitude;
  fp_t out;

 private:
  inline fp_t computeBilinear(fp_t in) {
    out = state[1] * coeff[0];
    out += in * coeff[1];
    out += state[0] * coeff[2];
    state[0] = in;
    state[1] = out;
    return out;
  }
};

template <class fp_t>
class OnePoleHighPass : public BilinearFilterBase<fp_t> {
 public:
  OnePoleHighPass(fp_t sampleRate) : BilinearFilterBase<fp_t>(sampleRate) {}
  ~OnePoleHighPass() {}

  void setFrequency(float frequency) {
    fp_t freq = BLTPrewarp<fp_t>(frequency, this->SR);
    // coeffs
    this->coeff[0] = 1.0f - freq;
    this->coeff[1] = 1.0f + freq;
    this->coeff[0] /= this->coeff[1];
    this->coeff[1] /= 1.0f;
    this->coeff[2] = -this->coeff[1];
  }
};

template <class fp_t>
class OnePoleLowPass : public BilinearFilterBase<fp_t> {
 public:
  OnePoleLowPass(fp_t sampleRate) : BilinearFilterBase<fp_t>(sampleRate) {}
  ~OnePoleLowPass() {}

  void setFrequency(fp_t frequency) {
    fp_t freq = BLTPrewarp<fp_t>(frequency, this->SR);
    // coeffs
    this->coeff[0] = 1.0f - freq;
    this->coeff[1] = 1.0f + freq;
    this->coeff[0] /= this->coeff[1];
    this->coeff[1] /= freq;
    this->coeff[2] = this->coeff[1];
  }
};

template <class fp_t>
class OnePoleHighShelf : public BilinearFilterBase<fp_t> {
 public:
  OnePoleHighShelf(fp_t sampleRate) : BilinearFilterBase<fp_t>(sampleRate) {}
  ~OnePoleHighShelf() {}

  void setFreq(fp_t frequency) {
    // prewarp
    fp_t freq = BLTPrewarp<fp_t>(frequency * this->amplitude, this->SR);
    // coeffs
    this->coeff[0] = 1.0f - freq;
    this->coeff[1] = 1.0f + freq;
    this->coeff[0] /= this->coeff[1];
    this->coeff[2] = this->amplitude - 1.0f;
    this->coeff[1] = this->coeff[2] / this->coeff[1];
    this->coeff[2] = this->coeff[0] + this->coeff[1];
    this->coeff[2] *= -1.0f;
    this->coeff[1] += 1.0f;
  }
};

template <class fp_t>
class OnePoleLowShelf : public BilinearFilterBase<fp_t> {
 public:
  OnePoleLowShelf(fp_t sampleRate) : BilinearFilterBase<fp_t>(sampleRate) {}
  ~OnePoleLowShelf() {}

  void setFreq(fp_t frequency) {
    // prewarp
    fp_t freq = BLTPrewarp<fp_t>(frequency / this->amplitude, this->SR);
    // coeffs
    this->coeff[0] = 1.0f - freq;
    this->coeff[1] = 1.0f + freq;
    this->coeff[0] /= this->coeff[1];
    this->coeff[2] = this->amplitude - 1.0f;
    this->coeff[1] = this->coeff[2] * this->coeff[1];
    this->coeff[2] = this->coeff[0] + this->coeff[1];
    this->coeff[2] -= this->coeff[0];
    this->coeff[1] += 1.0f;
  }
};


}; // !bilin
}; // !snd

#endif // !BILINEAR_H_
