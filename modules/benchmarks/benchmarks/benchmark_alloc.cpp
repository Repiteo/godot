/**************************************************************************/
/*  benchmark_alloc.cpp                                                   */
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

#include "benchmark_alloc.h"

#ifdef GODOT_MODULE
#include "core/math/random_number_generator.h"
#include "core/object/class_db.h"
#include "scene/main/node.h"
#else
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

void BenchmarkAlloc::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_deep_tree"), &BenchmarkAlloc::benchmark_deep_tree);
	ClassDB::bind_method(D_METHOD("benchmark_wide_tree"), &BenchmarkAlloc::benchmark_wide_tree);
	ClassDB::bind_method(D_METHOD("benchmark_fragmentation"), &BenchmarkAlloc::benchmark_fragmentation);
	ClassDB::bind_method(D_METHOD("benchmark_duplicate"), &BenchmarkAlloc::benchmark_duplicate);
}

void BenchmarkAlloc::benchmark_deep_tree() {
	Node *rt = memnew(Node);
	for (int i = 0; i < iterations; i++) {
		Node *n = memnew(Node);
		n->add_child(rt);
		rt = n;
	}
	// Avoid triggering a stack overflow with memdelete(rt)
	while (rt->get_child_count() != 0) {
		Node *n = rt->get_child(0);
		rt->remove_child(n);
		memdelete(rt);
		rt = n;
	}
	memdelete(rt);
}

void BenchmarkAlloc::benchmark_wide_tree() {
	Node *rt = memnew(Node);
	for (int i = 0; i < iterations; i++) {
		rt->add_child(memnew(Node));
	}
	memdelete(rt);
}

void BenchmarkAlloc::benchmark_fragmentation() {
	Node *top = memnew(Node);
	for (int i = 0; i < 5; i++) {
		top->add_child(memnew(Node));
	}
	Ref<RandomNumberGenerator> rand;
	rand.instantiate();
	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < iterations; i++) {
			// Attempt to scatter children in memory by assigning newly created nodes to a random parent
			int idx = rand->randi() % top->get_child_count();
			top->get_child(idx)->add_child(memnew(Node));
		}

		Node *tmp = top->get_child(0);
		top->remove_child(tmp);
		// Since nodes in the tree are scattered in memory,
		// freeing subtrees this way should maximize fragmentation.
		memdelete(tmp);
		top->add_child(memnew(Node));
	}

	memdelete(top);
}

void BenchmarkAlloc::benchmark_duplicate() {
	Node *rt = memnew(Node);
	for (int i = 0; i < 16; i++) {
		Node *n = memnew(Node);
		n->add_child(rt->duplicate());
		n->add_child(rt->duplicate());
		memdelete(rt);
		rt = n;
	}
	memdelete(rt);
}

BenchmarkAlloc::BenchmarkAlloc() {}

BenchmarkAlloc::~BenchmarkAlloc() {}
