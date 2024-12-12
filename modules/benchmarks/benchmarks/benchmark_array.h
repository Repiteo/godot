/**************************************************************************/
/*  benchmark_array.h                                                     */
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

#ifndef BENCHMARK_ARRAY_H
#define BENCHMARK_ARRAY_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkArray BENCHMARK(Array)

class BenchmarkArray : public Benchmark {
	BENCHMARK_GDCLASS(Array)

	static constexpr int iterations = 2000000;

protected:
	static void _bind_methods();

public:
	void benchmark_fill_loop();
	void benchmark_int32_array();
	void benchmark_int64_array();
	void benchmark_float32_array();
	void benchmark_float64_array();
	void benchmark_vector2_array();
	void benchmark_vector3_array();
	void benchmark_vector4_array();
	void benchmark_color_array();
	void benchmark_string_array();

	BenchmarkArray();
	~BenchmarkArray();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_ARRAY_H
