<h1 align="center">
<img src="assets/libsnd.png" />
<br/><br/>
</h1>

> Digital Signal Processing Library and Audio Toolbox for the Modern Synthesist.

## Attention

This library is still under development!  
Read the [docs](/docs) and check out the [examples](/examples).

Currently looking for contributors / enthusiasts, if you have an idea, found a bug or have an amazing new feature you want to add, feel free to clone, edit and open a Pull Request.

## Building

```bash
git clone https://github.com/everdrone/libsnd.git
cd libsnd

mkdir build
cd build
cmake ..
make install
```

## Usage

```cpp
// main.cc
#include <iostream>
#include <snd.h>

#define SAMPLE_RATE 44100

int main(int argc, char **argv) {
  snd::Sine<float> s(SAMPLE_RATE);
  s.setFrequency(440);

  for (int i = 0; i < 512; i++) {
    std::cout << s.tick() << std::endl;
  }

  return 0;
}
```

```bash
g++ main.cc -o a.out -lsnd
```

## Features

* [ ] Oscillators
  * [ ] Anti Aliased
    * [x] Sine
    * [ ] Triangle
    * [x] Sawtooth
    * [ ] Square
    * [ ] Spectral (Sine Bank)
* [ ] Filters
  * [ ] Zero Delay Feedback
  * [ ] Bilinear
  * [ ] Biquad
  * [ ] Modular / Multiband
  * [ ] Comb
* [ ] Multistage Waveshaper
* [ ] Envelope Generators
  * [x] Multistage Envelope Generator
  * [ ] Classic Dual Stage (AD) Envelope Generator
  * [ ] "Ducking" Curve Generator
* [ ] Envelope Follower
* [x] Interpolation
* [x] Denormal canceling
* [ ] LFOs
  * [x] Sine
  * [x] Parabolic
  * [x] Triangle
  * [x] Sawtooth
  * [x] Square
  * [ ] Random
  * [ ] Perlin
* [ ] Effects
  * [ ] Delay
    * [ ] Interpolated
    * [ ] Non-Interpolated
  * [ ] Reverb
    * [ ] Spring
    * [ ] Convolution
  * [ ] Flanger
  * [ ] Phaser
  * [ ] Chorus
  * [ ] Stereo Panner
  * [ ] Ring Modulator
  * [ ] Bit Crusher
  * [ ] Compressor
  * [ ] Driver / Saturator
* [ ] Utilities
  * [ ] LR to MS
  * [ ] MS to LR
  * [x] Pitch (MIDI) to Frequency (Hz)
  * [x] Frequency (Hz) to Pitch (MIDI)
  * [x] Amplitude Factor to dB
  * [x] dB to Amplitude Factor
  * [ ] Linear to Exponential
  * [ ] Linear to Logarithmic
