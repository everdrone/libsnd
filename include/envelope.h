#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <cstdlib>
#include <cstdint>
#include "denormal.h"

namespace snd {

template <typename fp_t>
struct EnvelopeFeed {
  bool forceStart;
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t Idx;
  EnvelopeFeed() :
    forceStart(false),
    start(0.0),
    stop(0.0),
    time(0.0),
    bend(0.0),
    Idx(0) {}
};

template <typename fp_t>
struct EnvelopeStorage {
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t nextIdx;
  uint8_t mode;
  EnvelopeStorage() :
    start(0.0),
    stop(0.0),
    time(0.0),
    bend(0.0),
    nextIdx(0),
    mode(0) {}
};

template <class fp_t>
class EnvelopeStage {
 public:
  struct EnvelopeStorage<fp_t> param;

  EnvelopeStage() {
    triggerRequest = false;
  }
  ~EnvelopeStage() {}

  void init(struct EnvelopeFeed<fp_t>* feedPtr, uint8_t* current) {
    this->feedPtr = feedPtr;
    currentIdxPtr = current;
  }

  void setIndex(uint8_t index) {
    this->Idx = index;
  }

  void setNextIndex(uint8_t nextIndex) {
    param.nextIdx = nextIndex;
  }

  void resetNextIndex() {
    param.nextIdx = Idx + 1;
  }

  uint8_t getIndex() {
    return this->Idx;
  }

  void inject(uint8_t mode, fp_t y0, fp_t y1, fp_t time, fp_t bend) {
    param.mode = mode;
    param.start = y0;
    param.stop = y1;
    param.time = time;
    param.bend = bend;

    // if is triggered
    if (triggerRequest) {
      *currentIdxPtr = Idx;
      feedPtr->forceStart = true;
      triggerRequest = false;
    } else if (triggerRequest && feedPtr->forceStart) {
      feedPtr->forceStart = true;
      triggerRequest = false;
    }

    // update previous state
    if (*currentIdxPtr == Idx) {
      feedPtr->start = param.start;
      feedPtr->stop = param.stop;
      feedPtr->time = param.time;
      feedPtr->bend = param.bend;
    }
    previous.start = y0;
    previous.stop = y1;
    previous.time = time;
    previous.bend = bend;
  }

  void trigger() {
    triggerRequest = true;
    if (triggerRequest && feedPtr->forceStart) {
      feedPtr->forceStart = true;
      triggerRequest = false;
    } else {
      *currentIdxPtr = Idx;
      feedPtr->forceStart = true;
      triggerRequest = false;
    }
  }

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
  EnvelopeStage<fp_t>* stage;
  fp_t speedFactor;

  EnvelopeGenerator(fp_t sampleRate, uint8_t nStages) {
    stage = new EnvelopeStage<fp_t>[nStages];
    for (int i = 0; i < nStages; ++i) {
      stage[i].init(&feed, &currentIdx);
      stage[i].setIndex(i);
      stage[i].resetNextIndex();
    }
    this->nStages = nStages;
    speedFactor = 1.0;
    SRR = sampleRate;
    a = 1.0f;
    b = 0.0f;
    state = 0.0f;
    phaseDec = 0;
    phase = 1;
    N = 0;
    currentIdx = nStages + 1;
  }

  ~EnvelopeGenerator() {}

  fp_t tick() {
    this->_stageSwitch();
    this->_phaseProcess();
    phase -= phaseDec;
    state = (state * a) - b;
    state = denormalCancel<fp_t>(state);
    return state;
  }

  void triggerStage(uint8_t index) {
    this->_setCurrentIdx(index);
    stage[index].trigger();
  }

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

  void _setCurrentIdx(uint8_t index) {
    this->currentIdx = index;
  }

  void _stageSwitch() {
    if (feed.forceStart) {
      _computeData(feed.forceStart, true, currentIdx);
      feed.forceStart = false;
    }
  }

  void _phaseProcess() {
    if (phase <= 0) {
      if (stage[currentIdx].param.nextIdx >= nStages) {
        _computeData(true, false, stage[currentIdx].param.nextIdx);
        a = 1.0f;
        b = 0.0f;
        phaseDec = 0;
      } else {
        currentIdx = stage[currentIdx].param.nextIdx;
        _computeData(true, false, currentIdx);
      }
    }
  }

  void _computeData(bool stageTrigger, bool paramTrigger, uint8_t index) {
    if (2 == stage[index].param.mode)
      phaseDec = 0;
    else
      phaseDec = 1;

    // calculate time
    N = std::round(stage[index].param.time * SRR / speedFactor);
    N = N < 1 ? 1 : N;
    float t_scaled = static_cast<float>(N) / SRR;
    // write read alternation
    int tau = 0;
    if (stageTrigger) {
      phase = N;
      Time = t_scaled;
    }
    phase = (t_scaled / Time) * phase;
    Time = t_scaled;
    if (stageTrigger || paramTrigger) {
      tau = phase;
      t_scaled = Time;
    }

    // calculate alpha
    float alpha;
    // infinite mode
    if (2 == stage[index].param.mode)
      alpha = std::log2(0.1);
    else {
      alpha = stage[index].param.bend < -10.0f ? -10.0f :
              (stage[index].param.bend > 10.0f ? 10.0f : stage[index].param.bend);
    }

    // calculate y0
    float y0_1 = stage[index].param.start;
    // jump mode
    if (1 == stage[index].param.mode) {
      if (stageTrigger)
        state = y0_1;
      else
        y0_1 = state;
    } else {
      if (stageTrigger || (paramTrigger && (!stageTrigger)))
        y0_1 = state;
    }

    // calculate y1
    float y1_1 = stage[index].param.stop;
    // const mode
    if (3 == stage[index].param.mode)
      y1_1 = y0_1;

    // calculate a
    float delta = std::sqrt(2.0f * 1.110223024625157E-016);
    float temp = (alpha / t_scaled) / SRR;
    float a_1;
    if (std::abs(temp) < delta) {
      a_1 = std::log(2.0) * temp;
      a = a_1 + 1.0f;
    } else {
      a = std::pow(2.0f, temp);
      a_1 = a - 1.0f;
    }

    // calculate b
    temp *= static_cast<float>(tau);
    if (std::abs(temp) < delta)
      b = (y1_1 - y0_1) / static_cast<float>(tau);
    else {
      if (2 == stage[index].param.mode)
        b = y1_1 * (-a_1);
      else {
        temp = std::pow(2.0f, temp);
        b = (a_1 / (temp - 1.0f)) * (y1_1 - (y0_1 * temp));
      }
    }
  }

};

}; // !snd

#endif // !ENVELOPE_H_
