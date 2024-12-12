/**************************************************************************/
/*  benchmark_string_manipulation.h                                       */
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

#ifndef BENCHMARK_STRING_MANIPULATION_H
#define BENCHMARK_STRING_MANIPULATION_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkStringManipulation BENCHMARK(StringManipulation)

class BenchmarkStringManipulation : public Benchmark {
	BENCHMARK_GDCLASS(StringManipulation)

protected:
	static void _bind_methods();

public:
	static constexpr int iterations = 1000000;

	void benchmark_begins_with();
	void benchmark_ends_with();
	void benchmark_count();
	void benchmark_countn();
	void benchmark_contains();
	void benchmark_find();
	void benchmark_findn();
	void benchmark_rfind();
	void benchmark_rfindn();
	void benchmark_substr();
	void benchmark_insert();
	void benchmark_get_slice();
	void benchmark_get_slice_count();
	void benchmark_bigrams();
	void benchmark_split();
	void benchmark_rsplit();
	void benchmark_split_floats();
	void benchmark_pad_zeros_pre_constructed();
	void benchmark_pad_zeros();
	void benchmark_pad_decimals_pre_constructed();
	void benchmark_pad_decimals();
	void benchmark_lpad();
	void benchmark_rpad();
	void benchmark_similarity();
	void benchmark_simplify_path();
	void benchmark_capitalize();
	void benchmark_to_snake_case();
	void benchmark_to_camel_case();
	void benchmark_to_pascal_case();
	void benchmark_to_lower();
	void benchmark_uri_decode();
	void benchmark_uri_encode();
	void benchmark_xml_escape();
	void benchmark_xml_unescape();
	void benchmark_humanize_size();
	void benchmark_is_valid_filename();
	void benchmark_validate_filename();
	void benchmark_validate_node_name();
	void benchmark_casecmp_to();
	void benchmark_nocasecmp_to();
	void benchmark_naturalnocasecmp_to();
	void benchmark_to_utf8_buffer();
	void benchmark_to_utf16_buffer();
	void benchmark_to_utf32_buffer();
	void benchmark_to_wchar_buffer();

	BenchmarkStringManipulation();
	~BenchmarkStringManipulation();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_STRING_MANIPULATION_H
