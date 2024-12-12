/**************************************************************************/
/*  benchmark_spectral_norm.cpp                                           */
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

#include "benchmark_spectral_norm.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"

#define PRINT(...) // FIXME: Needs equivalent implementation.
#else
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define PRINT() UtilityFunctions::print(__VA_ARGS__)

using namespace godot;
#endif // GODOT_MODULE

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void BenchmarkSpectralNorm::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_spectral_norm_100"), &BenchmarkSpectralNorm::benchmark_spectral_norm_100);
	ClassDB::bind_method(D_METHOD("benchmark_spectral_norm_500"), &BenchmarkSpectralNorm::benchmark_spectral_norm_500);
	ClassDB::bind_method(D_METHOD("benchmark_spectral_norm_1000"), &BenchmarkSpectralNorm::benchmark_spectral_norm_1000);
}

double BenchmarkSpectralNorm::eval_a(int i, int j) {
	return 1.0 / ((i + j) * (i + j + 1) / 2 + i + 1);
}

/* multiply vector v by matrix A, each thread evaluate its range only */
void BenchmarkSpectralNorm::multiply_av(double v[], double av[], int n) {
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			sum += eval_a(i, j) * v[j];
		}

		av[i] = sum;
	}
}

/* multiply vector v by matrix A transposed */
void BenchmarkSpectralNorm::multiply_atv(double v[], double atv[], int n) {
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			sum += eval_a(j, i) * v[j];
		}

		atv[i] = sum;
	}
}

/* multiply vector v by matrix A and then by matrix A transposed */
void BenchmarkSpectralNorm::multiply_at_av(double v[], double tmp[], double at_av[], int n) {
	multiply_av(v, tmp, n);
	multiply_atv(tmp, at_av, n);
}

void BenchmarkSpectralNorm::calculate_spectral_norm(int n) {
	double *u = (double *)alloca(sizeof(double) * n);
	double *v = (double *)alloca(sizeof(double) * n);
	double *tmp = (double *)alloca(sizeof(double) * n);

	// create unit vector
	for (int i = 0; i < n; i++) {
		u[i] = 1.0;
	}

	for (int i = 0; i < 10; i++) {
		multiply_at_av(u, v, tmp, n);
		multiply_at_av(v, u, tmp, n);
	}

	double vbv = 0, vv = 0;
	for (int i = 0; i < n; i++) {
		vbv += u[i] * v[i];
		vv += v[i] * v[i];
	}

	double square_root = Math::sqrt(vbv / vv);
	PRINT(square_root);
}

void BenchmarkSpectralNorm::benchmark_spectral_norm_100() {
	calculate_spectral_norm(100);
}

void BenchmarkSpectralNorm::benchmark_spectral_norm_500() {
	calculate_spectral_norm(500);
}

void BenchmarkSpectralNorm::benchmark_spectral_norm_1000() {
	calculate_spectral_norm(1000);
}

BenchmarkSpectralNorm::BenchmarkSpectralNorm() {}

BenchmarkSpectralNorm::~BenchmarkSpectralNorm() {}
