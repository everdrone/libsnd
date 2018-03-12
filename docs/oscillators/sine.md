# `snd::Sine<T>`

Anti Aliased sine wave oscillator

> [Source](../include/sine.hh)

## Methods

### `void setFrequency(T frequency)`

Sets the oscillation frequency (Hz)  
Range: [`-R`..`+R`], with `R` being `sampleRate / 2`

##### Arguments

* `frequency`  
  Oscillator frequency in Hz

### `void setPhase(T phase)`

Sets the oscillator's phase expressed in cycles  
Range: [`0`..`1`], multiples are wrapped in that range.

##### Arguments

* `phase`  
  The oscillator's phase

### `T tick()`

Returns the signal output at the current time.

#### Returns

Sine wave oscillator signal at the current time.
