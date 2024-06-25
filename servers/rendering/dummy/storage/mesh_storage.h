/**************************************************************************/
/*  mesh_storage.h                                                        */
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

#ifndef MESH_STORAGE_DUMMY_H
#define MESH_STORAGE_DUMMY_H

#include "core/templates/local_vector.h"
#include "core/templates/rid_owner.h"
#include "servers/rendering/storage/mesh_storage.h"

namespace RendererDummy {

class MeshStorage : public RendererMeshStorage {
private:
	static MeshStorage *singleton;

	struct DummyMesh {
		Vector<RS::SurfaceData> surfaces;
		int blend_shape_count;
		RS::BlendShapeMode blend_shape_mode;
		PackedFloat32Array blend_shape_values;
	};

	mutable RID_Owner<DummyMesh> mesh_owner;

	struct DummyMultiMesh {
		PackedFloat32Array buffer;
	};

	mutable RID_Owner<DummyMultiMesh> multimesh_owner;

public:
	static MeshStorage *get_singleton() { return singleton; }

	MeshStorage();
	~MeshStorage() override;

	/* MESH API */

	bool owns_mesh(RID p_rid) { return mesh_owner.owns(p_rid); };

	RID mesh_allocate() override;
	void mesh_initialize(RID p_rid) override;
	void mesh_free(RID p_rid) override;

	void mesh_set_blend_shape_count(RID p_mesh, int p_blend_shape_count) override {}
	bool mesh_needs_instance(RID p_mesh, bool p_has_skeleton) override { return false; }

	void mesh_add_surface(RID p_mesh, const RS::SurfaceData &p_surface) override {
		DummyMesh *m = mesh_owner.get_or_null(p_mesh);
		ERR_FAIL_NULL(m);
		m->surfaces.push_back(RS::SurfaceData());
		RS::SurfaceData *s = &m->surfaces.write[m->surfaces.size() - 1];
		s->format = p_surface.format;
		s->primitive = p_surface.primitive;
		s->vertex_data = p_surface.vertex_data;
		s->attribute_data = p_surface.attribute_data;
		s->vertex_count = p_surface.vertex_count;
		s->index_data = p_surface.index_data;
		s->index_count = p_surface.index_count;
		s->aabb = p_surface.aabb;
		s->skin_data = p_surface.skin_data;
		s->lods = p_surface.lods;
		s->bone_aabbs = p_surface.bone_aabbs;
		s->mesh_to_skeleton_xform = p_surface.mesh_to_skeleton_xform;
		s->blend_shape_data = p_surface.blend_shape_data;
		s->uv_scale = p_surface.uv_scale;
		s->material = p_surface.material;
	}

	int mesh_get_blend_shape_count(RID p_mesh) const override { return 0; }

	void mesh_set_blend_shape_mode(RID p_mesh, RS::BlendShapeMode p_mode) override {}
	RS::BlendShapeMode mesh_get_blend_shape_mode(RID p_mesh) const override { return RS::BLEND_SHAPE_MODE_NORMALIZED; }

	void mesh_surface_update_vertex_region(RID p_mesh, int p_surface, int p_offset, const Vector<uint8_t> &p_data) override {}
	void mesh_surface_update_attribute_region(RID p_mesh, int p_surface, int p_offset, const Vector<uint8_t> &p_data) override {}
	void mesh_surface_update_skin_region(RID p_mesh, int p_surface, int p_offset, const Vector<uint8_t> &p_data) override {}

	void mesh_surface_set_material(RID p_mesh, int p_surface, RID p_material) override {}
	RID mesh_surface_get_material(RID p_mesh, int p_surface) const override { return RID(); }

	RS::SurfaceData mesh_get_surface(RID p_mesh, int p_surface) const override {
		DummyMesh *m = mesh_owner.get_or_null(p_mesh);
		ERR_FAIL_NULL_V(m, RS::SurfaceData());
		ERR_FAIL_INDEX_V(p_surface, m->surfaces.size(), RS::SurfaceData());
		RS::SurfaceData s = m->surfaces[p_surface];
		return s;
	}

	int mesh_get_surface_count(RID p_mesh) const override {
		DummyMesh *m = mesh_owner.get_or_null(p_mesh);
		ERR_FAIL_NULL_V(m, 0);
		return m->surfaces.size();
	}

	void mesh_set_custom_aabb(RID p_mesh, const AABB &p_aabb) override {}
	AABB mesh_get_custom_aabb(RID p_mesh) const override { return AABB(); }
	AABB mesh_get_aabb(RID p_mesh, RID p_skeleton = RID()) override { return AABB(); }

	void mesh_set_path(RID p_mesh, const String &p_path) override {}
	String mesh_get_path(RID p_mesh) const override { return String(); }

	void mesh_set_shadow_mesh(RID p_mesh, RID p_shadow_mesh) override {}
	void mesh_clear(RID p_mesh) override;

	/* MESH INSTANCE */

	RID mesh_instance_create(RID p_base) override { return RID(); }
	void mesh_instance_free(RID p_rid) override {}

	void mesh_instance_set_skeleton(RID p_mesh_instance, RID p_skeleton) override {}
	void mesh_instance_set_blend_shape_weight(RID p_mesh_instance, int p_shape, float p_weight) override {}
	void mesh_instance_check_for_update(RID p_mesh_instance) override {}
	void mesh_instance_set_canvas_item_transform(RID p_mesh_instance, const Transform2D &p_transform) override {}
	void update_mesh_instances() override {}

	/* MULTIMESH API */

	bool owns_multimesh(RID p_rid) { return multimesh_owner.owns(p_rid); }

	RID multimesh_allocate() override;
	void multimesh_initialize(RID p_rid) override;
	void multimesh_free(RID p_rid) override;

	void multimesh_allocate_data(RID p_multimesh, int p_instances, RS::MultimeshTransformFormat p_transform_format, bool p_use_colors = false, bool p_use_custom_data = false) override {}
	int multimesh_get_instance_count(RID p_multimesh) const override { return 0; }

	void multimesh_set_mesh(RID p_multimesh, RID p_mesh) override {}
	void multimesh_instance_set_transform(RID p_multimesh, int p_index, const Transform3D &p_transform) override {}
	void multimesh_instance_set_transform_2d(RID p_multimesh, int p_index, const Transform2D &p_transform) override {}
	void multimesh_instance_set_color(RID p_multimesh, int p_index, const Color &p_color) override {}
	void multimesh_instance_set_custom_data(RID p_multimesh, int p_index, const Color &p_color) override {}

	void multimesh_set_custom_aabb(RID p_multimesh, const AABB &p_aabb) override {}
	AABB multimesh_get_custom_aabb(RID p_multimesh) const override { return AABB(); }

	RID multimesh_get_mesh(RID p_multimesh) const override { return RID(); }
	AABB multimesh_get_aabb(RID p_multimesh) const override { return AABB(); }

	Transform3D multimesh_instance_get_transform(RID p_multimesh, int p_index) const override { return Transform3D(); }
	Transform2D multimesh_instance_get_transform_2d(RID p_multimesh, int p_index) const override { return Transform2D(); }
	Color multimesh_instance_get_color(RID p_multimesh, int p_index) const override { return Color(); }
	Color multimesh_instance_get_custom_data(RID p_multimesh, int p_index) const override { return Color(); }
	void multimesh_set_buffer(RID p_multimesh, const Vector<float> &p_buffer) override;
	Vector<float> multimesh_get_buffer(RID p_multimesh) const override;

	void multimesh_set_visible_instances(RID p_multimesh, int p_visible) override {}
	int multimesh_get_visible_instances(RID p_multimesh) const override { return 0; }

	/* SKELETON API */

	RID skeleton_allocate() override { return RID(); }
	void skeleton_initialize(RID p_rid) override {}
	void skeleton_free(RID p_rid) override {}
	void skeleton_allocate_data(RID p_skeleton, int p_bones, bool p_2d_skeleton = false) override {}
	void skeleton_set_base_transform_2d(RID p_skeleton, const Transform2D &p_base_transform) override {}
	int skeleton_get_bone_count(RID p_skeleton) const override { return 0; }
	void skeleton_bone_set_transform(RID p_skeleton, int p_bone, const Transform3D &p_transform) override {}
	Transform3D skeleton_bone_get_transform(RID p_skeleton, int p_bone) const override { return Transform3D(); }
	void skeleton_bone_set_transform_2d(RID p_skeleton, int p_bone, const Transform2D &p_transform) override {}
	Transform2D skeleton_bone_get_transform_2d(RID p_skeleton, int p_bone) const override { return Transform2D(); }

	void skeleton_update_dependency(RID p_base, DependencyTracker *p_instance) override {}

	/* OCCLUDER */

	void occluder_set_mesh(RID p_occluder, const PackedVector3Array &p_vertices, const PackedInt32Array &p_indices) {}
};

} // namespace RendererDummy

#endif // MESH_STORAGE_DUMMY_H
