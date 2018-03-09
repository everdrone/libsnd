#include "denormal.hh"

namespace snd {

template float denormalCancel<float>(float x);
template double denormalCancel<double>(double x);
template bool isDenormal<float>(float x);
template bool isDenormal<double>(double x);

}; // !snd

