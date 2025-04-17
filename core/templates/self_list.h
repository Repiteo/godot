/**************************************************************************/
/*  self_list.h                                                           */
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

#include "core/error/error_macros.h"
#include "core/typedefs.h"

template <typename T>
class SelfList {
public:
	class List {
		SelfList<T> *_first = nullptr;
		SelfList<T> *_last = nullptr;

	public:
		void add(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root);

			p_elem->_root = this;
			p_elem->_next = _first;
			p_elem->_prev = nullptr;

			if (_first) {
				_first->_prev = p_elem;

			} else {
				_last = p_elem;
			}

			_first = p_elem;
		}

		void add_last(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root);

			p_elem->_root = this;
			p_elem->_next = nullptr;
			p_elem->_prev = _last;

			if (_last) {
				_last->_next = p_elem;

			} else {
				_first = p_elem;
			}

			_last = p_elem;
		}

		void remove(SelfList<T> *p_elem) {
			ERR_FAIL_COND(p_elem->_root != this);
			if (p_elem->_next) {
				p_elem->_next->_prev = p_elem->_prev;
			}

			if (p_elem->_prev) {
				p_elem->_prev->_next = p_elem->_next;
			}

			if (_first == p_elem) {
				_first = p_elem->_next;
			}

			if (_last == p_elem) {
				_last = p_elem->_prev;
			}

			p_elem->_next = nullptr;
			p_elem->_prev = nullptr;
			p_elem->_root = nullptr;
		}

		void clear() {
			while (_first) {
				remove(_first);
			}
		}

		void sort() {
			sort_custom<Comparator<T>>();
		}

		template <typename C>
		void sort_custom() {
			if (_first == _last) {
				return;
			}

			SelfList<T> *from = _first;
			SelfList<T> *current = from;
			SelfList<T> *to = from;

			while (current) {
				SelfList<T> *next = current->_next;

				if (from != current) {
					current->_prev = nullptr;
					current->_next = from;

					SelfList<T> *find = from;
					C less;
					while (find && less(*find->_self, *current->_self)) {
						current->_prev = find;
						current->_next = find->_next;
						find = find->_next;
					}

					if (current->_prev) {
						current->_prev->_next = current;
					} else {
						from = current;
					}

					if (current->_next) {
						current->_next->_prev = current;
					} else {
						to = current;
					}
				} else {
					current->_prev = nullptr;
					current->_next = nullptr;
				}

				current = next;
			}
			_first = from;
			_last = to;
		}

		GD_FORCE_INLINE SelfList<T> *first() { return _first; }
		GD_FORCE_INLINE const SelfList<T> *first() const { return _first; }

		// Forbid copying, which has broken behavior.
		void operator=(const List &) = delete;

		GD_FORCE_INLINE List() {}
		GD_FORCE_INLINE ~List() {
			// A self list must be empty on destruction.
			DEV_ASSERT(_first == nullptr);
		}
	};

private:
	List *_root = nullptr;
	T *_self = nullptr;
	SelfList<T> *_next = nullptr;
	SelfList<T> *_prev = nullptr;

public:
	GD_FORCE_INLINE bool in_list() const { return _root; }
	GD_FORCE_INLINE void remove_from_list() {
		if (_root) {
			_root->remove(this);
		}
	}
	GD_FORCE_INLINE SelfList<T> *next() { return _next; }
	GD_FORCE_INLINE SelfList<T> *prev() { return _prev; }
	GD_FORCE_INLINE const SelfList<T> *next() const { return _next; }
	GD_FORCE_INLINE const SelfList<T> *prev() const { return _prev; }
	GD_FORCE_INLINE T *self() const { return _self; }

	// Forbid copying, which has broken behavior.
	void operator=(const SelfList<T> &) = delete;

	GD_FORCE_INLINE SelfList(T *p_self) {
		_self = p_self;
	}

	GD_FORCE_INLINE ~SelfList() {
		if (_root) {
			_root->remove(this);
		}
	}
};
