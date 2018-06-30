#ifndef APPROX_H_
#define APPROX_H_

#include <cmath>

#define DB_FACTOR 1.1220184543019634355910389464779057367223085073606
#define DB_MULT 8.175800000000001
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530717958647692
#define EULER_NUMBER 2.71828182846

namespace snd {

template <typename fp_t>
fp_t sineApprox7odd(fp_t x) {
  fp_t x2 = x * x;
  return x * (3.141592653589793 + (x2 * (-5.166512943349853 + (x2 *
                                         (2.535656174488765 + (-0.540347434104161 * x2))))));
}

template <typename fp_t>
fp_t tanRatApprox0Pi2(fp_t x) {
  return (x * (1.00005 + (x * (0.0388452 + (x * -0.0896638))))) / (1.0 + (x *
         (0.0404318 + (-0.430871 * x))));
}

template <typename fp_t>
fp_t sin(fp_t x) {
  fp_t a = (x / TWO_PI) - 0.25;
  a = a - std::round(a);
  return sineApprox7odd(0.5 - (std::abs(a + a)));
}

template <typename fp_t>
fp_t cos(fp_t x) {
  fp_t a = x / TWO_PI;
  a = a - std::round(a);
  return sineApprox7odd(0.5 - (std::abs(a + a)));
}

template <typename fp_t>
fp_t tanh(fp_t x) {
  fp_t a = std::abs(x);
  if (a > 0.05) {
    if (a > 20) {
      return x >= 0 ? 1 : -1;
    } else {
      fp_t b = std::exp(x + x);
      return (b - 1) / (b + 1);
    }
  } else {
    return x - (x * x * x / 3);
  }
}

}; // !snd

#endif // !APPROX_H_
