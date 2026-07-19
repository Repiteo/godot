/**************************************************************************/
/*  native_ptr.h                                                          */
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

#include "core/templates/name_of.h"
#include "core/variant/method_ptrcall.h"
#include "core/variant/type_info.h"
#include "core/variant/variant_caster.h"
#include "core/variant/variant_internal.h"

// Metafunction for pointee name; takes into account const & pointers.
template <typename T>
struct GDExtensionPtrName {
	static const String get() { return String::utf8(name_of_type_v<T>); }
};
template <typename T>
struct GDExtensionPtrName<const T> {
	static const String get() {
		return "const " + GDExtensionPtrName<T>::get();
	}
};
template <typename T>
struct GDExtensionPtrName<T *> {
	static const String get() {
		return GDExtensionPtrName<T>::get() + " *";
	}
};

#if false
#define GDVIRTUAL_NATIVE_PTR(m_type) \
	template <> \
	struct GDExtensionPtrName<m_type> { \
		static const char *get() { return #m_type; } \
	};
#else
#define GDVIRTUAL_NATIVE_PTR(m_type)
#endif

// Raw pointer passed across the GDExtension boundary. T can be const-qualified to map to `const MyClass*`.
template <typename T>
struct GDExtensionPtr {
	T *data = nullptr;
	GDExtensionPtr() {}
	GDExtensionPtr(T *p_assign) { data = p_assign; }
	static String get_name() { return GDExtensionPtrName<T>::get(); }
	operator T *() const { return data; }
	operator Variant() const { return uint64_t(data); }
};

template <typename T>
struct GetTypeInfo<GDExtensionPtr<T>> {
	static const Variant::Type VARIANT_TYPE = Variant::INT;
	static const GodotTypeInfo::Metadata METADATA = GodotTypeInfo::METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::INT, String(), PROPERTY_HINT_INT_IS_POINTER, GDExtensionPtr<T>::get_name());
	}
};

template <typename T>
struct VariantCaster<GDExtensionPtr<T>> {
	static _FORCE_INLINE_ GDExtensionPtr<T> cast(const Variant &p_variant) {
		return GDExtensionPtr<T>(reinterpret_cast<T *>(p_variant.operator uint64_t()));
	}
};

template <typename T>
struct VariantInternalAccessor<GDExtensionPtr<T>> {
	static _FORCE_INLINE_ const GDExtensionPtr<T> &get(const Variant *p_variant) {
		return *reinterpret_cast<const GDExtensionPtr<T> *>(VariantInternal::get_int(p_variant));
	}
	static _FORCE_INLINE_ void set(Variant *r_variant, const GDExtensionPtr<T> &p_value) {
		*VariantInternal::get_int(r_variant) = uint64_t(p_value.data);
	}
};

template <typename T>
struct PtrToArg<GDExtensionPtr<T>> {
	_FORCE_INLINE_ static GDExtensionPtr<T> convert(const void *p_ptr) {
		return GDExtensionPtr<T>(static_cast<T *>(const_cast<void *>(p_ptr)));
	}
	typedef T *EncodeT;
	_FORCE_INLINE_ static void encode(GDExtensionPtr<T> p_val, void *p_ptr) {
		*static_cast<T **>(p_ptr) = p_val.data;
	}
};

GDVIRTUAL_NATIVE_PTR(AudioFrame)
GDVIRTUAL_NATIVE_PTR(bool)
GDVIRTUAL_NATIVE_PTR(char)
GDVIRTUAL_NATIVE_PTR(char16_t)
GDVIRTUAL_NATIVE_PTR(char32_t)
GDVIRTUAL_NATIVE_PTR(wchar_t)
GDVIRTUAL_NATIVE_PTR(uint8_t)
GDVIRTUAL_NATIVE_PTR(int8_t)
GDVIRTUAL_NATIVE_PTR(uint16_t)
GDVIRTUAL_NATIVE_PTR(int16_t)
GDVIRTUAL_NATIVE_PTR(uint32_t)
GDVIRTUAL_NATIVE_PTR(int32_t)
GDVIRTUAL_NATIVE_PTR(int64_t)
GDVIRTUAL_NATIVE_PTR(uint64_t)
GDVIRTUAL_NATIVE_PTR(float)
GDVIRTUAL_NATIVE_PTR(double)
