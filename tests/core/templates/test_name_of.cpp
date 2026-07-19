/**************************************************************************/
/*  test_name_of.cpp                                                      */
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

#include "tests/test_macros.h"

TEST_FORCE_LINK(test_name_of)

#include "core/templates/name_of.h"

namespace TestNameOf {

TEST_CASE("[NameOf] Scalar types") {
	static_assert(name_of_type_v<void> == Span("void"));
	static_assert(name_of_type_v<std::nullptr_t> == Span("nullptr_t"));

	static_assert(name_of_type_v<char> == Span("char"));
	static_assert(name_of_type_v<char16_t> == Span("char16_t"));
	static_assert(name_of_type_v<char32_t> == Span("char32_t"));

	static_assert(name_of_type_v<int8_t> == Span("int8_t"));
	static_assert(name_of_type_v<int16_t> == Span("int16_t"));
	static_assert(name_of_type_v<int32_t> == Span("int32_t"));
	static_assert(name_of_type_v<int64_t> == Span("int64_t"));

	static_assert(name_of_type_v<uint8_t> == Span("uint8_t"));
	static_assert(name_of_type_v<uint16_t> == Span("uint16_t"));
	static_assert(name_of_type_v<uint32_t> == Span("uint32_t"));
	static_assert(name_of_type_v<uint64_t> == Span("uint64_t"));

	static_assert(name_of_type_v<float> == Span("float"));
	static_assert(name_of_type_v<double> == Span("double"));

	// static_assert(name_of_type_v<Error> == "Error");
}

enum ScopedEnum {};
class ForwardDeclaredClass;

TEST_CASE("[NameOf] Complex types") {
	static_assert(name_of_type_v<Error> == Span("Error"));
	static_assert(name_of_type_v<ScopedEnum> == Span("TestNameOf::ScopedEnum"));
	static_assert(name_of_type_v<ForwardDeclaredClass> == Span("TestNameOf::ForwardDeclaredClass"));
}

} // namespace TestNameOf
