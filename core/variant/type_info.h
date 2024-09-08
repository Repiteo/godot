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

#include "core/templates/simple_type.h"
#include "core/typedefs.h"

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
	METADATA_REAL_IS_DOUBLE
};

template <typename T>
struct _VariantType {
	static constexpr Variant::Type value() {
		if constexpr (std::is_base_of_v<Object, std::remove_pointer_t<T>>) {
			return Variant::OBJECT;
		} else if constexpr (std::is_enum_v<T>) {
			return Variant::INT;
		} else {
			static_assert(false, "Value is not a Variant type, or is not yet bound.");
		}
	}
};
template <typename T>
inline constexpr Variant::Type variant_type_v = _VariantType<GetSimpleTypeT<T>>::value();

template <typename T>
struct _Metadata {
	static constexpr Metadata value() { return METADATA_NONE; }
};
template <typename T>
inline constexpr Metadata metadata_v = _Metadata<GetSimpleTypeT<T>>::value();

template <typename T>
struct _PropertyHint {
	static constexpr PropertyHint value() { return PROPERTY_HINT_NONE; }
};
template <typename T>
inline constexpr PropertyHint property_hint_v = _PropertyHint<GetSimpleTypeT<T>>::value();

template <typename T>
struct _PropertyUsage {
	static constexpr PropertyUsageFlags value() {
		if constexpr (std::is_enum_v<T>) {
			return static_cast<PropertyUsageFlags>(PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_CLASS_IS_ENUM);
		} else {
			return PROPERTY_USAGE_DEFAULT;
		}
	}
};
template <typename T>
inline constexpr PropertyUsageFlags property_usage_v = _PropertyUsage<GetSimpleTypeT<T>>::value();

template <typename T>
struct _HintString {
	static inline String value() { return String(); }
};
template <typename T>
inline String hint_string_v = _HintString<GetSimpleTypeT<T>>::value();

template <typename T>
struct _ClassName {
	static inline String value() {
		if constexpr (variant_type_v<T> == Variant::OBJECT) {
			return std::remove_pointer_t<T>::get_class_static();
		} else {
			return String();
		}
	}
};
template <typename T>
inline String class_name_v = _ClassName<GetSimpleTypeT<T>>::value();

inline constexpr const char *_variant_names[Variant::VARIANT_MAX] = {
	"Variant",
	"bool",
	"int",
	"float",
	"String",
	"Vector2",
	"Vector2i",
	"Rect2",
	"Rect2i",
	"Vector3",
	"Vector3i",
	"Transform2D",
	"Vector4",
	"Vector4i",
	"Plane",
	"Quaternion",
	"AABB",
	"Basis",
	"Transform3D",
	"Projection",
	"Color",
	"StringName",
	"NodePath",
	"RID",
	"Object",
	"Callable",
	"Signal",
	"Dictionary",
	"Array",
	"PackedByteArray",
	"PackedInt32Array",
	"PackedInt64Array",
	"PackedFloat32Array",
	"PackedFloat64Array",
	"PackedStringArray",
	"PackedVector2Array",
	"PackedVector3Array",
	"PackedColorArray",
	"PackedVector4Array",
};

template <typename T>
struct _ConstClassName {
	static constexpr const char *value() {
		if constexpr (variant_type_v<T> == Variant::OBJECT) {
			return std::remove_pointer_t<T>::_get_class_static();
		} else {
			return _variant_names[variant_type_v<T>];
		}
	}
};
template <typename T>
inline constexpr const char *const_class_name_v = _ConstClassName<GetSimpleTypeT<T>>::value();

} //namespace GodotTypeInfo

#define GTI GodotTypeInfo

#define GTI_TMPL_VARIANT_TYPE(m_template, m_type, m_var_type)         \
	template <m_template>                                             \
	struct GodotTypeInfo::_VariantType<m_type> {                      \
		static constexpr Variant::Type value() { return m_var_type; } \
	};
#define GTI_TMPL_METADATA(m_template, m_type, m_metadata)                       \
	template <m_template>                                                       \
	struct GodotTypeInfo::_Metadata<m_type> {                                   \
		static constexpr GodotTypeInfo::Metadata value() { return m_metadata; } \
	};
#define GTI_TMPL_HINT_STRING(m_template, m_type, m_hint_string) \
	template <m_template>                                       \
	struct GodotTypeInfo::_HintString<m_type> {                 \
		static inline String value() { return m_hint_string; }  \
	};
#define GTI_TMPL_PROPERTY_HINT(m_template, m_type, m_property_hint)       \
	template <m_template>                                                 \
	struct GodotTypeInfo::_PropertyHint<m_type> {                         \
		static constexpr PropertyHint value() { return m_property_hint; } \
	};
#define GTI_TMPL_PROPERTY_USAGE(m_template, m_type, m_property_usage)                                             \
	template <m_template>                                                                                         \
	struct GodotTypeInfo::_PropertyUsage<m_type> {                                                                \
		static constexpr PropertyUsageFlags value() { return static_cast<PropertyUsageFlags>(m_property_usage); } \
	};
#define GTI_TMPL_CLASS_NAME(m_template, m_type, m_class_name) \
	template <m_template>                                     \
	struct GodotTypeInfo::_ClassName<m_type> {                \
		static inline String value() { return m_class_name; } \
	};

#define GTI_VARIANT_TYPE(m_type, m_var_type) GTI_TMPL_VARIANT_TYPE(, m_type, m_var_type)
#define GTI_METADATA(m_type, m_metadata) GTI_TMPL_METADATA(, m_type, m_metadata)
#define GTI_HINT_STRING(m_type, m_hint_string) GTI_TMPL_HINT_STRING(, m_type, m_hint_string)
#define GTI_PROPERTY_HINT(m_type, m_property_hint) GTI_TMPL_PROPERTY_HINT(, m_type, m_property_hint)
#define GTI_PROPERTY_USAGE(m_type, m_property_usage) GTI_TMPL_PROPERTY_USAGE(, m_type, m_property_usage)
#define GTI_CLASS_NAME(m_type, m_class_name) GTI_TMPL_CLASS_NAME(, m_type, m_class_name)

GTI_VARIANT_TYPE(Variant, Variant::NIL)
GTI_PROPERTY_USAGE(Variant, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT)
GTI_VARIANT_TYPE(bool, Variant::BOOL)
GTI_VARIANT_TYPE(uint8_t, Variant::INT)
GTI_METADATA(uint8_t, GodotTypeInfo::METADATA_INT_IS_UINT8)
GTI_VARIANT_TYPE(int8_t, Variant::INT)
GTI_METADATA(int8_t, GodotTypeInfo::METADATA_INT_IS_INT8)
GTI_VARIANT_TYPE(uint16_t, Variant::INT)
GTI_METADATA(uint16_t, GodotTypeInfo::METADATA_INT_IS_UINT16)
GTI_VARIANT_TYPE(int16_t, Variant::INT)
GTI_METADATA(int16_t, GodotTypeInfo::METADATA_INT_IS_INT16)
GTI_VARIANT_TYPE(uint32_t, Variant::INT)
GTI_METADATA(uint32_t, GodotTypeInfo::METADATA_INT_IS_UINT32)
GTI_VARIANT_TYPE(int32_t, Variant::INT)
GTI_METADATA(int32_t, GodotTypeInfo::METADATA_INT_IS_INT32)
GTI_VARIANT_TYPE(uint64_t, Variant::INT)
GTI_METADATA(uint64_t, GodotTypeInfo::METADATA_INT_IS_UINT64)
GTI_VARIANT_TYPE(int64_t, Variant::INT)
GTI_METADATA(int64_t, GodotTypeInfo::METADATA_INT_IS_INT64)
GTI_VARIANT_TYPE(char16_t, Variant::INT)
GTI_VARIANT_TYPE(char32_t, Variant::INT)
GTI_VARIANT_TYPE(float, Variant::FLOAT)
GTI_METADATA(float, GodotTypeInfo::METADATA_REAL_IS_FLOAT)
GTI_VARIANT_TYPE(double, Variant::FLOAT)
GTI_METADATA(double, GodotTypeInfo::METADATA_REAL_IS_DOUBLE)
GTI_VARIANT_TYPE(ObjectID, Variant::INT)
GTI_METADATA(ObjectID, GodotTypeInfo::METADATA_INT_IS_UINT64)
GTI_PROPERTY_HINT(ObjectID, PROPERTY_HINT_INT_IS_OBJECTID)
GTI_VARIANT_TYPE(String, Variant::STRING)
GTI_VARIANT_TYPE(Vector2, Variant::VECTOR2)
GTI_VARIANT_TYPE(Rect2, Variant::RECT2)
GTI_VARIANT_TYPE(Vector3, Variant::VECTOR3)
GTI_VARIANT_TYPE(Vector2i, Variant::VECTOR2I)
GTI_VARIANT_TYPE(Rect2i, Variant::RECT2I)
GTI_VARIANT_TYPE(Vector3i, Variant::VECTOR3I)
GTI_VARIANT_TYPE(Vector4, Variant::VECTOR4)
GTI_VARIANT_TYPE(Vector4i, Variant::VECTOR4I)
GTI_VARIANT_TYPE(Transform2D, Variant::TRANSFORM2D)
GTI_VARIANT_TYPE(Plane, Variant::PLANE)
GTI_VARIANT_TYPE(Quaternion, Variant::QUATERNION)
GTI_VARIANT_TYPE(AABB, Variant::AABB)
GTI_VARIANT_TYPE(Basis, Variant::BASIS)
GTI_VARIANT_TYPE(Transform3D, Variant::TRANSFORM3D)
GTI_VARIANT_TYPE(Projection, Variant::PROJECTION)
GTI_VARIANT_TYPE(Color, Variant::COLOR)
GTI_VARIANT_TYPE(StringName, Variant::STRING_NAME)
GTI_VARIANT_TYPE(NodePath, Variant::NODE_PATH)
GTI_VARIANT_TYPE(RID, Variant::RID)
GTI_VARIANT_TYPE(Callable, Variant::CALLABLE)
GTI_VARIANT_TYPE(Signal, Variant::SIGNAL)
GTI_VARIANT_TYPE(Dictionary, Variant::DICTIONARY)
GTI_VARIANT_TYPE(Array, Variant::ARRAY)
GTI_VARIANT_TYPE(PackedByteArray, Variant::PACKED_BYTE_ARRAY)
GTI_VARIANT_TYPE(PackedInt32Array, Variant::PACKED_INT32_ARRAY)
GTI_VARIANT_TYPE(PackedInt64Array, Variant::PACKED_INT64_ARRAY)
GTI_VARIANT_TYPE(PackedFloat32Array, Variant::PACKED_FLOAT32_ARRAY)
GTI_VARIANT_TYPE(PackedFloat64Array, Variant::PACKED_FLOAT64_ARRAY)
GTI_VARIANT_TYPE(PackedStringArray, Variant::PACKED_STRING_ARRAY)
GTI_VARIANT_TYPE(PackedVector2Array, Variant::PACKED_VECTOR2_ARRAY)
GTI_VARIANT_TYPE(PackedVector3Array, Variant::PACKED_VECTOR3_ARRAY)
GTI_VARIANT_TYPE(PackedColorArray, Variant::PACKED_COLOR_ARRAY)
GTI_VARIANT_TYPE(PackedVector4Array, Variant::PACKED_VECTOR4_ARRAY)
GTI_VARIANT_TYPE(IPAddress, Variant::STRING)
GTI_VARIANT_TYPE(Vector<Variant>, Variant::ARRAY)
GTI_VARIANT_TYPE(Vector<RID>, Variant::ARRAY)
GTI_VARIANT_TYPE(Vector<Plane>, Variant::ARRAY)
GTI_VARIANT_TYPE(Vector<Face3>, Variant::PACKED_VECTOR3_ARRAY)
GTI_VARIANT_TYPE(Vector<StringName>, Variant::PACKED_STRING_ARRAY)

#undef GTI_VARIANT_TYPE
#undef GTI_VARIANT_TYPE

// Legacy TypeInfo retrieval system.

template <typename T>
struct GetTypeInfo {
	static constexpr Variant::Type VARIANT_TYPE = GTI::variant_type_v<T>;
	static constexpr GodotTypeInfo::Metadata METADATA = GTI::metadata_v<T>;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(GTI::variant_type_v<T>, String(), GTI::property_hint_v<T>, GTI::hint_string_v<T>, GTI::property_usage_v<T>, GTI::class_name_v<T>);
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

#define MAKE_ENUM_TYPE_INFO(m_enum) \
	GTI_CLASS_NAME(m_enum, godot::details::enum_qualified_name_to_class_info_name(String(#m_enum)))

template <typename T>
inline StringName __constant_get_enum_name(T param, const String &p_constant) {
	String name = GTI::class_name_v<T>;
	if (name.is_empty()) {
		ERR_PRINT("Missing VARIANT_ENUM_CAST for constant's enum: " + p_constant);
	}
	return name;
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

GTI_TMPL_VARIANT_TYPE(typename T, BitField<T>, Variant::INT)
GTI_TMPL_PROPERTY_USAGE(typename T, BitField<T>, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_CLASS_IS_BITFIELD)

#define MAKE_BITFIELD_TYPE_INFO(m_enum)                                                             \
	GTI_CLASS_NAME(m_enum, godot::details::enum_qualified_name_to_class_info_name(String(#m_enum))) \
	GTI_CLASS_NAME(BitField<m_enum>, godot::details::enum_qualified_name_to_class_info_name(String(#m_enum)))

template <typename T>
inline StringName __constant_get_bitfield_name(T param, const String &p_constant) {
	String name = GTI::class_name_v<T>;
	if (name.is_empty()) {
		ERR_PRINT("Missing VARIANT_BITFIELD_CAST for constant's bitfield: " + p_constant);
	}
	return name;
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

#define ZERO_INITIALIZER_NUMBER(m_type)                      \
	template <>                                              \
	struct ZeroInitializer<m_type> {                         \
		static void initialize(m_type &value) { value = 0; } \
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
