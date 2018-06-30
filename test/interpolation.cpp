#include <gtest/gtest.h>
#include <snd.h>

TEST(Interpolation, interp_linear) {
  double x = 0.333;
  double y0 = 0;
  double y1 = 100;
  EXPECT_DOUBLE_EQ(
    33.3,
    snd::interp_linear<double>(x, y0, y1)
  );
}

TEST(Interpolation, interp_bSpline) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.130853408773741,
    snd::interp_bSpline<double>(x, y)
  );
}

TEST(Interpolation, interp_bSpline_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.130853408773742,
    snd::interp_bSpline_z<double>(x, y)
  );
}

TEST(Interpolation, interp_lagrange) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.4465230671070746,
    snd::interp_lagrange<double>(x, y)
  );
}

TEST(Interpolation, interp_lagrange_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.446523067107076,
    snd::interp_lagrange_z<double>(x, y)
  );
}

TEST(Interpolation, interp_hermite) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.245652760446225,
    snd::interp_hermite<double>(x, y)
  );
}

TEST(Interpolation, interp_hermite_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.2456527604462257,
    snd::interp_hermite_z<double>(x, y)
  );
}

TEST(Interpolation, interp_2oOscu) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.1118062463979808,
    snd::interp_2oOscu<double>(x, y)
  );
}

TEST(Interpolation, interp_2oOscu_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.1118062463979816,
    snd::interp_2oOscu_z<double>(x, y)
  );
}

TEST(Interpolation, interp_watteTriLin) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    4.058604790875,
    snd::interp_watteTriLin<double>(x, y)
  );
}

TEST(Interpolation, interp_watteTriLin_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    4.058604790875,
    snd::interp_watteTriLin_z<double>(x, y)
  );
}

TEST(Interpolation, interp_parabolic2x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.0734537329375,
    snd::interp_parabolic2x<double>(x, y)
  );
}

TEST(Interpolation, interp_parabolic2x_z) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.0734537329375002,
    snd::interp_parabolic2x_z<double>(x, y)
  );
}

TEST(Interpolation, interp_2p3o2x) {
  double x = 0.333;
  double y[2] = {2.718281828459045, -3.141592653589793};
  EXPECT_DOUBLE_EQ(
    0.7300620859820757,
    snd::interp_2p3o2x<double>(x, y[0], y[1])
  );
}

TEST(Interpolation, interp_2p3o4x) {
  double x = 0.333;
  double y[2] = {2.718281828459045, -3.141592653589793};
  EXPECT_DOUBLE_EQ(
    0.8248376920534839,
    snd::interp_2p3o4x<double>(x, y[0], y[1])
  );
}

TEST(Interpolation, interp_2p3o8x) {
  double x = 0.333;
  double y[2] = {2.718281828459045, -3.141592653589793};
  EXPECT_DOUBLE_EQ(
    0.8094760585202357,
    snd::interp_2p3o8x<double>(x, y[0], y[1])
  );
}

TEST(Interpolation, interp_2p3o16x) {
  double x = 0.333;
  double y[2] = {2.718281828459045, -3.141592653589793};
  EXPECT_DOUBLE_EQ(
    0.7914926696620368,
    snd::interp_2p3o16x<double>(x, y[0], y[1])
  );
}

TEST(Interpolation, interp_2p3o32x) {
  double x = 0.333;
  double y[2] = {2.718281828459045, -3.141592653589793};
  EXPECT_DOUBLE_EQ(
    0.7800325074403159,
    snd::interp_2p3o32x<double>(x, y[0], y[1])
  );
}

TEST(Interpolation, interp_4p2o2x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    2.941454945991901,
    snd::interp_4p2o2x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p2o4x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    2.8215589389304974,
    snd::interp_4p2o4x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p2o8x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    2.6166154105044988,
    snd::interp_4p2o8x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p2o16x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    2.1428428586227395,
    snd::interp_4p2o16x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p2o32x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    1.1974156153800637,
    snd::interp_4p2o32x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p3o2x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.069064309168339,
    snd::interp_4p3o2x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p3o4x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.0728428577073825,
    snd::interp_4p3o4x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p3o8x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.074609434461846,
    snd::interp_4p3o8x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p3o16x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.075859276683533,
    snd::interp_4p3o16x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p3o32x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.076334582363602,
    snd::interp_4p3o32x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p4o2x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.055569566646585,
    snd::interp_4p4o2x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p4o4x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.084445795260335,
    snd::interp_4p4o4x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p4o8x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.088772722019367,
    snd::interp_4p4o8x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p4o16x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.089749617078929,
    snd::interp_4p4o16x<double>(x, y)
  );
}

TEST(Interpolation, interp_4p4o32x) {
  double x = 0.333;
  double y[4] = {-2, 0.8991, 7.31415, 0.999};
  EXPECT_DOUBLE_EQ(
    3.0899825732283213,
    snd::interp_4p4o32x<double>(x, y)
  );
}
