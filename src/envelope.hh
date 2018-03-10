#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <cstdlib>
#include "denormal.hh"

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
    // TODO: add trigger function to remove 'bool trigger' from injection function
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
    // this->stageSwitch();
    // this->phaseProcess();
    phase -= phaseDec;
    state = (state * a) - b;
    state = denormalCancel<fp_t>(state);
    return state;
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
};

}; // !snd

#endif // !ENVELOPE_H_
