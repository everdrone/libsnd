# `T interp_linear(T x, T y0, T y1)`

Linear interpolation function.

#### Arguments

* `x`  
  Interpolation parameter
* `y0`  
  First parameter
* `y1`  
  Second parameter

#### Returns

The interpolated value between `y0` and `y1` parameters.

# `T interp_bSpline(T x, T y[4])`

4-point, 3rd-order B-spline interpolation function (_x_ form).  
Requires 7 multiplications.

#### Arguments

* `x`  
  Interpolation parameter
* `y[4]`  
  Coordinates

#### Returns

The interpolated value between `y` parameters.

# `T interp_bSpline_z(T x, T y[4])`

4-point, 3rd-order B-spline interpolation function (_z_ form).  
Requires 7 multiplications.

#### Arguments

* `x`  
  Interpolation parameter
* `y[4]`  
  Coordinates

#### Returns

The interpolated value between `y` parameters.

#### ...
