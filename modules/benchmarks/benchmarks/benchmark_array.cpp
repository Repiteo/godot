/**************************************************************************/
/*  benchmark_array.cpp                                                   */
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

#include "benchmark_array.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#include "core/variant/typed_array.h"
#else
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void BenchmarkArray::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_fill_loop"), &BenchmarkArray::benchmark_fill_loop);
	ClassDB::bind_method(D_METHOD("benchmark_int32_array"), &BenchmarkArray::benchmark_int32_array);
	ClassDB::bind_method(D_METHOD("benchmark_int64_array"), &BenchmarkArray::benchmark_int64_array);
	ClassDB::bind_method(D_METHOD("benchmark_float32_array"), &BenchmarkArray::benchmark_float32_array);
	ClassDB::bind_method(D_METHOD("benchmark_float64_array"), &BenchmarkArray::benchmark_float64_array);
	ClassDB::bind_method(D_METHOD("benchmark_vector2_array"), &BenchmarkArray::benchmark_vector2_array);
	ClassDB::bind_method(D_METHOD("benchmark_vector3_array"), &BenchmarkArray::benchmark_vector3_array);
	ClassDB::bind_method(D_METHOD("benchmark_vector4_array"), &BenchmarkArray::benchmark_vector4_array);
	ClassDB::bind_method(D_METHOD("benchmark_color_array"), &BenchmarkArray::benchmark_color_array);
	ClassDB::bind_method(D_METHOD("benchmark_string_array"), &BenchmarkArray::benchmark_string_array);
}

void BenchmarkArray::benchmark_fill_loop() {
	constexpr int length = 10000000;
	int array[length];
	for (int i = 0; i < length; i++) {
		array[i] = 1234;
	}
}

void BenchmarkArray::benchmark_int32_array() {
	TypedArray<int32_t> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(i);
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = 0;
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_int64_array() {
	TypedArray<int64_t> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(i);
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = 0;
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_float32_array() {
	TypedArray<float> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(i);
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = 0.0;
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_float64_array() {
	TypedArray<double> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(i);
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = 0.0;
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_vector2_array() {
	TypedArray<Vector2> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(Vector2(i, i));
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = Vector2(0, 0);
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_vector3_array() {
	TypedArray<Vector3> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(Vector3(i, i, i));
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = Vector3(0, 0, 0);
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_vector4_array() {
	TypedArray<Vector4> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(Vector4(i, i, i, i));
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = Vector4(0, 0, 0, 0);
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_color_array() {
	TypedArray<Color> array;

	for (int i = 0; i < iterations; i++) {
		array.push_back(Color(i, i, i, 1.0));
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = Color(0, 0, 0, 0);
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

void BenchmarkArray::benchmark_string_array() {
	TypedArray<String> array;

	for (int64_t i = 0; i < iterations; i++) { // i needs to be int64_t for string formatting to work, as the String::% operator is not overloaded for int
#ifdef GODOT_MODULE
		array.push_back(vformat("Godot %d", i));
#else
		array.push_back(String("Godot %d") % i);
#endif
	}

	for (int i = 0; i < iterations; i++) {
		array[i] = "";
	}

	for (int i = 0; i < iterations; i++) {
		array.remove_at(array.size() - 1);
	}
}

BenchmarkArray::BenchmarkArray() {}

BenchmarkArray::~BenchmarkArray() {}
