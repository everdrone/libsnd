#include "denormal.hh"

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

// instantiate the templates
template float denormalCancel<float>(float x);
template double denormalCancel<double>(double x);
template bool isDenormal<float>(float x);
template bool isDenormal<double>(double x);

}; // !snd

