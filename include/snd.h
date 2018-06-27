#ifndef SND_H_
#define SND_H_

#include <memory>
#include <cstdint>

namespace snd {

/**
 * @defgroup Utils
 * @{
 */
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
inline fp_t computeBLEP(fp_t x);

template <typename fp_t>
inline fp_t computeBLAMP(fp_t x);

class FlipFlop {
 public:
  FlipFlop();
  FlipFlop(bool initialState);
  ~FlipFlop();

  bool tick();
  bool state;
};
/**
 * @}
 */

/**
 * #defgroup Denormal
 * @{
 */
template<typename fp_t>
bool isDenormal(fp_t x);

template<typename fp_t>
fp_t denormalCancel(fp_t x);
/**
 * @} !Denormal
 */

/**
 * @defgroup Approximation
 * @{
 */
template<typename fp_t>
fp_t sineApprox7odd(fp_t x);

template <typename fp_t>
fp_t tanRatApprox0Pi2(fp_t x);

template <typename fp_t>
fp_t sin(fp_t x);

template <typename fp_t>
fp_t cos(fp_t x);

template <typename fp_t>
fp_t tanh(fp_t x);
/**
 * @} !Approximation
 */

/**
 * @defgroup Conversion
 * @{
 */
template <typename fp_t> fp_t pitchToFrequency(fp_t pitch);
template <typename fp_t> fp_t frequencyToPitch(fp_t frequency);
template <typename fp_t> fp_t ampFactorToDeciBel(fp_t amp);
template <typename fp_t> fp_t deciBelToAmpFactor(fp_t dB);
template <typename fp_t> fp_t logTimeToSeconds(fp_t time);
template <typename fp_t> fp_t scale(fp_t x, fp_t a, fp_t b, fp_t c, fp_t d);
template <typename fp_t> fp_t BLTPrewarp(fp_t frequency, fp_t sampleRate);
/**
 * @} !Conversion
 */

/**
 * @defgroup Saturator
 * @{
 */
template <typename fp_t>
fp_t tanhSaturator(fp_t x, fp_t level);
/**
 * @} !Saturator
 */

/**
 * @defgroup LFO
 * @{
 */
namespace LFO {

template<class fp_t>
class LFOBase {
 public:
  LFOBase(fp_t sampleRate);
  ~LFOBase();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  fp_t tick();
 private:
  fp_t SR;
  fp_t state;
  fp_t freq;
};

template<class fp_t>
class Sine {
 public:
  Sine(fp_t sampleRate);
  ~Sine();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  fp_t tick();

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template<class fp_t>
class Parabolic {
 public:
  Parabolic(fp_t sampleRate);
  ~Parabolic();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  fp_t tick();

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template<class fp_t>
class Triangle {
 public:
  Triangle(fp_t sampleRate);
  ~Triangle();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  fp_t tick();

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template<class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sampleRate);
  ~Sawtooth();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  fp_t tick();

 private:
  fp_t out;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

template<class fp_t>
class Square {
 public:
  Square(fp_t sampleRate);
  ~Square();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);
  void setPulseWidth(fp_t pw);
  fp_t tick();

 private:
  fp_t out;
  fp_t pulseWidth;
  std::unique_ptr<LFOBase<fp_t>> phaseDriver;
};

}; // !LFO
/**
 * @} !LFO
 */

/**
 * @defgroup Interpolation
 * @{
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
 * @} !Interpolation
 */

/**
 * @defgroup Oscillators
 * @{
 */
template <class fp_t>
class Sine {
 public:
  Sine(fp_t sampleRate);
  ~Sine();

  fp_t tick();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);


 private:
  fp_t SR, frequency;
  fp_t phase, frequencyState, increment,
       latency, sineStep, out;

  void _interpolateFrequency();
  void _triangularDriver();
};

template <class fp_t>
class Sawtooth {
 public:
  Sawtooth(fp_t sampleRate);
  ~Sawtooth();

  fp_t tick();

  void setFrequency(fp_t frequency);
  void setPhase(fp_t phase);

 private:
  fp_t SR, phase, frequency,
       frequencyState, increment;
  fp_t latency, out, phaseSign,
       snc, phaseState;
  FlipFlop flipFlop;
  bool flipFlop_old;
  int8_t state[2];
  fp_t temp[2], sign[2], inject[2], blep;

  void _interpolateFrequency();
};
/**
 * @} !Oscillators
 */

/**
 * @defgroup Bilinear
 * @{
 */
namespace bilin {

template <class fp_t>
class BilinearFilterBase {
 public:
  BilinearFilterBase(fp_t sampleRate);
  ~BilinearFilterBase();

  virtual void setFrequency(fp_t frequency);
  void setGain(fp_t gain);
  fp_t tick(fp_t input);

 protected:
  fp_t SR;
  fp_t coeff[3];
  fp_t state[2];
  fp_t amplitude;
  fp_t out;

 private:
  inline fp_t computeBilinear(fp_t in);
};

template <class fp_t>
class OnePoleHighPass : public BilinearFilterBase<fp_t> {
 public:
  OnePoleHighPass(fp_t sampleRate);
  ~OnePoleHighPass();
  void setFrequency(float frequency);
};

template <class fp_t>
class OnePoleLowPass : public BilinearFilterBase<fp_t> {
 public:
  OnePoleLowPass(fp_t sampleRate);
  ~OnePoleLowPass();
  void setFrequency(fp_t frequency);
};

template <class fp_t>
class OnePoleHighShelf : public BilinearFilterBase<fp_t> {
 public:
  OnePoleHighShelf(fp_t sampleRate);
  ~OnePoleHighShelf();
  void setFreq(fp_t frequency);
};

template <class fp_t>
class OnePoleLowShelf : public BilinearFilterBase<fp_t> {
 public:
  OnePoleLowShelf(fp_t sampleRate);
  ~OnePoleLowShelf();
  void setFreq(fp_t frequency);
};

}; // !bilin
/**
 * #} !Bilinear
 */

/**
 * @defgroup Envelope
 * @{
 */
template <typename fp_t>
struct EnvelopeFeed {
  bool forceStart;
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t Idx;
  EnvelopeFeed();
};

template <typename fp_t>
struct EnvelopeStorage {
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t nextIdx;
  uint8_t mode;
  EnvelopeStorage();
};

template <class fp_t>
class EnvelopeStage {
 public:
  struct EnvelopeStorage<fp_t> param;
  EnvelopeStage();
  ~EnvelopeStage();

  void init(struct EnvelopeFeed<fp_t> *feedPtr, uint8_t *current);
  void setIndex(uint8_t index);
  void setNextIndex(uint8_t nextIndex);
  void resetNextIndex();
  uint8_t getIndex();
  void inject(uint8_t mode, fp_t y0, fp_t y1, fp_t time, fp_t bend);
  void trigger();

 private:
  bool triggerRequest;
  uint8_t Idx;
  uint8_t *currentIdxPtr;
  struct EnvelopeFeed<fp_t> *feedPtr;
  struct EnvelopeFeed<fp_t> previous;
};

template <class fp_t>
class EnvelopeGenerator {
 public:
  EnvelopeStage<fp_t> *stage;
  fp_t speedFactor;

  EnvelopeGenerator(fp_t sampleRate, uint8_t nStages);
  ~EnvelopeGenerator();
  fp_t tick();
  void triggerStage(uint8_t index);

 private:
  struct EnvelopeFeed<fp_t> feed;
  fp_t SRR;
  fp_t Time;
  fp_t a;
  fp_t b;
  fp_t state;
  uint32_t N;
  uint32_t phase;
  uint8_t nStages;
  uint8_t phaseDec;
  uint8_t currentIdx;

  void _setCurrentIdx(uint8_t index);
  void _stageSwitch();
  void _phaseProcess();
  void _computeData(bool stageTrigger, bool paramTrigger, uint8_t index);
};
/**
 * @} !Envelope
 */

/**
 * @defgroup Waveshaper
 * @{
 */
template <class fp_t>
class WaveShaper {
 public:
  WaveShaper();
  ~WaveShaper();

  fp_t tick(fp_t x, fp_t switchPoint);

 private:
  fp_t folded[3];
  fp_t bus[6];
  fp_t output;
  static fp_t piSquared;
  static fp_t fourThirdsPiCubed;

  void folder(fp_t x);
};
/**
 * @} !Waveshaper
 */

}; // !snd


#endif // !SND_H_
