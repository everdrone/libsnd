#pragma once

#include <cmath>
#include <cfloat>

namespace snd {

template <typename fp_t>
bool isDenormal(fp_t x) {
  return (std::fpclassify(x) == FP_SUBNORMAL);
}

template <typename fp_t>
fp_t denormalCancel(fp_t x) {
  if (isDenormal(x))
    return 0;
  return x;
}

}; // !snd
