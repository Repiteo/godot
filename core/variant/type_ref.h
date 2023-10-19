/**************************************************************************/
/*  type_ref.h                                                            */
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

#ifndef TYPE_REF_H
#define TYPE_REF_H

#include "core/typedefs.h"

struct TypeRefPrivate;
class String;
class StringName;
class Variant;
class Array;

class TypeRef {
	mutable TypeRefPrivate *_p = nullptr;
	void _ref(const TypeRef &p_from);
	void _unref();

	// TypeRef(const TypeRefPrivate &p_from);

public:
	static TypeRef from_builtin_type(uint32_t p_variant_type);
	static TypeRef from_native_type(const StringName &p_class_name);
	static TypeRef from_script_type(const Variant &p_script);

	uint32_t get_builtin_type() const;
	StringName get_native_type() const;
	Variant get_script_type() const;

	bool has_nested_types() const;
	Array get_nested_types() const;

	uint32_t hash() const;
	bool operator==(const TypeRef &p_type) const;
	bool operator!=(const TypeRef &p_type) const;
	void operator=(const TypeRef &p_type);

	operator String() const;

	bool is_variant() const;

	TypeRef(uint32_t p_variant_type, const StringName &p_class_name, const Variant &p_script, const Array &p_nested_types);
	TypeRef(const Array &p_type_struct);
	TypeRef(const TypeRef &p_from);
	TypeRef();
	~TypeRef();
};

#endif // TYPE_REF_H
