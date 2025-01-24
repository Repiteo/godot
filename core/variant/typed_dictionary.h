/**************************************************************************/
/*  typed_dictionary.h                                                    */
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

#ifndef TYPED_DICTIONARY_H
#define TYPED_DICTIONARY_H

#include "core/object/object.h"
#include "core/variant/binder_common.h"
#include "core/variant/dictionary.h"
#include "core/variant/method_ptrcall.h"
#include "core/variant/type_info.h"
#include "core/variant/variant.h"

template <typename K, typename V>
class TypedDictionary : public Dictionary {
public:
	_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {
		ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign a dictionary with a different element type.");
		Dictionary::operator=(p_dictionary);
	}
	_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :
			TypedDictionary(Dictionary(p_variant)) {
	}
	_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {
		set_typed(VariantType::OBJECT, K::get_class_static(), Variant(), VariantType::OBJECT, V::get_class_static(), Variant());
		if (is_same_typed(p_dictionary)) {
			Dictionary::operator=(p_dictionary);
		} else {
			assign(p_dictionary);
		}
	}
	_FORCE_INLINE_ TypedDictionary() {
		set_typed(VariantType::OBJECT, K::get_class_static(), Variant(), VariantType::OBJECT, V::get_class_static(), Variant());
	}

	_FORCE_INLINE_ TypedDictionary(std::initializer_list<KeyValue<K, V>> p_init) :
			Dictionary() {
		set_typed(VariantType::OBJECT, K::get_class_static(), Variant(), VariantType::OBJECT, V::get_class_static(), Variant());
		for (const KeyValue<K, V> &E : p_init) {
			operator[](E.key) = E.value;
		}
	}
};

template <typename K, typename V>
struct VariantInternalAccessor<TypedDictionary<K, V>> {
	static _FORCE_INLINE_ TypedDictionary<K, V> get(const Variant *v) { return *VariantInternal::get_dictionary(v); }
	static _FORCE_INLINE_ void set(Variant *v, const TypedDictionary<K, V> &p_dictionary) { *VariantInternal::get_dictionary(v) = p_dictionary; }
};

template <typename K, typename V>
struct VariantInternalAccessor<const TypedDictionary<K, V> &> {
	static _FORCE_INLINE_ TypedDictionary<K, V> get(const Variant *v) { return *VariantInternal::get_dictionary(v); }
	static _FORCE_INLINE_ void set(Variant *v, const TypedDictionary<K, V> &p_dictionary) { *VariantInternal::get_dictionary(v) = p_dictionary; }
};

template <typename K, typename V>
struct PtrToArg<TypedDictionary<K, V>> {
	_FORCE_INLINE_ static TypedDictionary<K, V> convert(const void *p_ptr) {
		return TypedDictionary<K, V>(*reinterpret_cast<const Dictionary *>(p_ptr));
	}
	typedef Dictionary EncodeT;
	_FORCE_INLINE_ static void encode(TypedDictionary<K, V> p_val, void *p_ptr) {
		*(Dictionary *)p_ptr = p_val;
	}
};

template <typename K, typename V>
struct PtrToArg<const TypedDictionary<K, V> &> {
	typedef Dictionary EncodeT;
	_FORCE_INLINE_ static TypedDictionary<K, V>
	convert(const void *p_ptr) {
		return TypedDictionary<K, V>(*reinterpret_cast<const Dictionary *>(p_ptr));
	}
};

template <typename K, typename V>
struct GetTypeInfo<TypedDictionary<K, V>> {
	static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;
	static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE, vformat("%s;%s", K::get_class_static(), V::get_class_static()));
	}
};

template <typename K, typename V>
struct GetTypeInfo<const TypedDictionary<K, V> &> {
	static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;
	static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE, vformat("%s;%s", K::get_class_static(), V::get_class_static()));
	}
};

// Specialization for the rest of the Variant types.

#define MAKE_TYPED_DICTIONARY_WITH_OBJECT(m_type, m_variant_type)                                                                                      \
	template <typename T>                                                                                                                              \
	class TypedDictionary<T, m_type> : public Dictionary {                                                                                             \
	public:                                                                                                                                            \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                                                \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type.");                             \
			Dictionary::operator=(p_dictionary);                                                                                                       \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                                                     \
				TypedDictionary(Dictionary(p_variant)) {                                                                                               \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                                               \
			set_typed(VariantType::OBJECT, T::get_class_static(), Variant(), m_variant_type, StringName(), Variant());                                 \
			if (is_same_typed(p_dictionary)) {                                                                                                         \
				Dictionary::operator=(p_dictionary);                                                                                                   \
			} else {                                                                                                                                   \
				assign(p_dictionary);                                                                                                                  \
			}                                                                                                                                          \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary() {                                                                                                             \
			set_typed(VariantType::OBJECT, T::get_class_static(), Variant(), m_variant_type, StringName(), Variant());                                 \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary(std::initializer_list<KeyValue<T, m_type>> p_init) :                                                            \
				Dictionary() {                                                                                                                         \
			set_typed(VariantType::OBJECT, T::get_class_static(), Variant(), m_variant_type, StringName(), Variant());                                 \
			for (const KeyValue<T, m_type> &E : p_init) {                                                                                              \
				operator[](E.key) = E.value;                                                                                                           \
			}                                                                                                                                          \
		}                                                                                                                                              \
	};                                                                                                                                                 \
	template <typename T>                                                                                                                              \
	struct GetTypeInfo<TypedDictionary<T, m_type>> {                                                                                                   \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                                               \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                                  \
		static inline PropertyInfo get_class_info() {                                                                                                  \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                      \
					vformat("%s;%s", T::get_class_static(), m_variant_type == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type))); \
		}                                                                                                                                              \
	};                                                                                                                                                 \
	template <typename T>                                                                                                                              \
	struct GetTypeInfo<const TypedDictionary<T, m_type> &> {                                                                                           \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                                               \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                                  \
		static inline PropertyInfo get_class_info() {                                                                                                  \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                      \
					vformat("%s;%s", T::get_class_static(), m_variant_type == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type))); \
		}                                                                                                                                              \
	};                                                                                                                                                 \
	template <typename T>                                                                                                                              \
	class TypedDictionary<m_type, T> : public Dictionary {                                                                                             \
	public:                                                                                                                                            \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                                                \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type.");                             \
			Dictionary::operator=(p_dictionary);                                                                                                       \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                                                     \
				TypedDictionary(Dictionary(p_variant)) {                                                                                               \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                                               \
			set_typed(m_variant_type, StringName(), Variant(), VariantType::OBJECT, T::get_class_static(), Variant());                                 \
			if (is_same_typed(p_dictionary)) {                                                                                                         \
				Dictionary::operator=(p_dictionary);                                                                                                   \
			} else {                                                                                                                                   \
				assign(p_dictionary);                                                                                                                  \
			}                                                                                                                                          \
		}                                                                                                                                              \
		_FORCE_INLINE_ TypedDictionary() {                                                                                                             \
			set_typed(m_variant_type, StringName(), Variant(), VariantType::OBJECT, T::get_class_static(), Variant());                                 \
		}                                                                                                                                              \
	};                                                                                                                                                 \
	template <typename T>                                                                                                                              \
	struct GetTypeInfo<TypedDictionary<m_type, T>> {                                                                                                   \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                                               \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                                  \
		static inline PropertyInfo get_class_info() {                                                                                                  \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                      \
					vformat("%s;%s", m_variant_type == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type), T::get_class_static())); \
		}                                                                                                                                              \
	};                                                                                                                                                 \
	template <typename T>                                                                                                                              \
	struct GetTypeInfo<const TypedDictionary<m_type, T> &> {                                                                                           \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                                               \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                                  \
		static inline PropertyInfo get_class_info() {                                                                                                  \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                      \
					vformat("%s;%s", m_variant_type == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type), T::get_class_static())); \
		}                                                                                                                                              \
	};

#define MAKE_TYPED_DICTIONARY_EXPANDED(m_type_key, m_variant_type_key, m_type_value, m_variant_type_value)                            \
	template <>                                                                                                                       \
	class TypedDictionary<m_type_key, m_type_value> : public Dictionary {                                                             \
	public:                                                                                                                           \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                               \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type.");            \
			Dictionary::operator=(p_dictionary);                                                                                      \
		}                                                                                                                             \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                                    \
				TypedDictionary(Dictionary(p_variant)) {                                                                              \
		}                                                                                                                             \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                              \
			set_typed(m_variant_type_key, StringName(), Variant(), m_variant_type_value, StringName(), Variant());                    \
			if (is_same_typed(p_dictionary)) {                                                                                        \
				Dictionary::operator=(p_dictionary);                                                                                  \
			} else {                                                                                                                  \
				assign(p_dictionary);                                                                                                 \
			}                                                                                                                         \
		}                                                                                                                             \
		_FORCE_INLINE_ TypedDictionary() {                                                                                            \
			set_typed(m_variant_type_key, StringName(), Variant(), m_variant_type_value, StringName(), Variant());                    \
		}                                                                                                                             \
		_FORCE_INLINE_ TypedDictionary(std::initializer_list<KeyValue<m_type_key, m_type_value>> p_init) :                            \
				Dictionary() {                                                                                                        \
			set_typed(m_variant_type_key, StringName(), Variant(), m_variant_type_value, StringName(), Variant());                    \
			for (const KeyValue<m_type_key, m_type_value> &E : p_init) {                                                              \
				operator[](E.key) = E.value;                                                                                          \
			}                                                                                                                         \
		}                                                                                                                             \
	};                                                                                                                                \
	template <>                                                                                                                       \
	struct GetTypeInfo<TypedDictionary<m_type_key, m_type_value>> {                                                                   \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                              \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                 \
		static inline PropertyInfo get_class_info() {                                                                                 \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                     \
					vformat("%s;%s", m_variant_type_key == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type_key), \
							m_variant_type_value == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type_value)));    \
		}                                                                                                                             \
	};                                                                                                                                \
	template <>                                                                                                                       \
	struct GetTypeInfo<const TypedDictionary<m_type_key, m_type_value> &> {                                                           \
		static const VariantType VARIANT_TYPE = VariantType::DICTIONARY;                                                              \
		static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;                                                 \
		static inline PropertyInfo get_class_info() {                                                                                 \
			return PropertyInfo(VariantType::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                     \
					vformat("%s;%s", m_variant_type_key == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type_key), \
							m_variant_type_value == VariantType::NIL ? "Variant" : Variant::get_type_name(m_variant_type_value)));    \
		}                                                                                                                             \
	};

#define MAKE_TYPED_DICTIONARY_NIL(m_type, m_variant_type)                                                         \
	MAKE_TYPED_DICTIONARY_WITH_OBJECT(m_type, m_variant_type)                                                     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, bool, VariantType::BOOL)                               \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint8_t, VariantType::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int8_t, VariantType::INT)                              \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint16_t, VariantType::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int16_t, VariantType::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint32_t, VariantType::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int32_t, VariantType::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint64_t, VariantType::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int64_t, VariantType::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, float, VariantType::FLOAT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, double, VariantType::FLOAT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, String, VariantType::STRING)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector2, VariantType::VECTOR2)                         \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector2i, VariantType::VECTOR2I)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Rect2, VariantType::RECT2)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Rect2i, VariantType::RECT2I)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector3, VariantType::VECTOR3)                         \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector3i, VariantType::VECTOR3I)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Transform2D, VariantType::TRANSFORM2D)                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Plane, VariantType::PLANE)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Quaternion, VariantType::QUATERNION)                   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, AABB, VariantType::AABB)                               \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Basis, VariantType::BASIS)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Transform3D, VariantType::TRANSFORM3D)                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Color, VariantType::COLOR)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, StringName, VariantType::STRING_NAME)                  \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, NodePath, VariantType::NODE_PATH)                      \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, RID, VariantType::RID)                                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Callable, VariantType::CALLABLE)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Signal, VariantType::SIGNAL)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Dictionary, VariantType::DICTIONARY)                   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Array, VariantType::ARRAY)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedByteArray, VariantType::PACKED_BYTE_ARRAY)       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedInt32Array, VariantType::PACKED_INT32_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedInt64Array, VariantType::PACKED_INT64_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedFloat32Array, VariantType::PACKED_FLOAT32_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedFloat64Array, VariantType::PACKED_FLOAT64_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedStringArray, VariantType::PACKED_STRING_ARRAY)   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector2Array, VariantType::PACKED_VECTOR2_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector3Array, VariantType::PACKED_VECTOR3_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedColorArray, VariantType::PACKED_COLOR_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector4Array, VariantType::PACKED_VECTOR4_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, IPAddress, VariantType::STRING)

#define MAKE_TYPED_DICTIONARY(m_type, m_variant_type)                                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Variant, VariantType::NIL) \
	MAKE_TYPED_DICTIONARY_NIL(m_type, m_variant_type)

MAKE_TYPED_DICTIONARY_NIL(Variant, VariantType::NIL)
MAKE_TYPED_DICTIONARY(bool, VariantType::BOOL)
MAKE_TYPED_DICTIONARY(uint8_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(int8_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(uint16_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(int16_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(uint32_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(int32_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(uint64_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(int64_t, VariantType::INT)
MAKE_TYPED_DICTIONARY(float, VariantType::FLOAT)
MAKE_TYPED_DICTIONARY(double, VariantType::FLOAT)
MAKE_TYPED_DICTIONARY(String, VariantType::STRING)
MAKE_TYPED_DICTIONARY(Vector2, VariantType::VECTOR2)
MAKE_TYPED_DICTIONARY(Vector2i, VariantType::VECTOR2I)
MAKE_TYPED_DICTIONARY(Rect2, VariantType::RECT2)
MAKE_TYPED_DICTIONARY(Rect2i, VariantType::RECT2I)
MAKE_TYPED_DICTIONARY(Vector3, VariantType::VECTOR3)
MAKE_TYPED_DICTIONARY(Vector3i, VariantType::VECTOR3I)
MAKE_TYPED_DICTIONARY(Transform2D, VariantType::TRANSFORM2D)
MAKE_TYPED_DICTIONARY(Plane, VariantType::PLANE)
MAKE_TYPED_DICTIONARY(Quaternion, VariantType::QUATERNION)
MAKE_TYPED_DICTIONARY(AABB, VariantType::AABB)
MAKE_TYPED_DICTIONARY(Basis, VariantType::BASIS)
MAKE_TYPED_DICTIONARY(Transform3D, VariantType::TRANSFORM3D)
MAKE_TYPED_DICTIONARY(Color, VariantType::COLOR)
MAKE_TYPED_DICTIONARY(StringName, VariantType::STRING_NAME)
MAKE_TYPED_DICTIONARY(NodePath, VariantType::NODE_PATH)
MAKE_TYPED_DICTIONARY(RID, VariantType::RID)
MAKE_TYPED_DICTIONARY(Callable, VariantType::CALLABLE)
MAKE_TYPED_DICTIONARY(Signal, VariantType::SIGNAL)
MAKE_TYPED_DICTIONARY(Dictionary, VariantType::DICTIONARY)
MAKE_TYPED_DICTIONARY(Array, VariantType::ARRAY)
MAKE_TYPED_DICTIONARY(PackedByteArray, VariantType::PACKED_BYTE_ARRAY)
MAKE_TYPED_DICTIONARY(PackedInt32Array, VariantType::PACKED_INT32_ARRAY)
MAKE_TYPED_DICTIONARY(PackedInt64Array, VariantType::PACKED_INT64_ARRAY)
MAKE_TYPED_DICTIONARY(PackedFloat32Array, VariantType::PACKED_FLOAT32_ARRAY)
MAKE_TYPED_DICTIONARY(PackedFloat64Array, VariantType::PACKED_FLOAT64_ARRAY)
MAKE_TYPED_DICTIONARY(PackedStringArray, VariantType::PACKED_STRING_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector2Array, VariantType::PACKED_VECTOR2_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector3Array, VariantType::PACKED_VECTOR3_ARRAY)
MAKE_TYPED_DICTIONARY(PackedColorArray, VariantType::PACKED_COLOR_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector4Array, VariantType::PACKED_VECTOR4_ARRAY)
MAKE_TYPED_DICTIONARY(IPAddress, VariantType::STRING)

#undef MAKE_TYPED_DICTIONARY
#undef MAKE_TYPED_DICTIONARY_NIL
#undef MAKE_TYPED_DICTIONARY_EXPANDED
#undef MAKE_TYPED_DICTIONARY_WITH_OBJECT

#endif // TYPED_DICTIONARY_H
