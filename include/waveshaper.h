#ifndef WAVESHAPER_H_
#define WAVESHAPER_H_

#include <cmath>
#include "approx.h"
#include "conversion.h"

namespace snd {

template <class fp_t>
class WaveShaper {
 public:
  WaveShaper() {
    output = 0;
    for (int i = 0; i < 3; i++) {
      folded[i] = 0;
      bus[i] = 0;
      bus[i + 3] = 0;
    }
  }
  ~WaveShaper() {}

  fp_t tick(fp_t x, fp_t switchPoint) {
    this->folder(x);
    fp_t i = 1 / (x - bus[3]);
    fp_t h = 1 / ((x - bus[4]) * 0.5);
    // calc L
    fp_t l;
    if (std::abs(i) > 1e+11) {
      l = (folded[2] + bus[2]) * 0.5;
    } else {
      l = folded[1] - bus[1] * i;
    }
    // calc output
    if (std::abs(h) > switchPoint) {
      output = (bus[0] + folded[0]) * 0.5;
    } else {
      output = h * (l - bus[5]);
    }
    // write state variables
    bus[5] = l;
    bus[0] = folded[0];
    bus[1] = folded[1];
    bus[2] = folded[2];
    bus[4] = bus[3];
    bus[3] = x;
    return output;
  }

 private:
  fp_t folded[3];
  fp_t bus[6];
  fp_t output;
  static constexpr fp_t piSquared = PI * PI;
  static constexpr fp_t fourThirdsPiCubed = piSquared * PI * 1.333333333333333;

  void folder(fp_t x) {
    bool threshold = x > TWO_PI;
    fp_t sign = x >= 0 ? 1 : -1;
    fp_t sine = snd::sin(x);
    fp_t cosine = snd::cos(x);
    if (threshold) {
      fp_t a = x - sign * TWO_PI;
      folded[0] = a;
      fp_t b = piSquared + piSquared * x;
      fp_t c = x * x * x * 0.1666666666666666;
      b += c;
      c = ((x * x) - 2) * PI;
      c += fourThirdsPiCubed;
      c *= sign;
      folded[1] = b - c;
      folded[2] = 0.5 * a * a;
    } else {
      folded[0] = sine;
      folded[1] = x - sine;
      folded[2] = 1 - cosine;
    }
  }
};

}; // !snd

#endif // !WAVESHAPER_H_
