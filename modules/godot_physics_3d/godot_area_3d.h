/**************************************************************************/
/*  godot_area_3d.h                                                       */
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

#include "godot_collision_object_3d.h"

#include "core/templates/self_list.h"
#include "servers/physics_server_3d.h"

class GodotSpace3D;
class GodotBody3D;
class GodotSoftBody3D;
class GodotConstraint3D;

class GodotArea3D : public GodotCollisionObject3D {
	PhysicsServer3D::AreaSpaceOverrideMode gravity_override_mode = PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED;
	PhysicsServer3D::AreaSpaceOverrideMode linear_damping_override_mode = PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED;
	PhysicsServer3D::AreaSpaceOverrideMode angular_damping_override_mode = PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED;

	real_t gravity = 9.80665;
	Vector3 gravity_vector = Vector3(0, -1, 0);
	bool gravity_is_point = false;
	real_t gravity_point_unit_distance = 0.0;
	real_t linear_damp = 0.1;
	real_t angular_damp = 0.1;
	real_t wind_force_magnitude = 0.0;
	real_t wind_attenuation_factor = 0.0;
	Vector3 wind_source;
	Vector3 wind_direction;
	int priority = 0;
	bool monitorable = false;

	Callable monitor_callback;
	Callable area_monitor_callback;

	SelfList<GodotArea3D> monitor_query_list;
	SelfList<GodotArea3D> moved_list;

	struct BodyKey {
		RID rid;
		ObjectID instance_id;
		uint32_t body_shape = 0;
		uint32_t area_shape = 0;

		static uint32_t hash(const BodyKey &p_key) {
			uint32_t h = hash_one_uint64(p_key.rid.get_id());
			h = hash_murmur3_one_64(p_key.instance_id, h);
			h = hash_murmur3_one_32(p_key.area_shape, h);
			return hash_fmix32(hash_murmur3_one_32(p_key.body_shape, h));
		}

		GD_FORCE_INLINE bool operator==(const BodyKey &p_key) const {
			return rid == p_key.rid && instance_id == p_key.instance_id && body_shape == p_key.body_shape && area_shape == p_key.area_shape;
		}

		GD_FORCE_INLINE BodyKey() {}
		BodyKey(GodotSoftBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape);
		BodyKey(GodotBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape);
		BodyKey(GodotArea3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape);
	};

	struct BodyState {
		int state = 0;
		GD_FORCE_INLINE void inc() { state++; }
		GD_FORCE_INLINE void dec() { state--; }
	};

	HashMap<BodyKey, BodyState, BodyKey> monitored_soft_bodies;
	HashMap<BodyKey, BodyState, BodyKey> monitored_bodies;
	HashMap<BodyKey, BodyState, BodyKey> monitored_areas;

	HashSet<GodotConstraint3D *> constraints;

	virtual void _shapes_changed() override;
	void _queue_monitor_update();

	void _set_space_override_mode(PhysicsServer3D::AreaSpaceOverrideMode &r_mode, PhysicsServer3D::AreaSpaceOverrideMode p_new_mode);

public:
	void set_monitor_callback(const Callable &p_callback);
	GD_FORCE_INLINE bool has_monitor_callback() const { return monitor_callback.is_valid(); }

	void set_area_monitor_callback(const Callable &p_callback);
	GD_FORCE_INLINE bool has_area_monitor_callback() const { return area_monitor_callback.is_valid(); }

	GD_FORCE_INLINE void add_body_to_query(GodotBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape);
	GD_FORCE_INLINE void remove_body_from_query(GodotBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape);

	GD_FORCE_INLINE void add_soft_body_to_query(GodotSoftBody3D *p_soft_body, uint32_t p_soft_body_shape, uint32_t p_area_shape);
	GD_FORCE_INLINE void remove_soft_body_from_query(GodotSoftBody3D *p_soft_body, uint32_t p_soft_body_shape, uint32_t p_area_shape);

	GD_FORCE_INLINE void add_area_to_query(GodotArea3D *p_area, uint32_t p_area_shape, uint32_t p_self_shape);
	GD_FORCE_INLINE void remove_area_from_query(GodotArea3D *p_area, uint32_t p_area_shape, uint32_t p_self_shape);

	void set_param(PhysicsServer3D::AreaParameter p_param, const Variant &p_value);
	Variant get_param(PhysicsServer3D::AreaParameter p_param) const;

	GD_FORCE_INLINE void set_gravity(real_t p_gravity) { gravity = p_gravity; }
	GD_FORCE_INLINE real_t get_gravity() const { return gravity; }

	GD_FORCE_INLINE void set_gravity_vector(const Vector3 &p_gravity) { gravity_vector = p_gravity; }
	GD_FORCE_INLINE Vector3 get_gravity_vector() const { return gravity_vector; }

	GD_FORCE_INLINE void set_gravity_as_point(bool p_enable) { gravity_is_point = p_enable; }
	GD_FORCE_INLINE bool is_gravity_point() const { return gravity_is_point; }

	GD_FORCE_INLINE void set_gravity_point_unit_distance(real_t scale) { gravity_point_unit_distance = scale; }
	GD_FORCE_INLINE real_t get_gravity_point_unit_distance() const { return gravity_point_unit_distance; }

	GD_FORCE_INLINE void set_linear_damp(real_t p_linear_damp) { linear_damp = p_linear_damp; }
	GD_FORCE_INLINE real_t get_linear_damp() const { return linear_damp; }

	GD_FORCE_INLINE void set_angular_damp(real_t p_angular_damp) { angular_damp = p_angular_damp; }
	GD_FORCE_INLINE real_t get_angular_damp() const { return angular_damp; }

	GD_FORCE_INLINE void set_priority(int p_priority) { priority = p_priority; }
	GD_FORCE_INLINE int get_priority() const { return priority; }

	GD_FORCE_INLINE void set_wind_force_magnitude(real_t p_wind_force_magnitude) { wind_force_magnitude = p_wind_force_magnitude; }
	GD_FORCE_INLINE real_t get_wind_force_magnitude() const { return wind_force_magnitude; }

	GD_FORCE_INLINE void set_wind_attenuation_factor(real_t p_wind_attenuation_factor) { wind_attenuation_factor = p_wind_attenuation_factor; }
	GD_FORCE_INLINE real_t get_wind_attenuation_factor() const { return wind_attenuation_factor; }

	GD_FORCE_INLINE void set_wind_source(const Vector3 &p_wind_source) { wind_source = p_wind_source; }
	GD_FORCE_INLINE const Vector3 &get_wind_source() const { return wind_source; }

	GD_FORCE_INLINE void set_wind_direction(const Vector3 &p_wind_direction) { wind_direction = p_wind_direction; }
	GD_FORCE_INLINE const Vector3 &get_wind_direction() const { return wind_direction; }

	GD_FORCE_INLINE void add_constraint(GodotConstraint3D *p_constraint) { constraints.insert(p_constraint); }
	GD_FORCE_INLINE void remove_constraint(GodotConstraint3D *p_constraint) { constraints.erase(p_constraint); }
	GD_FORCE_INLINE const HashSet<GodotConstraint3D *> &get_constraints() const { return constraints; }
	GD_FORCE_INLINE void clear_constraints() { constraints.clear(); }

	void set_monitorable(bool p_monitorable);
	GD_FORCE_INLINE bool is_monitorable() const { return monitorable; }

	void set_transform(const Transform3D &p_transform);

	void set_space(GodotSpace3D *p_space) override;

	void call_queries();

	void compute_gravity(const Vector3 &p_position, Vector3 &r_gravity) const;

	GodotArea3D();
	~GodotArea3D();
};

void GodotArea3D::add_soft_body_to_query(GodotSoftBody3D *p_soft_body, uint32_t p_soft_body_shape, uint32_t p_area_shape) {
	BodyKey bk(p_soft_body, p_soft_body_shape, p_area_shape);
	monitored_soft_bodies[bk].inc();
	if (!monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

void GodotArea3D::remove_soft_body_from_query(GodotSoftBody3D *p_soft_body, uint32_t p_soft_body_shape, uint32_t p_area_shape) {
	BodyKey bk(p_soft_body, p_soft_body_shape, p_area_shape);
	monitored_soft_bodies[bk].dec();
	if (get_space() && !monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

void GodotArea3D::add_body_to_query(GodotBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape) {
	BodyKey bk(p_body, p_body_shape, p_area_shape);
	monitored_bodies[bk].inc();
	if (!monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

void GodotArea3D::remove_body_from_query(GodotBody3D *p_body, uint32_t p_body_shape, uint32_t p_area_shape) {
	BodyKey bk(p_body, p_body_shape, p_area_shape);
	monitored_bodies[bk].dec();
	if (get_space() && !monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

void GodotArea3D::add_area_to_query(GodotArea3D *p_area, uint32_t p_area_shape, uint32_t p_self_shape) {
	BodyKey bk(p_area, p_area_shape, p_self_shape);
	monitored_areas[bk].inc();
	if (!monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

void GodotArea3D::remove_area_from_query(GodotArea3D *p_area, uint32_t p_area_shape, uint32_t p_self_shape) {
	BodyKey bk(p_area, p_area_shape, p_self_shape);
	monitored_areas[bk].dec();
	if (get_space() && !monitor_query_list.in_list()) {
		_queue_monitor_update();
	}
}

struct AreaCMP {
	GodotArea3D *area = nullptr;
	int refCount = 0;
	GD_FORCE_INLINE bool operator==(const AreaCMP &p_cmp) const { return area->get_self() == p_cmp.area->get_self(); }
	GD_FORCE_INLINE bool operator<(const AreaCMP &p_cmp) const { return area->get_priority() < p_cmp.area->get_priority(); }
	GD_FORCE_INLINE AreaCMP() {}
	GD_FORCE_INLINE AreaCMP(GodotArea3D *p_area) {
		area = p_area;
		refCount = 1;
	}
};
