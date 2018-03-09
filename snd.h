/**
 * @file snd.hh
 * @brief main header file
 *
 * This is the long description everyone was waiting for.
 * Ipsum tempor eu Lorem cillum.In quis pariatur aute commodo cupidatat cupidatat ea cillum minim minim et.
 */

#ifndef SND_H_
#define SND_H_

namespace snd {

template<typename fp_t>
bool isDenormal(fp_t);

template<typename fp_t>
fp_t denormalCancel(fp_t);

template <class fp_t>
class Sine {
 public:
  Sine(fp_t);
  ~Sine();

  fp_t tick();

  void setFrequency(fp_t);
  void setPhase(fp_t);

  fp_t SR, frequency;

 private:
  fp_t phase, frequencyState, increment, latency, sineStep, out;

  void _interpolateFrequency();
  void _triangularDriver();
  void _sineApprox7odd();
};

}; // !snd


#endif // !SND_H_
