/**************************************************************************/
/*  dynamic_bvh.h                                                         */
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

#pragma once

#include "core/math/aabb.h"
#include "core/templates/list.h"
#include "core/templates/local_vector.h"
#include "core/templates/paged_allocator.h"
#include "core/typedefs.h"

// Based on bullet Dbvh

/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2013 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///DynamicBVH implementation by Nathanael Presson
// The DynamicBVH class implements a fast dynamic bounding volume tree based on axis aligned bounding boxes (aabb tree).

class DynamicBVH {
	struct Node;

public:
	struct ID {
		Node *node = nullptr;

	public:
		_FORCE_INLINE_ bool is_valid() const { return node != nullptr; }
	};

private:
	struct Volume {
		Vector3 min, max;

		_FORCE_INLINE_ Vector3 get_center() const { return ((min + max) / 2); }
		_FORCE_INLINE_ Vector3 get_length() const { return (max - min); }

		_FORCE_INLINE_ bool contains(const Volume &a) const {
			return ((min.x <= a.min.x) &&
					(min.y <= a.min.y) &&
					(min.z <= a.min.z) &&
					(max.x >= a.max.x) &&
					(max.y >= a.max.y) &&
					(max.z >= a.max.z));
		}

		_FORCE_INLINE_ Volume merge(const Volume &b) const {
			Volume r;
			for (int i = 0; i < 3; ++i) {
				if (min[i] < b.min[i]) {
					r.min[i] = min[i];
				} else {
					r.min[i] = b.min[i];
				}
				if (max[i] > b.max[i]) {
					r.max[i] = max[i];
				} else {
					r.max[i] = b.max[i];
				}
			}
			return r;
		}

		_FORCE_INLINE_ real_t get_size() const {
			const Vector3 edges = get_length();
			return (edges.x * edges.y * edges.z +
					edges.x + edges.y + edges.z);
		}

		_FORCE_INLINE_ bool is_not_equal_to(const Volume &b) const {
			return ((min.x != b.min.x) ||
					(min.y != b.min.y) ||
					(min.z != b.min.z) ||
					(max.x != b.max.x) ||
					(max.y != b.max.y) ||
					(max.z != b.max.z));
		}

		_FORCE_INLINE_ real_t get_proximity_to(const Volume &b) const {
			const Vector3 d = (min + max) - (b.min + b.max);
			return (Math::abs(d.x) + Math::abs(d.y) + Math::abs(d.z));
		}

		_FORCE_INLINE_ int select_by_proximity(const Volume &a, const Volume &b) const {
			return (get_proximity_to(a) < get_proximity_to(b) ? 0 : 1);
		}

		//
		_FORCE_INLINE_ bool intersects(const Volume &b) const {
			return ((min.x <= b.max.x) &&
					(max.x >= b.min.x) &&
					(min.y <= b.max.y) &&
					(max.y >= b.min.y) &&
					(min.z <= b.max.z) &&
					(max.z >= b.min.z));
		}

		_FORCE_INLINE_ bool intersects_convex(const Plane *p_planes, int p_plane_count, const Vector3 *p_points, int p_point_count) const {
			Vector3 half_extents = (max - min) * 0.5;
			Vector3 ofs = min + half_extents;

			for (int i = 0; i < p_plane_count; i++) {
				const Plane &p = p_planes[i];
				Vector3 point(
						(p.normal.x > 0) ? -half_extents.x : half_extents.x,
						(p.normal.y > 0) ? -half_extents.y : half_extents.y,
						(p.normal.z > 0) ? -half_extents.z : half_extents.z);
				point += ofs;
				if (p.is_point_over(point)) {
					return false;
				}
			}

			// Make sure all points in the shape aren't fully separated from the AABB on
			// each axis.
			int bad_point_counts_positive[3] = { 0 };
			int bad_point_counts_negative[3] = { 0 };

			for (int k = 0; k < 3; k++) {
				for (int i = 0; i < p_point_count; i++) {
					if (p_points[i].coord[k] > ofs.coord[k] + half_extents.coord[k]) {
						bad_point_counts_positive[k]++;
					}
					if (p_points[i].coord[k] < ofs.coord[k] - half_extents.coord[k]) {
						bad_point_counts_negative[k]++;
					}
				}

				if (bad_point_counts_negative[k] == p_point_count) {
					return false;
				}
				if (bad_point_counts_positive[k] == p_point_count) {
					return false;
				}
			}

			return true;
		}
	};

	struct Node {
		Volume volume;
		Node *parent = nullptr;
		union {
			Node *children[2];
			void *data;
		};

		_FORCE_INLINE_ bool is_leaf() const { return children[1] == nullptr; }
		_FORCE_INLINE_ bool is_internal() const { return (!is_leaf()); }

		_FORCE_INLINE_ int get_index_in_parent() const {
			ERR_FAIL_NULL_V(parent, 0);
			return (parent->children[1] == this) ? 1 : 0;
		}
		void get_max_depth(int depth, int &maxdepth) {
			if (is_internal()) {
				children[0]->get_max_depth(depth + 1, maxdepth);
				children[1]->get_max_depth(depth + 1, maxdepth);
			} else {
				maxdepth = MAX(maxdepth, depth);
			}
		}

		//
		int count_leaves() const {
			if (is_internal()) {
				return children[0]->count_leaves() + children[1]->count_leaves();
			} else {
				return (1);
			}
		}

		bool is_left_of_axis(const Vector3 &org, const Vector3 &axis) const {
			return axis.dot(volume.get_center() - org) <= 0;
		}

		Node() {
			children[0] = nullptr;
			children[1] = nullptr;
		}
	};

	PagedAllocator<Node> node_allocator;
	// Fields
	Node *bvh_root = nullptr;
	int lkhd = -1;
	int total_leaves = 0;
	uint32_t opath = 0;
	uint32_t index = 0;

	enum {
		ALLOCA_STACK_SIZE = 128
	};

	_FORCE_INLINE_ void _delete_node(Node *p_node);
	void _recurse_delete_node(Node *p_node);
	_FORCE_INLINE_ Node *_create_node(Node *p_parent, void *p_data);
	_FORCE_INLINE_ DynamicBVH::Node *_create_node_with_volume(Node *p_parent, const Volume &p_volume, void *p_data);
	_FORCE_INLINE_ void _insert_leaf(Node *p_root, Node *p_leaf);
	_FORCE_INLINE_ Node *_remove_leaf(Node *leaf);
	void _fetch_leaves(Node *p_root, LocalVector<Node *> &r_leaves, int p_depth = -1);
	static int _split(Node **leaves, int p_count, const Vector3 &p_org, const Vector3 &p_axis);
	static Volume _bounds(Node **leaves, int p_count);
	void _bottom_up(Node **leaves, int p_count);
	Node *_top_down(Node **leaves, int p_count, int p_bu_threshold);
	Node *_node_sort(Node *n, Node *&r);

	_FORCE_INLINE_ void _update(Node *leaf, int lookahead = -1);

	void _extract_leaves(Node *p_node, List<ID> *r_elements);

	_FORCE_INLINE_ bool _ray_aabb(const Vector3 &rayFrom, const Vector3 &rayInvDirection, const unsigned int raySign[3], const Vector3 bounds[2], real_t &tmin, real_t lambda_min, real_t lambda_max) {
		real_t tmax, tymin, tymax, tzmin, tzmax;
		tmin = (bounds[raySign[0]].x - rayFrom.x) * rayInvDirection.x;
		tmax = (bounds[1 - raySign[0]].x - rayFrom.x) * rayInvDirection.x;
		tymin = (bounds[raySign[1]].y - rayFrom.y) * rayInvDirection.y;
		tymax = (bounds[1 - raySign[1]].y - rayFrom.y) * rayInvDirection.y;

		if ((tmin > tymax) || (tymin > tmax)) {
			return false;
		}

		if (tymin > tmin) {
			tmin = tymin;
		}

		if (tymax < tmax) {
			tmax = tymax;
		}

		tzmin = (bounds[raySign[2]].z - rayFrom.z) * rayInvDirection.z;
		tzmax = (bounds[1 - raySign[2]].z - rayFrom.z) * rayInvDirection.z;

		if ((tmin > tzmax) || (tzmin > tmax)) {
			return false;
		}
		if (tzmin > tmin) {
			tmin = tzmin;
		}
		if (tzmax < tmax) {
			tmax = tzmax;
		}
		return ((tmin < lambda_max) && (tmax > lambda_min));
	}

public:
	// Methods
	void clear();
	bool is_empty() const { return (nullptr == bvh_root); }
	void optimize_bottom_up();
	void optimize_top_down(int bu_threshold = 128);
	void optimize_incremental(int passes);
	ID insert(const AABB &p_box, void *p_userdata);
	bool update(const ID &p_id, const AABB &p_box);
	void remove(const ID &p_id);
	void get_elements(List<ID> *r_elements);

	int get_leaf_count() const;
	int get_max_depth() const;

	/* Discouraged, but works as a reference on how it must be used */
	struct DefaultQueryResult {
		virtual bool operator()(void *p_data) = 0; //return true whether you want to continue the query
		virtual ~DefaultQueryResult() {}
	};

	template <typename QueryResult>
	_FORCE_INLINE_ void aabb_query(const AABB &p_aabb, QueryResult &r_result);
	template <typename QueryResult>
	_FORCE_INLINE_ void convex_query(const Plane *p_planes, int p_plane_count, const Vector3 *p_points, int p_point_count, QueryResult &r_result);
	template <typename QueryResult>
	_FORCE_INLINE_ void ray_query(const Vector3 &p_from, const Vector3 &p_to, QueryResult &r_result);

	void set_index(uint32_t p_index);
	uint32_t get_index() const;

	~DynamicBVH();
};

template <typename QueryResult>
void DynamicBVH::aabb_query(const AABB &p_box, QueryResult &r_result) {
	if (!bvh_root) {
		return;
	}

	Volume volume;
	volume.min = p_box.position;
	volume.max = p_box.position + p_box.size;

	const Node **alloca_stack = (const Node **)alloca(ALLOCA_STACK_SIZE * sizeof(const Node *));
	const Node **stack = alloca_stack;
	stack[0] = bvh_root;
	int32_t depth = 1;
	int32_t threshold = ALLOCA_STACK_SIZE - 2;

	LocalVector<const Node *> aux_stack; //only used in rare occasions when you run out of alloca memory because tree is too unbalanced. Should correct itself over time.

	do {
		depth--;
		const Node *n = stack[depth];
		if (n->volume.intersects(volume)) {
			if (n->is_internal()) {
				if (depth > threshold) {
					if (aux_stack.is_empty()) {
						aux_stack.resize(ALLOCA_STACK_SIZE * 2);
						memcpy(aux_stack.ptr(), alloca_stack, ALLOCA_STACK_SIZE * sizeof(const Node *));
						alloca_stack = nullptr;
					} else {
						aux_stack.resize(aux_stack.size() * 2);
					}
					stack = aux_stack.ptr();
					threshold = aux_stack.size() - 2;
				}
				stack[depth++] = n->children[0];
				stack[depth++] = n->children[1];
			} else {
				if (r_result(n->data)) {
					return;
				}
			}
		}
	} while (depth > 0);
}

template <typename QueryResult>
void DynamicBVH::convex_query(const Plane *p_planes, int p_plane_count, const Vector3 *p_points, int p_point_count, QueryResult &r_result) {
	if (!bvh_root) {
		return;
	}

	//generate a volume anyway to improve pre-testing
	Volume volume;
	for (int i = 0; i < p_point_count; i++) {
		if (i == 0) {
			volume.min = p_points[0];
			volume.max = p_points[0];
		} else {
			volume.min = volume.min.min(p_points[i]);
			volume.max = volume.max.max(p_points[i]);
		}
	}

	const Node **alloca_stack = (const Node **)alloca(ALLOCA_STACK_SIZE * sizeof(const Node *));
	const Node **stack = alloca_stack;
	stack[0] = bvh_root;
	int32_t depth = 1;
	int32_t threshold = ALLOCA_STACK_SIZE - 2;

	LocalVector<const Node *> aux_stack; //only used in rare occasions when you run out of alloca memory because tree is too unbalanced. Should correct itself over time.

	do {
		depth--;
		const Node *n = stack[depth];
		if (n->volume.intersects(volume) && n->volume.intersects_convex(p_planes, p_plane_count, p_points, p_point_count)) {
			if (n->is_internal()) {
				if (depth > threshold) {
					if (aux_stack.is_empty()) {
						aux_stack.resize(ALLOCA_STACK_SIZE * 2);
						memcpy(aux_stack.ptr(), alloca_stack, ALLOCA_STACK_SIZE * sizeof(const Node *));
						alloca_stack = nullptr;
					} else {
						aux_stack.resize(aux_stack.size() * 2);
					}
					stack = aux_stack.ptr();
					threshold = aux_stack.size() - 2;
				}
				stack[depth++] = n->children[0];
				stack[depth++] = n->children[1];
			} else {
				if (r_result(n->data)) {
					return;
				}
			}
		}
	} while (depth > 0);
}
template <typename QueryResult>
void DynamicBVH::ray_query(const Vector3 &p_from, const Vector3 &p_to, QueryResult &r_result) {
	if (!bvh_root) {
		return;
	}

	Vector3 ray_dir = (p_to - p_from);
	ray_dir.normalize();

	///what about division by zero? --> just set rayDirection[i] to INF/B3_LARGE_FLOAT
	Vector3 inv_dir;
	inv_dir[0] = ray_dir[0] == real_t(0.0) ? real_t(1e20) : real_t(1.0) / ray_dir[0];
	inv_dir[1] = ray_dir[1] == real_t(0.0) ? real_t(1e20) : real_t(1.0) / ray_dir[1];
	inv_dir[2] = ray_dir[2] == real_t(0.0) ? real_t(1e20) : real_t(1.0) / ray_dir[2];
	unsigned int signs[3] = { inv_dir[0] < 0.0, inv_dir[1] < 0.0, inv_dir[2] < 0.0 };

	real_t lambda_max = ray_dir.dot(p_to - p_from);

	Vector3 bounds[2];

	const Node **alloca_stack = (const Node **)alloca(ALLOCA_STACK_SIZE * sizeof(const Node *));
	const Node **stack = alloca_stack;
	stack[0] = bvh_root;
	int32_t depth = 1;
	int32_t threshold = ALLOCA_STACK_SIZE - 2;

	LocalVector<const Node *> aux_stack; //only used in rare occasions when you run out of alloca memory because tree is too unbalanced. Should correct itself over time.

	do {
		depth--;
		const Node *node = stack[depth];
		bounds[0] = node->volume.min;
		bounds[1] = node->volume.max;
		real_t tmin = 1.f, lambda_min = 0.f;
		unsigned int result1 = false;
		result1 = _ray_aabb(p_from, inv_dir, signs, bounds, tmin, lambda_min, lambda_max);
		if (result1) {
			if (node->is_internal()) {
				if (depth > threshold) {
					if (aux_stack.is_empty()) {
						aux_stack.resize(ALLOCA_STACK_SIZE * 2);
						memcpy(aux_stack.ptr(), alloca_stack, ALLOCA_STACK_SIZE * sizeof(const Node *));
						alloca_stack = nullptr;
					} else {
						aux_stack.resize(aux_stack.size() * 2);
					}
					stack = aux_stack.ptr();
					threshold = aux_stack.size() - 2;
				}
				stack[depth++] = node->children[0];
				stack[depth++] = node->children[1];
			} else {
				if (r_result(node->data)) {
					return;
				}
			}
		}
	} while (depth > 0);
}

inline void DynamicBVH::_delete_node(Node *p_node) {
	node_allocator.free(p_node);
}

inline void DynamicBVH::_recurse_delete_node(Node *p_node) {
	if (!p_node->is_leaf()) {
		_recurse_delete_node(p_node->children[0]);
		_recurse_delete_node(p_node->children[1]);
	}
	if (p_node == bvh_root) {
		bvh_root = nullptr;
	}
	_delete_node(p_node);
}

inline DynamicBVH::Node *DynamicBVH::_create_node(Node *p_parent, void *p_data) {
	Node *node = node_allocator.alloc();
	node->parent = p_parent;
	node->data = p_data;
	return (node);
}

inline DynamicBVH::Node *DynamicBVH::_create_node_with_volume(Node *p_parent, const Volume &p_volume, void *p_data) {
	Node *node = _create_node(p_parent, p_data);
	node->volume = p_volume;
	return node;
}

inline void DynamicBVH::_insert_leaf(Node *p_root, Node *p_leaf) {
	if (!bvh_root) {
		bvh_root = p_leaf;
		p_leaf->parent = nullptr;
	} else {
		if (!p_root->is_leaf()) {
			do {
				p_root = p_root->children[p_leaf->volume.select_by_proximity(
						p_root->children[0]->volume,
						p_root->children[1]->volume)];
			} while (!p_root->is_leaf());
		}
		Node *prev = p_root->parent;
		Node *node = _create_node_with_volume(prev, p_leaf->volume.merge(p_root->volume), nullptr);
		if (prev) {
			prev->children[p_root->get_index_in_parent()] = node;
			node->children[0] = p_root;
			p_root->parent = node;
			node->children[1] = p_leaf;
			p_leaf->parent = node;
			do {
				if (!prev->volume.contains(node->volume)) {
					prev->volume = prev->children[0]->volume.merge(prev->children[1]->volume);
				} else {
					break;
				}
				node = prev;
			} while (nullptr != (prev = node->parent));
		} else {
			node->children[0] = p_root;
			p_root->parent = node;
			node->children[1] = p_leaf;
			p_leaf->parent = node;
			bvh_root = node;
		}
	}
}

inline DynamicBVH::Node *DynamicBVH::_remove_leaf(Node *leaf) {
	if (leaf == bvh_root) {
		bvh_root = nullptr;
		return (nullptr);
	} else {
		Node *parent = leaf->parent;
		Node *prev = parent->parent;
		Node *sibling = parent->children[1 - leaf->get_index_in_parent()];
		if (prev) {
			prev->children[parent->get_index_in_parent()] = sibling;
			sibling->parent = prev;
			_delete_node(parent);
			while (prev) {
				const Volume pb = prev->volume;
				prev->volume = prev->children[0]->volume.merge(prev->children[1]->volume);
				if (pb.is_not_equal_to(prev->volume)) {
					prev = prev->parent;
				} else {
					break;
				}
			}
			return (prev ? prev : bvh_root);
		} else {
			bvh_root = sibling;
			sibling->parent = nullptr;
			_delete_node(parent);
			return (bvh_root);
		}
	}
}

inline void DynamicBVH::_fetch_leaves(Node *p_root, LocalVector<Node *> &r_leaves, int p_depth) {
	if (p_root->is_internal() && p_depth) {
		_fetch_leaves(p_root->children[0], r_leaves, p_depth - 1);
		_fetch_leaves(p_root->children[1], r_leaves, p_depth - 1);
		_delete_node(p_root);
	} else {
		r_leaves.push_back(p_root);
	}
}

// Partitions leaves such that leaves[0, n) are on the
// left of axis, and leaves[n, count) are on the right
// of axis. returns N.
inline int DynamicBVH::_split(Node **leaves, int p_count, const Vector3 &p_org, const Vector3 &p_axis) {
	int begin = 0;
	int end = p_count;
	for (;;) {
		while (begin != end && leaves[begin]->is_left_of_axis(p_org, p_axis)) {
			++begin;
		}

		if (begin == end) {
			break;
		}

		while (begin != end && !leaves[end - 1]->is_left_of_axis(p_org, p_axis)) {
			--end;
		}

		if (begin == end) {
			break;
		}

		// swap out of place nodes
		--end;
		Node *temp = leaves[begin];
		leaves[begin] = leaves[end];
		leaves[end] = temp;
		++begin;
	}

	return begin;
}

inline DynamicBVH::Volume DynamicBVH::_bounds(Node **leaves, int p_count) {
	Volume volume = leaves[0]->volume;
	for (int i = 1, ni = p_count; i < ni; ++i) {
		volume = volume.merge(leaves[i]->volume);
	}
	return (volume);
}

inline void DynamicBVH::_bottom_up(Node **leaves, int p_count) {
	while (p_count > 1) {
		real_t minsize = INFINITY;
		int minidx[2] = { -1, -1 };
		for (int i = 0; i < p_count; ++i) {
			for (int j = i + 1; j < p_count; ++j) {
				const real_t sz = leaves[i]->volume.merge(leaves[j]->volume).get_size();
				if (sz < minsize) {
					minsize = sz;
					minidx[0] = i;
					minidx[1] = j;
				}
			}
		}
		Node *n[] = { leaves[minidx[0]], leaves[minidx[1]] };
		Node *p = _create_node_with_volume(nullptr, n[0]->volume.merge(n[1]->volume), nullptr);
		p->children[0] = n[0];
		p->children[1] = n[1];
		n[0]->parent = p;
		n[1]->parent = p;
		leaves[minidx[0]] = p;
		leaves[minidx[1]] = leaves[p_count - 1];
		--p_count;
	}
}

inline DynamicBVH::Node *DynamicBVH::_top_down(Node **leaves, int p_count, int p_bu_threshold) {
	static const Vector3 axis[] = { Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1) };

	ERR_FAIL_COND_V(p_bu_threshold <= 1, nullptr);
	if (p_count > 1) {
		if (p_count > p_bu_threshold) {
			const Volume vol = _bounds(leaves, p_count);
			const Vector3 org = vol.get_center();
			int partition;
			int bestaxis = -1;
			int bestmidp = p_count;
			int splitcount[3][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
			int i;
			for (i = 0; i < p_count; ++i) {
				const Vector3 x = leaves[i]->volume.get_center() - org;
				for (int j = 0; j < 3; ++j) {
					++splitcount[j][x.dot(axis[j]) > 0 ? 1 : 0];
				}
			}
			for (i = 0; i < 3; ++i) {
				if ((splitcount[i][0] > 0) && (splitcount[i][1] > 0)) {
					const int midp = (int)Math::abs(real_t(splitcount[i][0] - splitcount[i][1]));
					if (midp < bestmidp) {
						bestaxis = i;
						bestmidp = midp;
					}
				}
			}
			if (bestaxis >= 0) {
				partition = _split(leaves, p_count, org, axis[bestaxis]);
				ERR_FAIL_COND_V(partition == 0 || partition == p_count, nullptr);
			} else {
				partition = p_count / 2 + 1;
			}

			Node *node = _create_node_with_volume(nullptr, vol, nullptr);
			node->children[0] = _top_down(&leaves[0], partition, p_bu_threshold);
			node->children[1] = _top_down(&leaves[partition], p_count - partition, p_bu_threshold);
			node->children[0]->parent = node;
			node->children[1]->parent = node;
			return (node);
		} else {
			_bottom_up(leaves, p_count);
			return (leaves[0]);
		}
	}
	return (leaves[0]);
}

inline DynamicBVH::Node *DynamicBVH::_node_sort(Node *n, Node *&r) {
	Node *p = n->parent;
	ERR_FAIL_COND_V(!n->is_internal(), nullptr);
	if (p > n) {
		const int i = n->get_index_in_parent();
		const int j = 1 - i;
		Node *s = p->children[j];
		Node *q = p->parent;
		ERR_FAIL_COND_V(n != p->children[i], nullptr);
		if (q) {
			q->children[p->get_index_in_parent()] = n;
		} else {
			r = n;
		}
		s->parent = n;
		p->parent = n;
		n->parent = q;
		p->children[0] = n->children[0];
		p->children[1] = n->children[1];
		n->children[0]->parent = p;
		n->children[1]->parent = p;
		n->children[i] = p;
		n->children[j] = s;
		SWAP(p->volume, n->volume);
		return (p);
	}
	return (n);
}

inline void DynamicBVH::clear() {
	if (bvh_root) {
		_recurse_delete_node(bvh_root);
	}
	lkhd = -1;
	opath = 0;
}

inline void DynamicBVH::optimize_bottom_up() {
	if (bvh_root) {
		LocalVector<Node *> leaves;
		_fetch_leaves(bvh_root, leaves);
		_bottom_up(&leaves[0], leaves.size());
		bvh_root = leaves[0];
	}
}

inline void DynamicBVH::optimize_top_down(int bu_threshold) {
	if (bvh_root) {
		LocalVector<Node *> leaves;
		_fetch_leaves(bvh_root, leaves);
		bvh_root = _top_down(&leaves[0], leaves.size(), bu_threshold);
	}
}

inline void DynamicBVH::optimize_incremental(int passes) {
	if (passes < 0) {
		passes = total_leaves;
	}
	if (passes > 0) {
		do {
			if (!bvh_root) {
				break;
			}
			Node *node = bvh_root;
			unsigned bit = 0;
			while (node->is_internal()) {
				node = _node_sort(node, bvh_root)->children[(opath >> bit) & 1];
				bit = (bit + 1) & (sizeof(unsigned) * 8 - 1);
			}
			_update(node);
			++opath;
		} while (--passes);
	}
}

inline DynamicBVH::ID DynamicBVH::insert(const AABB &p_box, void *p_userdata) {
	Volume volume;
	volume.min = p_box.position;
	volume.max = p_box.position + p_box.size;

	Node *leaf = _create_node_with_volume(nullptr, volume, p_userdata);
	_insert_leaf(bvh_root, leaf);
	++total_leaves;

	ID id;
	id.node = leaf;

	return id;
}

inline void DynamicBVH::_update(Node *leaf, int lookahead) {
	Node *root = _remove_leaf(leaf);
	if (root) {
		if (lookahead >= 0) {
			for (int i = 0; (i < lookahead) && root->parent; ++i) {
				root = root->parent;
			}
		} else {
			root = bvh_root;
		}
	}
	_insert_leaf(root, leaf);
}

inline bool DynamicBVH::update(const ID &p_id, const AABB &p_box) {
	ERR_FAIL_COND_V(!p_id.is_valid(), false);
	Node *leaf = p_id.node;

	Volume volume;
	volume.min = p_box.position;
	volume.max = p_box.position + p_box.size;

	if (leaf->volume.min.is_equal_approx(volume.min) && leaf->volume.max.is_equal_approx(volume.max)) {
		// noop
		return false;
	}

	Node *base = _remove_leaf(leaf);
	if (base) {
		if (lkhd >= 0) {
			for (int i = 0; (i < lkhd) && base->parent; ++i) {
				base = base->parent;
			}
		} else {
			base = bvh_root;
		}
	}
	leaf->volume = volume;
	_insert_leaf(base, leaf);
	return true;
}

inline void DynamicBVH::remove(const ID &p_id) {
	ERR_FAIL_COND(!p_id.is_valid());
	Node *leaf = p_id.node;
	_remove_leaf(leaf);
	_delete_node(leaf);
	--total_leaves;
}

inline void DynamicBVH::_extract_leaves(Node *p_node, List<ID> *r_elements) {
	if (p_node->is_internal()) {
		_extract_leaves(p_node->children[0], r_elements);
		_extract_leaves(p_node->children[1], r_elements);
	} else {
		ID id;
		id.node = p_node;
		r_elements->push_back(id);
	}
}

inline void DynamicBVH::set_index(uint32_t p_index) {
	ERR_FAIL_COND(bvh_root != nullptr);
	index = p_index;
}

inline uint32_t DynamicBVH::get_index() const {
	return index;
}

inline void DynamicBVH::get_elements(List<ID> *r_elements) {
	if (bvh_root) {
		_extract_leaves(bvh_root, r_elements);
	}
}

inline int DynamicBVH::get_leaf_count() const {
	return total_leaves;
}
inline int DynamicBVH::get_max_depth() const {
	if (bvh_root) {
		int depth = 1;
		int max_depth = 0;
		bvh_root->get_max_depth(depth, max_depth);
		return max_depth;
	} else {
		return 0;
	}
}

inline DynamicBVH::~DynamicBVH() {
	clear();
}
