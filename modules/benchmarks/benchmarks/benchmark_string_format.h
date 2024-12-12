/**************************************************************************/
/*  benchmark_string_format.h                                             */
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

#ifndef BENCHMARK_STRING_FORMAT_H
#define BENCHMARK_STRING_FORMAT_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkStringFormat BENCHMARK(StringFormat)

class BenchmarkStringFormat : public Benchmark {
	BENCHMARK_GDCLASS(StringFormat)

	const String ENGINE_NAME = "Godot";
	Dictionary FORMAT_DICT;

	String engine_name = "Godot";
	int some_integer = 123456;
	float some_float = 1.2;
	Vector2i some_vector2i = Vector2i(12, 34);

protected:
	static void _bind_methods();

public:
	static constexpr int iterations = 1000000;

	void benchmark_no_op_constant_method();
	void benchmark_simple_constant_concatenate();
	void benchmark_simple_constant_percent();
	void benchmark_simple_constant_method();
	void benchmark_simple_constant_method_constant_dict();
	void benchmark_simple_variable_concatenate();
	void benchmark_simple_variable_percent();
	void benchmark_simple_variable_method();
	void benchmark_complex_variable_concatenate();
	void benchmark_complex_variable_percent();
	void benchmark_complex_variable_method();

	BenchmarkStringFormat();
	~BenchmarkStringFormat();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_STRING_FORMAT_H
