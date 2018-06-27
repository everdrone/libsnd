#include <RtAudio.h>
#include <RtMidi.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <snd.h>

class WaveFolderSynth {
 public:
  WaveFolderSynth(double sampleRate) {
    frequency = 0.f;
    mix = 1.f;
    drive = 0.f;
    output = 0.f;
    osc = new snd::Sine<double>(sampleRate);
    filter = new snd::bilin::OnePoleLowPass<double>(sampleRate);
    filter->setFrequency(1000);
  }
  ~WaveFolderSynth() {}

  double tick() {
    double a = osc->tick();
    double b = a * 2 * ((drive * drive * 7) + 1);
    b = filter->tick(b);
    b = shaper.tick(b, fabs(frequency) * 10 + 100);
    b = snd::tanhSaturator<double>(b, 0);
    b *= 0.5;
    output = snd::interp_linear(mix, a, b);
    return output * 0.5;
  }

  void setPitch(int note) {
    frequency = snd::pitchToFrequency<double>(note);
    osc->setFrequency(frequency);
  }

  void setMix(double mix) {
    this->mix = mix;
  }

  void setDrive(double drv) {
    this->drive = drv;
  }

 private:
  snd::Sine<double> *osc;
  snd::WaveShaper<double> shaper;
  snd::bilin::OnePoleLowPass<double> *filter;
  double frequency;
  double mix, drive;
  double output;
};

int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void *userData) {
  unsigned int i;
  double *buffer = reinterpret_cast<double *>(outputBuffer);
  WaveFolderSynth *synth = reinterpret_cast<WaveFolderSynth *>(userData);

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
  WaveFolderSynth *synth = reinterpret_cast<WaveFolderSynth *>(userData);
  if ((int)message->at(0) == 176) {
    if ((int)message->at(1) == 1) {
      synth->setDrive((int)message->at(2) / 127.f);
    } else if ((int)message->at(1) == 2) {
      synth->setMix((int)message->at(2) / 127.f);
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

  WaveFolderSynth synth(sampleRate);
  synth.setPitch(60 - 12);

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
