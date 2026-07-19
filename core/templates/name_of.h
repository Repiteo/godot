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
	return __FUNCSIG__; // "const class Span<char> __cdecl Internal::_wrapped_function_name<some_type_t>(void)".
#else
	return __PRETTY_FUNCTION__; // "constexpr const Span<char> Internal::_wrapped_function_name() [with T = some_type_t]".
#endif
}

// Utilize "double" as our control; a primitive type with a unique name.
inline constexpr Span<char> _double_name = "double";
inline constexpr Span<char> _double_wrapped = _wrapped_function_name<double>();
inline constexpr int64_t _double_begin = _double_wrapped.find_sequence(_double_name);
inline constexpr int64_t _double_end = _double_wrapped.size() - _double_begin - _double_name.size();

template <typename T>
struct _RemoveAllPointers {
	using type = T;
};

template <typename T>
struct _RemoveAllPointers<T *> {
	using type = typename _RemoveAllPointers<T>::type;
};

template <typename T>
using remove_all_pointers_t = typename _RemoveAllPointers<T>::type;

template <typename T>
constexpr const Span<char> _get_type_name() {
	// Initial subspan. Use stripped type.
	using simple_t = remove_all_pointers_t<std::decay_t<T>>;
	constexpr Span<char> subspan_init = { _wrapped_function_name<simple_t>().begin() + _double_begin, _wrapped_function_name<simple_t>().size() - _double_begin - _double_end };

	// MSVC has extraneous keyword prefixes for types; account for those.
	constexpr int64_t offset_space = subspan_init.find(' ');
	constexpr int64_t offset_rangle = subspan_init.find('<');
	constexpr int64_t offset_new = (offset_space != -1 && (offset_rangle == -1 || offset_space < offset_rangle)) ? offset_space + 1 : 0;
	constexpr Span<char> subspan = { subspan_init.begin() + offset_new, subspan_init.size() - offset_new };

	// TODO: Create new arrays to capture a platform-agnostic representation of type qualifiers.
	return subspan;
}

template <typename T, typename = void>
struct _TypeName {
	static constexpr const Span<char> value = _get_type_name<T>();
};

}; // namespace Internal

template <typename T>
inline constexpr Span<char> name_of_type_v = Internal::_TypeName<T>::value;

#define NAME_OF_TYPE_OVERRIDE(m_type, m_override) \
	template <> \
	struct Internal::_TypeName<m_type> { \
		static constexpr const Span<char> value = #m_override; \
	};

NAME_OF_TYPE_OVERRIDE(std::nullptr_t, nullptr_t)
NAME_OF_TYPE_OVERRIDE(int8_t, int8_t)
NAME_OF_TYPE_OVERRIDE(int16_t, int16_t)
NAME_OF_TYPE_OVERRIDE(int32_t, int32_t)
NAME_OF_TYPE_OVERRIDE(int64_t, int64_t)
NAME_OF_TYPE_OVERRIDE(uint8_t, uint8_t)
NAME_OF_TYPE_OVERRIDE(uint16_t, uint16_t)
NAME_OF_TYPE_OVERRIDE(uint32_t, uint32_t)
NAME_OF_TYPE_OVERRIDE(uint64_t, uint64_t)
