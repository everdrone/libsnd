#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <cmath>
#include "approx.hh"

#define DB_FACTOR 1.1220184543019634355910389464779057367223085073606
#define DB_MULT 8.175800000000001
#define PI 3.14159265358979323846

namespace snd {

template <typename fp_t>
fp_t pitchToFrequency(fp_t pitch) {
  return std::exp2(pitch / 12.0) * DB_MULT;
}

template <typename fp_t>
fp_t frequencyToPitch(fp_t frequency) {
  return 12.0 * std::log2(frequency / DB_MULT);
}

template <typename fp_t>
fp_t ampFactorToDeciBel(fp_t amp) {
  return std::log(amp) / std::log(DB_FACTOR);
}

template <typename fp_t>
fp_t deciBelToAmpFactor(fp_t dB) {
  return std::pow(DB_FACTOR, dB);
}

template <typename fp_t>
fp_t logTimeToSeconds(fp_t time) {
  return std::pow(DB_FACTOR, time - 60.0);
}

template <typename fp_t>
fp_t scale(fp_t x, fp_t a, fp_t b, fp_t c, fp_t d) {
  return ((x - a) * ((c - d) / (a - b))) + c;
}

template <typename fp_t>
fp_t BLTPrewarp(fp_t frequency, fp_t sampleRate) {
  fp_t x = frequency < 0.0 ? 0.0 : frequency;
  x *= PI / sampleRate;
  x = x > 1.50845 ? 1.50845 : x;
  return tanRatApprox0Pi2(x);
}

}; // !snd

#endif // !CONVERSION_H_
