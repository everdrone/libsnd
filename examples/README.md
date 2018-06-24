# Examples

## [Sine Oscillator](https://github.com/everdrone/libsnd/tree/master/examples/sine)

Produces a 440Hz sine wave audio stream through the default system audio channel output.

#### Requirements

* [RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/)

#### Compiling

```bash
g++ -std=c++14 sine.cc -o sine.out -lrtaudio -lsnd
```

## [Audio + MIDI](https://github.com/everdrone/libsnd/tree/master/examples/midi)

Minimal synthesizer composed of a sine oscillator and a basic Attack-Decay envelope generator.

This examples will listen on MIDI port 0 on your machine for *Note On* events.

#### Requirements

* [RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/)
* [RtMIDI](http://www.music.mcgill.ca/~gary/rtmidi/)

#### Compiling

```bash
g++ -std=c++14 midi.cc -o midi.out -lrtaudio -lrtmidi -lsnd
```
