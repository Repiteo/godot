/**************************************************************************/
/*  benchmark_binary_trees.cpp                                            */
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

#include "benchmark_binary_trees.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"

#define PRINT(...) // FIXME: Needs equivalent implementation.
#else
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define PRINT(...) UtilityFunctions::print(__VA_ARGS__)
#define MAX(...) Math::max(__VA_ARGS__) // TODO: Remove when MAX added to Math.

using namespace godot;
#endif // GODOT_MODULE

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

void BenchmarkBinaryTrees::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_binary_trees_13"), &BenchmarkBinaryTrees::benchmark_binary_trees_13);
	ClassDB::bind_method(D_METHOD("benchmark_binary_trees_15"), &BenchmarkBinaryTrees::benchmark_binary_trees_15);
	ClassDB::bind_method(D_METHOD("benchmark_binary_trees_18"), &BenchmarkBinaryTrees::benchmark_binary_trees_18);
}

void BenchmarkBinaryTrees::calculate_binary_trees(int input) {
	int max_depth = MAX(min_depth + 2, input);

	int stretch_depth = max_depth + 1;
	TreeNode *stretch_tree = TreeNode::create(stretch_depth);
	PRINT("stretch tree of depth ", stretch_depth, "\t check: ", stretch_tree->check());
	delete stretch_tree;

	TreeNode *long_lived_tree = TreeNode::create(max_depth);
	int max_plus_min_depth = max_depth + min_depth;
	for (int depth = min_depth; depth < max_depth; depth += 2) {
		int iterations = 1 << (max_plus_min_depth - depth);
		int check = 0;
		for (int i = 0; i < iterations; i++) {
			TreeNode *check_tree = TreeNode::create(depth);
			check += check_tree->check();
			delete check_tree;
		}

		PRINT(iterations, "\t trees of depth ", depth, "\t check: ", check);
	}

	PRINT("long lived tree of depth ", max_depth, "\t check: ", long_lived_tree->check());
	delete long_lived_tree;
}

void BenchmarkBinaryTrees::benchmark_binary_trees_13() {
	calculate_binary_trees(13);
}

void BenchmarkBinaryTrees::benchmark_binary_trees_15() {
	calculate_binary_trees(15);
}

void BenchmarkBinaryTrees::benchmark_binary_trees_18() {
	calculate_binary_trees(18);
}

BenchmarkBinaryTrees::BenchmarkBinaryTrees() {}

BenchmarkBinaryTrees::~BenchmarkBinaryTrees() {}
