#include "interpolation.h"

namespace snd {

template float interp_linear<float>(float x, float y0, float y1);
template float interp_bSpline<float>(float x, float y[4]);
template float interp_bSpline_z<float>(float x, float y[4]);
template float interp_lagrange<float>(float x, float y[4]);
template float interp_lagrange_z<float>(float x, float y[4]);
template float interp_hermite<float>(float x, float y[4]);
template float interp_hermite_z<float>(float x, float y[4]);
template float interp_2oOscu<float>(float x, float y[4]);
template float interp_2oOscu_z<float>(float x, float y[4]);
template float interp_watteTriLin<float>(float x, float y[4]);
template float interp_watteTriLin_z<float>(float x, float y[4]);
template float interp_parabolic2x<float>(float x, float y[4]);
template float interp_parabolic2x_z<float>(float x, float y[4]);
template float interp_2p3o2x<float>(float x, float y0, float y1);
template float interp_2p3o4x<float>(float x, float y0, float y1);
template float interp_2p3o8x<float>(float x, float y0, float y1);
template float interp_2p3o16x<float>(float x, float y0, float y1);
template float interp_2p3o32x<float>(float x, float y0, float y1);
template float interp_4p2o2x<float>(float x, float y[4]);
template float interp_4p2o4x<float>(float x, float y[4]);
template float interp_4p2o8x<float>(float x, float y[4]);
template float interp_4p2o16x<float>(float x, float y[4]);
template float interp_4p2o32x<float>(float x, float y[4]);
template float interp_4p3o2x<float>(float x, float y[4]);
template float interp_4p3o4x<float>(float x, float y[4]);
template float interp_4p3o8x<float>(float x, float y[4]);
template float interp_4p3o16x<float>(float x, float y[4]);
template float interp_4p3o32x<float>(float x, float y[4]);
template float interp_4p4o2x<float>(float x, float y[4]);
template float interp_4p4o4x<float>(float x, float y[4]);
template float interp_4p4o8x<float>(float x, float y[4]);
template float interp_4p4o16x<float>(float x, float y[4]);
template float interp_4p4o32x<float>(float x, float y[4]);

template double interp_linear<double>(double x, double y0, double y1);
template double interp_bSpline<double>(double x, double y[4]);
template double interp_bSpline_z<double>(double x, double y[4]);
template double interp_lagrange<double>(double x, double y[4]);
template double interp_lagrange_z<double>(double x, double y[4]);
template double interp_hermite<double>(double x, double y[4]);
template double interp_hermite_z<double>(double x, double y[4]);
template double interp_2oOscu<double>(double x, double y[4]);
template double interp_2oOscu_z<double>(double x, double y[4]);
template double interp_watteTriLin<double>(double x, double y[4]);
template double interp_watteTriLin_z<double>(double x, double y[4]);
template double interp_parabolic2x<double>(double x, double y[4]);
template double interp_parabolic2x_z<double>(double x, double y[4]);
template double interp_2p3o2x<double>(double x, double y0, double y1);
template double interp_2p3o4x<double>(double x, double y0, double y1);
template double interp_2p3o8x<double>(double x, double y0, double y1);
template double interp_2p3o16x<double>(double x, double y0, double y1);
template double interp_2p3o32x<double>(double x, double y0, double y1);
template double interp_4p2o2x<double>(double x, double y[4]);
template double interp_4p2o4x<double>(double x, double y[4]);
template double interp_4p2o8x<double>(double x, double y[4]);
template double interp_4p2o16x<double>(double x, double y[4]);
template double interp_4p2o32x<double>(double x, double y[4]);
template double interp_4p3o2x<double>(double x, double y[4]);
template double interp_4p3o4x<double>(double x, double y[4]);
template double interp_4p3o8x<double>(double x, double y[4]);
template double interp_4p3o16x<double>(double x, double y[4]);
template double interp_4p3o32x<double>(double x, double y[4]);
template double interp_4p4o2x<double>(double x, double y[4]);
template double interp_4p4o4x<double>(double x, double y[4]);
template double interp_4p4o8x<double>(double x, double y[4]);
template double interp_4p4o16x<double>(double x, double y[4]);
template double interp_4p4o32x<double>(double x, double y[4]);

}; // !snd
