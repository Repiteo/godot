/**************************************************************************/
/*  test_name_of.h                                                        */
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

#include "tests/test_macros.h"

namespace TestNameOf {

TEST_CASE("[NameOf] Scalar types") {
	REQUIRE(name_of_type_v<void> == "void");
	REQUIRE(name_of_type_v<std::nullptr_t> == "nullptr_t");

	REQUIRE(name_of_type_v<char> == "char");
	REQUIRE(name_of_type_v<char16_t> == "char16_t");
	REQUIRE(name_of_type_v<char32_t> == "char32_t");

	REQUIRE(name_of_type_v<int8_t> == "int8_t");
	REQUIRE(name_of_type_v<int16_t> == "int16_t");
	REQUIRE(name_of_type_v<int32_t> == "int32_t");
	REQUIRE(name_of_type_v<int64_t> == "int64_t");

	REQUIRE(name_of_type_v<uint8_t> == "uint8_t");
	REQUIRE(name_of_type_v<uint16_t> == "uint16_t");
	REQUIRE(name_of_type_v<uint32_t> == "uint32_t");
	REQUIRE(name_of_type_v<uint64_t> == "uint64_t");

	REQUIRE(name_of_type_v<float> == "float");
	REQUIRE(name_of_type_v<double> == "double");
}

enum ScopedEnum {};

TEST_CASE("[NameOf] Enum types") {
	CHECK_EQ(name_of_type_v<Error>, "Error");
	CHECK_EQ(name_of_type_v<ScopedEnum>, "TestNameOf::ScopedEnum");
}

} // namespace TestNameOf
