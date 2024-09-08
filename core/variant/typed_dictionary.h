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
	_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) :
			TypedDictionary() {
		if (is_same_typed(p_dictionary)) {
			Dictionary::operator=(p_dictionary);
		} else {
			assign(p_dictionary);
		}
	}
	_FORCE_INLINE_ TypedDictionary() {
		static_assert(GTI::variant_type_v<K> != Variant::NIL || GTI::variant_type_v<V> != Variant::NIL, "`TypedDictionary<Variant, Variant>` is undefined.");
		set_typed(GTI::variant_type_v<K>, GTI::variant_type_v<K> == Variant::OBJECT ? GTI::const_class_name_v<K> : "", Variant(),
				GTI::variant_type_v<V>, GTI::variant_type_v<V> == Variant::OBJECT ? GTI::const_class_name_v<V> : "", Variant());
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

GTI_TMPL_VARIANT_TYPE(typename K _COMMA typename V, TypedDictionary<K _COMMA V>, Variant::DICTIONARY)
GTI_TMPL_PROPERTY_HINT(typename K _COMMA typename V, TypedDictionary<K _COMMA V>, PROPERTY_HINT_DICTIONARY_TYPE)
GTI_TMPL_HINT_STRING(typename K _COMMA typename V, TypedDictionary<K _COMMA V>, GTI::const_class_name_v<K> _COMMA GTI::const_class_name_v<V>)
// // clang-format off
// GTI_TMPL_HINT_STRING(typename K _COMMA typename V, TypedDictionary<K _COMMA V>, vformat("%s;%s" _COMMA
// 		GTI::variant_type_v<K> == Variant::OBJECT ? K::get_class_static() : GTI::variant_type_v<K> == Variant::NIL ? "Variant" : Variant::get_type_name(GTI::variant_type_v<K>) _COMMA
// 		GTI::variant_type_v<V> == Variant::OBJECT ? V::get_class_static() : GTI::variant_type_v<K> == Variant::NIL ? "Variant" : Variant::get_type_name(GTI::variant_type_v<V>)))
// // clang-format on

#endif // TYPED_DICTIONARY_H
