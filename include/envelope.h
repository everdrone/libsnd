#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <cstdlib>
#include <cstdint>
#include "denormal.h"

namespace snd {

template <typename fp_t>
struct EnvelopeFeed {
  bool force_start;
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t index;
  EnvelopeFeed() :
    force_start(false),
    start(0.0),
    stop(0.0),
    time(0.0),
    bend(0.0),
    index(0) {}
};

template <typename fp_t>
struct EnvelopeStorage {
  fp_t start;
  fp_t stop;
  fp_t time;
  fp_t bend;
  uint8_t next_index;
  uint8_t mode;
  EnvelopeStorage() :
    start(0.0),
    stop(0.0),
    time(0.0),
    bend(0.0),
    next_index(0),
    mode(0) {}
};

template <class fp_t>
class EnvelopeStage {
 public:
  struct EnvelopeStorage<fp_t> param;

  EnvelopeStage() {
    pending_trigger = false;
  }
  ~EnvelopeStage() {}

  void init(struct EnvelopeFeed<fp_t> *feed_ptr, uint8_t *current) {
    this->feed_ptr = feed_ptr;
    current_idx_ptr = current;
  }

  void setIndex(uint8_t index) {
    this->index = index;
  }

  void setNextIndex(uint8_t next_index) {
    param.next_index = next_index;
  }

  void resetNextIndex() {
    param.next_index = index + 1;
  }

  uint8_t getIndex() {
    return this->index;
  }

  void inject(uint8_t mode, fp_t y0, fp_t y1, fp_t time, fp_t bend) {
    param.mode = mode;
    param.start = y0;
    param.stop = y1;
    param.time = time;
    param.bend = bend;

    // if is triggered
    if (pending_trigger) {
      *current_idx_ptr = index;
      feed_ptr->force_start = true;
      pending_trigger = false;
    } else if (pending_trigger && feed_ptr->force_start) {
      feed_ptr->force_start = true;
      pending_trigger = false;
    }

    // update previous state
    if (*current_idx_ptr == index) {
      feed_ptr->start = param.start;
      feed_ptr->stop = param.stop;
      feed_ptr->time = param.time;
      feed_ptr->bend = param.bend;
    }
    previous.start = y0;
    previous.stop = y1;
    previous.time = time;
    previous.bend = bend;
  }

  void trigger() {
    pending_trigger = true;
    if (pending_trigger && feed_ptr->force_start) {
      feed_ptr->force_start = true;
      pending_trigger = false;
    } else {
      *current_idx_ptr = index;
      feed_ptr->force_start = true;
      pending_trigger = false;
    }
  }

 private:
  bool pending_trigger;
  uint8_t index;
  uint8_t *current_idx_ptr;
  struct EnvelopeFeed<fp_t> *feed_ptr;
  struct EnvelopeFeed<fp_t> previous;
};

template <class fp_t>
class EnvelopeGenerator {
 public:
  EnvelopeStage<fp_t> *stage;
  fp_t speed_factor;

  EnvelopeGenerator(fp_t sample_rate, uint8_t num_stages) {
    stage = new EnvelopeStage<fp_t>[num_stages];
    for (int i = 0; i < num_stages; ++i) {
      stage[i].init(&feed, &current_idx);
      stage[i].setIndex(i);
      stage[i].resetNextIndex();
    }
    this->num_stages = num_stages;
    speed_factor = 1.0;
    sample_rate = sample_rate;
    a = 1.0f;
    b = 0.0f;
    state = 0.0f;
    phase_dec = 0;
    phase = 1;
    N = 0;
    current_idx = num_stages + 1;
  }

  ~EnvelopeGenerator() {}

  fp_t tick() {
    this->_stageSwitch();
    this->_phaseProcess();
    phase -= phase_dec;
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
  fp_t sample_rate;
  fp_t time;
  fp_t a;
  fp_t b;
  fp_t state;
  uint32_t N;
  uint32_t phase;
  uint8_t num_stages;
  uint8_t phase_dec;
  uint8_t current_idx;

  void _setCurrentIdx(uint8_t index) {
    this->current_idx = index;
  }

  void _stageSwitch() {
    if (feed.force_start) {
      _computeData(feed.force_start, true, current_idx);
      feed.force_start = false;
    }
  }

  void _phaseProcess() {
    if (phase <= 0) {
      if (stage[current_idx].param.next_index >= num_stages) {
        _computeData(true, false, stage[current_idx].param.next_index);
        a = 1.0f;
        b = 0.0f;
        phase_dec = 0;
      } else {
        current_idx = stage[current_idx].param.next_index;
        _computeData(true, false, current_idx);
      }
    }
  }

  void _computeData(bool stage_trigger, bool param_trigger, uint8_t index) {
    if (2 == stage[index].param.mode)
      phase_dec = 0;
    else
      phase_dec = 1;

    // calculate time
    N = std::round(stage[index].param.time * sample_rate / speed_factor);
    N = N < 1 ? 1 : N;
    float t_scaled = static_cast<float>(N) / sample_rate;
    // write read alternation
    int tau = 0;
    if (stage_trigger) {
      phase = N;
      time = t_scaled;
    }
    phase = (t_scaled / time) * phase;
    time = t_scaled;
    if (stage_trigger || param_trigger) {
      tau = phase;
      t_scaled = time;
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
      if (stage_trigger)
        state = y0_1;
      else
        y0_1 = state;
    } else {
      if (stage_trigger || (param_trigger && (!stage_trigger)))
        y0_1 = state;
    }

    // calculate y1
    float y1_1 = stage[index].param.stop;
    // const mode
    if (3 == stage[index].param.mode)
      y1_1 = y0_1;

    // calculate a
    float delta = std::sqrt(2.0f * 1.110223024625157E-016);
    float temp = (alpha / t_scaled) / sample_rate;
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
