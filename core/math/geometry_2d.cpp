/**************************************************************************/
/*  geometry_2d.cpp                                                       */
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

#include "geometry_2d.h"

#include "thirdparty/clipper2/include/clipper2/clipper.h"
#include "thirdparty/misc/polypartition.h"
#define STB_RECT_PACK_IMPLEMENTATION
#include "thirdparty/misc/stb_rect_pack.h"

const int clipper_precision = 5; // Based on CMP_EPSILON.
const double clipper_scale = Math::pow(10.0, clipper_precision);

void Geometry2D::merge_many_polygons(const Vector<Vector<Vector2>> &p_polygons, Vector<Vector<Vector2>> &r_out_polygons, Vector<Vector<Vector2>> &r_out_holes) {
	using namespace Clipper2Lib;

	PathsD subjects;
	for (const Vector<Vector2> &polygon : p_polygons) {
		PathD path(polygon.size());
		for (int i = 0; i < polygon.size(); i++) {
			const Vector2 &point = polygon[i];
			path[i] = PointD(point.x, point.y);
		}
		subjects.push_back(path);
	}

	PathsD solution = Union(subjects, FillRule::NonZero);
	solution = SimplifyPaths(solution, 0.01);

	r_out_polygons.clear();
	r_out_holes.clear();
	for (PathsD::size_type i = 0; i < solution.size(); ++i) {
		PathD &path = solution[i];

		Vector<Point2> output_polygon;
		output_polygon.resize(path.size());
		for (PathsD::size_type j = 0; j < path.size(); ++j) {
			output_polygon.set(j, Vector2(static_cast<real_t>(path[j].x), static_cast<real_t>(path[j].y)));
		}
		if (IsPositive(path)) {
			r_out_polygons.push_back(output_polygon);
		} else {
			r_out_holes.push_back(output_polygon);
		}
	}
}

Vector<Vector<Vector2>> Geometry2D::decompose_many_polygons_in_convex(const Vector<Vector<Point2>> &p_polygons, const Vector<Vector<Point2>> &p_holes) {
	Vector<Vector<Vector2>> decomp;
	List<TPPLPoly> in_poly, out_poly;

	for (const Vector<Vector2> &polygon : p_polygons) {
		TPPLPoly inp;
		inp.Init(polygon.size());
		for (int i = 0; i < polygon.size(); i++) {
			inp.GetPoint(i) = polygon[i];
		}
		inp.SetOrientation(TPPL_ORIENTATION_CCW);
		in_poly.push_back(inp);
	}
	for (const Vector<Vector2> &polygon : p_holes) {
		TPPLPoly inp;
		inp.Init(polygon.size());
		for (int i = 0; i < polygon.size(); i++) {
			inp.GetPoint(i) = polygon[i];
		}
		inp.SetOrientation(TPPL_ORIENTATION_CW);
		inp.SetHole(true);
		in_poly.push_back(inp);
	}
	TPPLPartition tpart;
	if (tpart.ConvexPartition_HM(&in_poly, &out_poly) == 0) { // Failed.
		ERR_PRINT("Convex decomposing failed!");
		return decomp;
	}

	decomp.resize(out_poly.size());
	int idx = 0;
	for (List<TPPLPoly>::Element *I = out_poly.front(); I; I = I->next()) {
		TPPLPoly &tp = I->get();

		decomp.write[idx].resize(tp.GetNumPoints());

		for (int64_t i = 0; i < tp.GetNumPoints(); i++) {
			decomp.write[idx].write[i] = tp.GetPoint(i);
		}

		idx++;
	}

	return decomp;
}

Vector<Vector<Point2>> Geometry2D::_polypaths_do_operation(PolyBooleanOperation p_op, const Vector<Point2> &p_polypath_a, const Vector<Point2> &p_polypath_b, bool is_a_open) {
	using namespace Clipper2Lib;

	ClipType op = ClipType::Union;

	switch (p_op) {
		case OPERATION_UNION:
			op = ClipType::Union;
			break;
		case OPERATION_DIFFERENCE:
			op = ClipType::Difference;
			break;
		case OPERATION_INTERSECTION:
			op = ClipType::Intersection;
			break;
		case OPERATION_XOR:
			op = ClipType::Xor;
			break;
	}

	PathD path_a(p_polypath_a.size());
	for (int i = 0; i != p_polypath_a.size(); ++i) {
		path_a[i] = PointD(p_polypath_a[i].x, p_polypath_a[i].y);
	}
	PathD path_b(p_polypath_b.size());
	for (int i = 0; i != p_polypath_b.size(); ++i) {
		path_b[i] = PointD(p_polypath_b[i].x, p_polypath_b[i].y);
	}

	ClipperD clp(clipper_precision); // Scale points up internally to attain the desired precision.
	clp.PreserveCollinear(false); // Remove redundant vertices.
	if (is_a_open) {
		clp.AddOpenSubject({ path_a });
	} else {
		clp.AddSubject({ path_a });
	}
	clp.AddClip({ path_b });

	PathsD paths;

	if (is_a_open) {
		PolyTreeD tree; // Needed to populate polylines.
		clp.Execute(op, FillRule::EvenOdd, tree, paths);
	} else {
		clp.Execute(op, FillRule::EvenOdd, paths); // Works on closed polygons only.
	}

	Vector<Vector<Point2>> polypaths;
	for (PathsD::size_type i = 0; i < paths.size(); ++i) {
		const PathD &path = paths[i];

		Vector<Vector2> polypath;
		for (PathsD::size_type j = 0; j < path.size(); ++j) {
			polypath.push_back(Point2(static_cast<real_t>(path[j].x), static_cast<real_t>(path[j].y)));
		}
		polypaths.push_back(polypath);
	}
	return polypaths;
}

Vector<Vector<Point2>> Geometry2D::_polypath_offset(const Vector<Point2> &p_polypath, real_t p_delta, PolyJoinType p_join_type, PolyEndType p_end_type) {
	using namespace Clipper2Lib;

	JoinType jt = JoinType::Square;

	switch (p_join_type) {
		case JOIN_SQUARE:
			jt = JoinType::Square;
			break;
		case JOIN_ROUND:
			jt = JoinType::Round;
			break;
		case JOIN_MITER:
			jt = JoinType::Miter;
			break;
	}

	EndType et = EndType::Polygon;

	switch (p_end_type) {
		case END_POLYGON:
			et = EndType::Polygon;
			break;
		case END_JOINED:
			et = EndType::Joined;
			break;
		case END_BUTT:
			et = EndType::Butt;
			break;
		case END_SQUARE:
			et = EndType::Square;
			break;
		case END_ROUND:
			et = EndType::Round;
			break;
	}

	PathD polypath(p_polypath.size());
	for (int i = 0; i != p_polypath.size(); ++i) {
		polypath[i] = PointD(p_polypath[i].x, p_polypath[i].y);
	}

	// Inflate/deflate.
	PathsD paths = InflatePaths({ polypath }, p_delta, jt, et, 2.0, clipper_precision, 0.25 * clipper_scale);
	// Here the points are scaled up internally and
	// the arc_tolerance is scaled accordingly
	// to attain the desired precision.

	Vector<Vector<Point2>> polypaths;
	for (PathsD::size_type i = 0; i < paths.size(); ++i) {
		const PathD &path = paths[i];

		Vector<Vector2> polypath2;
		for (PathsD::size_type j = 0; j < path.size(); ++j) {
			polypath2.push_back(Point2(static_cast<real_t>(path[j].x), static_cast<real_t>(path[j].y)));
		}
		polypaths.push_back(polypath2);
	}
	return polypaths;
}

Vector<Vector3i> Geometry2D::partial_pack_rects(const Vector<Vector2i> &p_sizes, const Size2i &p_atlas_size) {
	Vector<stbrp_node> nodes;
	nodes.resize(p_atlas_size.width);
	memset(nodes.ptrw(), 0, sizeof(stbrp_node) * nodes.size());

	stbrp_context context;
	stbrp_init_target(&context, p_atlas_size.width, p_atlas_size.height, nodes.ptrw(), p_atlas_size.width);

	Vector<stbrp_rect> rects;
	rects.resize(p_sizes.size());

	for (int i = 0; i < p_sizes.size(); i++) {
		rects.write[i].id = i;
		rects.write[i].w = p_sizes[i].width;
		rects.write[i].h = p_sizes[i].height;
		rects.write[i].x = 0;
		rects.write[i].y = 0;
		rects.write[i].was_packed = 0;
	}

	stbrp_pack_rects(&context, rects.ptrw(), rects.size());

	Vector<Vector3i> ret;
	ret.resize(p_sizes.size());

	for (int i = 0; i < p_sizes.size(); i++) {
		ret.write[rects[i].id] = Vector3i(rects[i].x, rects[i].y, rects[i].was_packed != 0 ? 1 : 0);
	}

	return ret;
}
