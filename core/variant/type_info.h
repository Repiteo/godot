/**************************************************************************/
/*  type_info.h                                                           */
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

#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include "core/typedefs.h"
#include "core/variant/variant_enums.h"
#include <cstdint>

class Variant;
class String;
struct Vector2;
struct Vector2i;
struct Rect2;
struct Rect2i;
struct Vector3;
struct Vector3i;
struct Transform2D;
struct Vector4;
struct Vector4i;
struct Plane;
struct Quaternion;
struct AABB;
struct Basis;
struct Transform3D;
struct Projection;
struct Color;
class StringName;
class NodePath;
class RID;
class Object;
class ObjectID;
class Callable;
class Signal;
class Dictionary;
class Array;
struct IPAddress;
struct Face3;

template <typename T>
class TypedArray;
template <typename K, typename V>
class TypedDictionary;
template <typename T>
class Ref;
template <typename T>
class BitField;
template <typename T>
class Vector;

using PackedByteArray = Vector<uint8_t>;
using PackedInt32Array = Vector<int32_t>;
using PackedInt64Array = Vector<int64_t>;
using PackedFloat32Array = Vector<float>;
using PackedFloat64Array = Vector<double>;
using PackedStringArray = Vector<String>;
using PackedVector2Array = Vector<Vector2>;
using PackedVector3Array = Vector<Vector3>;
using PackedColorArray = Vector<Color>;
using PackedVector4Array = Vector<Vector4>;

// namespace godot {
// namespace details {

// template <typename T>
// struct _IsVector {
// 	static constexpr bool value() { return false; }
// };

// template <typename T>
// struct _IsVector<Vector<T>> {
// 	static constexpr bool value() { return true; }
// };

// } // namespace details
// } // namespace godot

// template <typename T>
// inline constexpr bool is_vector_v = godot::details::_IsVector<std::decay_t<T>>::value();

namespace godot {
namespace details {

template <typename T>
struct _VariantType {
	static constexpr VariantType value() {
		if constexpr (std::is_same_v<T, Variant>) {
			return VariantType::NIL;
		} else if constexpr (std::is_same_v<T, bool>) {
			return VariantType::BOOL;
		} else if constexpr (std::is_integral_v<T> || std::is_enum_v<T> || std::is_same_v<T, ObjectID>) {
			return VariantType::INT;
		} else if constexpr (std::is_floating_point_v<T>) {
			return VariantType::FLOAT;
		} else if constexpr (std::is_same_v<T, String> || std::is_same_v<T, IPAddress> || std::is_same_v<T, char *> || std::is_same_v<T, char16_t *> || std::is_same_v<T, char32_t *> || std::is_same_v<T, wchar_t *>) {
			return VariantType::STRING;
		} else if constexpr (std::is_same_v<T, Vector2>) {
			return VariantType::VECTOR2;
		} else if constexpr (std::is_same_v<T, Vector2i>) {
			return VariantType::VECTOR2I;
		} else if constexpr (std::is_same_v<T, Rect2>) {
			return VariantType::RECT2;
		} else if constexpr (std::is_same_v<T, Rect2i>) {
			return VariantType::RECT2I;
		} else if constexpr (std::is_same_v<T, Vector3>) {
			return VariantType::VECTOR3;
		} else if constexpr (std::is_same_v<T, Vector3i>) {
			return VariantType::VECTOR3I;
		} else if constexpr (std::is_same_v<T, Transform2D>) {
			return VariantType::TRANSFORM2D;
		} else if constexpr (std::is_same_v<T, Vector4>) {
			return VariantType::VECTOR4;
		} else if constexpr (std::is_same_v<T, Vector4i>) {
			return VariantType::VECTOR4I;
		} else if constexpr (std::is_same_v<T, Plane>) {
			return VariantType::PLANE;
		} else if constexpr (std::is_same_v<T, Quaternion>) {
			return VariantType::QUATERNION;
		} else if constexpr (std::is_same_v<T, ::AABB>) {
			return VariantType::AABB;
		} else if constexpr (std::is_same_v<T, Basis>) {
			return VariantType::BASIS;
		} else if constexpr (std::is_same_v<T, Transform3D>) {
			return VariantType::TRANSFORM3D;
		} else if constexpr (std::is_same_v<T, Projection>) {
			return VariantType::PROJECTION;
		} else if constexpr (std::is_same_v<T, Color>) {
			return VariantType::COLOR;
		} else if constexpr (std::is_same_v<T, StringName>) {
			return VariantType::STRING_NAME;
		} else if constexpr (std::is_same_v<T, NodePath>) {
			return VariantType::NODE_PATH;
		} else if constexpr (std::is_same_v<T, ::RID>) {
			return VariantType::RID;
		} else if constexpr (std::is_pointer_v<T>) {
			return VariantType::OBJECT;
		} else if constexpr (std::is_same_v<T, Callable>) {
			return VariantType::CALLABLE;
		} else if constexpr (std::is_same_v<T, Signal>) {
			return VariantType::SIGNAL;
		} else if constexpr (std::is_same_v<T, Dictionary>) {
			return VariantType::DICTIONARY;
		} else if constexpr (std::is_same_v<T, Array>) {
			return VariantType::ARRAY;
		} else if constexpr (std::is_same_v<T, PackedByteArray>) {
			return VariantType::PACKED_BYTE_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedInt32Array>) {
			return VariantType::PACKED_INT32_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedInt64Array>) {
			return VariantType::PACKED_INT64_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedFloat32Array>) {
			return VariantType::PACKED_FLOAT32_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedFloat64Array>) {
			return VariantType::PACKED_FLOAT64_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedStringArray> || std::is_same_v<T, Vector<StringName>>) {
			return VariantType::PACKED_STRING_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedVector2Array>) {
			return VariantType::PACKED_VECTOR2_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedVector3Array> || std::is_same_v<T, Vector<Face3>>) {
			return VariantType::PACKED_VECTOR3_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedColorArray>) {
			return VariantType::PACKED_COLOR_ARRAY;
		} else if constexpr (std::is_same_v<T, PackedVector4Array>) {
			return VariantType::PACKED_VECTOR4_ARRAY;
		} else {
			static_assert(false, "Unassigned variant type!");
		}
	}
};

// Special case for Vector.
template <typename T>
struct _VariantType<Vector<T>> {
	static constexpr VariantType value() {
		if constexpr (std::is_same_v<T, uint8_t>) {
			return VariantType::PACKED_BYTE_ARRAY;
		} else if constexpr (std::is_same_v<T, int32_t>) {
			return VariantType::PACKED_INT32_ARRAY;
		} else if constexpr (std::is_same_v<T, int64_t>) {
			return VariantType::PACKED_INT64_ARRAY;
		} else if constexpr (std::is_same_v<T, float>) {
			return VariantType::PACKED_FLOAT32_ARRAY;
		} else if constexpr (std::is_same_v<T, double>) {
			return VariantType::PACKED_FLOAT64_ARRAY;
		} else if constexpr (std::is_same_v<T, String> || std::is_same_v<T, StringName>) {
			return VariantType::PACKED_STRING_ARRAY;
		} else if constexpr (std::is_same_v<T, Vector2>) {
			return VariantType::PACKED_VECTOR2_ARRAY;
		} else if constexpr (std::is_same_v<T, Vector3> || std::is_same_v<T, Face3>) {
			return VariantType::PACKED_VECTOR3_ARRAY;
		} else if constexpr (std::is_same_v<T, Color>) {
			return VariantType::PACKED_COLOR_ARRAY;
		} else if constexpr (std::is_same_v<T, Vector4>) {
			return VariantType::PACKED_VECTOR4_ARRAY;
		} else {
			return VariantType::ARRAY;
		}
	}
};

} // namespace details
} // namespace godot

template <typename T>
inline constexpr VariantType variant_type_v = godot::details::_VariantType<std::decay_t<T>>::value();

#define ADD_VARIANT_TYPE_TEMPLATED(m_template, m_type, m_variant_type) \
	template <m_template>                                              \
	struct godot::details::_VariantType<m_type> {                      \
		static constexpr VariantType value() {                         \
			return m_variant_type;                                     \
		}                                                              \
	};
#define ADD_VARIANT_TYPE(m_type, m_variant_type) ADD_VARIANT_TYPE_TEMPLATED(, m_type, m_variant_type)

ADD_VARIANT_TYPE_TEMPLATED(typename T, Ref<T>, OBJECT)
ADD_VARIANT_TYPE_TEMPLATED(typename T, BitField<T>, INT)
ADD_VARIANT_TYPE_TEMPLATED(typename T, TypedArray<T>, ARRAY)
#define _COMMA ,
ADD_VARIANT_TYPE_TEMPLATED(typename K _COMMA typename V, TypedDictionary<K _COMMA V>, DICTIONARY)

namespace GodotTypeInfo {
enum Metadata {
	METADATA_NONE,
	METADATA_INT_IS_INT8,
	METADATA_INT_IS_INT16,
	METADATA_INT_IS_INT32,
	METADATA_INT_IS_INT64,
	METADATA_INT_IS_UINT8,
	METADATA_INT_IS_UINT16,
	METADATA_INT_IS_UINT32,
	METADATA_INT_IS_UINT64,
	METADATA_REAL_IS_FLOAT,
	METADATA_REAL_IS_DOUBLE,
	METADATA_INT_IS_CHAR16,
	METADATA_INT_IS_CHAR32,
};
}

namespace godot {
namespace details {
template <typename T>
struct _Metadata {
	static constexpr GodotTypeInfo::Metadata value() {
		if constexpr (std::is_same_v<T, int8_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_INT8;
		} else if constexpr (std::is_same_v<T, int16_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_INT16;
		} else if constexpr (std::is_same_v<T, int32_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_INT32;
		} else if constexpr (std::is_same_v<T, int64_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_INT64;
		} else if constexpr (std::is_same_v<T, uint8_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_UINT8;
		} else if constexpr (std::is_same_v<T, uint16_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_UINT16;
		} else if constexpr (std::is_same_v<T, uint32_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_UINT32;
		} else if constexpr (std::is_same_v<T, uint64_t> || std::is_same_v<T, ObjectID>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_UINT64;
		} else if constexpr (std::is_same_v<T, float>) {
			return GodotTypeInfo::Metadata::METADATA_REAL_IS_FLOAT;
		} else if constexpr (std::is_same_v<T, double>) {
			return GodotTypeInfo::Metadata::METADATA_REAL_IS_DOUBLE;
		} else if constexpr (std::is_same_v<T, char16_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_CHAR16;
		} else if constexpr (std::is_same_v<T, char32_t>) {
			return GodotTypeInfo::Metadata::METADATA_INT_IS_CHAR32;
		} else {
			return GodotTypeInfo::Metadata::METADATA_NONE;
		}
	}
};

} // namespace details
} // namespace godot

template <typename T>
inline constexpr GodotTypeInfo::Metadata metadata_v = godot::details::_Metadata<std::decay_t<T>>::value();

#define ADD_METADATA_TEMPLATED(m_template, m_type, m_metadata) \
	template <m_template>                                      \
	struct godot::details::_Metadata<m_type> {                 \
		static constexpr GodotTypeInfo::MetaData value() {     \
			return m_metadata;                                 \
		}                                                      \
	};
#define ADD_METADATA(m_type, m_metadata) ADD_METADATA_TEMPLATED(, m_type, m_metadata)

// // If the compiler fails because it's trying to instantiate the primary 'GetTypeInfo' template
// // instead of one of the specializations, it's most likely because the type 'T' is not supported.
// // If 'T' is a class that inherits 'Object', make sure it can see the actual class declaration
// // instead of a forward declaration. You can always forward declare 'T' in a header file, and then
// // include the actual declaration of 'T' in the source file where 'GetTypeInfo<T>' is instantiated.
// template <typename T, typename = void>
// struct GetTypeInfo;

template <typename T>
struct GetTypeInfo {
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(variant_type_v<T>, String());
	}
};

//objectID
template <>
struct GetTypeInfo<ObjectID> {
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::INT, String(), PROPERTY_HINT_INT_IS_OBJECTID);
	}
};

//for variant
template <>
struct GetTypeInfo<Variant> {
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::NIL, String(), PROPERTY_HINT_NONE, String(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT);
	}
};

template <>
struct GetTypeInfo<const Variant &> {
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::NIL, String(), PROPERTY_HINT_NONE, String(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT);
	}
};

template <typename T>
struct GetTypeInfo<T *> {
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(StringName(T::get_class_static()));
	}
};

namespace godot {
namespace details {
inline String enum_qualified_name_to_class_info_name(const String &p_qualified_name) {
	Vector<String> parts = p_qualified_name.split("::", false);
	if (parts.size() <= 2) {
		return String(".").join(parts);
	}
	// Contains namespace. We only want the class and enum names.
	return parts[parts.size() - 2] + "." + parts[parts.size() - 1];
}
} // namespace details
} // namespace godot

#define TEMPL_MAKE_ENUM_TYPE_INFO(m_enum, m_impl)                                                                                            \
	template <>                                                                                                                              \
	struct GetTypeInfo<m_impl> {                                                                                                             \
		static const Variant::Type VARIANT_TYPE = Variant::INT;                                                                              \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                        \
		static inline PropertyInfo get_class_info() {                                                                                        \
			return PropertyInfo(Variant::INT, String(), PROPERTY_HINT_NONE, String(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_CLASS_IS_ENUM, \
					godot::details::enum_qualified_name_to_class_info_name(String(#m_enum)));                                                \
		}                                                                                                                                    \
	};

#define MAKE_ENUM_TYPE_INFO(m_enum)                 \
	TEMPL_MAKE_ENUM_TYPE_INFO(m_enum, m_enum)       \
	TEMPL_MAKE_ENUM_TYPE_INFO(m_enum, m_enum const) \
	TEMPL_MAKE_ENUM_TYPE_INFO(m_enum, m_enum &)     \
	TEMPL_MAKE_ENUM_TYPE_INFO(m_enum, const m_enum &)

template <typename T>
inline StringName __constant_get_enum_name(T param, const String &p_constant) {
	return GetTypeInfo<T>::get_class_info().class_name;
}

template <typename T>
class BitField {
	int64_t value = 0;

public:
	_FORCE_INLINE_ BitField<T> &set_flag(T p_flag) {
		value |= (int64_t)p_flag;
		return *this;
	}
	_FORCE_INLINE_ bool has_flag(T p_flag) const { return value & (int64_t)p_flag; }
	_FORCE_INLINE_ bool is_empty() const { return value == 0; }
	_FORCE_INLINE_ void clear_flag(T p_flag) { value &= ~(int64_t)p_flag; }
	_FORCE_INLINE_ void clear() { value = 0; }
	_FORCE_INLINE_ constexpr BitField() = default;
	_FORCE_INLINE_ constexpr BitField(int64_t p_value) { value = p_value; }
	_FORCE_INLINE_ constexpr BitField(T p_value) { value = (int64_t)p_value; }
	_FORCE_INLINE_ operator int64_t() const { return value; }
	_FORCE_INLINE_ operator Variant() const { return value; }
	_FORCE_INLINE_ BitField<T> operator^(const BitField<T> &p_b) const { return BitField<T>(value ^ p_b.value); }
};

#define TEMPL_MAKE_BITFIELD_TYPE_INFO(m_enum, m_impl)                                                                                            \
	template <>                                                                                                                                  \
	struct GetTypeInfo<m_impl> {                                                                                                                 \
		static const Variant::Type VARIANT_TYPE = Variant::INT;                                                                                  \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                            \
		static inline PropertyInfo get_class_info() {                                                                                            \
			return PropertyInfo(Variant::INT, String(), PROPERTY_HINT_NONE, String(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_CLASS_IS_BITFIELD, \
					godot::details::enum_qualified_name_to_class_info_name(String(#m_enum)));                                                    \
		}                                                                                                                                        \
	};                                                                                                                                           \
	template <>                                                                                                                                  \
	struct GetTypeInfo<BitField<m_impl>> {                                                                                                       \
		static const Variant::Type VARIANT_TYPE = Variant::INT;                                                                                  \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                            \
		static inline PropertyInfo get_class_info() {                                                                                            \
			return PropertyInfo(Variant::INT, String(), PROPERTY_HINT_NONE, String(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_CLASS_IS_BITFIELD, \
					godot::details::enum_qualified_name_to_class_info_name(String(#m_enum)));                                                    \
		}                                                                                                                                        \
	};

#define MAKE_BITFIELD_TYPE_INFO(m_enum)                 \
	TEMPL_MAKE_BITFIELD_TYPE_INFO(m_enum, m_enum)       \
	TEMPL_MAKE_BITFIELD_TYPE_INFO(m_enum, m_enum const) \
	TEMPL_MAKE_BITFIELD_TYPE_INFO(m_enum, m_enum &)     \
	TEMPL_MAKE_BITFIELD_TYPE_INFO(m_enum, const m_enum &)

template <typename T>
inline StringName __constant_get_bitfield_name(T param, const String &p_constant) {
	return GetTypeInfo<BitField<T>>::get_class_info().class_name;
}
#define CLASS_INFO(m_type) (GetTypeInfo<m_type *>::get_class_info())

template <typename T>
struct ZeroInitializer {
	static void initialize(T &value) {} //no initialization by default
};

template <>
struct ZeroInitializer<bool> {
	static void initialize(bool &value) { value = false; }
};

template <typename T>
struct ZeroInitializer<T *> {
	static void initialize(T *&value) { value = nullptr; }
};

#define ZERO_INITIALIZER_NUMBER(m_type)         \
	template <>                                 \
	struct ZeroInitializer<m_type> {            \
		static void initialize(m_type &value) { \
			value = 0;                          \
		}                                       \
	};

ZERO_INITIALIZER_NUMBER(uint8_t)
ZERO_INITIALIZER_NUMBER(int8_t)
ZERO_INITIALIZER_NUMBER(uint16_t)
ZERO_INITIALIZER_NUMBER(int16_t)
ZERO_INITIALIZER_NUMBER(uint32_t)
ZERO_INITIALIZER_NUMBER(int32_t)
ZERO_INITIALIZER_NUMBER(uint64_t)
ZERO_INITIALIZER_NUMBER(int64_t)
ZERO_INITIALIZER_NUMBER(char16_t)
ZERO_INITIALIZER_NUMBER(char32_t)
ZERO_INITIALIZER_NUMBER(float)
ZERO_INITIALIZER_NUMBER(double)

#endif // TYPE_INFO_H
