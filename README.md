<h1 align="center">
<img src="assets/libsnd.png" />
<br/><br/>
</h1>

> Digital Signal Processing Library and Audio Toolbox for the Modern Synthesist.

## Attention
This library is still under development!  
Currently looking for contributors / enthusiasts, if you have an idea, found a bug or have and amazing new feature you want to add, feel free to clone, edit and push.

## Install

Download the latest [release](https://github.com/everdrone/libsnd/releases/tag/v0.0.4) and `cd` into it.

```bash
./configure
make
make install
```

## Usage

```cpp
// main.cc
#include <iostream>
#include <snd.h>

#define SAMPLE_RATE 44100

int main(int argc, char* argv[]) {
  snd::Sine<float> s(SAMPLE_RATE);
  s.setFrequency(440);
  
  for (int i = 0; i < 512; i++) {
    std::cout << s.tick(); << std::endl;
  }
  
  return 0;
}
```
```bash
g++ main.cc -o a.out -lsnd
```
