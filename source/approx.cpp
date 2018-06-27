#include "approx.h"

namespace snd {

template float tanRatApprox0Pi2<float>(float x);
template double tanRatApprox0Pi2<double>(double x);

template float sineApprox7odd<float>(float x);
template double sineApprox7odd<double>(double x);

template float sin(float x);
template double sin(double x);

template float cos(float x);
template double cos(double x);

template float tanh(float x);
template double tanh(double x);

}; // !snd
