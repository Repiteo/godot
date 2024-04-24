/**************************************************************************/
/*  vector3i.h                                                            */
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

#ifndef VECTOR3I_H
#define VECTOR3I_H

#include "core/error/error_macros.h"
#include "core/math/math_funcs.h"

class String;
struct Vector3;

struct _NO_DISCARD_ Vector3i {
	static constexpr int AXIS_COUNT = 3;

	enum Axis {
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
	};

	union {
		struct {
			int32_t x;
			int32_t y;
			int32_t z;
		};

		int32_t coord[3] = { 0, 0, 0 };
	};

	constexpr const int32_t &operator[](int p_axis) const;
	constexpr int32_t &operator[](int p_axis);

	constexpr Vector3i::Axis min_axis_index() const;
	constexpr Vector3i::Axis max_axis_index() const;

	constexpr Vector3i min(const Vector3i &p_vector3i) const {
		return Vector3i(MIN(x, p_vector3i.x), MIN(y, p_vector3i.y), MIN(z, p_vector3i.z));
	}

	constexpr Vector3i max(const Vector3i &p_vector3i) const {
		return Vector3i(MAX(x, p_vector3i.x), MAX(y, p_vector3i.y), MAX(z, p_vector3i.z));
	}

	constexpr int64_t length_squared() const;
	_FORCE_INLINE_ double length() const;

	constexpr void zero();

	constexpr Vector3i abs() const;
	constexpr Vector3i sign() const;
	constexpr Vector3i clamp(const Vector3i &p_min, const Vector3i &p_max) const;
	Vector3i snapped(const Vector3i &p_step) const;

	_FORCE_INLINE_ double distance_to(const Vector3i &p_to) const;
	constexpr int64_t distance_squared_to(const Vector3i &p_to) const;

	/* Operators */

	constexpr Vector3i &operator+=(const Vector3i &p_other);
	constexpr Vector3i operator+(const Vector3i &p_other) const;
	constexpr Vector3i &operator-=(const Vector3i &p_other);
	constexpr Vector3i operator-(const Vector3i &p_other) const;
	constexpr Vector3i &operator*=(const Vector3i &p_other);
	constexpr Vector3i operator*(const Vector3i &p_other) const;
	constexpr Vector3i &operator/=(const Vector3i &p_other);
	constexpr Vector3i operator/(const Vector3i &p_other) const;
	constexpr Vector3i &operator%=(const Vector3i &p_other);
	constexpr Vector3i operator%(const Vector3i &p_other) const;

	constexpr Vector3i &operator*=(int32_t p_scalar);
	constexpr Vector3i operator*(int32_t p_scalar) const;
	constexpr Vector3i &operator/=(int32_t p_scalar);
	constexpr Vector3i operator/(int32_t p_scalar) const;
	constexpr Vector3i &operator%=(int32_t p_scalar);
	constexpr Vector3i operator%(int32_t p_scalar) const;

	constexpr Vector3i operator-() const;

	constexpr bool operator==(const Vector3i &p_other) const;
	constexpr bool operator!=(const Vector3i &p_other) const;
	constexpr bool operator<(const Vector3i &p_other) const;
	constexpr bool operator<=(const Vector3i &p_other) const;
	constexpr bool operator>(const Vector3i &p_other) const;
	constexpr bool operator>=(const Vector3i &p_other) const;

	operator String() const;
	operator Vector3() const;

	constexpr Vector3i();
	constexpr Vector3i(int32_t p_x, int32_t p_y, int32_t p_z);
};

constexpr const int32_t &Vector3i::operator[](int p_axis) const {
	switch (p_axis) {
		case AXIS_X:
			return x;
		case AXIS_Y:
			return y;
		case AXIS_Z:
			return z;
		default:
			return coord[p_axis];
	}
}

constexpr int32_t &Vector3i::operator[](int p_axis) {
	switch (p_axis) {
		case AXIS_X:
			return x;
		case AXIS_Y:
			return y;
		case AXIS_Z:
			return z;
		default:
			return coord[p_axis];
	}
}

constexpr Vector3i::Axis Vector3i::min_axis_index() const {
	return x < y ? (x < z ? Vector3i::AXIS_X : Vector3i::AXIS_Z) : (y < z ? Vector3i::AXIS_Y : Vector3i::AXIS_Z);
}

constexpr Vector3i::Axis Vector3i::max_axis_index() const {
	return x < y ? (y < z ? Vector3i::AXIS_Z : Vector3i::AXIS_Y) : (x < z ? Vector3i::AXIS_Z : Vector3i::AXIS_X);
}

constexpr Vector3i Vector3i::clamp(const Vector3i &p_min, const Vector3i &p_max) const {
	return Vector3i(
			CLAMP(x, p_min.x, p_max.x),
			CLAMP(y, p_min.y, p_max.y),
			CLAMP(z, p_min.z, p_max.z));
}

constexpr int64_t Vector3i::length_squared() const {
	return x * (int64_t)x + y * (int64_t)y + z * (int64_t)z;
}

double Vector3i::length() const {
	return Math::sqrt((double)length_squared());
}

constexpr void Vector3i::zero() {
	x = y = z = 0;
}

constexpr Vector3i Vector3i::abs() const {
	return Vector3i(ABS(x), ABS(y), ABS(z));
}

constexpr Vector3i Vector3i::sign() const {
	return Vector3i(SIGN(x), SIGN(y), SIGN(z));
}

double Vector3i::distance_to(const Vector3i &p_to) const {
	return (p_to - *this).length();
}

constexpr int64_t Vector3i::distance_squared_to(const Vector3i &p_to) const {
	return (p_to - *this).length_squared();
}

/* Operators */

constexpr Vector3i &Vector3i::operator+=(const Vector3i &p_other) {
	x += p_other.x;
	y += p_other.y;
	z += p_other.z;
	return *this;
}

constexpr Vector3i Vector3i::operator+(const Vector3i &p_other) const {
	return Vector3i(x + p_other.x, y + p_other.y, z + p_other.z);
}

constexpr Vector3i &Vector3i::operator-=(const Vector3i &p_other) {
	x -= p_other.x;
	y -= p_other.y;
	z -= p_other.z;
	return *this;
}

constexpr Vector3i Vector3i::operator-(const Vector3i &p_other) const {
	return Vector3i(x - p_other.x, y - p_other.y, z - p_other.z);
}

constexpr Vector3i &Vector3i::operator*=(const Vector3i &p_other) {
	x *= p_other.x;
	y *= p_other.y;
	z *= p_other.z;
	return *this;
}

constexpr Vector3i Vector3i::operator*(const Vector3i &p_other) const {
	return Vector3i(x * p_other.x, y * p_other.y, z * p_other.z);
}

constexpr Vector3i &Vector3i::operator/=(const Vector3i &p_other) {
	x /= p_other.x;
	y /= p_other.y;
	z /= p_other.z;
	return *this;
}

constexpr Vector3i Vector3i::operator/(const Vector3i &p_other) const {
	return Vector3i(x / p_other.x, y / p_other.y, z / p_other.z);
}

constexpr Vector3i &Vector3i::operator%=(const Vector3i &p_other) {
	x %= p_other.x;
	y %= p_other.y;
	z %= p_other.z;
	return *this;
}

constexpr Vector3i Vector3i::operator%(const Vector3i &p_other) const {
	return Vector3i(x % p_other.x, y % p_other.y, z % p_other.z);
}

constexpr Vector3i &Vector3i::operator*=(int32_t p_scalar) {
	x *= p_scalar;
	y *= p_scalar;
	z *= p_scalar;
	return *this;
}

constexpr Vector3i Vector3i::operator*(int32_t p_scalar) const {
	return Vector3i(x * p_scalar, y * p_scalar, z * p_scalar);
}

constexpr Vector3i &Vector3i::operator/=(int32_t p_scalar) {
	x /= p_scalar;
	y /= p_scalar;
	z /= p_scalar;
	return *this;
}

constexpr Vector3i Vector3i::operator/(int32_t p_scalar) const {
	return Vector3i(x / p_scalar, y / p_scalar, z / p_scalar);
}

constexpr Vector3i &Vector3i::operator%=(int32_t p_scalar) {
	x %= p_scalar;
	y %= p_scalar;
	z %= p_scalar;
	return *this;
}

constexpr Vector3i Vector3i::operator%(int32_t p_scalar) const {
	return Vector3i(x % p_scalar, y % p_scalar, z % p_scalar);
}

constexpr Vector3i Vector3i::operator-() const {
	return Vector3i(-x, -y, -z);
}

constexpr bool Vector3i::operator==(const Vector3i &p_other) const {
	return (x == p_other.x && y == p_other.y && z == p_other.z);
}

constexpr bool Vector3i::operator!=(const Vector3i &p_other) const {
	return (x != p_other.x || y != p_other.y || z != p_other.z);
}

constexpr bool Vector3i::operator<(const Vector3i &p_other) const {
	if (x == p_other.x) {
		if (y == p_other.y) {
			return z < p_other.z;
		}
		return y < p_other.y;
	}
	return x < p_other.x;
}

constexpr bool Vector3i::operator>(const Vector3i &p_other) const {
	if (x == p_other.x) {
		if (y == p_other.y) {
			return z > p_other.z;
		}
		return y > p_other.y;
	}
	return x > p_other.x;
}

constexpr bool Vector3i::operator<=(const Vector3i &p_other) const {
	if (x == p_other.x) {
		if (y == p_other.y) {
			return z <= p_other.z;
		}
		return y < p_other.y;
	}
	return x < p_other.x;
}

constexpr bool Vector3i::operator>=(const Vector3i &p_other) const {
	if (x == p_other.x) {
		if (y == p_other.y) {
			return z >= p_other.z;
		}
		return y > p_other.y;
	}
	return x > p_other.x;
}

// Multiplication operators required to workaround issues with LLVM using implicit conversion.

constexpr Vector3i operator*(int32_t p_scalar, const Vector3i &p_vector3i) {
	return p_vector3i * p_scalar;
}

constexpr Vector3i operator*(int64_t p_scalar, const Vector3i &p_vector3i) {
	return p_vector3i * p_scalar;
}

constexpr Vector3i operator*(float p_scalar, const Vector3i &p_vector3i) {
	return p_vector3i * p_scalar;
}

constexpr Vector3i operator*(double p_scalar, const Vector3i &p_vector3i) {
	return p_vector3i * p_scalar;
}

/* Constructors */

constexpr Vector3i::Vector3i() :
		x(0),
		y(0),
		z(0) {}

constexpr Vector3i::Vector3i(int32_t p_x, int32_t p_y, int32_t p_z) :
		x(p_x),
		y(p_y),
		z(p_z) {}

#endif // VECTOR3I_H
