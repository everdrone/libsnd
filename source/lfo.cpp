#include "lfo.h"

namespace snd {
namespace LFO {

template class LFOBase<float>;
template class LFOBase<double>;

template class Sine<float>;
template class Sine<double>;

template class Parabolic<float>;
template class Parabolic<double>;

template class Triangle<float>;
template class Triangle<double>;

template class Sawtooth<float>;
template class Sawtooth<double>;

template class Square<float>;
template class Square<double>;

}; // !LFO
}; // !snd
