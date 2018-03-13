#ifndef APPROX_H_
#define APPROX_H_

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

}; // !snd

#endif // !APPROX_H_
