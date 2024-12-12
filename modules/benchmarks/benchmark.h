/**************************************************************************/
/*  benchmark.h                                                           */
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

#ifndef BENCHMARK_H
#define BENCHMARK_H

#ifdef GODOT_MODULE
#define BENCHMARK(m_name) BenchmarkModule##m_name
#define BENCHMARK_GDCLASS(m_name) GDCLASS(BenchmarkModule##m_name, Benchmark)
#else
#define BENCHMARK(m_name) BenchmarkGDExtension##m_name
#endif // GODOT_MODULE

#ifdef GODOT_MODULE
#include "core/object/ref_counted.h"
#else
#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {
#endif // GODOT_MODULE

class Benchmark : public RefCounted {
	GDCLASS(Benchmark, RefCounted)

	int64_t _benchmark_time = 5e6;
	bool _test_render_cpu = false;
	bool _test_render_gpu = false;
	bool _test_idle = false;
	bool _test_physics = false;

protected:
	static void _bind_methods();

public:
	inline void set_benchmark_time(int64_t p_benchmark_time) { _benchmark_time = p_benchmark_time; }
	inline int64_t get_benchmark_time() const { return _benchmark_time; }

	inline void set_test_render_cpu(bool p_test_render_cpu) { _test_render_cpu = p_test_render_cpu; }
	inline bool get_test_render_cpu() const { return _test_render_cpu; }

	inline void set_test_render_gpu(bool p_test_render_gpu) { _test_render_gpu = p_test_render_gpu; }
	inline bool get_test_render_gpu() const { return _test_render_gpu; }

	inline void set_test_idle(bool p_test_idle) { _test_idle = p_test_idle; }
	inline bool get_test_idle() const { return _test_idle; }

	inline void set_test_physics(bool p_test_physics) { _test_physics = p_test_physics; }
	inline bool get_test_physics() const { return _test_physics; }

	Benchmark() = default;
	virtual ~Benchmark() = default;
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_H
