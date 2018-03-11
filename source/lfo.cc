#include "lfo.hh"

namespace snd {
namespace LFO {

template class LFOBase<float>;
template class LFOBase<double>;

template class Sine<float>;
template class Sine<double>;

template class Triangle<float>;
template class Triangle<double>;

}; // !LFO
}; // !snd
