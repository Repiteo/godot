/**************************************************************************/
/*  vector3.cpp                                                           */
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

#include "vector3.h"

#include "core/math/basis.h"
#include "core/math/vector2.h"
#include "core/math/vector3i.h"
#include "core/string/ustring.h"

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector3 Vector3::slide(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector3(), "The normal Vector3 " + p_normal.operator String() + " must be normalized.");
#endif
	return *this - p_normal * dot(p_normal);
}

Vector3 Vector3::reflect(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector3(), "The normal Vector3 " + p_normal.operator String() + " must be normalized.");
#endif
	return 2.0f * p_normal * dot(p_normal) - *this;
}

void Vector3::rotate(const Vector3 &p_axis, real_t p_angle) {
	*this = Basis(p_axis, p_angle).xform(*this);
}

Basis Vector3::outer(const Vector3 &p_with) const {
	Basis basis;
	basis.rows[0] = Vector3(x * p_with.x, x * p_with.y, x * p_with.z);
	basis.rows[1] = Vector3(y * p_with.x, y * p_with.y, y * p_with.z);
	basis.rows[2] = Vector3(z * p_with.x, z * p_with.y, z * p_with.z);
	return basis;
}

Vector3::operator String() const {
	return "(" + String::num_real(x, true) + ", " + String::num_real(y, true) + ", " + String::num_real(z, true) + ")";
}

Vector3::operator Vector3i() const {
	return Vector3i(x, y, z);
}
