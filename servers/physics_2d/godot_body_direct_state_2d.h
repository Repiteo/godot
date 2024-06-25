/**************************************************************************/
/*  godot_body_direct_state_2d.h                                          */
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

#ifndef GODOT_BODY_DIRECT_STATE_2D_H
#define GODOT_BODY_DIRECT_STATE_2D_H

#include "servers/physics_server_2d.h"

class GodotBody2D;

class GodotPhysicsDirectBodyState2D : public PhysicsDirectBodyState2D {
	GDCLASS(GodotPhysicsDirectBodyState2D, PhysicsDirectBodyState2D);

public:
	GodotBody2D *body = nullptr;

	Vector2 get_total_gravity() const override;
	real_t get_total_angular_damp() const override;
	real_t get_total_linear_damp() const override;

	Vector2 get_center_of_mass() const override;
	Vector2 get_center_of_mass_local() const override;
	real_t get_inverse_mass() const override;
	real_t get_inverse_inertia() const override;

	void set_linear_velocity(const Vector2 &p_velocity) override;
	Vector2 get_linear_velocity() const override;

	void set_angular_velocity(real_t p_velocity) override;
	real_t get_angular_velocity() const override;

	void set_transform(const Transform2D &p_transform) override;
	Transform2D get_transform() const override;

	Vector2 get_velocity_at_local_position(const Vector2 &p_position) const override;

	void apply_central_impulse(const Vector2 &p_impulse) override;
	void apply_impulse(const Vector2 &p_impulse, const Vector2 &p_position = Vector2()) override;
	void apply_torque_impulse(real_t p_torque) override;

	void apply_central_force(const Vector2 &p_force) override;
	void apply_force(const Vector2 &p_force, const Vector2 &p_position = Vector2()) override;
	void apply_torque(real_t p_torque) override;

	void add_constant_central_force(const Vector2 &p_force) override;
	void add_constant_force(const Vector2 &p_force, const Vector2 &p_position = Vector2()) override;
	void add_constant_torque(real_t p_torque) override;

	void set_constant_force(const Vector2 &p_force) override;
	Vector2 get_constant_force() const override;

	void set_constant_torque(real_t p_torque) override;
	real_t get_constant_torque() const override;

	void set_sleep_state(bool p_enable) override;
	bool is_sleeping() const override;

	int get_contact_count() const override;

	Vector2 get_contact_local_position(int p_contact_idx) const override;
	Vector2 get_contact_local_normal(int p_contact_idx) const override;
	int get_contact_local_shape(int p_contact_idx) const override;
	Vector2 get_contact_local_velocity_at_position(int p_contact_idx) const override;

	RID get_contact_collider(int p_contact_idx) const override;
	Vector2 get_contact_collider_position(int p_contact_idx) const override;
	ObjectID get_contact_collider_id(int p_contact_idx) const override;
	int get_contact_collider_shape(int p_contact_idx) const override;
	Vector2 get_contact_collider_velocity_at_position(int p_contact_idx) const override;
	Vector2 get_contact_impulse(int p_contact_idx) const override;

	PhysicsDirectSpaceState2D *get_space_state() override;

	real_t get_step() const override;
};

#endif // GODOT_BODY_DIRECT_STATE_2D_H
