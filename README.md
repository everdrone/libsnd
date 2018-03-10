<h1 align="center">
<img src="assets/libsnd.png" />
<br/><br/>
</h1>

> Digital Signal Processing Library and Audio Toolbox for the Modern Synthesist.

## Install

Download the latest [stable release](https://github.com/everdrone/libsnd/releases/tag/v0.0.4) and `cd` into it.

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
  std::cout << "libsnd " << snd::snd_version << std::endl;  

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
