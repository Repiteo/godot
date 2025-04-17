/**************************************************************************/
/*  math_funcs.h                                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include "core/error/error_macros.h"
#include "core/math/math_defs.h"
#include "core/typedefs.h"

#include <float.h>
#include <math.h>

namespace Math {

GD_ALWAYS_INLINE double sin(double p_x) {
	return ::sin(p_x);
}
GD_ALWAYS_INLINE float sin(float p_x) {
	return ::sinf(p_x);
}

GD_ALWAYS_INLINE double cos(double p_x) {
	return ::cos(p_x);
}
GD_ALWAYS_INLINE float cos(float p_x) {
	return ::cosf(p_x);
}

GD_ALWAYS_INLINE double tan(double p_x) {
	return ::tan(p_x);
}
GD_ALWAYS_INLINE float tan(float p_x) {
	return ::tanf(p_x);
}

GD_ALWAYS_INLINE double sinh(double p_x) {
	return ::sinh(p_x);
}
GD_ALWAYS_INLINE float sinh(float p_x) {
	return ::sinhf(p_x);
}

GD_ALWAYS_INLINE double sinc(double p_x) {
	return p_x == 0 ? 1 : sin(p_x) / p_x;
}
GD_ALWAYS_INLINE float sinc(float p_x) {
	return p_x == 0 ? 1 : sin(p_x) / p_x;
}

GD_ALWAYS_INLINE double sincn(double p_x) {
	return sinc(PI * p_x);
}
GD_ALWAYS_INLINE float sincn(float p_x) {
	return sinc((float)PI * p_x);
}

GD_ALWAYS_INLINE double cosh(double p_x) {
	return ::cosh(p_x);
}
GD_ALWAYS_INLINE float cosh(float p_x) {
	return ::coshf(p_x);
}

GD_ALWAYS_INLINE double tanh(double p_x) {
	return ::tanh(p_x);
}
GD_ALWAYS_INLINE float tanh(float p_x) {
	return ::tanhf(p_x);
}

// Always does clamping so always safe to use.
GD_ALWAYS_INLINE double asin(double p_x) {
	return p_x < -1 ? (-PI / 2) : (p_x > 1 ? (PI / 2) : ::asin(p_x));
}
GD_ALWAYS_INLINE float asin(float p_x) {
	return p_x < -1 ? (-(float)PI / 2) : (p_x > 1 ? ((float)PI / 2) : ::asinf(p_x));
}

// Always does clamping so always safe to use.
GD_ALWAYS_INLINE double acos(double p_x) {
	return p_x < -1 ? PI : (p_x > 1 ? 0 : ::acos(p_x));
}
GD_ALWAYS_INLINE float acos(float p_x) {
	return p_x < -1 ? (float)PI : (p_x > 1 ? 0 : ::acosf(p_x));
}

GD_ALWAYS_INLINE double atan(double p_x) {
	return ::atan(p_x);
}
GD_ALWAYS_INLINE float atan(float p_x) {
	return ::atanf(p_x);
}

GD_ALWAYS_INLINE double atan2(double p_y, double p_x) {
	return ::atan2(p_y, p_x);
}
GD_ALWAYS_INLINE float atan2(float p_y, float p_x) {
	return ::atan2f(p_y, p_x);
}

GD_ALWAYS_INLINE double asinh(double p_x) {
	return ::asinh(p_x);
}
GD_ALWAYS_INLINE float asinh(float p_x) {
	return ::asinhf(p_x);
}

// Always does clamping so always safe to use.
GD_ALWAYS_INLINE double acosh(double p_x) {
	return p_x < 1 ? 0 : ::acosh(p_x);
}
GD_ALWAYS_INLINE float acosh(float p_x) {
	return p_x < 1 ? 0 : ::acoshf(p_x);
}

// Always does clamping so always safe to use.
GD_ALWAYS_INLINE double atanh(double p_x) {
	return p_x <= -1 ? -INF : (p_x >= 1 ? INF : ::atanh(p_x));
}
GD_ALWAYS_INLINE float atanh(float p_x) {
	return p_x <= -1 ? (float)-INF : (p_x >= 1 ? (float)INF : ::atanhf(p_x));
}

GD_ALWAYS_INLINE double sqrt(double p_x) {
	return ::sqrt(p_x);
}
GD_ALWAYS_INLINE float sqrt(float p_x) {
	return ::sqrtf(p_x);
}

GD_ALWAYS_INLINE double fmod(double p_x, double p_y) {
	return ::fmod(p_x, p_y);
}
GD_ALWAYS_INLINE float fmod(float p_x, float p_y) {
	return ::fmodf(p_x, p_y);
}

GD_ALWAYS_INLINE double modf(double p_x, double *r_y) {
	return ::modf(p_x, r_y);
}
GD_ALWAYS_INLINE float modf(float p_x, float *r_y) {
	return ::modff(p_x, r_y);
}

GD_ALWAYS_INLINE double floor(double p_x) {
	return ::floor(p_x);
}
GD_ALWAYS_INLINE float floor(float p_x) {
	return ::floorf(p_x);
}

GD_ALWAYS_INLINE double ceil(double p_x) {
	return ::ceil(p_x);
}
GD_ALWAYS_INLINE float ceil(float p_x) {
	return ::ceilf(p_x);
}

GD_ALWAYS_INLINE double pow(double p_x, double p_y) {
	return ::pow(p_x, p_y);
}
GD_ALWAYS_INLINE float pow(float p_x, float p_y) {
	return ::powf(p_x, p_y);
}

GD_ALWAYS_INLINE double log(double p_x) {
	return ::log(p_x);
}
GD_ALWAYS_INLINE float log(float p_x) {
	return ::logf(p_x);
}

GD_ALWAYS_INLINE double log1p(double p_x) {
	return ::log1p(p_x);
}
GD_ALWAYS_INLINE float log1p(float p_x) {
	return ::log1pf(p_x);
}

GD_ALWAYS_INLINE double log2(double p_x) {
	return ::log2(p_x);
}
GD_ALWAYS_INLINE float log2(float p_x) {
	return ::log2f(p_x);
}

GD_ALWAYS_INLINE double exp(double p_x) {
	return ::exp(p_x);
}
GD_ALWAYS_INLINE float exp(float p_x) {
	return ::expf(p_x);
}

GD_ALWAYS_INLINE bool is_nan(double p_val) {
#ifdef _MSC_VER
	return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint64_t u;
		double f;
	} ieee754;
	ieee754.f = p_val;
	// (unsigned)(0x7ff0000000000001 >> 32) : 0x7ff00000
	return ((((unsigned)(ieee754.u >> 32) & 0x7fffffff) + ((unsigned)ieee754.u != 0)) > 0x7ff00000);
#else
	return isnan(p_val);
#endif
}

GD_ALWAYS_INLINE bool is_nan(float p_val) {
#ifdef _MSC_VER
	return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint32_t u;
		float f;
	} ieee754;
	ieee754.f = p_val;
	// -----------------------------------
	// (single-precision floating-point)
	// NaN : s111 1111 1xxx xxxx xxxx xxxx xxxx xxxx
	//     : (> 0x7f800000)
	// where,
	//   s : sign
	//   x : non-zero number
	// -----------------------------------
	return ((ieee754.u & 0x7fffffff) > 0x7f800000);
#else
	return isnan(p_val);
#endif
}

GD_ALWAYS_INLINE bool is_inf(double p_val) {
#ifdef _MSC_VER
	return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint64_t u;
		double f;
	} ieee754;
	ieee754.f = p_val;
	return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
			((unsigned)ieee754.u == 0);
#else
	return isinf(p_val);
#endif
}

GD_ALWAYS_INLINE bool is_inf(float p_val) {
#ifdef _MSC_VER
	return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint32_t u;
		float f;
	} ieee754;
	ieee754.f = p_val;
	return (ieee754.u & 0x7fffffff) == 0x7f800000;
#else
	return isinf(p_val);
#endif
}

// These methods assume (p_num + p_den) doesn't overflow.
GD_ALWAYS_INLINE int32_t division_round_up(int32_t p_num, int32_t p_den) {
	int32_t offset = (p_num < 0 && p_den < 0) ? 1 : -1;
	return (p_num + p_den + offset) / p_den;
}
GD_ALWAYS_INLINE uint32_t division_round_up(uint32_t p_num, uint32_t p_den) {
	return (p_num + p_den - 1) / p_den;
}
GD_ALWAYS_INLINE int64_t division_round_up(int64_t p_num, int64_t p_den) {
	int32_t offset = (p_num < 0 && p_den < 0) ? 1 : -1;
	return (p_num + p_den + offset) / p_den;
}
GD_ALWAYS_INLINE uint64_t division_round_up(uint64_t p_num, uint64_t p_den) {
	return (p_num + p_den - 1) / p_den;
}

GD_ALWAYS_INLINE bool is_finite(double p_val) {
	return isfinite(p_val);
}
GD_ALWAYS_INLINE bool is_finite(float p_val) {
	return isfinite(p_val);
}

GD_ALWAYS_INLINE double absd(double p_value) {
	return ::fabs(p_value);
}
GD_ALWAYS_INLINE float absf(float p_value) {
	return ::fabsf(p_value);
}

GD_ALWAYS_INLINE double abs(double p_value) {
	return absd(p_value);
}
GD_ALWAYS_INLINE float abs(float p_value) {
	return absf(p_value);
}
GD_ALWAYS_INLINE int8_t abs(int8_t p_value) {
	return p_value > 0 ? p_value : -p_value;
}
GD_ALWAYS_INLINE int16_t abs(int16_t p_value) {
	return p_value > 0 ? p_value : -p_value;
}
GD_ALWAYS_INLINE int32_t abs(int32_t p_value) {
	return ::abs(p_value);
}
GD_ALWAYS_INLINE int64_t abs(int64_t p_value) {
	return ::llabs(p_value);
}

GD_ALWAYS_INLINE double fposmod(double p_x, double p_y) {
	double value = fmod(p_x, p_y);
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	value += 0.0;
	return value;
}
GD_ALWAYS_INLINE float fposmod(float p_x, float p_y) {
	float value = fmod(p_x, p_y);
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	value += 0.0f;
	return value;
}

GD_ALWAYS_INLINE double fposmodp(double p_x, double p_y) {
	double value = fmod(p_x, p_y);
	if (value < 0) {
		value += p_y;
	}
	value += 0.0;
	return value;
}
GD_ALWAYS_INLINE float fposmodp(float p_x, float p_y) {
	float value = fmod(p_x, p_y);
	if (value < 0) {
		value += p_y;
	}
	value += 0.0f;
	return value;
}

GD_ALWAYS_INLINE int64_t posmod(int64_t p_x, int64_t p_y) {
	ERR_FAIL_COND_V_MSG(p_y == 0, 0, "Division by zero in posmod is undefined. Returning 0 as fallback.");
	int64_t value = p_x % p_y;
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	return value;
}

GD_ALWAYS_INLINE double deg_to_rad(double p_y) {
	return p_y * (PI / 180.0);
}
GD_ALWAYS_INLINE float deg_to_rad(float p_y) {
	return p_y * ((float)PI / 180.0f);
}

GD_ALWAYS_INLINE double rad_to_deg(double p_y) {
	return p_y * (180.0 / PI);
}
GD_ALWAYS_INLINE float rad_to_deg(float p_y) {
	return p_y * (180.0f / (float)PI);
}

GD_ALWAYS_INLINE double lerp(double p_from, double p_to, double p_weight) {
	return p_from + (p_to - p_from) * p_weight;
}
GD_ALWAYS_INLINE float lerp(float p_from, float p_to, float p_weight) {
	return p_from + (p_to - p_from) * p_weight;
}

GD_ALWAYS_INLINE double cubic_interpolate(double p_from, double p_to, double p_pre, double p_post, double p_weight) {
	return 0.5 *
			((p_from * 2.0) +
					(-p_pre + p_to) * p_weight +
					(2.0 * p_pre - 5.0 * p_from + 4.0 * p_to - p_post) * (p_weight * p_weight) +
					(-p_pre + 3.0 * p_from - 3.0 * p_to + p_post) * (p_weight * p_weight * p_weight));
}
GD_ALWAYS_INLINE float cubic_interpolate(float p_from, float p_to, float p_pre, float p_post, float p_weight) {
	return 0.5f *
			((p_from * 2.0f) +
					(-p_pre + p_to) * p_weight +
					(2.0f * p_pre - 5.0f * p_from + 4.0f * p_to - p_post) * (p_weight * p_weight) +
					(-p_pre + 3.0f * p_from - 3.0f * p_to + p_post) * (p_weight * p_weight * p_weight));
}

GD_ALWAYS_INLINE double cubic_interpolate_angle(double p_from, double p_to, double p_pre, double p_post, double p_weight) {
	double from_rot = fmod(p_from, TAU);

	double pre_diff = fmod(p_pre - from_rot, TAU);
	double pre_rot = from_rot + fmod(2.0 * pre_diff, TAU) - pre_diff;

	double to_diff = fmod(p_to - from_rot, TAU);
	double to_rot = from_rot + fmod(2.0 * to_diff, TAU) - to_diff;

	double post_diff = fmod(p_post - to_rot, TAU);
	double post_rot = to_rot + fmod(2.0 * post_diff, TAU) - post_diff;

	return cubic_interpolate(from_rot, to_rot, pre_rot, post_rot, p_weight);
}

GD_ALWAYS_INLINE float cubic_interpolate_angle(float p_from, float p_to, float p_pre, float p_post, float p_weight) {
	float from_rot = fmod(p_from, (float)TAU);

	float pre_diff = fmod(p_pre - from_rot, (float)TAU);
	float pre_rot = from_rot + fmod(2.0f * pre_diff, (float)TAU) - pre_diff;

	float to_diff = fmod(p_to - from_rot, (float)TAU);
	float to_rot = from_rot + fmod(2.0f * to_diff, (float)TAU) - to_diff;

	float post_diff = fmod(p_post - to_rot, (float)TAU);
	float post_rot = to_rot + fmod(2.0f * post_diff, (float)TAU) - post_diff;

	return cubic_interpolate(from_rot, to_rot, pre_rot, post_rot, p_weight);
}

GD_ALWAYS_INLINE double cubic_interpolate_in_time(double p_from, double p_to, double p_pre, double p_post, double p_weight,
		double p_to_t, double p_pre_t, double p_post_t) {
	/* Barry-Goldman method */
	double t = lerp(0.0, p_to_t, p_weight);
	double a1 = lerp(p_pre, p_from, p_pre_t == 0 ? 0.0 : (t - p_pre_t) / -p_pre_t);
	double a2 = lerp(p_from, p_to, p_to_t == 0 ? 0.5 : t / p_to_t);
	double a3 = lerp(p_to, p_post, p_post_t - p_to_t == 0 ? 1.0 : (t - p_to_t) / (p_post_t - p_to_t));
	double b1 = lerp(a1, a2, p_to_t - p_pre_t == 0 ? 0.0 : (t - p_pre_t) / (p_to_t - p_pre_t));
	double b2 = lerp(a2, a3, p_post_t == 0 ? 1.0 : t / p_post_t);
	return lerp(b1, b2, p_to_t == 0 ? 0.5 : t / p_to_t);
}
GD_ALWAYS_INLINE float cubic_interpolate_in_time(float p_from, float p_to, float p_pre, float p_post, float p_weight,
		float p_to_t, float p_pre_t, float p_post_t) {
	/* Barry-Goldman method */
	float t = lerp(0.0f, p_to_t, p_weight);
	float a1 = lerp(p_pre, p_from, p_pre_t == 0 ? 0.0f : (t - p_pre_t) / -p_pre_t);
	float a2 = lerp(p_from, p_to, p_to_t == 0 ? 0.5f : t / p_to_t);
	float a3 = lerp(p_to, p_post, p_post_t - p_to_t == 0 ? 1.0f : (t - p_to_t) / (p_post_t - p_to_t));
	float b1 = lerp(a1, a2, p_to_t - p_pre_t == 0 ? 0.0f : (t - p_pre_t) / (p_to_t - p_pre_t));
	float b2 = lerp(a2, a3, p_post_t == 0 ? 1.0f : t / p_post_t);
	return lerp(b1, b2, p_to_t == 0 ? 0.5f : t / p_to_t);
}

GD_ALWAYS_INLINE double cubic_interpolate_angle_in_time(double p_from, double p_to, double p_pre, double p_post, double p_weight,
		double p_to_t, double p_pre_t, double p_post_t) {
	double from_rot = fmod(p_from, TAU);

	double pre_diff = fmod(p_pre - from_rot, TAU);
	double pre_rot = from_rot + fmod(2.0 * pre_diff, TAU) - pre_diff;

	double to_diff = fmod(p_to - from_rot, TAU);
	double to_rot = from_rot + fmod(2.0 * to_diff, TAU) - to_diff;

	double post_diff = fmod(p_post - to_rot, TAU);
	double post_rot = to_rot + fmod(2.0 * post_diff, TAU) - post_diff;

	return cubic_interpolate_in_time(from_rot, to_rot, pre_rot, post_rot, p_weight, p_to_t, p_pre_t, p_post_t);
}
GD_ALWAYS_INLINE float cubic_interpolate_angle_in_time(float p_from, float p_to, float p_pre, float p_post, float p_weight,
		float p_to_t, float p_pre_t, float p_post_t) {
	float from_rot = fmod(p_from, (float)TAU);

	float pre_diff = fmod(p_pre - from_rot, (float)TAU);
	float pre_rot = from_rot + fmod(2.0f * pre_diff, (float)TAU) - pre_diff;

	float to_diff = fmod(p_to - from_rot, (float)TAU);
	float to_rot = from_rot + fmod(2.0f * to_diff, (float)TAU) - to_diff;

	float post_diff = fmod(p_post - to_rot, (float)TAU);
	float post_rot = to_rot + fmod(2.0f * post_diff, (float)TAU) - post_diff;

	return cubic_interpolate_in_time(from_rot, to_rot, pre_rot, post_rot, p_weight, p_to_t, p_pre_t, p_post_t);
}

GD_ALWAYS_INLINE double bezier_interpolate(double p_start, double p_control_1, double p_control_2, double p_end, double p_t) {
	/* Formula from Wikipedia article on Bezier curves. */
	double omt = (1.0 - p_t);
	double omt2 = omt * omt;
	double omt3 = omt2 * omt;
	double t2 = p_t * p_t;
	double t3 = t2 * p_t;

	return p_start * omt3 + p_control_1 * omt2 * p_t * 3.0 + p_control_2 * omt * t2 * 3.0 + p_end * t3;
}
GD_ALWAYS_INLINE float bezier_interpolate(float p_start, float p_control_1, float p_control_2, float p_end, float p_t) {
	/* Formula from Wikipedia article on Bezier curves. */
	float omt = (1.0f - p_t);
	float omt2 = omt * omt;
	float omt3 = omt2 * omt;
	float t2 = p_t * p_t;
	float t3 = t2 * p_t;

	return p_start * omt3 + p_control_1 * omt2 * p_t * 3.0f + p_control_2 * omt * t2 * 3.0f + p_end * t3;
}

GD_ALWAYS_INLINE double bezier_derivative(double p_start, double p_control_1, double p_control_2, double p_end, double p_t) {
	/* Formula from Wikipedia article on Bezier curves. */
	double omt = (1.0 - p_t);
	double omt2 = omt * omt;
	double t2 = p_t * p_t;

	double d = (p_control_1 - p_start) * 3.0 * omt2 + (p_control_2 - p_control_1) * 6.0 * omt * p_t + (p_end - p_control_2) * 3.0 * t2;
	return d;
}
GD_ALWAYS_INLINE float bezier_derivative(float p_start, float p_control_1, float p_control_2, float p_end, float p_t) {
	/* Formula from Wikipedia article on Bezier curves. */
	float omt = (1.0f - p_t);
	float omt2 = omt * omt;
	float t2 = p_t * p_t;

	float d = (p_control_1 - p_start) * 3.0f * omt2 + (p_control_2 - p_control_1) * 6.0f * omt * p_t + (p_end - p_control_2) * 3.0f * t2;
	return d;
}

GD_ALWAYS_INLINE double angle_difference(double p_from, double p_to) {
	double difference = fmod(p_to - p_from, TAU);
	return fmod(2.0 * difference, TAU) - difference;
}
GD_ALWAYS_INLINE float angle_difference(float p_from, float p_to) {
	float difference = fmod(p_to - p_from, (float)TAU);
	return fmod(2.0f * difference, (float)TAU) - difference;
}

GD_ALWAYS_INLINE double lerp_angle(double p_from, double p_to, double p_weight) {
	return p_from + angle_difference(p_from, p_to) * p_weight;
}
GD_ALWAYS_INLINE float lerp_angle(float p_from, float p_to, float p_weight) {
	return p_from + angle_difference(p_from, p_to) * p_weight;
}

GD_ALWAYS_INLINE double inverse_lerp(double p_from, double p_to, double p_value) {
	return (p_value - p_from) / (p_to - p_from);
}
GD_ALWAYS_INLINE float inverse_lerp(float p_from, float p_to, float p_value) {
	return (p_value - p_from) / (p_to - p_from);
}

GD_ALWAYS_INLINE double remap(double p_value, double p_istart, double p_istop, double p_ostart, double p_ostop) {
	return lerp(p_ostart, p_ostop, inverse_lerp(p_istart, p_istop, p_value));
}
GD_ALWAYS_INLINE float remap(float p_value, float p_istart, float p_istop, float p_ostart, float p_ostop) {
	return lerp(p_ostart, p_ostop, inverse_lerp(p_istart, p_istop, p_value));
}

GD_ALWAYS_INLINE bool is_equal_approx(double p_left, double p_right, double p_tolerance) {
	// Check for exact equality first, required to handle "infinity" values.
	if (p_left == p_right) {
		return true;
	}
	// Then check for approximate equality.
	return abs(p_left - p_right) < p_tolerance;
}
GD_ALWAYS_INLINE bool is_equal_approx(float p_left, float p_right, float p_tolerance) {
	// Check for exact equality first, required to handle "infinity" values.
	if (p_left == p_right) {
		return true;
	}
	// Then check for approximate equality.
	return abs(p_left - p_right) < p_tolerance;
}

GD_ALWAYS_INLINE bool is_equal_approx(double p_left, double p_right) {
	// Check for exact equality first, required to handle "infinity" values.
	if (p_left == p_right) {
		return true;
	}
	// Then check for approximate equality.
	double tolerance = CMP_EPSILON * abs(p_left);
	if (tolerance < CMP_EPSILON) {
		tolerance = CMP_EPSILON;
	}
	return abs(p_left - p_right) < tolerance;
}
GD_ALWAYS_INLINE bool is_equal_approx(float p_left, float p_right) {
	// Check for exact equality first, required to handle "infinity" values.
	if (p_left == p_right) {
		return true;
	}
	// Then check for approximate equality.
	float tolerance = (float)CMP_EPSILON * abs(p_left);
	if (tolerance < (float)CMP_EPSILON) {
		tolerance = (float)CMP_EPSILON;
	}
	return abs(p_left - p_right) < tolerance;
}

GD_ALWAYS_INLINE bool is_zero_approx(double p_value) {
	return abs(p_value) < CMP_EPSILON;
}
GD_ALWAYS_INLINE bool is_zero_approx(float p_value) {
	return abs(p_value) < (float)CMP_EPSILON;
}

GD_ALWAYS_INLINE bool is_same(double p_left, double p_right) {
	return (p_left == p_right) || (is_nan(p_left) && is_nan(p_right));
}
GD_ALWAYS_INLINE bool is_same(float p_left, float p_right) {
	return (p_left == p_right) || (is_nan(p_left) && is_nan(p_right));
}

GD_ALWAYS_INLINE double smoothstep(double p_from, double p_to, double p_s) {
	if (is_equal_approx(p_from, p_to)) {
		if (likely(p_from <= p_to)) {
			return p_s <= p_from ? 0.0 : 1.0;
		} else {
			return p_s <= p_to ? 1.0 : 0.0;
		}
	}
	double s = CLAMP((p_s - p_from) / (p_to - p_from), 0.0, 1.0);
	return s * s * (3.0 - 2.0 * s);
}
GD_ALWAYS_INLINE float smoothstep(float p_from, float p_to, float p_s) {
	if (is_equal_approx(p_from, p_to)) {
		if (likely(p_from <= p_to)) {
			return p_s <= p_from ? 0.0f : 1.0f;
		} else {
			return p_s <= p_to ? 1.0f : 0.0f;
		}
	}
	float s = CLAMP((p_s - p_from) / (p_to - p_from), 0.0f, 1.0f);
	return s * s * (3.0f - 2.0f * s);
}

GD_ALWAYS_INLINE double move_toward(double p_from, double p_to, double p_delta) {
	return abs(p_to - p_from) <= p_delta ? p_to : p_from + SIGN(p_to - p_from) * p_delta;
}
GD_ALWAYS_INLINE float move_toward(float p_from, float p_to, float p_delta) {
	return abs(p_to - p_from) <= p_delta ? p_to : p_from + SIGN(p_to - p_from) * p_delta;
}

GD_ALWAYS_INLINE double rotate_toward(double p_from, double p_to, double p_delta) {
	double difference = angle_difference(p_from, p_to);
	double abs_difference = abs(difference);
	// When `p_delta < 0` move no further than to PI radians away from `p_to` (as PI is the max possible angle distance).
	return p_from + CLAMP(p_delta, abs_difference - PI, abs_difference) * (difference >= 0.0 ? 1.0 : -1.0);
}
GD_ALWAYS_INLINE float rotate_toward(float p_from, float p_to, float p_delta) {
	float difference = angle_difference(p_from, p_to);
	float abs_difference = abs(difference);
	// When `p_delta < 0` move no further than to PI radians away from `p_to` (as PI is the max possible angle distance).
	return p_from + CLAMP(p_delta, abs_difference - (float)PI, abs_difference) * (difference >= 0.0f ? 1.0f : -1.0f);
}

GD_ALWAYS_INLINE double linear_to_db(double p_linear) {
	return log(p_linear) * 8.6858896380650365530225783783321;
}
GD_ALWAYS_INLINE float linear_to_db(float p_linear) {
	return log(p_linear) * (float)8.6858896380650365530225783783321;
}

GD_ALWAYS_INLINE double db_to_linear(double p_db) {
	return exp(p_db * 0.11512925464970228420089957273422);
}
GD_ALWAYS_INLINE float db_to_linear(float p_db) {
	return exp(p_db * (float)0.11512925464970228420089957273422);
}

GD_ALWAYS_INLINE double round(double p_val) {
	return ::round(p_val);
}
GD_ALWAYS_INLINE float round(float p_val) {
	return ::roundf(p_val);
}

GD_ALWAYS_INLINE double wrapf(double p_value, double p_min, double p_max) {
	double range = p_max - p_min;
	if (is_zero_approx(range)) {
		return p_min;
	}
	double result = p_value - (range * floor((p_value - p_min) / range));
	if (is_equal_approx(result, p_max)) {
		return p_min;
	}
	return result;
}
GD_ALWAYS_INLINE float wrapf(float p_value, float p_min, float p_max) {
	float range = p_max - p_min;
	if (is_zero_approx(range)) {
		return p_min;
	}
	float result = p_value - (range * floor((p_value - p_min) / range));
	if (is_equal_approx(result, p_max)) {
		return p_min;
	}
	return result;
}

GD_ALWAYS_INLINE int64_t wrapi(int64_t p_value, int64_t p_min, int64_t p_max) {
	int64_t range = p_max - p_min;
	return range == 0 ? p_min : p_min + ((((p_value - p_min) % range) + range) % range);
}

GD_ALWAYS_INLINE double fract(double p_value) {
	return p_value - floor(p_value);
}
GD_ALWAYS_INLINE float fract(float p_value) {
	return p_value - floor(p_value);
}

GD_ALWAYS_INLINE double pingpong(double p_value, double p_length) {
	return (p_length != 0.0) ? abs(fract((p_value - p_length) / (p_length * 2.0)) * p_length * 2.0 - p_length) : 0.0;
}
GD_ALWAYS_INLINE float pingpong(float p_value, float p_length) {
	return (p_length != 0.0f) ? abs(fract((p_value - p_length) / (p_length * 2.0f)) * p_length * 2.0f - p_length) : 0.0f;
}

// double only, as these functions are mainly used by the editor and not performance-critical,
double ease(double p_x, double p_c);
int step_decimals(double p_step);
int range_step_decimals(double p_step); // For editor use only.
double snapped(double p_value, double p_step);

uint32_t larger_prime(uint32_t p_val);

void seed(uint64_t p_seed);
void randomize();
uint32_t rand_from_seed(uint64_t *p_seed);
uint32_t rand();
GD_ALWAYS_INLINE double randd() {
	return (double)rand() / (double)UINT32_MAX;
}
GD_ALWAYS_INLINE float randf() {
	return (float)rand() / (float)UINT32_MAX;
}
double randfn(double p_mean, double p_deviation);

double random(double p_from, double p_to);
float random(float p_from, float p_to);
int random(int p_from, int p_to);

// This function should be as fast as possible and rounding mode should not matter.
GD_ALWAYS_INLINE int fast_ftoi(float p_value) {
	// Assuming every supported compiler has `lrint()`.
	return lrintf(p_value);
}

GD_ALWAYS_INLINE uint32_t halfbits_to_floatbits(uint16_t p_half) {
	uint16_t h_exp, h_sig;
	uint32_t f_sgn, f_exp, f_sig;

	h_exp = (p_half & 0x7c00u);
	f_sgn = ((uint32_t)p_half & 0x8000u) << 16;
	switch (h_exp) {
		case 0x0000u: /* 0 or subnormal */
			h_sig = (p_half & 0x03ffu);
			/* Signed zero */
			if (h_sig == 0) {
				return f_sgn;
			}
			/* Subnormal */
			h_sig <<= 1;
			while ((h_sig & 0x0400u) == 0) {
				h_sig <<= 1;
				h_exp++;
			}
			f_exp = ((uint32_t)(127 - 15 - h_exp)) << 23;
			f_sig = ((uint32_t)(h_sig & 0x03ffu)) << 13;
			return f_sgn + f_exp + f_sig;
		case 0x7c00u: /* inf or NaN */
			/* All-ones exponent and a copy of the significand */
			return f_sgn + 0x7f800000u + (((uint32_t)(p_half & 0x03ffu)) << 13);
		default: /* normalized */
			/* Just need to adjust the exponent and shift */
			return f_sgn + (((uint32_t)(p_half & 0x7fffu) + 0x1c000u) << 13);
	}
}

GD_ALWAYS_INLINE float halfptr_to_float(const uint16_t *p_half) {
	union {
		uint32_t u32;
		float f32;
	} u;

	u.u32 = halfbits_to_floatbits(*p_half);
	return u.f32;
}

GD_ALWAYS_INLINE float half_to_float(const uint16_t p_half) {
	return halfptr_to_float(&p_half);
}

GD_ALWAYS_INLINE uint16_t make_half_float(float p_value) {
	union {
		float fv;
		uint32_t ui;
	} ci;
	ci.fv = p_value;

	uint32_t x = ci.ui;
	uint32_t sign = (unsigned short)(x >> 31);
	uint32_t mantissa;
	uint32_t exponent;
	uint16_t hf;

	// get mantissa
	mantissa = x & ((1 << 23) - 1);
	// get exponent bits
	exponent = x & (0xFF << 23);
	if (exponent >= 0x47800000) {
		// check if the original single precision float number is a NaN
		if (mantissa && (exponent == (0xFF << 23))) {
			// we have a single precision NaN
			mantissa = (1 << 23) - 1;
		} else {
			// 16-bit half-float representation stores number as Inf
			mantissa = 0;
		}
		hf = (((uint16_t)sign) << 15) | (uint16_t)((0x1F << 10)) |
				(uint16_t)(mantissa >> 13);
	}
	// check if exponent is <= -15
	else if (exponent <= 0x38000000) {
		/*
		// store a denorm half-float value or zero
		exponent = (0x38000000 - exponent) >> 23;
		mantissa >>= (14 + exponent);

		hf = (((uint16_t)sign) << 15) | (uint16_t)(mantissa);
		*/
		hf = 0; //denormals do not work for 3D, convert to zero
	} else {
		hf = (((uint16_t)sign) << 15) |
				(uint16_t)((exponent - 0x38000000) >> 13) |
				(uint16_t)(mantissa >> 13);
	}

	return hf;
}

GD_ALWAYS_INLINE float snap_scalar(float p_offset, float p_step, float p_target) {
	return p_step != 0 ? snapped(p_target - p_offset, p_step) + p_offset : p_target;
}

GD_ALWAYS_INLINE float snap_scalar_separation(float p_offset, float p_step, float p_target, float p_separation) {
	if (p_step != 0) {
		float a = snapped(p_target - p_offset, p_step + p_separation) + p_offset;
		float b = a;
		if (p_target >= 0) {
			b -= p_separation;
		} else {
			b += p_step;
		}
		return (abs(p_target - a) < abs(p_target - b)) ? a : b;
	}
	return p_target;
}

}; // namespace Math
