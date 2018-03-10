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
bool isDenormal(fp_t x);

template<typename fp_t>
fp_t denormalCancel(fp_t x);

/**
 * interpolation
 */

template <typename fp_t> fp_t interp_linear(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_bSpline(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_bSpline_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_lagrange(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_lagrange_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_hermite(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_hermite_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_2oOscu(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_2oOscu_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_watteTriLin(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_watteTriLin_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_parabolic2x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_parabolic2x_z(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_2p3o2x(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_2p3o4x(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_2p3o8x(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_2p3o16x(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_2p3o32x(fp_t x, fp_t y0, fp_t y1);
template <typename fp_t> fp_t interp_4p2o2x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p2o4x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p2o8x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p2o16x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p2o32x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p3o2x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p3o4x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p3o8x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p3o16x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p3o32x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p4o2x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p4o4x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p4o8x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p4o16x(fp_t x, fp_t y[4]);
template <typename fp_t> fp_t interp_4p4o32x(fp_t x, fp_t y[4]);

/**
 * end interpolation
 */

template <class fp_t>
class Sine {
 public:
  Sine(fp_t sampleRate);
  ~Sine();

  fp_t tick();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);

  fp_t SR, frequency;

 private:
  fp_t phase, frequencyState, increment, latency, sineStep, out;

  void _interpolateFrequency();
  void _triangularDriver();
  void _sineApprox7odd();
};

}; // !snd


#endif // !SND_H_
