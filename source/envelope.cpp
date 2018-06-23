#include "envelope.h"

namespace snd {

template struct EnvelopeFeed<float>;
template struct EnvelopeFeed<double>;

template struct EnvelopeStorage<float>;
template struct EnvelopeStorage<double>;

template class EnvelopeStage<float>;
template class EnvelopeStage<double>;

template class EnvelopeGenerator<float>;
template class EnvelopeGenerator<double>;

}; // !snd

