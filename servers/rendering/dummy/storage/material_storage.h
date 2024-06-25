/**************************************************************************/
/*  material_storage.h                                                    */
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

#ifndef MATERIAL_STORAGE_DUMMY_H
#define MATERIAL_STORAGE_DUMMY_H

#include "servers/rendering/shader_compiler.h"
#include "servers/rendering/shader_language.h"
#include "servers/rendering/storage/material_storage.h"
#include "servers/rendering/storage/utilities.h"

namespace RendererDummy {

class MaterialStorage : public RendererMaterialStorage {
private:
	static MaterialStorage *singleton;

	struct DummyShader {
		HashMap<StringName, ShaderLanguage::ShaderNode::Uniform> uniforms;
	};

	mutable RID_Owner<DummyShader> shader_owner;

	ShaderCompiler dummy_compiler;

public:
	static MaterialStorage *get_singleton() { return singleton; }

	MaterialStorage();
	~MaterialStorage() override;

	/* GLOBAL SHADER UNIFORM API */

	void global_shader_parameter_add(const StringName &p_name, RS::GlobalShaderParameterType p_type, const Variant &p_value) override {}
	void global_shader_parameter_remove(const StringName &p_name) override {}
	Vector<StringName> global_shader_parameter_get_list() const override { return Vector<StringName>(); }

	void global_shader_parameter_set(const StringName &p_name, const Variant &p_value) override {}
	void global_shader_parameter_set_override(const StringName &p_name, const Variant &p_value) override {}
	Variant global_shader_parameter_get(const StringName &p_name) const override { return Variant(); }
	RS::GlobalShaderParameterType global_shader_parameter_get_type(const StringName &p_name) const override { return RS::GLOBAL_VAR_TYPE_MAX; }

	void global_shader_parameters_load_settings(bool p_load_textures = true) override {}
	void global_shader_parameters_clear() override {}

	int32_t global_shader_parameters_instance_allocate(RID p_instance) override { return 0; }
	void global_shader_parameters_instance_free(RID p_instance) override {}
	void global_shader_parameters_instance_update(RID p_instance, int p_index, const Variant &p_value, int p_flags_count = 0) override {}

	/* SHADER API */

	bool owns_shader(RID p_rid) { return shader_owner.owns(p_rid); }

	RID shader_allocate() override;
	void shader_initialize(RID p_rid) override;
	void shader_free(RID p_rid) override;

	void shader_set_code(RID p_shader, const String &p_code) override;
	void shader_set_path_hint(RID p_shader, const String &p_code) override {}

	String shader_get_code(RID p_shader) const override { return ""; }
	void get_shader_parameter_list(RID p_shader, List<PropertyInfo> *p_param_list) const override;

	void shader_set_default_texture_parameter(RID p_shader, const StringName &p_name, RID p_texture, int p_index) override {}
	RID shader_get_default_texture_parameter(RID p_shader, const StringName &p_name, int p_index) const override { return RID(); }
	Variant shader_get_parameter_default(RID p_material, const StringName &p_param) const override { return Variant(); }

	RS::ShaderNativeSourceCode shader_get_native_source_code(RID p_shader) const override { return RS::ShaderNativeSourceCode(); };

	/* MATERIAL API */
	RID material_allocate() override { return RID(); }
	void material_initialize(RID p_rid) override {}
	void material_free(RID p_rid) override{};

	void material_set_render_priority(RID p_material, int priority) override {}
	void material_set_shader(RID p_shader_material, RID p_shader) override {}

	void material_set_param(RID p_material, const StringName &p_param, const Variant &p_value) override {}
	Variant material_get_param(RID p_material, const StringName &p_param) const override { return Variant(); }

	void material_set_next_pass(RID p_material, RID p_next_material) override {}

	bool material_is_animated(RID p_material) override { return false; }
	bool material_casts_shadows(RID p_material) override { return false; }
	void material_get_instance_shader_parameters(RID p_material, List<InstanceShaderParam> *r_parameters) override {}
	void material_update_dependency(RID p_material, DependencyTracker *p_instance) override {}
};

} // namespace RendererDummy

#endif // MATERIAL_STORAGE_DUMMY_H
