/**************************************************************************/
/*  benchmark_mandelbrot_set.cpp                                          */
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

#include "benchmark_mandelbrot_set.h"

#ifdef GODOT_MODULE
#include "core/io/image.h"
#include "core/object/class_db.h"
#else
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
#endif // GODOT_MODULE

void BenchmarkMandelbrotSet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_mandelbrot_set"), &BenchmarkMandelbrotSet::benchmark_mandelbrot_set);
}

Color BenchmarkMandelbrotSet::hsv(float hue, float sat, float value) {
	hue = Math::fposmod(hue, 360.0f);
	int h = Math::floor(hue) / 60;
	float f = hue / 60.0 - h;
	float p = value * (1.0 - sat);
	float q = value * (1.0 - sat * f);
	float t = value * (1.0 - sat * (1.0 - f));
	if (h == 0 || h == 6) {
		return Color(value, t, p);
	}
	if (h == 1) {
		return Color(q, value, p);
	}
	if (h == 2) {
		return Color(p, value, t);
	}
	if (h == 3) {
		return Color(p, q, value);
	}
	if (h == 4) {
		return Color(t, p, value);
	}
	return Color(value, p, q);
}

void BenchmarkMandelbrotSet::mandelbrot_set(int p_width, int p_height, int p_max_iteration) {
	Ref<Image> image = memnew(Image);
	image = Image::create_empty(p_width, p_height, false, Image::Format::FORMAT_RGB8);
	float ratio = float(p_width) / float(p_height);
	float x_range = 3.6;
	float y_range = x_range / ratio;
	float min_x = -x_range / 2.0;
	float max_y = y_range / 2.0;
	for (int x = 0; x < image->get_width(); x++) {
		for (int y = 0; y < image->get_height(); y++) {
			int iteration = 0;
			float x0 = min_x + x_range * x / p_width;
			float y0 = max_y - y_range * y / p_height;
			float xx = 0.0;
			float yy = 0.0;
			float x2 = 0.0;
			float y2 = 0.0;
			while (x2 + y2 <= 4 && iteration < p_max_iteration) {
				yy = 2 * xx * yy + y0;
				xx = x2 - y2 + x0;
				x2 = xx * xx;
				y2 = yy * yy;
				iteration += 1;
			}
			float m = float(iteration) / float(p_max_iteration);
			Color color = hsv(360.0 * m, 1.0, ceilf(1.0 - 1.1 * m));
			image->set_pixel(x, y, color);
		}
	}
}

void BenchmarkMandelbrotSet::benchmark_mandelbrot_set() {
	mandelbrot_set(width, height, max_iteration);
}

BenchmarkMandelbrotSet::BenchmarkMandelbrotSet() {}

BenchmarkMandelbrotSet::~BenchmarkMandelbrotSet() {}
