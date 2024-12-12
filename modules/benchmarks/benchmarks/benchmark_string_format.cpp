/**************************************************************************/
/*  benchmark_string_format.cpp                                           */
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

#include "benchmark_string_format.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#include "core/variant/variant_utility.h"

#define TO_STR VariantUtilityFunctions::var_to_str
#else
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define TO_STR UtilityFunctions::str

using namespace godot;
#endif // GODOT_MODULE

void BenchmarkStringFormat::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_no_op_constant_method"), &BenchmarkStringFormat::benchmark_no_op_constant_method);
	ClassDB::bind_method(D_METHOD("benchmark_simple_constant_concatenate"), &BenchmarkStringFormat::benchmark_simple_constant_concatenate);
	ClassDB::bind_method(D_METHOD("benchmark_simple_constant_percent"), &BenchmarkStringFormat::benchmark_simple_constant_percent);
	ClassDB::bind_method(D_METHOD("benchmark_simple_constant_method"), &BenchmarkStringFormat::benchmark_simple_constant_method);
	ClassDB::bind_method(D_METHOD("benchmark_simple_constant_method_constant_dict"), &BenchmarkStringFormat::benchmark_simple_constant_method_constant_dict);
	ClassDB::bind_method(D_METHOD("benchmark_simple_variable_concatenate"), &BenchmarkStringFormat::benchmark_simple_variable_concatenate);
	ClassDB::bind_method(D_METHOD("benchmark_simple_variable_percent"), &BenchmarkStringFormat::benchmark_simple_variable_percent);
	ClassDB::bind_method(D_METHOD("benchmark_simple_variable_method"), &BenchmarkStringFormat::benchmark_simple_variable_method);
	ClassDB::bind_method(D_METHOD("benchmark_complex_variable_concatenate"), &BenchmarkStringFormat::benchmark_complex_variable_concatenate);
	ClassDB::bind_method(D_METHOD("benchmark_complex_variable_percent"), &BenchmarkStringFormat::benchmark_complex_variable_percent);
	ClassDB::bind_method(D_METHOD("benchmark_complex_variable_method"), &BenchmarkStringFormat::benchmark_complex_variable_method);
}

void BenchmarkStringFormat::benchmark_no_op_constant_method() {
	for (int i = 0; i < iterations; i++) {
		Dictionary dict;
		String("Hello nothing!").format(dict);
	}
}

void BenchmarkStringFormat::benchmark_simple_constant_concatenate() {
	for (int i = 0; i < iterations; i++) {
		"Hello " + ENGINE_NAME + "!";
	}
}

void BenchmarkStringFormat::benchmark_simple_constant_percent() {
	for (int i = 0; i < iterations; i++) {
#ifdef GODOT_MODULE
		vformat("Hello %s!", ENGINE_NAME);
#else
		String("Hello %s!") % ENGINE_NAME;
#endif
	}
}

void BenchmarkStringFormat::benchmark_simple_constant_method() {
	for (int i = 0; i < iterations; i++) {
		Dictionary dict;
		dict["engine"] = ENGINE_NAME;
		String("Hello {engine}!").format(dict);
	}
}

void BenchmarkStringFormat::benchmark_simple_constant_method_constant_dict() {
	for (int i = 0; i < iterations; i++) {
		String("Hello {engine}!").format(FORMAT_DICT);
	}
}

void BenchmarkStringFormat::benchmark_simple_variable_concatenate() {
	for (int i = 0; i < iterations; i++) {
		"Hello " + engine_name + "!";
	}
}

void BenchmarkStringFormat::benchmark_simple_variable_percent() {
	for (int i = 0; i < iterations; i++) {
#ifdef GODOT_MODULE
		vformat("Hello %s!", engine_name);
#else
		String("Hello %s!") % engine_name;
#endif
	}
}

void BenchmarkStringFormat::benchmark_simple_variable_method() {
	for (int i = 0; i < iterations; i++) {
		Dictionary dict;
		dict["engine"] = engine_name;
		String("Hello {engine}!").format(dict);
	}
}

void BenchmarkStringFormat::benchmark_complex_variable_concatenate() {
	for (int i = 0; i < iterations; i++) {
		"Hello " + engine_name + "!\nA few examples of formatting: " + TO_STR(some_integer) + ", " + TO_STR(some_float).pad_decimals(2) + ", " + TO_STR(some_vector2i);
	}
}

void BenchmarkStringFormat::benchmark_complex_variable_percent() {
	for (int i = 0; i < iterations; i++) {
#ifdef GODOT_MODULE
		Array arr;
		arr.append(engine_name);
		arr.append(some_integer);
		arr.append(some_float);
		arr.append(some_vector2i);
		vformat("Hello %s!\nA few examples of formatting: %d, %.2f, %v", arr);
#else
		Array arr = Array::make(engine_name, some_integer, some_float, some_vector2i);
		String("Hello %s!\nA few examples of formatting: %d, %.2f, %v") % arr;
#endif
	}
}

void BenchmarkStringFormat::benchmark_complex_variable_method() {
	for (int i = 0; i < iterations; i++) {
		Dictionary dict;
		dict["engine"] = engine_name;
		dict["an_integer"] = some_integer;
		dict["a_float"] = TO_STR(some_float).pad_decimals(2);
		dict["a_vector2i"] = some_vector2i;
		String("Hello {engine}!\nA few examples of formatting: {an_integer}, {a_float}, {a_vector2i}").format(dict);
	}
}

BenchmarkStringFormat::BenchmarkStringFormat() {
	FORMAT_DICT["engine"] = ENGINE_NAME;
}

BenchmarkStringFormat::~BenchmarkStringFormat() {}
