/**************************************************************************/
/*  benchmark_string_checksum.cpp                                         */
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

#include "benchmark_string_checksum.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#else
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

void BenchmarkStringChecksum::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_md5_buffer_empty"), &BenchmarkStringChecksum::benchmark_md5_buffer_empty);
	ClassDB::bind_method(D_METHOD("benchmark_md5_buffer_non_empty"), &BenchmarkStringChecksum::benchmark_md5_buffer_non_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha1_buffer_empty"), &BenchmarkStringChecksum::benchmark_sha1_buffer_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha1_buffer_non_empty"), &BenchmarkStringChecksum::benchmark_sha1_buffer_non_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha256_buffer_empty"), &BenchmarkStringChecksum::benchmark_sha256_buffer_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha256_buffer_non_empty"), &BenchmarkStringChecksum::benchmark_sha256_buffer_non_empty);
	ClassDB::bind_method(D_METHOD("benchmark_md5_text_empty"), &BenchmarkStringChecksum::benchmark_md5_text_empty);
	ClassDB::bind_method(D_METHOD("benchmark_md5_text_non_empty"), &BenchmarkStringChecksum::benchmark_md5_text_non_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha1_text_empty"), &BenchmarkStringChecksum::benchmark_sha1_text_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha1_text_non_empty"), &BenchmarkStringChecksum::benchmark_sha1_text_non_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha256_text_empty"), &BenchmarkStringChecksum::benchmark_sha256_text_empty);
	ClassDB::bind_method(D_METHOD("benchmark_sha256_text_non_empty"), &BenchmarkStringChecksum::benchmark_sha256_text_non_empty);
}

void BenchmarkStringChecksum::benchmark_md5_buffer_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").md5_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_md5_buffer_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.md5_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_sha1_buffer_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").sha1_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_sha1_buffer_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.sha1_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_sha256_buffer_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").sha256_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_sha256_buffer_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.sha256_buffer();
	}
}

void BenchmarkStringChecksum::benchmark_md5_text_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").md5_text();
	}
}

void BenchmarkStringChecksum::benchmark_md5_text_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.md5_text();
	}
}

void BenchmarkStringChecksum::benchmark_sha1_text_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").sha1_text();
	}
}

void BenchmarkStringChecksum::benchmark_sha1_text_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.sha1_text();
	}
}

void BenchmarkStringChecksum::benchmark_sha256_text_empty() {
	for (int i = 0; i < iterations; i++) {
		String("").sha256_text();
	}
}

void BenchmarkStringChecksum::benchmark_sha256_text_non_empty() {
	for (int i = 0; i < iterations; i++) {
		LOREM_IPSUM.sha256_text();
	}
}

BenchmarkStringChecksum::BenchmarkStringChecksum() {}

BenchmarkStringChecksum::~BenchmarkStringChecksum() {}
