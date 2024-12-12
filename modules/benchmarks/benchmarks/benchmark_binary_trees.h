/**************************************************************************/
/*  benchmark_binary_trees.h                                              */
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

#ifndef BENCHMARK_BINARY_TREES_H
#define BENCHMARK_BINARY_TREES_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkBinaryTrees BENCHMARK(BinaryTrees)

class BenchmarkBinaryTrees : public Benchmark {
	BENCHMARK_GDCLASS(BinaryTrees)

	class TreeNode {
		TreeNode *left;
		TreeNode *right;

	public:
		TreeNode() {
			left = nullptr;
			right = nullptr;
		}
		TreeNode(TreeNode *p_left, TreeNode *p_right) {
			left = p_left;
			right = p_right;
		}
		~TreeNode() {
			delete left;
			delete right;
		}
		static TreeNode *create(int d) {
			if (d == 0)
				return new TreeNode();
			return new TreeNode(create(d - 1), create(d - 1));
		}
		int check() {
			int c = 1;
			if (right != nullptr) {
				c += right->check();
			}
			if (left != nullptr) {
				c += left->check();
			}
			return c;
		}
	};

	static constexpr int min_depth = 4;
	void calculate_binary_trees(int input);

protected:
	static void _bind_methods();

public:
	void benchmark_binary_trees_13();
	void benchmark_binary_trees_15();
	void benchmark_binary_trees_18();

	BenchmarkBinaryTrees();
	~BenchmarkBinaryTrees();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_BINARY_TREES_H
