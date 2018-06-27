#include "bilinear.h"

namespace snd {
namespace bilin {

template class BilinearFilterBase<float>;
template class BilinearFilterBase<double>;

template class OnePoleHighPass<float>;
template class OnePoleHighPass<double>;

template class OnePoleLowPass<float>;
template class OnePoleLowPass<double>;

template class OnePoleHighShelf<float>;
template class OnePoleHighShelf<double>;

}; // !bilin
}; // !snd
