#ifndef SND_H_
#define SND_H_

namespace snd {

template<typename fp_t>
bool isDenormal(fp_t x);

template<typename fp_t>
fp_t denormalCancel(fp_t x);

template<typename fp_t>
fp_t sineApprox7odd(fp_t x);

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
  LFOBase<fp_t>* phaseDriver;
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
  LFOBase<fp_t>* phaseDriver;
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

  fp_t SR, frequency;

 private:
  fp_t phase, frequencyState, increment, latency, sineStep, out;

  void _interpolateFrequency();
  void _triangularDriver();
  void _sineApprox7odd();
};
/**
 * @} !Oscillators
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

  void init(struct EnvelopeFeed<fp_t>* feedPtr, uint8_t* current);
  void setIndex(uint8_t index);
  void setNextIndex(uint8_t nextIndex);
  void resetNextIndex();
  uint8_t getIndex();
  void inject(uint8_t mode, fp_t y0, fp_t y1, fp_t time, fp_t bend);
  void trigger();

 private:
  bool triggerRequest;
  uint8_t Idx;
  uint8_t* currentIdxPtr;
  struct EnvelopeFeed<fp_t>* feedPtr;
  struct EnvelopeFeed<fp_t> previous;
};

template <class fp_t>
class EnvelopeGenerator {
 public:
 public:
  EnvelopeStage<fp_t>* stage;
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

}; // !snd


#endif // !SND_H_
