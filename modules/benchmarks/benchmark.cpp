/**************************************************************************/
/*  benchmark.cpp                                                         */
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

#include "benchmark.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#else
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

void Benchmark::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_benchmark_time"), &Benchmark::get_benchmark_time);
	ClassDB::bind_method(D_METHOD("set_benchmark_time", "p_benchmark_time"), &Benchmark::set_benchmark_time);
	ClassDB::add_property("Benchmark", PropertyInfo(Variant::INT, "benchmark_time"), "set_benchmark_time", "get_benchmark_time");

	ClassDB::bind_method(D_METHOD("get_test_render_cpu"), &Benchmark::get_test_render_cpu);
	ClassDB::bind_method(D_METHOD("set_test_render_cpu", "p_test_render_cpu"), &Benchmark::set_test_render_cpu);
	ClassDB::add_property("Benchmark", PropertyInfo(Variant::BOOL, "test_render_cpu"), "set_test_render_cpu", "get_test_render_cpu");

	ClassDB::bind_method(D_METHOD("get_test_render_gpu"), &Benchmark::get_test_render_gpu);
	ClassDB::bind_method(D_METHOD("set_test_render_gpu", "p_test_render_gpu"), &Benchmark::set_test_render_gpu);
	ClassDB::add_property("Benchmark", PropertyInfo(Variant::BOOL, "test_render_gpu"), "set_test_render_gpu", "get_test_render_gpu");

	ClassDB::bind_method(D_METHOD("get_test_idle"), &Benchmark::get_test_idle);
	ClassDB::bind_method(D_METHOD("set_test_idle", "p_test_idle"), &Benchmark::set_test_idle);
	ClassDB::add_property("Benchmark", PropertyInfo(Variant::BOOL, "test_idle"), "set_test_idle", "get_test_idle");

	ClassDB::bind_method(D_METHOD("get_test_physics"), &Benchmark::get_test_physics);
	ClassDB::bind_method(D_METHOD("set_test_physics", "p_test_physics"), &Benchmark::set_test_physics);
	ClassDB::add_property("Benchmark", PropertyInfo(Variant::BOOL, "test_physics"), "set_test_physics", "get_test_physics");
}
