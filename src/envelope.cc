#include "envelope.hh"

namespace snd {

template struct EnvelopeFeed<float>;
template struct EnvelopeFeed<double>;

template struct EnvelopeStorage<float>;
template struct EnvelopeStorage<double>;

template class EnvelopeStage<float>;
template class EnvelopeStage<double>;

}; // !snd

