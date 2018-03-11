/**
 * g++ sine.cc -o sine.out -lrtaudio -lsnd
 */

#include <RtAudio.h>
#include <snd.h>
#include <iostream>
#include <cstdlib>

int audioCallback(void* outputBuffer, void* inputBuffer,
                  unsigned int nBufferFrames,
                  double streamTime, RtAudioStreamStatus status, void* userData) {
  unsigned int i;
  double* buffer = reinterpret_cast<double*>(outputBuffer);
  snd::Sine<double>* osc = reinterpret_cast<snd::Sine<double>*>(userData);

  if (status) std::cout << "Stream underflow detected!" << std::endl;

  double value = 0.;

  for (i = 0; i < nBufferFrames; i++) {
    value = osc->tick() * 0.5;
    *buffer++ = value;
    // copy to channel 2
    *buffer++ = value;
  }

  return 0;
}

int main() {
  // instantiate rtaudio
  RtAudio dac;
  // ensure output devices
  if (dac.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(0);
  }
  // set stream parameters
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  unsigned int sampleRate = 44100;
  unsigned int bufferSize = 256;

  snd::Sine<double> osc(sampleRate);
  osc.setFrequency(440);

  try {
    // start stream
    dac.openStream(&parameters, NULL, RTAUDIO_FLOAT64,
                   sampleRate, &bufferSize, &audioCallback, reinterpret_cast<void*>(&osc));
    dac.startStream();
  } catch (RtAudioError& e) {
    e.printMessage();
    exit(0);
  }

  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);
  try {
    // Stop the stream
    dac.stopStream();
  } catch (RtAudioError& e) {
    e.printMessage();
  }

  if (dac.isStreamOpen()) dac.closeStream();

  return 0;
}
