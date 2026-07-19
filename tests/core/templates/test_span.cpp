/**************************************************************************/
/*  test_span.cpp                                                         */
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

TEST_FORCE_LINK(test_span)

#include "core/templates/span.h"

namespace TestSpan {

TEST_CASE("[Span] Constructors") {
	constexpr Span<uint16_t> span_empty;
	static_assert(span_empty.ptr() == nullptr);
	static_assert(span_empty.size() == 0);
	static_assert(span_empty.is_empty());

	constexpr Span<uint16_t> span_nullptr = Span<uint16_t>(nullptr, 0);
	static_assert(span_nullptr.ptr() == nullptr);
	static_assert(span_nullptr.size() == 0);
	static_assert(span_nullptr.is_empty());

	static_assert(span_empty == span_nullptr);
}

TEST_CASE("[Span] Constexpr Validators") {
	constexpr static uint16_t value = 5;
	constexpr Span<uint16_t> span_value(&value, 1);
	static_assert(span_value.ptr() == &value);
	static_assert(span_value.size() == 1);
	static_assert(!span_value.is_empty());

	static constexpr int ints[] = { 0, 1, 2, 3, 4, 5 };
	constexpr Span<int> span_array = ints;
	static_assert(span_array.size() == 6);
	static_assert(!span_array.is_empty());
	static_assert(span_array[0] == 0);
	static_assert(span_array[span_array.size() - 1] == 5);

	constexpr Span<char32_t> span_string = U"122345";
	static_assert(span_string.size() == 6);
	static_assert(!span_string.is_empty());
	static_assert(span_string[0] == U'1');
	static_assert(span_string[span_string.size() - 1] == U'5');

	static_assert(span_string == span_string); // Same identity / ptr.
	static_assert(span_string == Span(U"1223456", 6)); // Different ptr.
	CHECK_EQ(span_string, Span("122345").reinterpret<uint8_t>()); // Different type.

	int idx = 0;
	for (const char32_t &chr : span_string) {
		CHECK_EQ(chr, span_string[idx++]);
	}
}

TEST_CASE("[Span] Comparison operators") {
	// Self.
	constexpr Span<char32_t> span_string = U"122345";
	static_assert(span_string == span_string);
	static_assert(!(span_string != span_string));
	static_assert(!(span_string < span_string));
	static_assert(span_string <= span_string);
	static_assert(!(span_string > span_string));
	static_assert(span_string >= span_string);

	// Matching contents.
	constexpr char32_t cstring[] = U"122345";
	static_assert(span_string == cstring);
	static_assert(!(span_string != cstring));
	static_assert(!(span_string < cstring));
	static_assert(span_string <= cstring);
	static_assert(!(span_string > cstring));
	static_assert(span_string >= cstring);

	// Shorter string.
	constexpr Span<char32_t> span_string_small = U"1223";
	static_assert(!(span_string == span_string_small));
	static_assert(span_string != span_string_small);
	static_assert(!(span_string < span_string_small));
	static_assert(!(span_string <= span_string_small));
	static_assert(span_string > span_string_small);
	static_assert(span_string >= span_string_small);

	// Larger string.
	constexpr Span<char32_t> span_string_large = U"12234567";
	static_assert(!(span_string == span_string_large));
	static_assert(span_string != span_string_large);
	static_assert(span_string < span_string_large);
	static_assert(span_string <= span_string_large);
	static_assert(!(span_string > span_string_large));
	static_assert(!(span_string >= span_string_large));
}

} // namespace TestSpan
