#include "saturator.h"

namespace snd {

template float tanhSaturator<float>(float x, float level);
template double tanhSaturator<double>(double x, double level);

}; // !snd
