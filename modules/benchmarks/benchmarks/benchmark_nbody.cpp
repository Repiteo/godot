/**************************************************************************/
/*  benchmark_nbody.cpp                                                   */
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

#include "benchmark_nbody.h"

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
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void BenchmarkNbody::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_nbody_500_000"), &BenchmarkNbody::benchmark_nbody_500_000);
	ClassDB::bind_method(D_METHOD("benchmark_nbody_1_000_000"), &BenchmarkNbody::benchmark_nbody_1_000_000);
}

void BenchmarkNbody::offset_momentum() {
	double px = 0, py = 0, pz = 0;
	for (int i = 0; i < body_count; i++) {
		Body b = bodies[i];
		px -= b.vx * b.mass;
		py -= b.vy * b.mass;
		pz -= b.vz * b.mass;
	}
	Body sol = bodies[0];
	bodies[0].vx = px / Solarmass;
	bodies[0].vy = py / Solarmass;
	bodies[0].vz = pz / Solarmass;
}

void BenchmarkNbody::advance(double dt) {
	for (int i = 0; i < body_count; i++) {
		double x = bodies[i].x;
		double y = bodies[i].y;
		double z = bodies[i].z;
		double vx = bodies[i].vx;
		double vy = bodies[i].vy;
		double vz = bodies[i].vz;
		double mi = bodies[i].mass;
		for (int j = i + 1; j < body_count; j++) {
			double dx = x - bodies[j].x;
			double dy = y - bodies[j].y;
			double dz = z - bodies[j].z;
			double d2 = dx * dx + dy * dy + dz * dz;
			double mag = dt / (d2 * Math::sqrt(d2));
			double bj_m_mag = bodies[j].mass * mag;
			vx -= dx * bj_m_mag;
			vy -= dy * bj_m_mag;
			vz -= dz * bj_m_mag;

			double bi_m_mag = mi * mag;
			bodies[j].vx += dx * bi_m_mag;
			bodies[j].vy += dy * bi_m_mag;
			bodies[j].vz += dz * bi_m_mag;
		}
		bodies[i].vx = vx;
		bodies[i].vy = vy;
		bodies[i].vz = vz;

		bodies[i].x += vx * dt;
		bodies[i].y += vy * dt;
		bodies[i].z += vz * dt;
	}
}

double BenchmarkNbody::energy() {
	double e = 0.0;
	for (int i = 0; i < body_count; i++) {
		e += 0.5 * bodies[i].mass * (bodies[i].vx * bodies[i].vx + bodies[i].vy * bodies[i].vy + bodies[i].vz * bodies[i].vz);
		for (int j = i + 1; j < body_count; j++) {
			double dx = bodies[i].x - bodies[j].x, dy = bodies[i].y - bodies[j].y, dz = bodies[i].z - bodies[j].z;
			e -= (bodies[i].mass * bodies[j].mass) / Math::sqrt(dx * dx + dy * dy + dz * dz);
		}
	}
	return e;
}

void BenchmarkNbody::calculate_nbody(int n) {
	offset_momentum();
	PRINT(energy());
	for (int i = 0; i < n; i++) {
		advance(0.01);
	}
	PRINT(energy());
}

void BenchmarkNbody::benchmark_nbody_500_000() {
	calculate_nbody(500000);
}

void BenchmarkNbody::benchmark_nbody_1_000_000() {
	calculate_nbody(1000000);
}

BenchmarkNbody::BenchmarkNbody() {}

BenchmarkNbody::~BenchmarkNbody() {}
