/**************************************************************************/
/*  variant_internal.h                                                    */
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

#include "variant.h"

#include "core/templates/simple_type.h"

// For use when you want to access the internal pointer of a Variant directly.
// Use with caution. You need to be sure that the type is correct.

class RefCounted;

class VariantInternal {
	friend class Variant;

public:
	// Set type.
	GD_FORCE_INLINE static void initialize(Variant *v, Variant::Type p_type) {
		v->clear();
		v->type = p_type;

		switch (p_type) {
			case Variant::STRING:
				init_string(v);
				break;
			case Variant::TRANSFORM2D:
				init_transform2d(v);
				break;
			case Variant::AABB:
				init_aabb(v);
				break;
			case Variant::BASIS:
				init_basis(v);
				break;
			case Variant::TRANSFORM3D:
				init_transform3d(v);
				break;
			case Variant::PROJECTION:
				init_projection(v);
				break;
			case Variant::COLOR:
				init_color(v);
				break;
			case Variant::STRING_NAME:
				init_string_name(v);
				break;
			case Variant::NODE_PATH:
				init_node_path(v);
				break;
			case Variant::CALLABLE:
				init_callable(v);
				break;
			case Variant::SIGNAL:
				init_signal(v);
				break;
			case Variant::DICTIONARY:
				init_dictionary(v);
				break;
			case Variant::ARRAY:
				init_array(v);
				break;
			case Variant::PACKED_BYTE_ARRAY:
				init_byte_array(v);
				break;
			case Variant::PACKED_INT32_ARRAY:
				init_int32_array(v);
				break;
			case Variant::PACKED_INT64_ARRAY:
				init_int64_array(v);
				break;
			case Variant::PACKED_FLOAT32_ARRAY:
				init_float32_array(v);
				break;
			case Variant::PACKED_FLOAT64_ARRAY:
				init_float64_array(v);
				break;
			case Variant::PACKED_STRING_ARRAY:
				init_string_array(v);
				break;
			case Variant::PACKED_VECTOR2_ARRAY:
				init_vector2_array(v);
				break;
			case Variant::PACKED_VECTOR3_ARRAY:
				init_vector3_array(v);
				break;
			case Variant::PACKED_COLOR_ARRAY:
				init_color_array(v);
				break;
			case Variant::PACKED_VECTOR4_ARRAY:
				init_vector4_array(v);
				break;
			case Variant::OBJECT:
				init_object(v);
				break;
			default:
				break;
		}
	}

	// Atomic types.
	GD_FORCE_INLINE static bool *get_bool(Variant *v) { return &v->_data._bool; }
	GD_FORCE_INLINE static const bool *get_bool(const Variant *v) { return &v->_data._bool; }
	GD_FORCE_INLINE static int64_t *get_int(Variant *v) { return &v->_data._int; }
	GD_FORCE_INLINE static const int64_t *get_int(const Variant *v) { return &v->_data._int; }
	GD_FORCE_INLINE static double *get_float(Variant *v) { return &v->_data._float; }
	GD_FORCE_INLINE static const double *get_float(const Variant *v) { return &v->_data._float; }
	GD_FORCE_INLINE static String *get_string(Variant *v) { return reinterpret_cast<String *>(v->_data._mem); }
	GD_FORCE_INLINE static const String *get_string(const Variant *v) { return reinterpret_cast<const String *>(v->_data._mem); }

	// Math types.
	GD_FORCE_INLINE static Vector2 *get_vector2(Variant *v) { return reinterpret_cast<Vector2 *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector2 *get_vector2(const Variant *v) { return reinterpret_cast<const Vector2 *>(v->_data._mem); }
	GD_FORCE_INLINE static Vector2i *get_vector2i(Variant *v) { return reinterpret_cast<Vector2i *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector2i *get_vector2i(const Variant *v) { return reinterpret_cast<const Vector2i *>(v->_data._mem); }
	GD_FORCE_INLINE static Rect2 *get_rect2(Variant *v) { return reinterpret_cast<Rect2 *>(v->_data._mem); }
	GD_FORCE_INLINE static const Rect2 *get_rect2(const Variant *v) { return reinterpret_cast<const Rect2 *>(v->_data._mem); }
	GD_FORCE_INLINE static Rect2i *get_rect2i(Variant *v) { return reinterpret_cast<Rect2i *>(v->_data._mem); }
	GD_FORCE_INLINE static const Rect2i *get_rect2i(const Variant *v) { return reinterpret_cast<const Rect2i *>(v->_data._mem); }
	GD_FORCE_INLINE static Vector3 *get_vector3(Variant *v) { return reinterpret_cast<Vector3 *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector3 *get_vector3(const Variant *v) { return reinterpret_cast<const Vector3 *>(v->_data._mem); }
	GD_FORCE_INLINE static Vector3i *get_vector3i(Variant *v) { return reinterpret_cast<Vector3i *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector3i *get_vector3i(const Variant *v) { return reinterpret_cast<const Vector3i *>(v->_data._mem); }
	GD_FORCE_INLINE static Vector4 *get_vector4(Variant *v) { return reinterpret_cast<Vector4 *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector4 *get_vector4(const Variant *v) { return reinterpret_cast<const Vector4 *>(v->_data._mem); }
	GD_FORCE_INLINE static Vector4i *get_vector4i(Variant *v) { return reinterpret_cast<Vector4i *>(v->_data._mem); }
	GD_FORCE_INLINE static const Vector4i *get_vector4i(const Variant *v) { return reinterpret_cast<const Vector4i *>(v->_data._mem); }
	GD_FORCE_INLINE static Transform2D *get_transform2d(Variant *v) { return v->_data._transform2d; }
	GD_FORCE_INLINE static const Transform2D *get_transform2d(const Variant *v) { return v->_data._transform2d; }
	GD_FORCE_INLINE static Plane *get_plane(Variant *v) { return reinterpret_cast<Plane *>(v->_data._mem); }
	GD_FORCE_INLINE static const Plane *get_plane(const Variant *v) { return reinterpret_cast<const Plane *>(v->_data._mem); }
	GD_FORCE_INLINE static Quaternion *get_quaternion(Variant *v) { return reinterpret_cast<Quaternion *>(v->_data._mem); }
	GD_FORCE_INLINE static const Quaternion *get_quaternion(const Variant *v) { return reinterpret_cast<const Quaternion *>(v->_data._mem); }
	GD_FORCE_INLINE static ::AABB *get_aabb(Variant *v) { return v->_data._aabb; }
	GD_FORCE_INLINE static const ::AABB *get_aabb(const Variant *v) { return v->_data._aabb; }
	GD_FORCE_INLINE static Basis *get_basis(Variant *v) { return v->_data._basis; }
	GD_FORCE_INLINE static const Basis *get_basis(const Variant *v) { return v->_data._basis; }
	GD_FORCE_INLINE static Transform3D *get_transform(Variant *v) { return v->_data._transform3d; }
	GD_FORCE_INLINE static const Transform3D *get_transform(const Variant *v) { return v->_data._transform3d; }
	GD_FORCE_INLINE static Projection *get_projection(Variant *v) { return v->_data._projection; }
	GD_FORCE_INLINE static const Projection *get_projection(const Variant *v) { return v->_data._projection; }

	// Misc types.
	GD_FORCE_INLINE static Color *get_color(Variant *v) { return reinterpret_cast<Color *>(v->_data._mem); }
	GD_FORCE_INLINE static const Color *get_color(const Variant *v) { return reinterpret_cast<const Color *>(v->_data._mem); }
	GD_FORCE_INLINE static StringName *get_string_name(Variant *v) { return reinterpret_cast<StringName *>(v->_data._mem); }
	GD_FORCE_INLINE static const StringName *get_string_name(const Variant *v) { return reinterpret_cast<const StringName *>(v->_data._mem); }
	GD_FORCE_INLINE static NodePath *get_node_path(Variant *v) { return reinterpret_cast<NodePath *>(v->_data._mem); }
	GD_FORCE_INLINE static const NodePath *get_node_path(const Variant *v) { return reinterpret_cast<const NodePath *>(v->_data._mem); }
	GD_FORCE_INLINE static ::RID *get_rid(Variant *v) { return reinterpret_cast<::RID *>(v->_data._mem); }
	GD_FORCE_INLINE static const ::RID *get_rid(const Variant *v) { return reinterpret_cast<const ::RID *>(v->_data._mem); }
	GD_FORCE_INLINE static Callable *get_callable(Variant *v) { return reinterpret_cast<Callable *>(v->_data._mem); }
	GD_FORCE_INLINE static const Callable *get_callable(const Variant *v) { return reinterpret_cast<const Callable *>(v->_data._mem); }
	GD_FORCE_INLINE static Signal *get_signal(Variant *v) { return reinterpret_cast<Signal *>(v->_data._mem); }
	GD_FORCE_INLINE static const Signal *get_signal(const Variant *v) { return reinterpret_cast<const Signal *>(v->_data._mem); }
	GD_FORCE_INLINE static Dictionary *get_dictionary(Variant *v) { return reinterpret_cast<Dictionary *>(v->_data._mem); }
	GD_FORCE_INLINE static const Dictionary *get_dictionary(const Variant *v) { return reinterpret_cast<const Dictionary *>(v->_data._mem); }
	GD_FORCE_INLINE static Array *get_array(Variant *v) { return reinterpret_cast<Array *>(v->_data._mem); }
	GD_FORCE_INLINE static const Array *get_array(const Variant *v) { return reinterpret_cast<const Array *>(v->_data._mem); }

	// Typed arrays.
	GD_FORCE_INLINE static PackedByteArray *get_byte_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<uint8_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedByteArray *get_byte_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<uint8_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedInt32Array *get_int32_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<int32_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedInt32Array *get_int32_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<int32_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedInt64Array *get_int64_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<int64_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedInt64Array *get_int64_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<int64_t> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedFloat32Array *get_float32_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<float> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedFloat32Array *get_float32_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<float> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedFloat64Array *get_float64_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<double> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedFloat64Array *get_float64_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<double> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedStringArray *get_string_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<String> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedStringArray *get_string_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<String> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedVector2Array *get_vector2_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<Vector2> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedVector2Array *get_vector2_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<Vector2> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedVector3Array *get_vector3_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<Vector3> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedVector3Array *get_vector3_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<Vector3> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedColorArray *get_color_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<Color> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedColorArray *get_color_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<Color> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static PackedVector4Array *get_vector4_array(Variant *v) { return &static_cast<Variant::PackedArrayRef<Vector4> *>(v->_data.packed_array)->array; }
	GD_FORCE_INLINE static const PackedVector4Array *get_vector4_array(const Variant *v) { return &static_cast<const Variant::PackedArrayRef<Vector4> *>(v->_data.packed_array)->array; }

	GD_FORCE_INLINE static Object **get_object(Variant *v) { return (Object **)&v->_get_obj().obj; }
	GD_FORCE_INLINE static const Object **get_object(const Variant *v) { return (const Object **)&v->_get_obj().obj; }

	GD_FORCE_INLINE static const ObjectID get_object_id(const Variant *v) { return v->_get_obj().id; }

	template <typename T>
	GD_FORCE_INLINE static void init_generic(Variant *v) {
		v->type = GetTypeInfo<T>::VARIANT_TYPE;
	}

	// Should be in the same order as Variant::Type for consistency.
	// Those primitive and vector types don't need an `init_` method:
	// Nil, bool, float, Vector2/i, Rect2/i, Vector3/i, Plane, Quat, RID.
	// Object is a special case, handled via `object_reset_data`.
	GD_FORCE_INLINE static void init_string(Variant *v) {
		memnew_placement(v->_data._mem, String);
		v->type = Variant::STRING;
	}
	GD_FORCE_INLINE static void init_transform2d(Variant *v) {
		v->_data._transform2d = (Transform2D *)Variant::Pools::_bucket_small.alloc();
		memnew_placement(v->_data._transform2d, Transform2D);
		v->type = Variant::TRANSFORM2D;
	}
	GD_FORCE_INLINE static void init_aabb(Variant *v) {
		v->_data._aabb = (AABB *)Variant::Pools::_bucket_small.alloc();
		memnew_placement(v->_data._aabb, AABB);
		v->type = Variant::AABB;
	}
	GD_FORCE_INLINE static void init_basis(Variant *v) {
		v->_data._basis = (Basis *)Variant::Pools::_bucket_medium.alloc();
		memnew_placement(v->_data._basis, Basis);
		v->type = Variant::BASIS;
	}
	GD_FORCE_INLINE static void init_transform3d(Variant *v) {
		v->_data._transform3d = (Transform3D *)Variant::Pools::_bucket_medium.alloc();
		memnew_placement(v->_data._transform3d, Transform3D);
		v->type = Variant::TRANSFORM3D;
	}
	GD_FORCE_INLINE static void init_projection(Variant *v) {
		v->_data._projection = (Projection *)Variant::Pools::_bucket_large.alloc();
		memnew_placement(v->_data._projection, Projection);
		v->type = Variant::PROJECTION;
	}
	GD_FORCE_INLINE static void init_color(Variant *v) {
		memnew_placement(v->_data._mem, Color);
		v->type = Variant::COLOR;
	}
	GD_FORCE_INLINE static void init_string_name(Variant *v) {
		memnew_placement(v->_data._mem, StringName);
		v->type = Variant::STRING_NAME;
	}
	GD_FORCE_INLINE static void init_node_path(Variant *v) {
		memnew_placement(v->_data._mem, NodePath);
		v->type = Variant::NODE_PATH;
	}
	GD_FORCE_INLINE static void init_callable(Variant *v) {
		memnew_placement(v->_data._mem, Callable);
		v->type = Variant::CALLABLE;
	}
	GD_FORCE_INLINE static void init_signal(Variant *v) {
		memnew_placement(v->_data._mem, Signal);
		v->type = Variant::SIGNAL;
	}
	GD_FORCE_INLINE static void init_dictionary(Variant *v) {
		memnew_placement(v->_data._mem, Dictionary);
		v->type = Variant::DICTIONARY;
	}
	GD_FORCE_INLINE static void init_array(Variant *v) {
		memnew_placement(v->_data._mem, Array);
		v->type = Variant::ARRAY;
	}
	GD_FORCE_INLINE static void init_byte_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<uint8_t>::create(Vector<uint8_t>());
		v->type = Variant::PACKED_BYTE_ARRAY;
	}
	GD_FORCE_INLINE static void init_int32_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<int32_t>::create(Vector<int32_t>());
		v->type = Variant::PACKED_INT32_ARRAY;
	}
	GD_FORCE_INLINE static void init_int64_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<int64_t>::create(Vector<int64_t>());
		v->type = Variant::PACKED_INT64_ARRAY;
	}
	GD_FORCE_INLINE static void init_float32_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<float>::create(Vector<float>());
		v->type = Variant::PACKED_FLOAT32_ARRAY;
	}
	GD_FORCE_INLINE static void init_float64_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<double>::create(Vector<double>());
		v->type = Variant::PACKED_FLOAT64_ARRAY;
	}
	GD_FORCE_INLINE static void init_string_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<String>::create(Vector<String>());
		v->type = Variant::PACKED_STRING_ARRAY;
	}
	GD_FORCE_INLINE static void init_vector2_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<Vector2>::create(Vector<Vector2>());
		v->type = Variant::PACKED_VECTOR2_ARRAY;
	}
	GD_FORCE_INLINE static void init_vector3_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<Vector3>::create(Vector<Vector3>());
		v->type = Variant::PACKED_VECTOR3_ARRAY;
	}
	GD_FORCE_INLINE static void init_color_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<Color>::create(Vector<Color>());
		v->type = Variant::PACKED_COLOR_ARRAY;
	}
	GD_FORCE_INLINE static void init_vector4_array(Variant *v) {
		v->_data.packed_array = Variant::PackedArrayRef<Vector4>::create(Vector<Vector4>());
		v->type = Variant::PACKED_VECTOR4_ARRAY;
	}
	GD_FORCE_INLINE static void init_object(Variant *v) {
		object_reset_data(v);
		v->type = Variant::OBJECT;
	}

	GD_FORCE_INLINE static void clear(Variant *v) {
		v->clear();
	}

	GD_FORCE_INLINE static void object_assign(Variant *v, const Variant *vo) {
		v->_get_obj().ref(vo->_get_obj());
	}

	GD_FORCE_INLINE static void object_assign(Variant *v, Object *o) {
		v->_get_obj().ref_pointer(o);
	}

	GD_FORCE_INLINE static void object_assign(Variant *v, const Object *o) {
		v->_get_obj().ref_pointer(const_cast<Object *>(o));
	}

	template <typename T>
	GD_FORCE_INLINE static void object_assign(Variant *v, const Ref<T> &r) {
		v->_get_obj().ref(r);
	}

	GD_FORCE_INLINE static void object_reset_data(Variant *v) {
		v->_get_obj() = Variant::ObjData();
	}

	GD_FORCE_INLINE static void update_object_id(Variant *v) {
		const Object *o = v->_get_obj().obj;
		if (o) {
			v->_get_obj().id = o->get_instance_id();
		}
	}

	GD_FORCE_INLINE static void *get_opaque_pointer(Variant *v) {
		switch (v->type) {
			case Variant::NIL:
				return nullptr;
			case Variant::BOOL:
				return get_bool(v);
			case Variant::INT:
				return get_int(v);
			case Variant::FLOAT:
				return get_float(v);
			case Variant::STRING:
				return get_string(v);
			case Variant::VECTOR2:
				return get_vector2(v);
			case Variant::VECTOR2I:
				return get_vector2i(v);
			case Variant::VECTOR3:
				return get_vector3(v);
			case Variant::VECTOR3I:
				return get_vector3i(v);
			case Variant::VECTOR4:
				return get_vector4(v);
			case Variant::VECTOR4I:
				return get_vector4i(v);
			case Variant::RECT2:
				return get_rect2(v);
			case Variant::RECT2I:
				return get_rect2i(v);
			case Variant::TRANSFORM3D:
				return get_transform(v);
			case Variant::PROJECTION:
				return get_projection(v);
			case Variant::TRANSFORM2D:
				return get_transform2d(v);
			case Variant::QUATERNION:
				return get_quaternion(v);
			case Variant::PLANE:
				return get_plane(v);
			case Variant::BASIS:
				return get_basis(v);
			case Variant::AABB:
				return get_aabb(v);
			case Variant::COLOR:
				return get_color(v);
			case Variant::STRING_NAME:
				return get_string_name(v);
			case Variant::NODE_PATH:
				return get_node_path(v);
			case Variant::RID:
				return get_rid(v);
			case Variant::CALLABLE:
				return get_callable(v);
			case Variant::SIGNAL:
				return get_signal(v);
			case Variant::DICTIONARY:
				return get_dictionary(v);
			case Variant::ARRAY:
				return get_array(v);
			case Variant::PACKED_BYTE_ARRAY:
				return get_byte_array(v);
			case Variant::PACKED_INT32_ARRAY:
				return get_int32_array(v);
			case Variant::PACKED_INT64_ARRAY:
				return get_int64_array(v);
			case Variant::PACKED_FLOAT32_ARRAY:
				return get_float32_array(v);
			case Variant::PACKED_FLOAT64_ARRAY:
				return get_float64_array(v);
			case Variant::PACKED_STRING_ARRAY:
				return get_string_array(v);
			case Variant::PACKED_VECTOR2_ARRAY:
				return get_vector2_array(v);
			case Variant::PACKED_VECTOR3_ARRAY:
				return get_vector3_array(v);
			case Variant::PACKED_COLOR_ARRAY:
				return get_color_array(v);
			case Variant::PACKED_VECTOR4_ARRAY:
				return get_vector4_array(v);
			case Variant::OBJECT:
				return get_object(v);
			case Variant::VARIANT_MAX:
				ERR_FAIL_V(nullptr);
		}
		ERR_FAIL_V(nullptr);
	}

	GD_FORCE_INLINE static const void *get_opaque_pointer(const Variant *v) {
		switch (v->type) {
			case Variant::NIL:
				return nullptr;
			case Variant::BOOL:
				return get_bool(v);
			case Variant::INT:
				return get_int(v);
			case Variant::FLOAT:
				return get_float(v);
			case Variant::STRING:
				return get_string(v);
			case Variant::VECTOR2:
				return get_vector2(v);
			case Variant::VECTOR2I:
				return get_vector2i(v);
			case Variant::VECTOR3:
				return get_vector3(v);
			case Variant::VECTOR3I:
				return get_vector3i(v);
			case Variant::VECTOR4:
				return get_vector4(v);
			case Variant::VECTOR4I:
				return get_vector4i(v);
			case Variant::RECT2:
				return get_rect2(v);
			case Variant::RECT2I:
				return get_rect2i(v);
			case Variant::TRANSFORM3D:
				return get_transform(v);
			case Variant::PROJECTION:
				return get_projection(v);
			case Variant::TRANSFORM2D:
				return get_transform2d(v);
			case Variant::QUATERNION:
				return get_quaternion(v);
			case Variant::PLANE:
				return get_plane(v);
			case Variant::BASIS:
				return get_basis(v);
			case Variant::AABB:
				return get_aabb(v);
			case Variant::COLOR:
				return get_color(v);
			case Variant::STRING_NAME:
				return get_string_name(v);
			case Variant::NODE_PATH:
				return get_node_path(v);
			case Variant::RID:
				return get_rid(v);
			case Variant::CALLABLE:
				return get_callable(v);
			case Variant::SIGNAL:
				return get_signal(v);
			case Variant::DICTIONARY:
				return get_dictionary(v);
			case Variant::ARRAY:
				return get_array(v);
			case Variant::PACKED_BYTE_ARRAY:
				return get_byte_array(v);
			case Variant::PACKED_INT32_ARRAY:
				return get_int32_array(v);
			case Variant::PACKED_INT64_ARRAY:
				return get_int64_array(v);
			case Variant::PACKED_FLOAT32_ARRAY:
				return get_float32_array(v);
			case Variant::PACKED_FLOAT64_ARRAY:
				return get_float64_array(v);
			case Variant::PACKED_STRING_ARRAY:
				return get_string_array(v);
			case Variant::PACKED_VECTOR2_ARRAY:
				return get_vector2_array(v);
			case Variant::PACKED_VECTOR3_ARRAY:
				return get_vector3_array(v);
			case Variant::PACKED_COLOR_ARRAY:
				return get_color_array(v);
			case Variant::PACKED_VECTOR4_ARRAY:
				return get_vector4_array(v);
			case Variant::OBJECT:
				return get_object(v);
			case Variant::VARIANT_MAX:
				ERR_FAIL_V(nullptr);
		}
		ERR_FAIL_V(nullptr);
	}
};

template <typename T, typename = void>
struct VariantGetInternalPtr;

template <typename T>
struct VariantGetInternalPtr<T, std::enable_if_t<!std::is_same_v<T, GetSimpleTypeT<T>>>> : VariantGetInternalPtr<GetSimpleTypeT<T>> {};

template <>
struct VariantGetInternalPtr<bool> {
	static bool *get_ptr(Variant *v) { return VariantInternal::get_bool(v); }
	static const bool *get_ptr(const Variant *v) { return VariantInternal::get_bool(v); }
};

template <typename T>
struct VariantGetInternalPtr<T, std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>> {
	static int64_t *get_ptr(Variant *v) { return VariantInternal::get_int(v); }
	static const int64_t *get_ptr(const Variant *v) { return VariantInternal::get_int(v); }
};

template <typename T>
struct VariantGetInternalPtr<BitField<T>, std::enable_if_t<std::is_enum_v<T>>> {
	static int64_t *get_ptr(Variant *v) { return VariantInternal::get_int(v); }
	static const int64_t *get_ptr(const Variant *v) { return VariantInternal::get_int(v); }
};

template <>
struct VariantGetInternalPtr<ObjectID> {
	static int64_t *get_ptr(Variant *v) { return VariantInternal::get_int(v); }
	static const int64_t *get_ptr(const Variant *v) { return VariantInternal::get_int(v); }
};

template <>
struct VariantGetInternalPtr<float> {
	static double *get_ptr(Variant *v) { return VariantInternal::get_float(v); }
	static const double *get_ptr(const Variant *v) { return VariantInternal::get_float(v); }
};

template <>
struct VariantGetInternalPtr<double> {
	static double *get_ptr(Variant *v) { return VariantInternal::get_float(v); }
	static const double *get_ptr(const Variant *v) { return VariantInternal::get_float(v); }
};

template <>
struct VariantGetInternalPtr<String> {
	static String *get_ptr(Variant *v) { return VariantInternal::get_string(v); }
	static const String *get_ptr(const Variant *v) { return VariantInternal::get_string(v); }
};

template <>
struct VariantGetInternalPtr<Vector2> {
	static Vector2 *get_ptr(Variant *v) { return VariantInternal::get_vector2(v); }
	static const Vector2 *get_ptr(const Variant *v) { return VariantInternal::get_vector2(v); }
};

template <>
struct VariantGetInternalPtr<Vector2i> {
	static Vector2i *get_ptr(Variant *v) { return VariantInternal::get_vector2i(v); }
	static const Vector2i *get_ptr(const Variant *v) { return VariantInternal::get_vector2i(v); }
};

template <>
struct VariantGetInternalPtr<Rect2> {
	static Rect2 *get_ptr(Variant *v) { return VariantInternal::get_rect2(v); }
	static const Rect2 *get_ptr(const Variant *v) { return VariantInternal::get_rect2(v); }
};

template <>
struct VariantGetInternalPtr<Rect2i> {
	static Rect2i *get_ptr(Variant *v) { return VariantInternal::get_rect2i(v); }
	static const Rect2i *get_ptr(const Variant *v) { return VariantInternal::get_rect2i(v); }
};

template <>
struct VariantGetInternalPtr<Vector3> {
	static Vector3 *get_ptr(Variant *v) { return VariantInternal::get_vector3(v); }
	static const Vector3 *get_ptr(const Variant *v) { return VariantInternal::get_vector3(v); }
};

template <>
struct VariantGetInternalPtr<Vector3i> {
	static Vector3i *get_ptr(Variant *v) { return VariantInternal::get_vector3i(v); }
	static const Vector3i *get_ptr(const Variant *v) { return VariantInternal::get_vector3i(v); }
};

template <>
struct VariantGetInternalPtr<Vector4> {
	static Vector4 *get_ptr(Variant *v) { return VariantInternal::get_vector4(v); }
	static const Vector4 *get_ptr(const Variant *v) { return VariantInternal::get_vector4(v); }
};

template <>
struct VariantGetInternalPtr<Vector4i> {
	static Vector4i *get_ptr(Variant *v) { return VariantInternal::get_vector4i(v); }
	static const Vector4i *get_ptr(const Variant *v) { return VariantInternal::get_vector4i(v); }
};
template <>
struct VariantGetInternalPtr<Transform2D> {
	static Transform2D *get_ptr(Variant *v) { return VariantInternal::get_transform2d(v); }
	static const Transform2D *get_ptr(const Variant *v) { return VariantInternal::get_transform2d(v); }
};

template <>
struct VariantGetInternalPtr<Transform3D> {
	static Transform3D *get_ptr(Variant *v) { return VariantInternal::get_transform(v); }
	static const Transform3D *get_ptr(const Variant *v) { return VariantInternal::get_transform(v); }
};

template <>
struct VariantGetInternalPtr<Projection> {
	static Projection *get_ptr(Variant *v) { return VariantInternal::get_projection(v); }
	static const Projection *get_ptr(const Variant *v) { return VariantInternal::get_projection(v); }
};

template <>
struct VariantGetInternalPtr<Plane> {
	static Plane *get_ptr(Variant *v) { return VariantInternal::get_plane(v); }
	static const Plane *get_ptr(const Variant *v) { return VariantInternal::get_plane(v); }
};

template <>
struct VariantGetInternalPtr<Quaternion> {
	static Quaternion *get_ptr(Variant *v) { return VariantInternal::get_quaternion(v); }
	static const Quaternion *get_ptr(const Variant *v) { return VariantInternal::get_quaternion(v); }
};

template <>
struct VariantGetInternalPtr<::AABB> {
	static ::AABB *get_ptr(Variant *v) { return VariantInternal::get_aabb(v); }
	static const ::AABB *get_ptr(const Variant *v) { return VariantInternal::get_aabb(v); }
};

template <>
struct VariantGetInternalPtr<Basis> {
	static Basis *get_ptr(Variant *v) { return VariantInternal::get_basis(v); }
	static const Basis *get_ptr(const Variant *v) { return VariantInternal::get_basis(v); }
};

//

template <>
struct VariantGetInternalPtr<Color> {
	static Color *get_ptr(Variant *v) { return VariantInternal::get_color(v); }
	static const Color *get_ptr(const Variant *v) { return VariantInternal::get_color(v); }
};

template <>
struct VariantGetInternalPtr<StringName> {
	static StringName *get_ptr(Variant *v) { return VariantInternal::get_string_name(v); }
	static const StringName *get_ptr(const Variant *v) { return VariantInternal::get_string_name(v); }
};

template <>
struct VariantGetInternalPtr<NodePath> {
	static NodePath *get_ptr(Variant *v) { return VariantInternal::get_node_path(v); }
	static const NodePath *get_ptr(const Variant *v) { return VariantInternal::get_node_path(v); }
};

template <>
struct VariantGetInternalPtr<::RID> {
	static ::RID *get_ptr(Variant *v) { return VariantInternal::get_rid(v); }
	static const ::RID *get_ptr(const Variant *v) { return VariantInternal::get_rid(v); }
};

template <>
struct VariantGetInternalPtr<Callable> {
	static Callable *get_ptr(Variant *v) { return VariantInternal::get_callable(v); }
	static const Callable *get_ptr(const Variant *v) { return VariantInternal::get_callable(v); }
};

template <>
struct VariantGetInternalPtr<Signal> {
	static Signal *get_ptr(Variant *v) { return VariantInternal::get_signal(v); }
	static const Signal *get_ptr(const Variant *v) { return VariantInternal::get_signal(v); }
};

template <>
struct VariantGetInternalPtr<Dictionary> {
	static Dictionary *get_ptr(Variant *v) { return VariantInternal::get_dictionary(v); }
	static const Dictionary *get_ptr(const Variant *v) { return VariantInternal::get_dictionary(v); }
};

template <>
struct VariantGetInternalPtr<Array> {
	static Array *get_ptr(Variant *v) { return VariantInternal::get_array(v); }
	static const Array *get_ptr(const Variant *v) { return VariantInternal::get_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedByteArray> {
	static PackedByteArray *get_ptr(Variant *v) { return VariantInternal::get_byte_array(v); }
	static const PackedByteArray *get_ptr(const Variant *v) { return VariantInternal::get_byte_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedInt32Array> {
	static PackedInt32Array *get_ptr(Variant *v) { return VariantInternal::get_int32_array(v); }
	static const PackedInt32Array *get_ptr(const Variant *v) { return VariantInternal::get_int32_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedInt64Array> {
	static PackedInt64Array *get_ptr(Variant *v) { return VariantInternal::get_int64_array(v); }
	static const PackedInt64Array *get_ptr(const Variant *v) { return VariantInternal::get_int64_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedFloat32Array> {
	static PackedFloat32Array *get_ptr(Variant *v) { return VariantInternal::get_float32_array(v); }
	static const PackedFloat32Array *get_ptr(const Variant *v) { return VariantInternal::get_float32_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedFloat64Array> {
	static PackedFloat64Array *get_ptr(Variant *v) { return VariantInternal::get_float64_array(v); }
	static const PackedFloat64Array *get_ptr(const Variant *v) { return VariantInternal::get_float64_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedStringArray> {
	static PackedStringArray *get_ptr(Variant *v) { return VariantInternal::get_string_array(v); }
	static const PackedStringArray *get_ptr(const Variant *v) { return VariantInternal::get_string_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedVector2Array> {
	static PackedVector2Array *get_ptr(Variant *v) { return VariantInternal::get_vector2_array(v); }
	static const PackedVector2Array *get_ptr(const Variant *v) { return VariantInternal::get_vector2_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedVector3Array> {
	static PackedVector3Array *get_ptr(Variant *v) { return VariantInternal::get_vector3_array(v); }
	static const PackedVector3Array *get_ptr(const Variant *v) { return VariantInternal::get_vector3_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedColorArray> {
	static PackedColorArray *get_ptr(Variant *v) { return VariantInternal::get_color_array(v); }
	static const PackedColorArray *get_ptr(const Variant *v) { return VariantInternal::get_color_array(v); }
};

template <>
struct VariantGetInternalPtr<PackedVector4Array> {
	static PackedVector4Array *get_ptr(Variant *v) { return VariantInternal::get_vector4_array(v); }
	static const PackedVector4Array *get_ptr(const Variant *v) { return VariantInternal::get_vector4_array(v); }
};

template <typename T, typename = void>
struct VariantInternalAccessor;

template <typename T>
struct VariantInternalAccessor<T, std::enable_if_t<!std::is_same_v<T, GetSimpleTypeT<T>>>> : VariantInternalAccessor<GetSimpleTypeT<T>> {};

template <>
struct VariantInternalAccessor<bool> {
	static GD_FORCE_INLINE bool get(const Variant *v) { return *VariantInternal::get_bool(v); }
	static GD_FORCE_INLINE void set(Variant *v, bool p_value) { *VariantInternal::get_bool(v) = p_value; }
};

template <typename T>
struct VariantInternalAccessor<T, std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>> {
	static GD_FORCE_INLINE T get(const Variant *v) { return static_cast<T>(*VariantInternal::get_int(v)); }
	static GD_FORCE_INLINE void set(Variant *v, T p_value) { *VariantInternal::get_int(v) = static_cast<int64_t>(p_value); }
};

template <typename T>
struct VariantInternalAccessor<BitField<T>, std::enable_if_t<std::is_enum_v<T>>> {
	static GD_FORCE_INLINE BitField<T> get(const Variant *v) { return BitField<T>(static_cast<T>(*VariantInternal::get_int(v))); }
	static GD_FORCE_INLINE void set(Variant *v, BitField<T> p_value) { *VariantInternal::get_int(v) = static_cast<int64_t>(p_value); }
};

template <>
struct VariantInternalAccessor<ObjectID> {
	static GD_FORCE_INLINE ObjectID get(const Variant *v) { return ObjectID(*VariantInternal::get_int(v)); }
	static GD_FORCE_INLINE void set(Variant *v, ObjectID p_value) { *VariantInternal::get_int(v) = p_value; }
};

template <typename T>
struct VariantInternalAccessor<T *> {
	static GD_FORCE_INLINE T *get(const Variant *v) { return const_cast<T *>(static_cast<const T *>(*VariantInternal::get_object(v))); }
	static GD_FORCE_INLINE void set(Variant *v, const T *p_value) { VariantInternal::object_assign(v, p_value); }
};

template <typename T>
struct VariantInternalAccessor<const T *> {
	static GD_FORCE_INLINE const T *get(const Variant *v) { return static_cast<const T *>(*VariantInternal::get_object(v)); }
	static GD_FORCE_INLINE void set(Variant *v, const T *p_value) { VariantInternal::object_assign(v, p_value); }
};

template <>
struct VariantInternalAccessor<IPAddress> {
	static GD_FORCE_INLINE IPAddress get(const Variant *v) { return IPAddress(*VariantInternal::get_string(v)); }
	static GD_FORCE_INLINE void set(Variant *v, IPAddress p_value) { *VariantInternal::get_string(v) = p_value; }
};

template <>
struct VariantInternalAccessor<float> {
	static GD_FORCE_INLINE float get(const Variant *v) { return *VariantInternal::get_float(v); }
	static GD_FORCE_INLINE void set(Variant *v, float p_value) { *VariantInternal::get_float(v) = p_value; }
};

template <>
struct VariantInternalAccessor<double> {
	static GD_FORCE_INLINE double get(const Variant *v) { return *VariantInternal::get_float(v); }
	static GD_FORCE_INLINE void set(Variant *v, double p_value) { *VariantInternal::get_float(v) = p_value; }
};

template <>
struct VariantInternalAccessor<String> {
	static GD_FORCE_INLINE const String &get(const Variant *v) { return *VariantInternal::get_string(v); }
	static GD_FORCE_INLINE void set(Variant *v, const String &p_value) { *VariantInternal::get_string(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector2> {
	static GD_FORCE_INLINE const Vector2 &get(const Variant *v) { return *VariantInternal::get_vector2(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector2 &p_value) { *VariantInternal::get_vector2(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector2i> {
	static GD_FORCE_INLINE const Vector2i &get(const Variant *v) { return *VariantInternal::get_vector2i(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector2i &p_value) { *VariantInternal::get_vector2i(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Rect2> {
	static GD_FORCE_INLINE const Rect2 &get(const Variant *v) { return *VariantInternal::get_rect2(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Rect2 &p_value) { *VariantInternal::get_rect2(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Rect2i> {
	static GD_FORCE_INLINE const Rect2i &get(const Variant *v) { return *VariantInternal::get_rect2i(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Rect2i &p_value) { *VariantInternal::get_rect2i(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector3> {
	static GD_FORCE_INLINE const Vector3 &get(const Variant *v) { return *VariantInternal::get_vector3(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector3 &p_value) { *VariantInternal::get_vector3(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector3i> {
	static GD_FORCE_INLINE const Vector3i &get(const Variant *v) { return *VariantInternal::get_vector3i(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector3i &p_value) { *VariantInternal::get_vector3i(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector4> {
	static GD_FORCE_INLINE const Vector4 &get(const Variant *v) { return *VariantInternal::get_vector4(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector4 &p_value) { *VariantInternal::get_vector4(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Vector4i> {
	static GD_FORCE_INLINE const Vector4i &get(const Variant *v) { return *VariantInternal::get_vector4i(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Vector4i &p_value) { *VariantInternal::get_vector4i(v) = p_value; }
};
template <>
struct VariantInternalAccessor<Transform2D> {
	static GD_FORCE_INLINE const Transform2D &get(const Variant *v) { return *VariantInternal::get_transform2d(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Transform2D &p_value) { *VariantInternal::get_transform2d(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Transform3D> {
	static GD_FORCE_INLINE const Transform3D &get(const Variant *v) { return *VariantInternal::get_transform(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Transform3D &p_value) { *VariantInternal::get_transform(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Projection> {
	static GD_FORCE_INLINE const Projection &get(const Variant *v) { return *VariantInternal::get_projection(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Projection &p_value) { *VariantInternal::get_projection(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Plane> {
	static GD_FORCE_INLINE const Plane &get(const Variant *v) { return *VariantInternal::get_plane(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Plane &p_value) { *VariantInternal::get_plane(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Quaternion> {
	static GD_FORCE_INLINE const Quaternion &get(const Variant *v) { return *VariantInternal::get_quaternion(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Quaternion &p_value) { *VariantInternal::get_quaternion(v) = p_value; }
};

template <>
struct VariantInternalAccessor<AABB> {
	static GD_FORCE_INLINE const AABB &get(const Variant *v) { return *VariantInternal::get_aabb(v); }
	static GD_FORCE_INLINE void set(Variant *v, const AABB &p_value) { *VariantInternal::get_aabb(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Basis> {
	static GD_FORCE_INLINE const Basis &get(const Variant *v) { return *VariantInternal::get_basis(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Basis &p_value) { *VariantInternal::get_basis(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Color> {
	static GD_FORCE_INLINE const Color &get(const Variant *v) { return *VariantInternal::get_color(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Color &p_value) { *VariantInternal::get_color(v) = p_value; }
};

template <>
struct VariantInternalAccessor<StringName> {
	static GD_FORCE_INLINE const StringName &get(const Variant *v) { return *VariantInternal::get_string_name(v); }
	static GD_FORCE_INLINE void set(Variant *v, const StringName &p_value) { *VariantInternal::get_string_name(v) = p_value; }
};

template <>
struct VariantInternalAccessor<NodePath> {
	static GD_FORCE_INLINE const NodePath &get(const Variant *v) { return *VariantInternal::get_node_path(v); }
	static GD_FORCE_INLINE void set(Variant *v, const NodePath &p_value) { *VariantInternal::get_node_path(v) = p_value; }
};

template <>
struct VariantInternalAccessor<::RID> {
	static GD_FORCE_INLINE const ::RID &get(const Variant *v) { return *VariantInternal::get_rid(v); }
	static GD_FORCE_INLINE void set(Variant *v, const ::RID &p_value) { *VariantInternal::get_rid(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Callable> {
	static GD_FORCE_INLINE const Callable &get(const Variant *v) { return *VariantInternal::get_callable(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Callable &p_value) { *VariantInternal::get_callable(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Signal> {
	static GD_FORCE_INLINE const Signal &get(const Variant *v) { return *VariantInternal::get_signal(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Signal &p_value) { *VariantInternal::get_signal(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Dictionary> {
	static GD_FORCE_INLINE const Dictionary &get(const Variant *v) { return *VariantInternal::get_dictionary(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Dictionary &p_value) { *VariantInternal::get_dictionary(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Array> {
	static GD_FORCE_INLINE const Array &get(const Variant *v) { return *VariantInternal::get_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const Array &p_value) { *VariantInternal::get_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedByteArray> {
	static GD_FORCE_INLINE const PackedByteArray &get(const Variant *v) { return *VariantInternal::get_byte_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedByteArray &p_value) { *VariantInternal::get_byte_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedInt32Array> {
	static GD_FORCE_INLINE const PackedInt32Array &get(const Variant *v) { return *VariantInternal::get_int32_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedInt32Array &p_value) { *VariantInternal::get_int32_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedInt64Array> {
	static GD_FORCE_INLINE const PackedInt64Array &get(const Variant *v) { return *VariantInternal::get_int64_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedInt64Array &p_value) { *VariantInternal::get_int64_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedFloat32Array> {
	static GD_FORCE_INLINE const PackedFloat32Array &get(const Variant *v) { return *VariantInternal::get_float32_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedFloat32Array &p_value) { *VariantInternal::get_float32_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedFloat64Array> {
	static GD_FORCE_INLINE const PackedFloat64Array &get(const Variant *v) { return *VariantInternal::get_float64_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedFloat64Array &p_value) { *VariantInternal::get_float64_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedStringArray> {
	static GD_FORCE_INLINE const PackedStringArray &get(const Variant *v) { return *VariantInternal::get_string_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedStringArray &p_value) { *VariantInternal::get_string_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedVector2Array> {
	static GD_FORCE_INLINE const PackedVector2Array &get(const Variant *v) { return *VariantInternal::get_vector2_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedVector2Array &p_value) { *VariantInternal::get_vector2_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedVector3Array> {
	static GD_FORCE_INLINE const PackedVector3Array &get(const Variant *v) { return *VariantInternal::get_vector3_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedVector3Array &p_value) { *VariantInternal::get_vector3_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedColorArray> {
	static GD_FORCE_INLINE const PackedColorArray &get(const Variant *v) { return *VariantInternal::get_color_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedColorArray &p_value) { *VariantInternal::get_color_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<PackedVector4Array> {
	static GD_FORCE_INLINE const PackedVector4Array &get(const Variant *v) { return *VariantInternal::get_vector4_array(v); }
	static GD_FORCE_INLINE void set(Variant *v, const PackedVector4Array &p_value) { *VariantInternal::get_vector4_array(v) = p_value; }
};

template <>
struct VariantInternalAccessor<Object *> {
	static GD_FORCE_INLINE Object *get(const Variant *v) { return const_cast<Object *>(*VariantInternal::get_object(v)); }
	static GD_FORCE_INLINE void set(Variant *v, const Object *p_value) { VariantInternal::object_assign(v, p_value); }
};

template <>
struct VariantInternalAccessor<Variant> {
	static GD_FORCE_INLINE Variant &get(Variant *v) { return *v; }
	static GD_FORCE_INLINE const Variant &get(const Variant *v) { return *v; }
	static GD_FORCE_INLINE void set(Variant *v, const Variant &p_value) { *v = p_value; }
};

template <>
struct VariantInternalAccessor<Vector<Variant>> {
	static GD_FORCE_INLINE Vector<Variant> get(const Variant *v) {
		Vector<Variant> ret;
		int s = VariantInternal::get_array(v)->size();
		ret.resize(s);
		for (int i = 0; i < s; i++) {
			ret.write[i] = VariantInternal::get_array(v)->get(i);
		}

		return ret;
	}
	static GD_FORCE_INLINE void set(Variant *v, const Vector<Variant> &p_value) {
		int s = p_value.size();
		VariantInternal::get_array(v)->resize(s);
		for (int i = 0; i < s; i++) {
			VariantInternal::get_array(v)->set(i, p_value[i]);
		}
	}
};

template <typename T>
struct VariantInitializer {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_generic<T>(v); }
};

template <>
struct VariantInitializer<String> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_string(v); }
};

template <>
struct VariantInitializer<Transform2D> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_transform2d(v); }
};

template <>
struct VariantInitializer<AABB> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_aabb(v); }
};

template <>
struct VariantInitializer<Basis> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_basis(v); }
};

template <>
struct VariantInitializer<Transform3D> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_transform3d(v); }
};

template <>
struct VariantInitializer<Projection> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_projection(v); }
};

template <>
struct VariantInitializer<StringName> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_string_name(v); }
};

template <>
struct VariantInitializer<NodePath> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_node_path(v); }
};

template <>
struct VariantInitializer<Callable> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_callable(v); }
};

template <>
struct VariantInitializer<Signal> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_signal(v); }
};

template <>
struct VariantInitializer<Dictionary> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_dictionary(v); }
};

template <>
struct VariantInitializer<Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_array(v); }
};

template <>
struct VariantInitializer<PackedByteArray> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_byte_array(v); }
};

template <>
struct VariantInitializer<PackedInt32Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_int32_array(v); }
};

template <>
struct VariantInitializer<PackedInt64Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_int64_array(v); }
};

template <>
struct VariantInitializer<PackedFloat32Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_float32_array(v); }
};

template <>
struct VariantInitializer<PackedFloat64Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_float64_array(v); }
};

template <>
struct VariantInitializer<PackedStringArray> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_string_array(v); }
};

template <>
struct VariantInitializer<PackedVector2Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_vector2_array(v); }
};

template <>
struct VariantInitializer<PackedVector3Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_vector3_array(v); }
};

template <>
struct VariantInitializer<PackedColorArray> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_color_array(v); }
};

template <>
struct VariantInitializer<PackedVector4Array> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_vector4_array(v); }
};

template <>
struct VariantInitializer<Object *> {
	static GD_FORCE_INLINE void init(Variant *v) { VariantInternal::init_object(v); }
};

template <typename T, typename = void>
struct VariantDefaultInitializer;

template <typename T>
struct VariantDefaultInitializer<T, std::enable_if_t<!std::is_same_v<T, GetSimpleTypeT<T>>>> : VariantDefaultInitializer<GetSimpleTypeT<T>> {};

template <>
struct VariantDefaultInitializer<bool> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_bool(v) = false; }
};

template <typename T>
struct VariantDefaultInitializer<T, std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_int(v) = 0; }
};

template <typename T>
struct VariantDefaultInitializer<BitField<T>, std::enable_if_t<std::is_enum_v<T>>> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_int(v) = 0; }
};

template <>
struct VariantDefaultInitializer<double> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_float(v) = 0.0; }
};

template <>
struct VariantDefaultInitializer<float> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_float(v) = 0.0; }
};

template <>
struct VariantDefaultInitializer<String> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_string(v) = String(); }
};

template <>
struct VariantDefaultInitializer<Vector2> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector2(v) = Vector2(); }
};

template <>
struct VariantDefaultInitializer<Vector2i> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector2i(v) = Vector2i(); }
};

template <>
struct VariantDefaultInitializer<Rect2> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_rect2(v) = Rect2(); }
};

template <>
struct VariantDefaultInitializer<Rect2i> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_rect2i(v) = Rect2i(); }
};

template <>
struct VariantDefaultInitializer<Vector3> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector3(v) = Vector3(); }
};

template <>
struct VariantDefaultInitializer<Vector3i> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector3i(v) = Vector3i(); }
};

template <>
struct VariantDefaultInitializer<Vector4> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector4(v) = Vector4(); }
};

template <>
struct VariantDefaultInitializer<Vector4i> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector4i(v) = Vector4i(); }
};

template <>
struct VariantDefaultInitializer<Transform2D> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_transform2d(v) = Transform2D(); }
};

template <>
struct VariantDefaultInitializer<Plane> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_plane(v) = Plane(); }
};

template <>
struct VariantDefaultInitializer<Quaternion> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_quaternion(v) = Quaternion(); }
};

template <>
struct VariantDefaultInitializer<AABB> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_aabb(v) = AABB(); }
};

template <>
struct VariantDefaultInitializer<Basis> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_basis(v) = Basis(); }
};

template <>
struct VariantDefaultInitializer<Transform3D> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_transform(v) = Transform3D(); }
};

template <>
struct VariantDefaultInitializer<Projection> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_projection(v) = Projection(); }
};

template <>
struct VariantDefaultInitializer<Color> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_color(v) = Color(); }
};

template <>
struct VariantDefaultInitializer<StringName> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_string_name(v) = StringName(); }
};

template <>
struct VariantDefaultInitializer<NodePath> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_node_path(v) = NodePath(); }
};

template <>
struct VariantDefaultInitializer<::RID> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_rid(v) = RID(); }
};

template <>
struct VariantDefaultInitializer<Callable> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_callable(v) = Callable(); }
};

template <>
struct VariantDefaultInitializer<Signal> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_signal(v) = Signal(); }
};

template <>
struct VariantDefaultInitializer<Dictionary> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_dictionary(v) = Dictionary(); }
};

template <>
struct VariantDefaultInitializer<Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_array(v) = Array(); }
};

template <>
struct VariantDefaultInitializer<PackedByteArray> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_byte_array(v) = PackedByteArray(); }
};

template <>
struct VariantDefaultInitializer<PackedInt32Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_int32_array(v) = PackedInt32Array(); }
};

template <>
struct VariantDefaultInitializer<PackedInt64Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_int64_array(v) = PackedInt64Array(); }
};

template <>
struct VariantDefaultInitializer<PackedFloat32Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_float32_array(v) = PackedFloat32Array(); }
};

template <>
struct VariantDefaultInitializer<PackedFloat64Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_float64_array(v) = PackedFloat64Array(); }
};

template <>
struct VariantDefaultInitializer<PackedStringArray> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_string_array(v) = PackedStringArray(); }
};

template <>
struct VariantDefaultInitializer<PackedVector2Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector2_array(v) = PackedVector2Array(); }
};

template <>
struct VariantDefaultInitializer<PackedVector3Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector3_array(v) = PackedVector3Array(); }
};

template <>
struct VariantDefaultInitializer<PackedColorArray> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_color_array(v) = PackedColorArray(); }
};

template <>
struct VariantDefaultInitializer<PackedVector4Array> {
	static GD_FORCE_INLINE void init(Variant *v) { *VariantInternal::get_vector4_array(v) = PackedVector4Array(); }
};

template <typename T>
struct VariantTypeChanger {
	static GD_FORCE_INLINE void change(Variant *v) {
		if (v->get_type() != GetTypeInfo<T>::VARIANT_TYPE || GetTypeInfo<T>::VARIANT_TYPE >= Variant::PACKED_BYTE_ARRAY) { //second condition removed by optimizer
			VariantInternal::clear(v);
			VariantInitializer<T>::init(v);
		}
	}
	static GD_FORCE_INLINE void change_and_reset(Variant *v) {
		if (v->get_type() != GetTypeInfo<T>::VARIANT_TYPE || GetTypeInfo<T>::VARIANT_TYPE >= Variant::PACKED_BYTE_ARRAY) { //second condition removed by optimizer
			VariantInternal::clear(v);
			VariantInitializer<T>::init(v);
		}

		VariantDefaultInitializer<T>::init(v);
	}
};

template <typename T>
struct VariantTypeAdjust {
	GD_FORCE_INLINE static void adjust(Variant *r_ret) {
		VariantTypeChanger<GetSimpleTypeT<T>>::change(r_ret);
	}
};

template <>
struct VariantTypeAdjust<Variant> {
	GD_FORCE_INLINE static void adjust(Variant *r_ret) {
		// Do nothing for variant.
	}
};

template <>
struct VariantTypeAdjust<Object *> {
	GD_FORCE_INLINE static void adjust(Variant *r_ret) {
		VariantInternal::clear(r_ret);
		*r_ret = (Object *)nullptr;
	}
};

// GDExtension helpers.

template <typename T>
struct VariantTypeConstructor {
	GD_FORCE_INLINE static void variant_from_type(void *r_variant, void *p_value) {
		// r_variant is provided by caller as uninitialized memory
		memnew_placement(r_variant, Variant(*((T *)p_value)));
	}

	GD_FORCE_INLINE static void type_from_variant(void *r_value, void *p_variant) {
		// r_value is provided by caller as uninitialized memory
		memnew_placement(r_value, T(*reinterpret_cast<Variant *>(p_variant)));
	}
};
