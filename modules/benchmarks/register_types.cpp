/**************************************************************************/
/*  register_types.cpp                                                    */
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

#include "register_types.h"

#include "benchmarks/benchmark_alloc.h"
#include "benchmarks/benchmark_array.h"
#include "benchmarks/benchmark_binary_trees.h"
#include "benchmarks/benchmark_control.h"
#include "benchmarks/benchmark_forloop.h"
#include "benchmarks/benchmark_hello_world.h"
#include "benchmarks/benchmark_lambda_performance.h"
#include "benchmarks/benchmark_mandelbrot_set.h"
#include "benchmarks/benchmark_merkle_trees.h"
#include "benchmarks/benchmark_nbody.h"
#include "benchmarks/benchmark_spectral_norm.h"
#include "benchmarks/benchmark_string_checksum.h"
#include "benchmarks/benchmark_string_format.h"
#include "benchmarks/benchmark_string_manipulation.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#else
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

void initialize_benchmarks_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

#ifdef GODOT_MODULE
	GDREGISTER_VIRTUAL_CLASS(Benchmark);
#endif // GODOT_MODULE

	GDREGISTER_INTERNAL_CLASS(BenchmarkAlloc);
	GDREGISTER_INTERNAL_CLASS(BenchmarkArray);
	GDREGISTER_INTERNAL_CLASS(BenchmarkBinaryTrees);
	GDREGISTER_INTERNAL_CLASS(BenchmarkControl);
	GDREGISTER_INTERNAL_CLASS(BenchmarkForLoop);
	GDREGISTER_INTERNAL_CLASS(BenchmarkHelloWorld);
	GDREGISTER_INTERNAL_CLASS(BenchmarkLambdaPerformance);
	GDREGISTER_INTERNAL_CLASS(BenchmarkMandelbrotSet);
	GDREGISTER_INTERNAL_CLASS(BenchmarkMerkleTrees);
	GDREGISTER_INTERNAL_CLASS(BenchmarkNbody);
	GDREGISTER_INTERNAL_CLASS(BenchmarkSpectralNorm);
	GDREGISTER_INTERNAL_CLASS(BenchmarkStringChecksum);
	GDREGISTER_INTERNAL_CLASS(BenchmarkStringFormat);
	GDREGISTER_INTERNAL_CLASS(BenchmarkStringManipulation);
}

void uninitialize_benchmarks_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

#ifndef GODOT_MODULE

extern "C" {

GDExtensionBool GDE_EXPORT textserver_fallback_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(&initialize_benchmarks_module);
	init_obj.register_terminator(&uninitialize_benchmarks_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}

} // extern "C"

#endif // ! GODOT_MODULE
