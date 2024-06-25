/**************************************************************************/
/*  godot_physics_server_2d.h                                             */
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

#ifndef GODOT_PHYSICS_SERVER_2D_H
#define GODOT_PHYSICS_SERVER_2D_H

#include "godot_joints_2d.h"
#include "godot_shape_2d.h"
#include "godot_space_2d.h"
#include "godot_step_2d.h"

#include "core/templates/rid_owner.h"
#include "servers/physics_server_2d.h"

class GodotPhysicsServer2D : public PhysicsServer2D {
	GDCLASS(GodotPhysicsServer2D, PhysicsServer2D);

	friend class GodotPhysicsDirectSpaceState2D;
	friend class GodotPhysicsDirectBodyState2D;
	bool active = true;
	bool doing_sync = false;

	int island_count = 0;
	int active_objects = 0;
	int collision_pairs = 0;

	bool using_threads = false;

	bool flushing_queries = false;

	GodotStep2D *stepper = nullptr;
	HashSet<const GodotSpace2D *> active_spaces;

	mutable RID_PtrOwner<GodotShape2D, true> shape_owner;
	mutable RID_PtrOwner<GodotSpace2D, true> space_owner;
	mutable RID_PtrOwner<GodotArea2D, true> area_owner;
	mutable RID_PtrOwner<GodotBody2D, true> body_owner;
	mutable RID_PtrOwner<GodotJoint2D, true> joint_owner;

	static GodotPhysicsServer2D *godot_singleton;

	friend class GodotCollisionObject2D;
	SelfList<GodotCollisionObject2D>::List pending_shape_update_list;
	void _update_shapes();

	RID _shape_create(ShapeType p_shape);

public:
	struct CollCbkData {
		Vector2 valid_dir;
		real_t valid_depth = 0.0;
		int max = 0;
		int amount = 0;
		int passed = 0;
		int invalid_by_dir = 0;
		Vector2 *ptr = nullptr;
	};

	RID world_boundary_shape_create() override;
	RID separation_ray_shape_create() override;
	RID segment_shape_create() override;
	RID circle_shape_create() override;
	RID rectangle_shape_create() override;
	RID capsule_shape_create() override;
	RID convex_polygon_shape_create() override;
	RID concave_polygon_shape_create() override;

	static void _shape_col_cbk(const Vector2 &p_point_A, const Vector2 &p_point_B, void *p_userdata);

	void shape_set_data(RID p_shape, const Variant &p_data) override;
	void shape_set_custom_solver_bias(RID p_shape, real_t p_bias) override;

	ShapeType shape_get_type(RID p_shape) const override;
	Variant shape_get_data(RID p_shape) const override;
	real_t shape_get_custom_solver_bias(RID p_shape) const override;

	bool shape_collide(RID p_shape_A, const Transform2D &p_xform_A, const Vector2 &p_motion_A, RID p_shape_B, const Transform2D &p_xform_B, const Vector2 &p_motion_B, Vector2 *r_results, int p_result_max, int &r_result_count) override;

	/* SPACE API */

	RID space_create() override;
	void space_set_active(RID p_space, bool p_active) override;
	bool space_is_active(RID p_space) const override;

	void space_set_param(RID p_space, SpaceParameter p_param, real_t p_value) override;
	real_t space_get_param(RID p_space, SpaceParameter p_param) const override;

	void space_set_debug_contacts(RID p_space, int p_max_contacts) override;
	Vector<Vector2> space_get_contacts(RID p_space) const override;
	int space_get_contact_count(RID p_space) const override;

	// this function only works on physics process, errors and returns null otherwise
	PhysicsDirectSpaceState2D *space_get_direct_state(RID p_space) override;

	/* AREA API */

	RID area_create() override;

	void area_set_space(RID p_area, RID p_space) override;
	RID area_get_space(RID p_area) const override;

	void area_add_shape(RID p_area, RID p_shape, const Transform2D &p_transform = Transform2D(), bool p_disabled = false) override;
	void area_set_shape(RID p_area, int p_shape_idx, RID p_shape) override;
	void area_set_shape_transform(RID p_area, int p_shape_idx, const Transform2D &p_transform) override;

	int area_get_shape_count(RID p_area) const override;
	RID area_get_shape(RID p_area, int p_shape_idx) const override;
	Transform2D area_get_shape_transform(RID p_area, int p_shape_idx) const override;

	void area_set_shape_disabled(RID p_area, int p_shape, bool p_disabled) override;

	void area_remove_shape(RID p_area, int p_shape_idx) override;
	void area_clear_shapes(RID p_area) override;

	void area_attach_object_instance_id(RID p_area, ObjectID p_id) override;
	ObjectID area_get_object_instance_id(RID p_area) const override;

	void area_attach_canvas_instance_id(RID p_area, ObjectID p_id) override;
	ObjectID area_get_canvas_instance_id(RID p_area) const override;

	void area_set_param(RID p_area, AreaParameter p_param, const Variant &p_value) override;
	void area_set_transform(RID p_area, const Transform2D &p_transform) override;

	Variant area_get_param(RID p_area, AreaParameter p_param) const override;
	Transform2D area_get_transform(RID p_area) const override;
	void area_set_monitorable(RID p_area, bool p_monitorable) override;

	void area_set_collision_layer(RID p_area, uint32_t p_layer) override;
	uint32_t area_get_collision_layer(RID p_area) const override;

	void area_set_collision_mask(RID p_area, uint32_t p_mask) override;
	uint32_t area_get_collision_mask(RID p_area) const override;

	void area_set_monitor_callback(RID p_area, const Callable &p_callback) override;
	void area_set_area_monitor_callback(RID p_area, const Callable &p_callback) override;

	void area_set_pickable(RID p_area, bool p_pickable) override;

	/* BODY API */

	// create a body of a given type
	RID body_create() override;

	void body_set_space(RID p_body, RID p_space) override;
	RID body_get_space(RID p_body) const override;

	void body_set_mode(RID p_body, BodyMode p_mode) override;
	BodyMode body_get_mode(RID p_body) const override;

	void body_add_shape(RID p_body, RID p_shape, const Transform2D &p_transform = Transform2D(), bool p_disabled = false) override;
	void body_set_shape(RID p_body, int p_shape_idx, RID p_shape) override;
	void body_set_shape_transform(RID p_body, int p_shape_idx, const Transform2D &p_transform) override;

	int body_get_shape_count(RID p_body) const override;
	RID body_get_shape(RID p_body, int p_shape_idx) const override;
	Transform2D body_get_shape_transform(RID p_body, int p_shape_idx) const override;

	void body_remove_shape(RID p_body, int p_shape_idx) override;
	void body_clear_shapes(RID p_body) override;

	void body_set_shape_disabled(RID p_body, int p_shape_idx, bool p_disabled) override;
	void body_set_shape_as_one_way_collision(RID p_body, int p_shape_idx, bool p_enable, real_t p_margin) override;

	void body_attach_object_instance_id(RID p_body, ObjectID p_id) override;
	ObjectID body_get_object_instance_id(RID p_body) const override;

	void body_attach_canvas_instance_id(RID p_body, ObjectID p_id) override;
	ObjectID body_get_canvas_instance_id(RID p_body) const override;

	void body_set_continuous_collision_detection_mode(RID p_body, CCDMode p_mode) override;
	CCDMode body_get_continuous_collision_detection_mode(RID p_body) const override;

	void body_set_collision_layer(RID p_body, uint32_t p_layer) override;
	uint32_t body_get_collision_layer(RID p_body) const override;

	void body_set_collision_mask(RID p_body, uint32_t p_mask) override;
	uint32_t body_get_collision_mask(RID p_body) const override;

	void body_set_collision_priority(RID p_body, real_t p_priority) override;
	real_t body_get_collision_priority(RID p_body) const override;

	void body_set_param(RID p_body, BodyParameter p_param, const Variant &p_value) override;
	Variant body_get_param(RID p_body, BodyParameter p_param) const override;

	void body_reset_mass_properties(RID p_body) override;

	void body_set_state(RID p_body, BodyState p_state, const Variant &p_variant) override;
	Variant body_get_state(RID p_body, BodyState p_state) const override;

	void body_apply_central_impulse(RID p_body, const Vector2 &p_impulse) override;
	void body_apply_torque_impulse(RID p_body, real_t p_torque) override;
	void body_apply_impulse(RID p_body, const Vector2 &p_impulse, const Vector2 &p_position = Vector2()) override;

	void body_apply_central_force(RID p_body, const Vector2 &p_force) override;
	void body_apply_force(RID p_body, const Vector2 &p_force, const Vector2 &p_position = Vector2()) override;
	void body_apply_torque(RID p_body, real_t p_torque) override;

	void body_add_constant_central_force(RID p_body, const Vector2 &p_force) override;
	void body_add_constant_force(RID p_body, const Vector2 &p_force, const Vector2 &p_position = Vector2()) override;
	void body_add_constant_torque(RID p_body, real_t p_torque) override;

	void body_set_constant_force(RID p_body, const Vector2 &p_force) override;
	Vector2 body_get_constant_force(RID p_body) const override;

	void body_set_constant_torque(RID p_body, real_t p_torque) override;
	real_t body_get_constant_torque(RID p_body) const override;

	void body_set_axis_velocity(RID p_body, const Vector2 &p_axis_velocity) override;

	void body_add_collision_exception(RID p_body, RID p_body_b) override;
	void body_remove_collision_exception(RID p_body, RID p_body_b) override;
	void body_get_collision_exceptions(RID p_body, List<RID> *p_exceptions) override;

	void body_set_contacts_reported_depth_threshold(RID p_body, real_t p_threshold) override;
	real_t body_get_contacts_reported_depth_threshold(RID p_body) const override;

	void body_set_omit_force_integration(RID p_body, bool p_omit) override;
	bool body_is_omitting_force_integration(RID p_body) const override;

	void body_set_max_contacts_reported(RID p_body, int p_contacts) override;
	int body_get_max_contacts_reported(RID p_body) const override;

	void body_set_state_sync_callback(RID p_body, const Callable &p_callable) override;
	void body_set_force_integration_callback(RID p_body, const Callable &p_callable, const Variant &p_udata = Variant()) override;

	bool body_collide_shape(RID p_body, int p_body_shape, RID p_shape, const Transform2D &p_shape_xform, const Vector2 &p_motion, Vector2 *r_results, int p_result_max, int &r_result_count) override;

	void body_set_pickable(RID p_body, bool p_pickable) override;

	bool body_test_motion(RID p_body, const MotionParameters &p_parameters, MotionResult *r_result = nullptr) override;

	// this function only works on physics process, errors and returns null otherwise
	PhysicsDirectBodyState2D *body_get_direct_state(RID p_body) override;

	/* JOINT API */

	RID joint_create() override;

	void joint_clear(RID p_joint) override;

	void joint_set_param(RID p_joint, JointParam p_param, real_t p_value) override;
	real_t joint_get_param(RID p_joint, JointParam p_param) const override;

	void joint_disable_collisions_between_bodies(RID p_joint, const bool p_disabled) override;
	bool joint_is_disabled_collisions_between_bodies(RID p_joint) const override;

	void joint_make_pin(RID p_joint, const Vector2 &p_anchor, RID p_body_a, RID p_body_b = RID()) override;
	void joint_make_groove(RID p_joint, const Vector2 &p_a_groove1, const Vector2 &p_a_groove2, const Vector2 &p_b_anchor, RID p_body_a, RID p_body_b) override;
	void joint_make_damped_spring(RID p_joint, const Vector2 &p_anchor_a, const Vector2 &p_anchor_b, RID p_body_a, RID p_body_b = RID()) override;

	void pin_joint_set_flag(RID p_joint, PinJointFlag p_flag, bool p_enabled) override;
	bool pin_joint_get_flag(RID p_joint, PinJointFlag p_flag) const override;
	void pin_joint_set_param(RID p_joint, PinJointParam p_param, real_t p_value) override;
	real_t pin_joint_get_param(RID p_joint, PinJointParam p_param) const override;
	void damped_spring_joint_set_param(RID p_joint, DampedSpringParam p_param, real_t p_value) override;
	real_t damped_spring_joint_get_param(RID p_joint, DampedSpringParam p_param) const override;

	JointType joint_get_type(RID p_joint) const override;

	/* MISC */

	void free(RID p_rid) override;

	void set_active(bool p_active) override;
	void init() override;
	void step(real_t p_step) override;
	void sync() override;
	void flush_queries() override;
	void end_sync() override;
	void finish() override;

	bool is_flushing_queries() const override { return flushing_queries; }

	int get_process_info(ProcessInfo p_info) override;

	GodotPhysicsServer2D(bool p_using_threads = false);
	~GodotPhysicsServer2D() override {}
};

#endif // GODOT_PHYSICS_SERVER_2D_H
