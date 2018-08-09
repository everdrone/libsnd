#pragma once

namespace snd {

/*
 * @brief:			linear interpolation
 */
template <typename fp_t>
fp_t interp_linear(fp_t x, fp_t y0, fp_t y1) {
  return y0 + x * (y1 - y0);
}

//------------------------------------------------------------------------------
/* 4-point */
/*
 * @brief: 			4-point, 3rd-order B-spline
 * 					x-form
 * @note: 			requires 6 multiplications.
 */
template <typename fp_t>
fp_t interp_bSpline(fp_t x, fp_t y[4]) {
  fp_t ym1py2 = y[0] + y[2];
  fp_t c0 = 1 / 6.0 * ym1py2 + 2 / 3.0 * y[1];
  fp_t c1 = 0.5 * (y[2] - y[0]);
  fp_t c2 = 0.5 * ym1py2 - y[1];
  fp_t c3 = 0.5 * (y[1] - y[2]) + 1 / 6.0 * (y[3] - y[0]);
  return ((c3 * x + c2) * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 3rd-order B-spline
 * 					z-form
 * @note: 			requires 7 multiplications.
 */
template <typename fp_t>
fp_t interp_bSpline_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], modd1 = y[3] - y[0];
  fp_t even2 = y[1] + y[2], modd2 = y[2] - y[1];
  fp_t c0 = 1 / 48.0 * even1 + 23 / 48.0 * even2;
  fp_t c1 = 1 / 8.0 * modd1 + 5 / 8.0 * modd2;
  fp_t c2 = 0.25 * (even1 - even2);
  fp_t c3 = 1 / 6.0 * modd1 - 0.5 * modd2;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order Lagrange
 *					x-form
 * @note: 			requires 6 multiplications.
 */
template <typename fp_t>
fp_t interp_lagrange(fp_t x, fp_t y[4]) {
  fp_t c0 = y[1];
  fp_t c1 = y[2] - 1 / 3.0 * y[0] - 0.5 * y[1] - 1 / 6.0 * y[3];
  fp_t c2 = 0.5 * (y[0] + y[2]) - y[1];
  fp_t c3 = 1 / 6.0 * (y[3] - y[0]) + 0.5 * (y[1] - y[2]);
  return ((c3 * x + c2) * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 3rd-order Lagrange
 *					z-form
 * @note: 			requires 7 multiplications.
 */
template <typename fp_t>
fp_t interp_lagrange_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], odd1 = y[0] - y[3];
  fp_t even2 = y[1] + y[2], odd2 = y[1] - y[2];
  fp_t c0 = 9 / 16.0 * even2 - 1 / 16.0 * even1;
  fp_t c1 = 1 / 24.0 * odd1 - 9 / 8.0 * odd2;
  fp_t c2 = 0.25 * (even1 - even2);
  fp_t c3 = 0.5 * odd2 - 1 / 6.0 * odd1;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order Hermite
 *					x-form
 * @note: 			requires 6 multiplications.
 */
template <typename fp_t>
fp_t interp_hermite(fp_t x, fp_t y[4]) {
  fp_t c0 = y[1];
  fp_t c1 = 0.5 * (y[2] - y[0]);
  fp_t c2 = y[0] - 5 / 2.0 * y[1] + 2 * y[2] - 0.5 * y[3];
  fp_t c3 = 0.5 * (y[3] - y[0]) + 3 / 2.0 * (y[1] - y[2]);
  return ((c3 * x + c2) * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 3rd-order Hermite
 *					z-form
 * @note: 			requires 7 multiplications.
 */
template <typename fp_t>
fp_t interp_hermite_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], odd1 = y[0] - y[3];
  fp_t even2 = y[1] + y[2], odd2 = y[1] - y[2];
  fp_t c0 = 9 / 16.0 * even2 - 1 / 16.0 * even1;
  fp_t c1 = 1 / 8.0 * odd1 - 11 / 8.0 * odd2;
  fp_t c2 = 0.25 * (even1 - even2);
  fp_t c3 = 3 / 2.0 * odd2 - 0.5 * odd1;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 5th-order 2nd-order-osculating
 *					x-form
 * @note: 			requires 7 multiplications.
 */
template <typename fp_t>
fp_t interp_2oOscu(fp_t x, fp_t y[4]) {
  fp_t y2my1 = y[2] - y[1];
  fp_t y3mym1 = y[3] - y[0];
  fp_t c0 = y[1];
  fp_t c1 = 0.5 * (y[2] - y[0]);
  fp_t c2 = 0.5 * (y[0] + y[2]) - y[1];
  fp_t c3 = 9 / 2.0 * y2my1 - 3 / 2.0 * y3mym1;
  fp_t c4 = 5 / 2.0 * y3mym1 - 15 / 2.0 * y2my1;
  fp_t c5 = y[0] + 3 * y2my1 - y[3];
  return ((((c5 * x + c4) * x + c3) * x + c2) * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 5th-order 2nd-order-osculating
 *					z-form
 * @note: 			requires 6 multiplications.
 */
template <typename fp_t>
fp_t interp_2oOscu_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], odd1 = y[0] - y[3];
  fp_t even2 = y[1] + y[2], odd2 = y[1] - y[2];
  fp_t c0 = 9 / 16.0 * even2 - 1 / 16.0 * even1;
  fp_t c1 = 3 / 16.0 * odd1 - 25 / 16.0 * odd2;
  fp_t c2 = 0.25 * (even1 - even2);
  fp_t c5 = odd1 - 3 * odd2;
  return (((c5 * z * z - c5) * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order Watte tri-linear
 *					x-form
 * @note: 			requires 3 multiplications.
 */
template <typename fp_t>
fp_t interp_watteTriLin(fp_t x, fp_t y[4]) {
  fp_t ym1py3 = y[0] + y[3];
  fp_t c0 = y[1];
  fp_t c1 = 3 / 2.0 * y[2] - 0.5 * (y[1] + ym1py3);
  fp_t c2 = 0.5 * (ym1py3 - y[1] - y[2]);
  return (c2 * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 2nd-order Watte tri-linear
 *					z-form
 * @note: 			requires 3 multiplications.
 */
template <typename fp_t>
fp_t interp_watteTriLin_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], even2 = y[1] + y[2];
  fp_t c0 = 5 / 8.0 * even2 - 1 / 8.0 * even1;
  fp_t c1 = y[2] - y[1];
  fp_t c2 = 0.5 * (even1 - even2);
  return (c2 * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order parabolic 2x
 *					x-form
 * @note: 			requires 4 multiplications.
 */
template <typename fp_t>
fp_t interp_parabolic2x(fp_t x, fp_t y[4]) {
  fp_t y2mym1 = y[2] - y[0];
  fp_t c0 = 0.5 * y[1] + 0.25 * (y[0] + y[2]);
  fp_t c1 = 0.5 * y2mym1;
  fp_t c2 = 0.25 * (y[3] - y[1] - y2mym1);
  return (c2 * x + c1) * x + c0;
}

/*
 * @brief: 			4-point, 2nd-order parabolic 2x
 *					z-form
 * @note: 			requires 4 multiplications.
 */
template <typename fp_t>
fp_t interp_parabolic2x_z(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[0] + y[3], even2 = y[1] + y[2];
  fp_t c0 = 1 / 16.0 * even1 + 7 / 16.0 * even2;
  fp_t c1 = 0.25 * (y[2] - y[1] + y[3] - y[0]);
  fp_t c2 = 0.25 * (even1 - even2);
  return (c2 * z + c1) * z + c0;
}

//------------------------------------------------------------------------------
/* optimal z-forms */
/* 2-points 3rd order */
/*
 * @brief: 			2-point, 3rd-order optimal 2x
 *					z-form
 */
template <typename fp_t>
fp_t interp_2p3o2x(fp_t x, fp_t y0, fp_t y1) {
  fp_t z = x - 0.5;
  fp_t even1 = y1 + y0, odd1 = y1 - y0;
  fp_t c0 = even1 * 0.50037842517188658;
  fp_t c1 = odd1 * 1.00621089801788210;
  fp_t c2 = even1 * -0.004541102062639801;
  fp_t c3 = odd1 * -1.57015627178718420;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			2-point, 3rd-order optimal 4x
 *					z-form
 */
template <typename fp_t>
fp_t interp_2p3o4x(fp_t x, fp_t y0, fp_t y1) {
  fp_t z = x - 0.5;
  fp_t even1 = y1 + y0, odd1 = y1 - y0;
  fp_t c0 = even1 * 0.50013034073688023;
  fp_t c1 = odd1 * 1.09617817497678520;
  fp_t c2 = even1 * -0.001564088842561871;
  fp_t c3 = odd1 * -1.32598918957298410;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			2-point, 3rd-order optimal 8x
 *					z-form
 */
template <typename fp_t>
fp_t interp_2p3o8x(fp_t x, fp_t y0, fp_t y1) {
  fp_t z = x - 0.5;
  fp_t even1 = y1 + y0, odd1 = y1 - y0;
  fp_t c0 = even1 * 0.50004007194083089;
  fp_t c1 = odd1 * 1.06397659072500650;
  fp_t c2 = even1 * -0.000480863289971321;
  fp_t c3 = odd1 * -0.73514591836770027;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			2-point, 3rd-order optimal 16x
 *					z-form
 */
template <typename fp_t>
fp_t interp_2p3o16x(fp_t x, fp_t y0, fp_t y1) {
  fp_t z = x - 0.5;
  fp_t even1 = y1 + y0, odd1 = y1 - y0;
  fp_t c0 = even1 * 0.50001096675880796;
  fp_t c1 = odd1 * 1.03585606328743830;
  fp_t c2 = even1 * -0.000131601105693441;
  fp_t c3 = odd1 * -0.38606621963374965;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			2-point, 3rd-order optimal 32x
 *					z-form
 */
template <typename fp_t>
fp_t interp_2p3o32x(fp_t x, fp_t y0, fp_t y1) {
  fp_t z = x - 0.5;
  fp_t even1 = y1 + y0, odd1 = y1 - y0;
  fp_t c0 = even1 * 0.50000286037713559;
  fp_t c1 = odd1 * 1.01889120864375270;
  fp_t c2 = even1 * -0.000034324525627571;
  fp_t c3 = odd1 * -0.19775766248673177;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/* 4-point 2nd order */
/*
 * @brief: 			4-point, 2nd-order optimal 2x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p2o2x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.42334633257225274 + even2 * 0.07668732202139628;
  fp_t c1 = odd1 * 0.26126047291143606 + odd2 * 0.24778879018226652;
  fp_t c2 = even1 * -0.213439787561776841 + even2 * 0.21303593243799016;
  return (c2 * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order optimal 4x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p2o4x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.38676264891201206 + even2 * 0.11324319172521946;
  fp_t c1 = odd1 * 0.01720901456660906 + odd2 * 0.32839294317251788;
  fp_t c2 = even1 * -0.228653995318581881 + even2 * 0.22858390767180370;
  return (c2 * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order optimal 8x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p2o8x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.32852206663814043 + even2 * 0.17147870380790242;
  fp_t c1 = odd1 * -0.35252373075274990 + odd2 * 0.45113687946292658;
  fp_t c2 = even1 * -0.240052062078895181 + even2 * 0.24004281672637814;
  return (c2 * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order optimal 16x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p2o16x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.20204741371575463 + even2 * 0.29795268253813623;
  fp_t c1 = odd1 * -1.11855475338366150 + odd2 * 0.70626377291054832;
  fp_t c2 = even1 * -0.245061178654743641 + even2 * 0.24506002360805534;
  return (c2 * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 2nd-order optimal 32x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p2o32x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * -0.04817865217726123 + even2 * 0.54817866412548932;
  fp_t c1 = odd1 * -2.62328241292796620 + odd2 * 1.20778105913587620;
  fp_t c2 = even1 * -0.247552438397138281 + even2 * 0.24755229501840223;
  return (c2 * z + c1) * z + c0;
}

/* 4-point 3rd order */
/*
 * @brief: 			4-point, 3rd-order optimal 2x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p3o2x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.45868970870461956 + even2 * 0.04131401926395584;
  fp_t c1 = odd1 * 0.48068024766578432 + odd2 * 0.17577925564495955;
  fp_t c2 = even1 * -0.246185007019907091 + even2 * 0.24614027139700284;
  fp_t c3 = odd1 * -0.36030925263849456 + odd2 * 0.10174985775982505;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order optimal 4x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p3o4x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46209345013918979 + even2 * 0.03790693583186333;
  fp_t c1 = odd1 * 0.51344507801315964 + odd2 * 0.16261507145522014;
  fp_t c2 = even1 * -0.248540332990294211 + even2 * 0.24853570133765701;
  fp_t c3 = odd1 * -0.42912649274763925 + odd2 * 0.13963062613760227;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order optimal 8x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p3o8x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46360002085841184 + even2 * 0.03640000638072349;
  fp_t c1 = odd1 * 0.52776949859997280 + odd2 * 0.15746108253367153;
  fp_t c2 = even1 * -0.249658121535793251 + even2 * 0.24965779466617388;
  fp_t c3 = odd1 * -0.46789242171187317 + odd2 * 0.15551896027602030;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order optimal 16x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p3o16x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46436507349411416 + even2 * 0.03563492826010761;
  fp_t c1 = odd1 * 0.53463126553787166 + odd2 * 0.15512856361039451;
  fp_t c2 = even1 * -0.249923540967159741 + even2 * 0.24992351991649797;
  fp_t c3 = odd1 * -0.48601256046234864 + odd2 * 0.16195131297091253;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 3rd-order optimal 32x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p3o32x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46465589031535864 + even2 * 0.03534410979496938;
  fp_t c1 = odd1 * 0.53726845877054186 + odd2 * 0.15424449410914165;
  fp_t c2 = even1 * -0.249981930954029101 + even2 * 0.24998192963009191;
  fp_t c3 = odd1 * -0.49369595780454456 + odd2 * 0.16455902278580614;
  return ((c3 * z + c2) * z + c1) * z + c0;
}

/* 4-point 4th order */
/*
 * @brief: 			4-point, 4th-order optimal 2x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p4o2x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.45645918406487612 + even2 * 0.04354173901996461;
  fp_t c1 = odd1 * 0.47236675362442071 + odd2 * 0.17686613581136501;
  fp_t c2 = even1 * -0.253674794204558521 + even2 * 0.25371918651882464;
  fp_t c3 = odd1 * -0.37917091811631082 + odd2 * 0.11952965967158000;
  fp_t c4 = even1 * 0.04252164479749607 + even2 * -0.04289144034653719;
  return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 4th-order optimal 4x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p4o4x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46567255120778489 + even2 * 0.03432729708429672;
  fp_t c1 = odd1 * 0.53743830753560162 + odd2 * 0.15429462557307461;
  fp_t c2 = even1 * -0.251942101340217441 + even2 * 0.25194744935939062;
  fp_t c3 = odd1 * -0.46896069955075126 + odd2 * 0.15578800670302476;
  fp_t c4 = even1 * 0.00986988334359864 + even2 * -0.00989340017126506;
  return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 4th-order optimal 8x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p4o8x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46771532012068961 + even2 * 0.03228466824404497;
  fp_t c1 = odd1 * 0.55448654344364423 + odd2 * 0.14851181120641987;
  fp_t c2 = even1 * -0.250587283698110121 + even2 * 0.25058765188457821;
  fp_t c3 = odd1 * -0.49209020939096676 + odd2 * 0.16399414834151946;
  fp_t c4 = even1 * 0.00255074537015887 + even2 * -0.00255226912537286;
  return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 4th-order optimal 16x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p4o16x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46822774170144532 + even2 * 0.03177225758005808;
  fp_t c1 = odd1 * 0.55890365706150436 + odd2 * 0.14703258836343669;
  fp_t c2 = even1 * -0.250153411893796031 + even2 * 0.25015343462990891;
  fp_t c3 = odd1 * -0.49800710906733769 + odd2 * 0.16600005174304033;
  fp_t c4 = even1 * 0.00064264050033187 + even2 * -0.00064273459469381;
  return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
}

/*
 * @brief: 			4-point, 4th-order optimal 32x
 *					z-form
 */
template <typename fp_t>
fp_t interp_4p4o32x(fp_t x, fp_t y[4]) {
  fp_t z = x - 0.5;
  fp_t even1 = y[2] + y[1], odd1 = y[2] - y[1];
  fp_t even2 = y[3] + y[0], odd2 = y[3] - y[0];
  fp_t c0 = even1 * 0.46835497211269561 + even2 * 0.03164502784253309;
  fp_t c1 = odd1 * 0.56001293337091440 + odd2 * 0.14666238593949288;
  fp_t c2 = even1 * -0.250038759826233691 + even2 * 0.25003876124297131;
  fp_t c3 = odd1 * -0.49949850957839148 + odd2 * 0.16649935475113800;
  fp_t c4 = even1 * 0.00016095224137360 + even2 * -0.00016095810460478;
  return (((c4 * z + c3) * z + c2) * z + c1) * z + c0;
}

}; // !snd
