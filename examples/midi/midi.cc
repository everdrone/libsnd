#include <RtAudio.h>
#include <RtMidi.h>
#include <snd.h>
#include <iostream>
#include <cstdlib>

class ADEnevelope {
 public:
  ADEnevelope(double sample_rate) {
    gen = new snd::EnvelopeGenerator<double>(sample_rate, 2);
    // set stage parameters
    gen->stage[0].inject(0, 0.f, 1.f, 0.001, 0);
    gen->stage[1].inject(2, 1.f, 0.f, 0.4f, 0);
  }
  ~ADEnevelope() {
    delete gen;
  }

  double tick() {
    return gen->tick();
  }

  void start() {
    gen->triggerStage(0);
  }

 private:
  snd::EnvelopeGenerator<double> *gen;
};

class MiniSynth {
 public:
  MiniSynth(double sample_rate) {
    osc = new snd::Sine<double>(sample_rate);
    env = new ADEnevelope(sample_rate);
    frequency = 0.f;
  }
  ~MiniSynth() {
    delete osc;
  }

  double tick() {
    return osc->tick() * env->tick() * 0.5;
  }

  void setPitch(int note) {
    frequency = snd::pitchToFrequency<double>(note);
    osc->setFrequency(frequency);
  }

  void noteOn() {
    env->start();
  }

 private:
  snd::Sine<double> *osc;
  ADEnevelope *env;
  double frequency;
};

int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void *userData) {
  unsigned int i;
  double *buffer = reinterpret_cast<double *>(outputBuffer);
  MiniSynth *synth = reinterpret_cast<MiniSynth *>(userData);

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
  MiniSynth *synth = reinterpret_cast<MiniSynth *>(userData);
  if ((int)message->at(0) == 144) {
    synth->setPitch((int)message->at(1));
    synth->noteOn();
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
  unsigned int sample_rate = 44100;
  unsigned int bufferSize = 256;

  MiniSynth synth(sample_rate);

  try {
    // setup midi port
    midiin->openPort(0);
    midiin->setCallback(&midiCallback, reinterpret_cast<void *>(&synth));
    // start stream
    dac.openStream(&parameters, NULL, RTAUDIO_FLOAT64,
                   sample_rate, &bufferSize, &audioCallback, reinterpret_cast<void *>(&synth));
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
