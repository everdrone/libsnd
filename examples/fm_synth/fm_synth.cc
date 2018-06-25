#include <RtAudio.h>
#include <RtMidi.h>
#include <snd.h>
#include <math.h>
#include <iostream>
#include <cstdlib>

class ADSREnevelope {
 public:
  ADSREnevelope(double sampleRate) {
    gen = new snd::EnvelopeGenerator<double>(sampleRate, 3);
    // set stage parameters
    this->sustainLevel = 0.35f;
    gen->stage[0].inject(0, 0.f, 1.f, 0.001, 0);
    gen->stage[1].inject(2, 1.f, sustainLevel, 0.4f, 0);
    gen->stage[2].inject(2, sustainLevel, 0.f, 0.1f, 0);
  }
  ~ADSREnevelope() {
    delete gen;
  }

  void attack(float atk) {
    gen->stage[0].inject(0, 0.f, 1.f, atk, 0);
  }
  void decay(float dec) {
    gen->stage[1].inject(2, 1.f, sustainLevel, dec, 0);
  }
  void sustain(float sus) {
    this->sustainLevel = sus;
  }
  void release(float rel) {
    gen->stage[2].inject(2, sustainLevel, 0.f, rel, 0);
  }

  double tick() {
    return gen->tick();
  }

  void start() {
    gen->triggerStage(0);
  }

  void stop() {
    gen->triggerStage(2);
  }

 private:
  snd::EnvelopeGenerator<double> *gen;
  float sustainLevel;
};

class FMSynth {
 public:
  FMSynth(double sampleRate) {
    env = new ADSREnevelope(sampleRate);
    frequency = mix = 0.f;
    output = 0.f;
    for (int i = 0; i < 2; i++) {
      osc[i] = new snd::Sine<double>(sampleRate);
      ops[i] = new snd::Sine<double>(sampleRate);
      interval[i] = 0.f;
      out[i] = 0.f;
      out[i + 2] = 0.f;
    }
  }
  ~FMSynth() {
    // delete[] osc;
  }

  double tick() {
    out[0] = osc[0]->tick();
    out[1] = osc[1]->tick();
    ops[0]->setPhase(out[0] * amount);
    ops[1]->setPhase(out[1] * amount);
    out[2] = ops[0]->tick();
    out[3] = ops[1]->tick();
    output = snd::interp_linear(mix, out[2], out[3]);
    return output * 0.5 * env->tick();
  }

  void setInterval(float itvl) {
    float val = itvl * 7.5f;
    interval[0] = 1 + (2 * (1 + floorf(val - 0.5f)));
    interval[1] = 2 * (1 + floorf(val));
    mix = 2.f * fabsf(val - roundf(val));
  }

  void setPitch(int note) {
    frequency = snd::pitchToFrequency<double>(note);
    osc[0]->setFrequency(frequency * interval[0]);
    osc[1]->setFrequency(frequency * interval[1]);
    ops[0]->setFrequency(frequency);
    ops[1]->setFrequency(frequency);
  }

  void setAmount(double amt) {
    this->amount = amt * amt * 3.14;
  }

  void noteOn() {
    env->start();
  }

  void noteOff() {
    env->stop();
  }

 private:
  snd::Sine<double> *osc[2];
  snd::Sine<double> *ops[2];
  ADSREnevelope *env;
  double frequency;
  float interval[2];
  double mix, amount;
  double out[4], output;
};

int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void *userData) {
  unsigned int i;
  double *buffer = reinterpret_cast<double *>(outputBuffer);
  FMSynth *synth = reinterpret_cast<FMSynth *>(userData);

  if (status) std::cout << "Stream underflow detected!" << std::endl;

  double value = 0.;

  for (i = 0; i < nBufferFrames; i++) {
    value = synth->tick();
    *buffer++ = value;
    // copy to channel 2
    *buffer++ = value;
  }

  return 0;
}

void midiCallback(double deltatime, std::vector<unsigned char> *message,
                  void *userData) {
  unsigned int nBytes = message->size();
  FMSynth *synth = reinterpret_cast<FMSynth *>(userData);
  if ((int)message->at(0) == 144) {
    synth->setPitch((int)message->at(1));
    synth->noteOn();
  } else if ((int)message->at(0) == 128) {
    synth->noteOff();
  } else if ((int)message->at(0) == 176) {
    if ((int)message->at(1) == 1) {
      synth->setInterval((int)message->at(2) / 127.f);
    } else if ((int)message->at(1) == 2) {
      synth->setAmount((int)message->at(2) / 127.f);
    }
  }
}

int main() {
  // instantiate rtaudio
  RtAudio dac;
  // ensure output devices
  if (dac.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(0);
  }

  // then the midi input
  RtMidiIn *midiin = new RtMidiIn();
  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if (nPorts == 0) {
    std::cout << "No ports available!\n";
    delete midiin;
    exit(0);
  }

  // configure audio stream
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferSize = 256;

  FMSynth synth(sampleRate);
  synth.setInterval(0.5);
  synth.setAmount(0.5);

  try {
    // setup midi port
    midiin->openPort(0);
    midiin->setCallback(&midiCallback, reinterpret_cast<void *>(&synth));
    // start stream
    dac.openStream(&parameters, NULL, RTAUDIO_FLOAT64,
                   sampleRate, &bufferSize, &audioCallback, reinterpret_cast<void *>(&synth));
    dac.startStream();
  } catch (RtAudioError &e) {
    e.printMessage();
    exit(0);
  }

  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);
  try {
    // Stop the stream
    dac.stopStream();
  } catch (RtAudioError &e) {
    e.printMessage();
  }

  if (dac.isStreamOpen()) dac.closeStream();

  return 0;
}
