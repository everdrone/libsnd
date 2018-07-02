#include "conversion.h"

namespace snd {

template float pitchToFrequency<float>(float pitch);
template float frequencyToPitch<float>(float frequency);
template float ampFactorToDeciBel<float>(float amp);
template float deciBelToAmpFactor<float>(float dB);
template float logTimeToSeconds<float>(float time);
template float scale<float>(float x, float a, float b, float c, float d);
template float BLTPrewarp<float>(float frequency, float sample_rate);

template double pitchToFrequency<double>(double pitch);
template double frequencyToPitch<double>(double frequency);
template double ampFactorToDeciBel<double>(double amp);
template double deciBelToAmpFactor<double>(double dB);
template double logTimeToSeconds<double>(double time);
template double scale<double>(double x, double a, double b, double c, double d);
template double BLTPrewarp<double>(double frequency, double sample_rate);

}; // !snd
