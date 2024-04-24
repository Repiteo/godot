/**************************************************************************/
/*  aabb.cpp                                                              */
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

#include "aabb.h"

#include "core/string/ustring.h"
#include "core/variant/variant.h"

bool AABB::is_equal_approx(const AABB &p_aabb) const {
	return position.is_equal_approx(p_aabb.position) && size.is_equal_approx(p_aabb.size);
}

bool AABB::is_finite() const {
	return position.is_finite() && size.is_finite();
}

bool AABB::intersects_ray(const Vector3 &p_from, const Vector3 &p_dir, Vector3 *r_clip, Vector3 *r_normal) const {
#ifdef MATH_CHECKS
	if (unlikely(size.x < 0 || size.y < 0 || size.z < 0)) {
		ERR_PRINT("AABB size is negative, this is not supported. Use AABB.abs() to get an AABB with a positive size.");
	}
#endif
	Vector3 c1, c2;
	Vector3 end = position + size;
	real_t depth_near = -1e20;
	real_t depth_far = 1e20;
	int axis = 0;

	for (int i = 0; i < 3; i++) {
		if (p_dir[i] == 0) {
			if ((p_from[i] < position[i]) || (p_from[i] > end[i])) {
				return false;
			}
		} else { // ray not parallel to planes in this direction
			c1[i] = (position[i] - p_from[i]) / p_dir[i];
			c2[i] = (end[i] - p_from[i]) / p_dir[i];

			if (c1[i] > c2[i]) {
				SWAP(c1, c2);
			}
			if (c1[i] > depth_near) {
				depth_near = c1[i];
				axis = i;
			}
			if (c2[i] < depth_far) {
				depth_far = c2[i];
			}
			if ((depth_near > depth_far) || (depth_far < 0)) {
				return false;
			}
		}
	}

	if (r_clip) {
		*r_clip = c1;
	}
	if (r_normal) {
		*r_normal = Vector3();
		(*r_normal)[axis] = p_dir[axis] ? -1 : 1;
	}

	return true;
}

Variant AABB::intersects_segment_bind(const Vector3 &p_from, const Vector3 &p_to) const {
	Vector3 inters;
	if (intersects_segment(p_from, p_to, &inters)) {
		return inters;
	}
	return Variant();
}

Variant AABB::intersects_ray_bind(const Vector3 &p_from, const Vector3 &p_dir) const {
	Vector3 inters;
	if (intersects_ray(p_from, p_dir, &inters)) {
		return inters;
	}
	return Variant();
}

AABB::operator String() const {
	return "[P: " + position.operator String() + ", S: " + size + "]";
}
