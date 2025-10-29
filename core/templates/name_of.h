/**************************************************************************/
/*  name_of.h                                                             */
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

#include "core/templates/span.h"

namespace Internal {

template <typename T>
constexpr const Span<char> _wrapped_function_name() {
#if defined(_MSC_VER)
	return __FUNCSIG__;
#else
	return __PRETTY_FUNCTION__;
#endif
}

inline constexpr Span<char> _double_name = _wrapped_function_name<double>();
inline constexpr int64_t _double_begin = _double_name.find_sequence("double");
inline constexpr int64_t _double_end = _double_name.size() - _double_begin - 6 /* "double" */;

template <typename T, typename = void>
struct _TypeName {
	static constexpr const Span<char> value = { _wrapped_function_name<T>().begin() + _double_begin, _wrapped_function_name<T>().size() - _double_begin - _double_end };
};

// Enums might have `enum` prefix; handle separately
inline constexpr Span<char> _error_name = _wrapped_function_name<Error>();
inline constexpr int64_t _error_begin = _error_name.find_sequence("Error");
inline constexpr int64_t _error_end = _error_name.size() - _error_begin - 5 /* "Error" */;

template <typename T>
struct _TypeName<T, std::enable_if_t<std::is_enum_v<T>>> {
	static constexpr const Span<char> value = { _wrapped_function_name<T>().begin() + _error_begin, _wrapped_function_name<T>().size() - _error_begin - _error_end };
};

// Explicit overrides.

template <>
struct _TypeName<std::nullptr_t> {
	static constexpr const Span<char> value = "nullptr_t";
};
template <>
struct _TypeName<int8_t> {
	static constexpr const Span<char> value = "int8_t";
};
template <>
struct _TypeName<int16_t> {
	static constexpr const Span<char> value = "int16_t";
};
template <>
struct _TypeName<int32_t> {
	static constexpr const Span<char> value = "int32_t";
};
template <>
struct _TypeName<int64_t> {
	static constexpr const Span<char> value = "int64_t";
};
template <>
struct _TypeName<uint8_t> {
	static constexpr const Span<char> value = "uint8_t";
};
template <>
struct _TypeName<uint16_t> {
	static constexpr const Span<char> value = "uint16_t";
};
template <>
struct _TypeName<uint32_t> {
	static constexpr const Span<char> value = "uint32_t";
};
template <>
struct _TypeName<uint64_t> {
	static constexpr const Span<char> value = "uint64_t";
};

}; // namespace Internal

template <typename T>
inline constexpr Span<char> name_of_type_v = Internal::_TypeName<T>::value;

static_assert(name_of_type_v<void> == "void");
static_assert(name_of_type_v<std::nullptr_t> == "nullptr_t");

static_assert(name_of_type_v<char> == "char");
static_assert(name_of_type_v<char16_t> == "char16_t");
static_assert(name_of_type_v<char32_t> == "char32_t");

static_assert(name_of_type_v<int8_t> == "int8_t");
static_assert(name_of_type_v<int16_t> == "int16_t");
static_assert(name_of_type_v<int32_t> == "int32_t");
static_assert(name_of_type_v<int64_t> == "int64_t");

static_assert(name_of_type_v<uint8_t> == "uint8_t");
static_assert(name_of_type_v<uint16_t> == "uint16_t");
static_assert(name_of_type_v<uint32_t> == "uint32_t");
static_assert(name_of_type_v<uint64_t> == "uint64_t");

static_assert(name_of_type_v<float> == "float");
static_assert(name_of_type_v<double> == "double");

static_assert(name_of_type_v<Error> == "Error");
