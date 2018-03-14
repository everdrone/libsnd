#ifndef UTILS_H_
#define UTILS_H_

namespace snd {

const double polyBLEP[8] = {
  0.49993,
  -1.48783,
  -0.11965,
  3.917645,
  -1.62547,
  -5.7564,
  6.7519,
  -2.180115
};

const double polyBLAMP[9] = {
  -0.824736,
    3.99944,
    -5.95132,
    -0.31906666666666666666666666666667,
    7.83529,
    -2.600752,
    -7.6752,
    7.7164571428571428571428571428571,
    -2.180115
  };

template <typename fp_t>
inline fp_t computeBLEP(fp_t x) {
  fp_t a0 = x * polyBLEP[7];
  a0 += polyBLEP[6];
  for (int i = 5; i >= 0;) {
    a0 *= x;
    a0 += polyBLEP[i];
    i--;
  }
  return a0;
}

template <typename fp_t>
inline fp_t computeBLAMP(fp_t x) {
  fp_t a0 = x * polyBLAMP[8];
  a0 += polyBLAMP[7];
  for (int i = 6; i >= 0;) {
    a0 *= x;
    a0 += polyBLAMP[i];
    i--;
  }
  return a0;
}

class FlipFlop {
 public:
  FlipFlop() {
    state = false;
  }
  FlipFlop(bool initialState) {
    state = initialState;
  }

  bool tick() {
    state ^= true;
    return state;
  }

  bool state;
};

}; // !snd

#endif // !UTILS_H_
