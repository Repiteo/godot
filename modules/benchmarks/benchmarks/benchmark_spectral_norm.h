/**************************************************************************/
/*  benchmark_spectral_norm.h                                             */
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

#ifndef BENCHMARK_SPECTRAL_NORM_H
#define BENCHMARK_SPECTRAL_NORM_H

#include "../benchmark.h"

#ifndef GODOT_MODULE
namespace godot {
#endif

#define BenchmarkSpectralNorm BENCHMARK(SpectralNorm)

class BenchmarkSpectralNorm : public Benchmark {
	BENCHMARK_GDCLASS(SpectralNorm)

	double eval_a(int i, int j);
	void multiply_av(double v[], double av[], int n);
	void multiply_atv(double v[], double atv[], int n);
	void multiply_at_av(double v[], double tmp[], double at_av[], int n);
	void calculate_spectral_norm(int input);

protected:
	static void _bind_methods();

public:
	void benchmark_spectral_norm_100();
	void benchmark_spectral_norm_500();
	void benchmark_spectral_norm_1000();

	BenchmarkSpectralNorm();
	~BenchmarkSpectralNorm();
};

#ifndef GODOT_MODULE
} // namespace godot
#endif

#endif // BENCHMARK_SPECTRAL_NORM_H
