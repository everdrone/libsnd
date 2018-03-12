# `T isDenormal(T x)`

Tests if `x` is denormal (subnormal)  
The output is different on every architecture.

#### Arguments

* `x`  
  The number to test

#### Returns

`true` if denormal, `false` otherwise.

# `T denormalCancel(T x)`

Flush to zero if the number is denormal (subnormal).

#### Argument

* `x`  
  The number to flush

#### Returns

`0` if `x` is denormal, `x` otherwise.
