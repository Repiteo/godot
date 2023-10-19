/**************************************************************************/
/*  type_ref.cpp                                                          */
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

#include "type_ref.h"

#include "core/object/script_language.h"

struct TypeRefPrivate {
	SafeRefCount refcount;
	Variant::Type variant_type;
	StringName class_name;
	Ref<Script> script;
	Vector<TypeRef> nested_types;

	bool operator==(const TypeRefPrivate &p_type) const {
		if (variant_type == p_type.variant_type && class_name == p_type.class_name &&
				script == p_type.script && nested_types.size() == p_type.nested_types.size()) {
			for (int i = 0; i < nested_types.size(); i++) {
				if (nested_types[i] != p_type.nested_types[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool operator!=(const TypeRefPrivate &p_type) const {
		return (!(*this == p_type));
	}
	TypeRefPrivate() {
		variant_type = Variant::NIL;
	}

	TypeRefPrivate(uint32_t p_variant_type, const StringName &p_class_name, const Variant &p_script, const Array &p_nested_types) {
		Variant::Type tmp_variant_type = (Variant::Type)(uint32_t)p_variant_type;
		ERR_FAIL_COND_MSG(p_class_name != StringName() && tmp_variant_type != Variant::OBJECT, "Class names can only be set for type OBJECT.");
		Ref<Script> tmp_script = p_script;
		ERR_FAIL_COND_MSG(tmp_script.is_valid() && p_class_name == StringName(), "Script class can only be set together with base class name");
		Vector<TypeRef> tmp_nested_types;
		for (int i = 0; i < p_nested_types.size(); i++) {
			ERR_FAIL_COND_MSG(p_nested_types[i].get_type() != Variant::ARRAY, "Nested type array members must be type ARRAY.");
			tmp_nested_types.append(TypeRef(p_nested_types[i]));
		}

		variant_type = tmp_variant_type;
		class_name = p_class_name;
		script = tmp_script;
		nested_types = tmp_nested_types;
	}

	TypeRefPrivate(const Array &p_type_struct) {
		ERR_FAIL_COND_MSG(p_type_struct.size() < 4, "Type struct was too small.");
		ERR_FAIL_COND_MSG(p_type_struct[0].get_type() != Variant::INT, "Type struct first member must be type INT.");
		Variant::Type tmp_variant_type = (Variant::Type)(uint32_t)p_type_struct[0];
		ERR_FAIL_COND_MSG(p_type_struct[1].get_type() != Variant::STRING_NAME, "Type struct second member must be type STRING_NAME.");
		StringName tmp_class_name = (StringName)p_type_struct[1];
		ERR_FAIL_COND_MSG(tmp_class_name != StringName() && tmp_variant_type != Variant::OBJECT, "Class names can only be set for type OBJECT.");
		Ref<Script> tmp_script = p_type_struct[2];
		ERR_FAIL_COND_MSG(tmp_script.is_valid() && tmp_class_name == StringName(), "Script class can only be set together with base class name");
		ERR_FAIL_COND_MSG(p_type_struct[3].get_type() != Variant::ARRAY, "Type struct final member must be type ARRAY.");
		Array array = p_type_struct[3];
		Vector<TypeRef> tmp_nested_types;
		for (int i = 0; i < array.size(); i++) {
			ERR_FAIL_COND_MSG(array[i].get_type() != Variant::ARRAY, "Nested type array members must be type ARRAY.");
			tmp_nested_types.append(TypeRef((Array)array[i]));
		}

		variant_type = tmp_variant_type;
		class_name = tmp_class_name;
		script = tmp_script;
		nested_types = tmp_nested_types;
	}
};

void TypeRef::_ref(const TypeRef &p_from) {
	TypeRefPrivate *_fp = p_from._p;

	ERR_FAIL_NULL(_fp); // Should NOT happen.

	if (_fp == _p) {
		return; // whatever it is, nothing to do here move along
	}

	bool success = _fp->refcount.ref();

	ERR_FAIL_COND(!success); // should really not happen either

	_unref();

	_p = _fp;
}

void TypeRef::_unref() {
	if (!_p) {
		return;
	}
	if (_p->refcount.unref()) {
		memdelete(_p);
	}
	_p = nullptr;
}

TypeRef TypeRef::from_builtin_type(uint32_t p_variant_type) {
	return TypeRef(p_variant_type, StringName(), Variant(), Array());
}

TypeRef TypeRef::from_native_type(const StringName &p_class_name) {
	return TypeRef(Variant::OBJECT, p_class_name, Variant(), Array());
}

TypeRef TypeRef::from_script_type(const Variant &p_script) {
	return TypeRef(Variant::OBJECT, StringName(), p_script, Array());
}

uint32_t TypeRef::get_builtin_type() const {
	return _p->variant_type;
}

StringName TypeRef::get_native_type() const {
	return _p->class_name;
}

Variant TypeRef::get_script_type() const {
	return _p->script;
}

bool TypeRef::has_nested_types() const {
	return _p->nested_types.size() > 0;
}

Array TypeRef::get_nested_types() const {
	Array types;
	for (int i = 0; i < _p->nested_types.size(); i++) {
		types.append(_p->nested_types[i]);
	}
	return types;
}

uint32_t TypeRef::hash() const {
	// TODO
	return 0;
}

bool TypeRef::operator==(const TypeRef &p_type) const {
	return _p == p_type._p;
}

bool TypeRef::operator!=(const TypeRef &p_type) const {
	return _p != p_type._p;
}

void TypeRef::operator=(const TypeRef &p_type) {
	if (this == &p_type) {
		return;
	}

	_ref(p_type);
}

TypeRef::operator String() const {
	Variant::Type type = (Variant::Type)get_builtin_type();
	if (get_builtin_type() == Variant::NIL) {
		return "Variant";
	} else {
		String name = Variant::get_type_name(type);
		if (has_nested_types()) {
			name += "<";
			TypedArray<TypeRef> nested_types = get_nested_types();
			for (int i = 0; i < nested_types.size(); i++) {
				if (i != 0) {
					name += ", ";
				}
				name += nested_types[i].operator String();
			}
			name += ">";
		}
		return name;
	}
}

bool TypeRef::is_variant() const {
	return _p->variant_type == Variant::NIL;
}

TypeRef::TypeRef(uint32_t p_variant_type, const StringName &p_class_name, const Variant &p_script, const Array &p_nested_types) {
	_p = memnew(TypeRefPrivate(p_variant_type, p_class_name, p_script, p_nested_types));
	_p->refcount.init();
}

TypeRef::TypeRef(const Array &p_type_struct) {
	_p = memnew(TypeRefPrivate(p_type_struct));
	_p->refcount.init();
}

TypeRef::TypeRef(const TypeRef &p_from) {
	_p = nullptr;
	_ref(p_from);
}

TypeRef::TypeRef() {
	_p = memnew(TypeRefPrivate);
	_p->refcount.init();
}

TypeRef::~TypeRef() {
	_unref();
}
