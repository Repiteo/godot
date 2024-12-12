/**************************************************************************/
/*  benchmark_merkle_trees.h                                              */
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

#ifndef BENCHMARK_MERKLE_TREES_H
#define BENCHMARK_MERKLE_TREES_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkMerkleTrees BENCHMARK(MerkleTrees)

class BenchmarkMerkleTrees : public Benchmark {
	BENCHMARK_GDCLASS(MerkleTrees)

	class TreeNode {
		int value;
		TreeNode *left;
		TreeNode *right;

	public:
		TreeNode() {
			value = -1;
			left = nullptr;
			right = nullptr;
			hash = -1;
		}
		TreeNode(int p_value, TreeNode *p_left, TreeNode *p_right) {
			value = p_value;
			left = p_left;
			right = p_right;
			hash = -1;
		}
		~TreeNode() {
			delete left;
			delete right;
		}
		bool check() {
			if (hash != -1) {
				if (value != -1) {
					return true;
				}
				if (left != nullptr && right != nullptr) {
					return left->check() && right->check();
				}
			}
			return false;
		}
		void cal_hash() {
			if (hash == -1) {
				if (value != -1) {
					hash = value;
				} else if (left != nullptr && right != nullptr) {
					left->cal_hash();
					right->cal_hash();
					hash = left->hash + right->hash;
				}
			}
		}
		int hash;
	};

	static constexpr int min_depth = 4;

	TreeNode *make_tree(int depth);
	void calculate_merkle_trees(int input);

protected:
	static void _bind_methods();

public:
	void benchmark_merkle_trees_13();
	void benchmark_merkle_trees_15();
	void benchmark_merkle_trees_18();

	BenchmarkMerkleTrees();
	~BenchmarkMerkleTrees();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_MERKLE_TREES_H
