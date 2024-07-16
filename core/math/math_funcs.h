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

#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include "core/error/error_macros.h"
#include "core/math/math_defs.h"
#include "core/typedefs.h"

#include <float.h>
#include <math.h>

#include <limits>

namespace Math {

template <typename T>
[[nodiscard]] constexpr T abs(T p_value) {
	return p_value == T(0) ? T(0) : (p_value < T(0) ? -p_value : p_value);
}

template <typename T>
[[nodiscard]] constexpr T sign(T p_value) {
	return p_value > T(0) ? T(1) : (p_value < T(0) ? T(-1) : T(0));
}

template <typename T>
[[nodiscard]] constexpr T min(T p_left, T p_right) {
	return p_left < p_right ? p_left : p_right;
}

template <typename T>
[[nodiscard]] constexpr T max(T p_left, T p_right) {
	return p_left > p_right ? p_left : p_right;
}

template <typename T>
[[nodiscard]] constexpr T clamp(T p_value, T p_min, T p_max) {
	return p_value < p_min ? p_min : (p_value > p_max ? p_max : p_value);
}

#define MATH_BUILDER(type_t) /***************************************************************************************************************************************************/ \
	[[nodiscard]] constexpr bool is_nan(type_t p_value) {                                                                                                                          \
		return p_value != p_value;                                                                                                                                                 \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr bool is_inf(type_t p_value) {                                                                                                                          \
		return p_value == std::numeric_limits<type_t>::infinity() || p_value == -std::numeric_limits<type_t>::infinity();                                                          \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr bool is_finite(type_t p_value) {                                                                                                                       \
		return !is_nan(p_value) && !is_inf(p_value);                                                                                                                               \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t ceil(type_t p_value) {                                                                                                                          \
		if (!is_finite(p_value) || std::numeric_limits<type_t>::min() > abs(p_value)) {                                                                                            \
			return p_value;                                                                                                                                                        \
		}                                                                                                                                                                          \
		const type_t whole = static_cast<type_t>(static_cast<int64_t>(p_value));                                                                                                   \
		return whole + static_cast<int>(p_value > type_t(0) && p_value > whole);                                                                                                   \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t floor(type_t p_value) {                                                                                                                         \
		if (!is_finite(p_value) || std::numeric_limits<type_t>::min() > abs(p_value)) {                                                                                            \
			return p_value;                                                                                                                                                        \
		}                                                                                                                                                                          \
		const type_t whole = static_cast<type_t>(static_cast<int64_t>(p_value));                                                                                                   \
		return whole - static_cast<int>(p_value < type_t(0) && p_value < whole);                                                                                                   \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t round(type_t p_value) {                                                                                                                         \
		if (!is_finite(p_value) || std::numeric_limits<type_t>::min() > abs(p_value)) {                                                                                            \
			return p_value;                                                                                                                                                        \
		}                                                                                                                                                                          \
		const type_t floored = floor(abs(p_value));                                                                                                                                \
		return sign(p_value) * (floored + static_cast<int>(abs(abs(p_value) - floored) >= type_t(0.5)));                                                                           \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t lerp(type_t p_from, type_t p_to, type_t p_weight) {                                                                                             \
		return p_from + (p_to - p_from) * p_weight;                                                                                                                                \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t inverse_lerp(type_t p_from, type_t p_to, type_t p_value) {                                                                                      \
		return (p_value - p_from) / (p_to - p_from);                                                                                                                               \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t remap(type_t p_value, type_t p_istart, type_t p_istop, type_t p_ostart, type_t p_ostop) {                                                       \
		return lerp(p_ostart, p_ostop, inverse_lerp(p_istart, p_istop, p_value));                                                                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr bool is_equal_approx(type_t p_left, type_t p_right, type_t p_tolerance) {                                                                              \
		return p_left == p_right ? true : abs(p_left - p_right) < p_tolerance;                                                                                                     \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr bool is_equal_approx(type_t p_left, type_t p_right) {                                                                                                  \
		return p_left == p_right ? true : abs(p_left - p_right) < max<type_t>(CMP_EPSILON, CMP_EPSILON * abs(p_left));                                                             \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr bool is_zero_approx(type_t p_value) {                                                                                                                  \
		return abs(p_value) < static_cast<type_t>(CMP_EPSILON);                                                                                                                    \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t deg_to_rad(type_t p_value) {                                                                                                                    \
		constexpr type_t DEG2RAD = static_cast<type_t>(Math_PI) / 180;                                                                                                             \
		return p_value * DEG2RAD;                                                                                                                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t rad_to_deg(type_t p_value) {                                                                                                                    \
		constexpr type_t RAD2DEG = 180 / static_cast<type_t>(Math_PI);                                                                                                             \
		return p_value * RAD2DEG;                                                                                                                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t fmod(type_t p_x, type_t p_y) {                                                                                                                  \
		return is_finite(p_x) || is_finite(p_y) ? std::numeric_limits<type_t>::quiet_NaN() : p_x - static_cast<int64_t>(p_x / p_y) * p_y;                                          \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t fposmod(type_t p_x, type_t p_y) {                                                                                                               \
		type_t value = fmod(p_x, p_y);                                                                                                                                             \
		if ((value < 0 && p_y > 0) || (value > 0 && p_y < 0)) {                                                                                                                    \
			value += p_y;                                                                                                                                                          \
		}                                                                                                                                                                          \
		return value + type_t(0);                                                                                                                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t fposmodp(type_t p_x, type_t p_y) {                                                                                                              \
		type_t value = fmod(p_x, p_y);                                                                                                                                             \
		if (value < 0) {                                                                                                                                                           \
			value += p_y;                                                                                                                                                          \
		}                                                                                                                                                                          \
		return value + type_t(0);                                                                                                                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t cubic_interpolate(type_t p_from, type_t p_to, type_t p_pre, type_t p_post, type_t p_weight) {                                                   \
		return type_t(0.5) *                                                                                                                                                       \
				((p_from * 2) +                                                                                                                                                    \
						(-p_pre + p_to) * p_weight +                                                                                                                               \
						(2 * p_pre - 5 * p_from + 4 * p_to - p_post) * (p_weight * p_weight) +                                                                                     \
						(-p_pre + 3 * p_from - 3 * p_to + p_post) * (p_weight * p_weight * p_weight));                                                                             \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t cubic_interpolate_angle(type_t p_from, type_t p_to, type_t p_pre, type_t p_post, type_t p_weight) {                                             \
		const type_t from_rot = fmod(p_from, type_t(Math_TAU));                                                                                                                    \
                                                                                                                                                                                   \
		const type_t pre_diff = fmod(p_pre - from_rot, type_t(Math_TAU));                                                                                                          \
		const type_t pre_rot = from_rot + fmod(2 * pre_diff, type_t(Math_TAU)) - pre_diff;                                                                                         \
                                                                                                                                                                                   \
		const type_t to_diff = fmod(p_to - from_rot, type_t(Math_TAU));                                                                                                            \
		const type_t to_rot = from_rot + fmod(2 * to_diff, type_t(Math_TAU)) - to_diff;                                                                                            \
                                                                                                                                                                                   \
		const type_t post_diff = fmod(p_post - to_rot, type_t(Math_TAU));                                                                                                          \
		const type_t post_rot = to_rot + fmod(2 * post_diff, type_t(Math_TAU)) - post_diff;                                                                                        \
                                                                                                                                                                                   \
		return cubic_interpolate(from_rot, to_rot, pre_rot, post_rot, p_weight);                                                                                                   \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t cubic_interpolate_in_time(type_t p_from, type_t p_to, type_t p_pre, type_t p_post, type_t p_weight,                                             \
			type_t p_to_t, type_t p_pre_t, type_t p_post_t) {                                                                                                                      \
		/* Barry-Goldman method */                                                                                                                                                 \
		const type_t t = lerp(0, p_to_t, p_weight);                                                                                                                                \
		const type_t a1 = lerp(p_pre, p_from, p_pre_t == 0 ? 0 : (t - p_pre_t) / -p_pre_t);                                                                                        \
		const type_t a2 = lerp(p_from, p_to, p_to_t == 0 ? type_t(0.5) : t / p_to_t);                                                                                              \
		const type_t a3 = lerp(p_to, p_post, p_post_t - p_to_t == 0 ? 1 : (t - p_to_t) / (p_post_t - p_to_t));                                                                     \
		const type_t b1 = lerp(a1, a2, p_to_t - p_pre_t == 0 ? 0 : (t - p_pre_t) / (p_to_t - p_pre_t));                                                                            \
		const type_t b2 = lerp(a2, a3, p_post_t == 0 ? 1 : t / p_post_t);                                                                                                          \
		return lerp(b1, b2, p_to_t == 0 ? type_t(0.5) : t / p_to_t);                                                                                                               \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t cubic_interpolate_angle_in_time(type_t p_from, type_t p_to, type_t p_pre, type_t p_post, type_t p_weight,                                       \
			type_t p_to_t, type_t p_pre_t, type_t p_post_t) {                                                                                                                      \
		const type_t from_rot = fmod(p_from, type_t(Math_TAU));                                                                                                                    \
                                                                                                                                                                                   \
		const type_t pre_diff = fmod(p_pre - from_rot, type_t(Math_TAU));                                                                                                          \
		const type_t pre_rot = from_rot + fmod(2 * pre_diff, type_t(Math_TAU)) - pre_diff;                                                                                         \
                                                                                                                                                                                   \
		const type_t to_diff = fmod(p_to - from_rot, type_t(Math_TAU));                                                                                                            \
		const type_t to_rot = from_rot + fmod(2 * to_diff, type_t(Math_TAU)) - to_diff;                                                                                            \
                                                                                                                                                                                   \
		const type_t post_diff = fmod(p_post - to_rot, type_t(Math_TAU));                                                                                                          \
		const type_t post_rot = to_rot + fmod(2 * post_diff, type_t(Math_TAU)) - post_diff;                                                                                        \
                                                                                                                                                                                   \
		return cubic_interpolate_in_time(from_rot, to_rot, pre_rot, post_rot, p_weight, p_to_t, p_pre_t, p_post_t);                                                                \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t bezier_interpolate(type_t p_start, type_t p_control_1, type_t p_control_2, type_t p_end, type_t p_t) {                                          \
		/* Formula from Wikipedia article on Bezier curves. */                                                                                                                     \
		const type_t omt = (1 - p_t);                                                                                                                                              \
		const type_t omt2 = omt * omt;                                                                                                                                             \
		const type_t omt3 = omt2 * omt;                                                                                                                                            \
		const type_t t2 = p_t * p_t;                                                                                                                                               \
		const type_t t3 = t2 * p_t;                                                                                                                                                \
                                                                                                                                                                                   \
		return p_start * omt3 + p_control_1 * omt2 * p_t * 3 + p_control_2 * omt * t2 * 3 + p_end * t3;                                                                            \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t bezier_derivative(type_t p_start, type_t p_control_1, type_t p_control_2, type_t p_end, type_t p_t) {                                           \
		/* Formula from Wikipedia article on Bezier curves. */                                                                                                                     \
		const type_t omt = (1 - p_t);                                                                                                                                              \
		const type_t omt2 = omt * omt;                                                                                                                                             \
		const type_t t2 = p_t * p_t;                                                                                                                                               \
                                                                                                                                                                                   \
		return (p_control_1 - p_start) * 3 * omt2 + (p_control_2 - p_control_1) * 6 * omt * p_t + (p_end - p_control_2) * 3 * t2;                                                  \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t angle_difference(type_t p_from, type_t p_to) {                                                                                                  \
		const type_t difference = fmod(p_to - p_from, type_t(Math_TAU));                                                                                                           \
		return fmod(2 * difference, type_t(Math_TAU)) - difference;                                                                                                                \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t lerp_angle(type_t p_from, type_t p_to, type_t p_weight) {                                                                                       \
		return p_from + angle_difference(p_from, p_to) * p_weight;                                                                                                                 \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t smoothstep(type_t p_from, type_t p_to, type_t p_s) {                                                                                            \
		if (is_equal_approx(p_from, p_to)) {                                                                                                                                       \
			return p_from;                                                                                                                                                         \
		}                                                                                                                                                                          \
		const type_t s = clamp<type_t>((p_s - p_from) / (p_to - p_from), 0, 1);                                                                                                    \
		return s * s * (3 - 2 * s);                                                                                                                                                \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t move_toward(type_t p_from, type_t p_to, type_t p_delta) {                                                                                       \
		return abs(p_to - p_from) <= p_delta ? p_to : p_from + sign(p_to - p_from) * p_delta;                                                                                      \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t rotate_toward(type_t p_from, type_t p_to, type_t p_delta) {                                                                                     \
		const type_t difference = angle_difference(p_from, p_to);                                                                                                                  \
		const type_t abs_difference = abs(difference);                                                                                                                             \
		/* When `p_delta < 0` move no further than to PI radians away from `p_to` (as PI is the max possible angle distance). */                                                   \
		return p_from + clamp<type_t>(p_delta, abs_difference - Math_PI, abs_difference) * (difference >= 0 ? 1 : -1);                                                             \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t wrapf(type_t value, type_t min, type_t max) {                                                                                                   \
		const type_t range = max - min;                                                                                                                                            \
		if (is_zero_approx(range)) {                                                                                                                                               \
			return min;                                                                                                                                                            \
		}                                                                                                                                                                          \
		const type_t result = value - (range * floor((value - min) / range));                                                                                                      \
		return is_equal_approx(result, max) ? min : result;                                                                                                                        \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t fract(type_t value) {                                                                                                                           \
		return value - floor(value);                                                                                                                                               \
	}                                                                                                                                                                              \
                                                                                                                                                                                   \
	[[nodiscard]] constexpr type_t pingpong(type_t value, type_t length) {                                                                                                         \
		return (length != 0) ? abs(fract((value - length) / (length * 2)) * length * 2 - length) : 0;                                                                              \
	}

MATH_BUILDER(double)
MATH_BUILDER(float)

#undef MATH_BUILDER

_ALWAYS_INLINE_ double sin(double p_x) { return ::sin(p_x); }
_ALWAYS_INLINE_ float sin(float p_x) { return ::sinf(p_x); }

_ALWAYS_INLINE_ double cos(double p_x) { return ::cos(p_x); }
_ALWAYS_INLINE_ float cos(float p_x) { return ::cosf(p_x); }

_ALWAYS_INLINE_ double tan(double p_x) { return ::tan(p_x); }
_ALWAYS_INLINE_ float tan(float p_x) { return ::tanf(p_x); }

_ALWAYS_INLINE_ double sinh(double p_x) { return ::sinh(p_x); }
_ALWAYS_INLINE_ float sinh(float p_x) { return ::sinhf(p_x); }

_ALWAYS_INLINE_ float sinc(float p_x) { return p_x == 0 ? 1 : sin(p_x) / p_x; }
_ALWAYS_INLINE_ double sinc(double p_x) { return p_x == 0 ? 1 : sin(p_x) / p_x; }

_ALWAYS_INLINE_ float sincn(float p_x) { return sinc((float)Math_PI * p_x); }
_ALWAYS_INLINE_ double sincn(double p_x) { return sinc(Math_PI * p_x); }

_ALWAYS_INLINE_ double cosh(double p_x) { return ::cosh(p_x); }
_ALWAYS_INLINE_ float cosh(float p_x) { return ::coshf(p_x); }

_ALWAYS_INLINE_ double tanh(double p_x) { return ::tanh(p_x); }
_ALWAYS_INLINE_ float tanh(float p_x) { return ::tanhf(p_x); }

// Always does clamping so always safe to use.
_ALWAYS_INLINE_ double asin(double p_x) { return p_x < -1 ? (-Math_PI / 2) : (p_x > 1 ? (Math_PI / 2) : ::asin(p_x)); }
_ALWAYS_INLINE_ float asin(float p_x) { return p_x < -1 ? (-Math_PI / 2) : (p_x > 1 ? (Math_PI / 2) : ::asinf(p_x)); }

// Always does clamping so always safe to use.
_ALWAYS_INLINE_ double acos(double p_x) { return p_x < -1 ? Math_PI : (p_x > 1 ? 0 : ::acos(p_x)); }
_ALWAYS_INLINE_ float acos(float p_x) { return p_x < -1 ? Math_PI : (p_x > 1 ? 0 : ::acosf(p_x)); }

_ALWAYS_INLINE_ double atan(double p_x) { return ::atan(p_x); }
_ALWAYS_INLINE_ float atan(float p_x) { return ::atanf(p_x); }

_ALWAYS_INLINE_ double atan2(double p_y, double p_x) { return ::atan2(p_y, p_x); }
_ALWAYS_INLINE_ float atan2(float p_y, float p_x) { return ::atan2f(p_y, p_x); }

_ALWAYS_INLINE_ double asinh(double p_x) { return ::asinh(p_x); }
_ALWAYS_INLINE_ float asinh(float p_x) { return ::asinhf(p_x); }

// Always does clamping so always safe to use.
_ALWAYS_INLINE_ double acosh(double p_x) { return p_x < 1 ? 0 : ::acosh(p_x); }
_ALWAYS_INLINE_ float acosh(float p_x) { return p_x < 1 ? 0 : ::acoshf(p_x); }

// Always does clamping so always safe to use.
_ALWAYS_INLINE_ double atanh(double p_x) { return p_x <= -1 ? -INFINITY : (p_x >= 1 ? INFINITY : ::atanh(p_x)); }
_ALWAYS_INLINE_ float atanh(float p_x) { return p_x <= -1 ? -INFINITY : (p_x >= 1 ? INFINITY : ::atanhf(p_x)); }

_ALWAYS_INLINE_ double sqrt(double p_x) { return ::sqrt(p_x); }
_ALWAYS_INLINE_ float sqrt(float p_x) { return ::sqrtf(p_x); }

_ALWAYS_INLINE_ double pow(double p_x, double p_y) { return ::pow(p_x, p_y); }
_ALWAYS_INLINE_ float pow(float p_x, float p_y) { return ::powf(p_x, p_y); }

_ALWAYS_INLINE_ double log(double p_x) { return ::log(p_x); }
_ALWAYS_INLINE_ float log(float p_x) { return ::logf(p_x); }

_ALWAYS_INLINE_ double log1p(double p_x) { return ::log1p(p_x); }
_ALWAYS_INLINE_ float log1p(float p_x) { return ::log1pf(p_x); }

_ALWAYS_INLINE_ double log2(double p_x) { return ::log2(p_x); }
_ALWAYS_INLINE_ float log2(float p_x) { return ::log2f(p_x); }

_ALWAYS_INLINE_ double exp(double p_x) { return ::exp(p_x); }
_ALWAYS_INLINE_ float exp(float p_x) { return ::expf(p_x); }

// These methods assume (p_num + p_den) doesn't overflow.
_ALWAYS_INLINE_ int32_t division_round_up(int32_t p_num, int32_t p_den) {
	int32_t offset = (p_num < 0 && p_den < 0) ? 1 : -1;
	return (p_num + p_den + offset) / p_den;
}
_ALWAYS_INLINE_ uint32_t division_round_up(uint32_t p_num, uint32_t p_den) {
	return (p_num + p_den - 1) / p_den;
}
_ALWAYS_INLINE_ int64_t division_round_up(int64_t p_num, int64_t p_den) {
	int32_t offset = (p_num < 0 && p_den < 0) ? 1 : -1;
	return (p_num + p_den + offset) / p_den;
}
_ALWAYS_INLINE_ uint64_t division_round_up(uint64_t p_num, uint64_t p_den) {
	return (p_num + p_den - 1) / p_den;
}

_ALWAYS_INLINE_ int64_t posmod(int64_t p_x, int64_t p_y) {
	ERR_FAIL_COND_V_MSG(p_y == 0, 0, "Division by zero in posmod is undefined. Returning 0 as fallback.");
	int64_t value = p_x % p_y;
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	return value;
}

_ALWAYS_INLINE_ double linear_to_db(double p_linear) {
	return Math::log(p_linear) * 8.6858896380650365530225783783321;
}
_ALWAYS_INLINE_ float linear_to_db(float p_linear) {
	return Math::log(p_linear) * (float)8.6858896380650365530225783783321;
}

_ALWAYS_INLINE_ double db_to_linear(double p_db) {
	return Math::exp(p_db * 0.11512925464970228420089957273422);
}
_ALWAYS_INLINE_ float db_to_linear(float p_db) {
	return Math::exp(p_db * (float)0.11512925464970228420089957273422);
}

_ALWAYS_INLINE_ int64_t wrapi(int64_t value, int64_t min, int64_t max) {
	int64_t range = max - min;
	return range == 0 ? min : min + ((((value - min) % range) + range) % range);
}

// double only, as these functions are mainly used by the editor and not performance-critical,
double ease(double p_x, double p_c);
int step_decimals(double p_step);
int range_step_decimals(double p_step); // For editor use only.
double snapped(double p_value, double p_step);

uint32_t larger_prime(uint32_t p_val);

void seed(uint64_t x);
void randomize();
uint32_t rand_from_seed(uint64_t *seed);
uint32_t rand();
_ALWAYS_INLINE_ double randd() { return (double)rand() / (double)UINT32_MAX; }
_ALWAYS_INLINE_ float randf() { return (float)rand() / (float)UINT32_MAX; }
double randfn(double mean, double deviation);

double random(double from, double to);
float random(float from, float to);
int random(int from, int to);

// This function should be as fast as possible and rounding mode should not matter.
_ALWAYS_INLINE_ int fast_ftoi(float a) {
	// Assuming every supported compiler has `lrint()`.
	return lrintf(a);
}

_ALWAYS_INLINE_ uint32_t halfbits_to_floatbits(uint16_t h) {
	uint16_t h_exp, h_sig;
	uint32_t f_sgn, f_exp, f_sig;

	h_exp = (h & 0x7c00u);
	f_sgn = ((uint32_t)h & 0x8000u) << 16;
	switch (h_exp) {
		case 0x0000u: /* 0 or subnormal */
			h_sig = (h & 0x03ffu);
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
			return f_sgn + 0x7f800000u + (((uint32_t)(h & 0x03ffu)) << 13);
		default: /* normalized */
			/* Just need to adjust the exponent and shift */
			return f_sgn + (((uint32_t)(h & 0x7fffu) + 0x1c000u) << 13);
	}
}

_ALWAYS_INLINE_ float halfptr_to_float(const uint16_t *h) {
	union {
		uint32_t u32;
		float f32;
	} u;

	u.u32 = halfbits_to_floatbits(*h);
	return u.f32;
}

_ALWAYS_INLINE_ float half_to_float(const uint16_t h) {
	return halfptr_to_float(&h);
}

_ALWAYS_INLINE_ uint16_t make_half_float(float f) {
	union {
		float fv;
		uint32_t ui;
	} ci;
	ci.fv = f;

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

_ALWAYS_INLINE_ float snap_scalar(float p_offset, float p_step, float p_target) {
	return p_step != 0 ? Math::snapped(p_target - p_offset, p_step) + p_offset : p_target;
}

_ALWAYS_INLINE_ float snap_scalar_separation(float p_offset, float p_step, float p_target, float p_separation) {
	if (p_step != 0) {
		float a = Math::snapped(p_target - p_offset, p_step + p_separation) + p_offset;
		float b = a;
		if (p_target >= 0) {
			b -= p_separation;
		} else {
			b += p_step;
		}
		return (Math::abs(p_target - a) < Math::abs(p_target - b)) ? a : b;
	}
	return p_target;
}

}; //namespace Math

#endif // MATH_FUNCS_H
