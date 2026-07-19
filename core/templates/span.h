/**************************************************************************/
/*  span.h                                                                */
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

template <typename T1, typename T2 = T1, typename = void>
struct HasComparisonOperators : std::false_type {};

template <typename T1, typename T2>
struct HasComparisonOperators<T1, T2, std::void_t<decltype(std::declval<T1>() < std::declval<T2>())>> : std::true_type {};

template <typename T1, typename T2>
inline constexpr bool has_comparison_operators_v = HasComparisonOperators<T1, T2>::value;

// Equivalent of std::span.
// Represents a view into a contiguous memory space.
// DISCLAIMER: This data type does not own the underlying buffer. DO NOT STORE IT.
//  Additionally, for the lifetime of the Span, do not resize the buffer, and do not insert or remove elements from it.
//  Failure to respect this may lead to crashes or undefined behavior.
template <typename T>
class Span {
	const T *_ptr = nullptr;
	uint64_t _len = 0;

public:
	static constexpr bool is_string = std::disjunction_v<
			std::is_same<T, char>,
			std::is_same<T, char16_t>,
			std::is_same<T, char32_t>,
			std::is_same<T, wchar_t>>;

	_FORCE_INLINE_ constexpr Span() = default;

	_FORCE_INLINE_ constexpr Span(const T *p_ptr, uint64_t p_len) :
			_ptr(p_ptr), _len(p_len) {
#ifdef DEBUG_ENABLED
		if (_ptr == nullptr && _len != 0) {
			ERR_PRINT("Internal bug, please report: Span was created from nullptr with size > 0. Recovering by using size = 0.");
			_len = 0;
		}
#endif
	}

	// Allows creating Span directly from C arrays and string literals.
	template <size_t N>
	_FORCE_INLINE_ constexpr Span(const T (&p_array)[N]) :
			_ptr(p_array), _len(N) {
		if constexpr (is_string) {
			// Cut off the \0 terminator implicitly added to string literals.
			if (N > 0 && p_array[N - 1] == '\0') {
				_len--;
			}
		}
	}

	_FORCE_INLINE_ constexpr uint64_t size() const { return _len; }
	_FORCE_INLINE_ constexpr bool is_empty() const { return _len == 0; }

	_FORCE_INLINE_ constexpr const T *ptr() const { return _ptr; }

	// NOTE: Span subscripts sanity check the bounds to avoid undefined behavior.
	//       This is slower than direct buffer access and can prevent autovectorization.
	//       If the bounds are known, use ptr() subscript instead.
	_FORCE_INLINE_ constexpr const T &operator[](uint64_t p_idx) const {
		CRASH_COND(p_idx >= _len);
		return _ptr[p_idx];
	}

	_FORCE_INLINE_ constexpr const T *begin() const { return _ptr; }
	_FORCE_INLINE_ constexpr const T *end() const { return _ptr + _len; }

	template <typename T_Other>
	_FORCE_INLINE_ Span<T_Other> reinterpret() const {
		return Span<T_Other>(reinterpret_cast<const T_Other *>(_ptr), _len * sizeof(T_Other) / sizeof(T_Other));
	}

	// Algorithms.
	template <typename T_Other = T>
	constexpr int64_t find(const T_Other &p_val, uint64_t p_from = 0) const;
	template <typename T_Other = T>
	constexpr int64_t find_sequence(const Span<T_Other> &p_span, uint64_t p_from = 0) const;
	template <typename T_Other = T>
	constexpr int64_t rfind(const T_Other &p_val, uint64_t p_from) const;
	template <typename T_Other = T>
	_FORCE_INLINE_ constexpr int64_t rfind(const T_Other &p_val) const { return rfind(p_val, size() - 1); }
	template <typename T_Other = T>
	constexpr int64_t rfind_sequence(const Span<T_Other> &p_span, uint64_t p_from) const;
	template <typename T_Other = T>
	_FORCE_INLINE_ constexpr int64_t rfind_sequence(const Span<T_Other> &p_span) const { return rfind_sequence(p_span, size() - p_span.size()); }
	template <typename T_Other = T>
	constexpr uint64_t count(const T_Other &p_val) const;
	/// Find the index of the given value using binary search.
	/// Note: Assumes that elements in the span are sorted. Otherwise, use find() instead.
	template <typename Comparator = Comparator<T>, typename T_Other = T>
	constexpr uint64_t bisect(const T_Other &p_value, bool p_before, Comparator p_compare = Comparator()) const;
	constexpr Span subspan(uint64_t p_pos, uint64_t p_len) const;
	constexpr Span subspan(uint64_t p_pos) const { return subspan(p_pos, size() - p_pos); }

	/// The caller is responsible to ensure size() > 0.
	constexpr T max() const;
	/// The caller is responsible to ensure size() > 0.
	constexpr T min() const;

	template <typename T_Other = T>
	[[nodiscard]] constexpr int8_t compare(const Span<T_Other> &p_other) const;

	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator==(const Span<T_Other> &p_other) const { return compare(p_other) == 0; }
	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator!=(const Span<T_Other> &p_other) const { return compare(p_other) != 0; }
	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator<(const Span<T_Other> &p_other) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(p_other) < 0;
	}
	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator<=(const Span<T_Other> &p_other) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(p_other) <= 0;
	}
	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator>(const Span<T_Other> &p_other) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(p_other) > 0;
	}
	template <typename T_Other = T>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator>=(const Span<T_Other> &p_other) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(p_other) >= 0;
	}

	// Allow comparing C-style arrays directly.
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator==(const T_Other (&p_other)[N]) const { return compare(Span(p_other)) == 0; }
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator!=(const T_Other (&p_other)[N]) const { return compare(Span(p_other)) != 0; }
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator<(const T_Other (&p_other)[N]) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(Span(p_other)) < 0;
	}
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator<=(const T_Other (&p_other)[N]) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(Span(p_other)) <= 0;
	}
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator>(const T_Other (&p_other)[N]) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(Span(p_other)) > 0;
	}
	template <typename T_Other = T, size_t N>
	[[nodiscard]] _FORCE_INLINE_ constexpr bool operator>=(const T_Other (&p_other)[N]) const {
		static_assert(has_comparison_operators_v<T, T_Other>);
		return compare(Span(p_other)) >= 0;
	}
};

template <typename T>
template <typename T_Other>
constexpr int64_t Span<T>::find(const T_Other &p_val, uint64_t p_from) const {
	for (uint64_t i = p_from; i < size(); i++) {
		if (ptr()[i] == p_val) {
			return i;
		}
	}
	return -1;
}

template <typename T>
template <typename T_Other>
constexpr int64_t Span<T>::find_sequence(const Span<T_Other> &p_span, uint64_t p_from) const {
	for (uint64_t i = p_from; i <= size() - p_span.size(); i++) {
		if (subspan(i, p_span.size()) == p_span) {
			return i;
		}
	}

	return -1;
}

template <typename T>
template <typename T_Other>
constexpr int64_t Span<T>::rfind(const T_Other &p_val, uint64_t p_from) const {
	DEV_ASSERT(p_from < size());
	for (int64_t i = p_from; i >= 0; i--) {
		if (ptr()[i] == p_val) {
			return i;
		}
	}
	return -1;
}

template <typename T>
template <typename T_Other>
constexpr int64_t Span<T>::rfind_sequence(const Span<T_Other> &p_span, uint64_t p_from) const {
	DEV_ASSERT(p_from + p_span.size() <= size());
	for (int64_t i = p_from; i >= 0; i--) {
		if (subspan(i, p_span.size()) == p_span) {
			return i;
		}
	}

	return -1;
}

template <typename T>
template <typename T_Other>
constexpr uint64_t Span<T>::count(const T_Other &p_val) const {
	uint64_t amount = 0;
	for (uint64_t i = 0; i < size(); i++) {
		if (ptr()[i] == p_val) {
			amount++;
		}
	}
	return amount;
}

template <typename T>
template <typename Comparator, typename T_Other>
constexpr uint64_t Span<T>::bisect(const T_Other &p_value, bool p_before, Comparator p_compare) const {
	uint64_t lo = 0;
	uint64_t hi = size();
	if (p_before) {
		while (lo < hi) {
			const uint64_t mid = (lo + hi) / 2;
			if (p_compare(ptr()[mid], p_value)) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
	} else {
		while (lo < hi) {
			const uint64_t mid = (lo + hi) / 2;
			if (p_compare(p_value, ptr()[mid])) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
	}
	return lo;
}

template <typename T>
constexpr T Span<T>::max() const {
	DEV_ASSERT(size() > 0);
	T max_val = _ptr[0];
	for (size_t i = 1; i < _len; ++i) {
		if (_ptr[i] > max_val) {
			max_val = _ptr[i];
		}
	}
	return max_val;
}

template <typename T>
constexpr T Span<T>::min() const {
	DEV_ASSERT(size() > 0);
	T min_val = _ptr[0];
	for (size_t i = 1; i < _len; ++i) {
		if (_ptr[i] < min_val) {
			min_val = _ptr[i];
		}
	}
	return min_val;
}

template <typename T>
constexpr Span<T> Span<T>::subspan(uint64_t p_pos, uint64_t p_len) const {
	DEV_ASSERT(size() >= p_pos);
	DEV_ASSERT(size() - p_pos >= p_len);
	return Span<T>(begin() + p_pos, p_len);
}

template <typename T>
template <typename T_Other>
constexpr int8_t Span<T>::compare(const Span<T_Other> &p_other) const {
	if (size() < p_other.size()) {
		return -1;
	} else if (size() > p_other.size()) {
		return 1;
	}

	for (uint64_t i = 0; i < size(); i++) {
		if constexpr (has_comparison_operators_v<T, T_Other>) {
			if (ptr()[i] < p_other.ptr()[i]) {
				return -1;
			} else if (p_other.ptr()[i] < ptr()[i]) {
				return 1;
			}
		} else {
			if (ptr()[i] != p_other.ptr()[i]) {
				return -1;
			}
		}
	}

	return 0;
}

// Zero-constructing Span initializes _ptr and _len to 0 (and thus empty).
template <typename T>
struct is_zero_constructible<Span<T>> : std::true_type {};
