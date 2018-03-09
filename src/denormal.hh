#ifndef DENORMAL_H_
#define DENORMAL_H_

#include <cmath>
#include <cfloat>

namespace snd {

template <typename fp_t>
bool isDenormal(fp_t);

template <typename fp_t>
fp_t denormalCancel(fp_t);

}; // !snd

#endif // !DENORMAL_H_
