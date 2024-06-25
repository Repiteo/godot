/**************************************************************************/
/*  text_server_extension.h                                               */
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

#ifndef TEXT_SERVER_EXTENSION_H
#define TEXT_SERVER_EXTENSION_H

#include "core/object/gdvirtual.gen.inc"
#include "core/os/thread_safe.h"
#include "core/variant/native_ptr.h"
#include "core/variant/typed_array.h"
#include "servers/text_server.h"

class TextServerExtension : public TextServer {
	GDCLASS(TextServerExtension, TextServer);

protected:
	_THREAD_SAFE_CLASS_

	static void _bind_methods();

public:
	bool has_feature(Feature p_feature) const override;
	String get_name() const override;
	int64_t get_features() const override;
	GDVIRTUAL1RC(bool, _has_feature, Feature);
	GDVIRTUAL0RC(String, _get_name);
	GDVIRTUAL0RC(int64_t, _get_features);

	void free_rid(const RID &p_rid) override;
	bool has(const RID &p_rid) override;
	bool load_support_data(const String &p_filename) override;
	GDVIRTUAL1(_free_rid, RID);
	GDVIRTUAL1R(bool, _has, RID);
	GDVIRTUAL1R(bool, _load_support_data, const String &);

	String get_support_data_filename() const override;
	String get_support_data_info() const override;
	bool save_support_data(const String &p_filename) const override;
	GDVIRTUAL0RC(String, _get_support_data_filename);
	GDVIRTUAL0RC(String, _get_support_data_info);
	GDVIRTUAL1RC(bool, _save_support_data, const String &);

	bool is_locale_right_to_left(const String &p_locale) const override;
	GDVIRTUAL1RC(bool, _is_locale_right_to_left, const String &);

	int64_t name_to_tag(const String &p_name) const override;
	String tag_to_name(int64_t p_tag) const override;
	GDVIRTUAL1RC(int64_t, _name_to_tag, const String &);
	GDVIRTUAL1RC(String, _tag_to_name, int64_t);

	/* Font interface */

	RID create_font() override;
	GDVIRTUAL0R(RID, _create_font);

	RID create_font_linked_variation(const RID &p_font_rid) override;
	GDVIRTUAL1R(RID, _create_font_linked_variation, RID);

	void font_set_data(const RID &p_font_rid, const PackedByteArray &p_data) override;
	void font_set_data_ptr(const RID &p_font_rid, const uint8_t *p_data_ptr, int64_t p_data_size) override;
	GDVIRTUAL2(_font_set_data, RID, const PackedByteArray &);
	GDVIRTUAL3(_font_set_data_ptr, RID, GDExtensionConstPtr<const uint8_t>, int64_t);

	void font_set_face_index(const RID &p_font_rid, int64_t p_index) override;
	int64_t font_get_face_index(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_face_index, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_face_index, RID);

	int64_t font_get_face_count(const RID &p_font_rid) const override;
	GDVIRTUAL1RC(int64_t, _font_get_face_count, RID);

	void font_set_style(const RID &p_font_rid, BitField<FontStyle> p_style) override;
	BitField<FontStyle> font_get_style(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_style, RID, BitField<FontStyle>);
	GDVIRTUAL1RC(BitField<FontStyle>, _font_get_style, RID);

	void font_set_name(const RID &p_font_rid, const String &p_name) override;
	String font_get_name(const RID &p_font_rid) const override;
	Dictionary font_get_ot_name_strings(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_name, RID, const String &);
	GDVIRTUAL1RC(String, _font_get_name, RID);
	GDVIRTUAL1RC(Dictionary, _font_get_ot_name_strings, RID);

	void font_set_style_name(const RID &p_font_rid, const String &p_name) override;
	String font_get_style_name(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_style_name, RID, const String &);
	GDVIRTUAL1RC(String, _font_get_style_name, RID);

	void font_set_weight(const RID &p_font_rid, int64_t p_weight) override;
	int64_t font_get_weight(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_weight, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_weight, RID);

	void font_set_stretch(const RID &p_font_rid, int64_t p_stretch) override;
	int64_t font_get_stretch(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_stretch, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_stretch, RID);

	void font_set_antialiasing(const RID &p_font_rid, TextServer::FontAntialiasing p_antialiasing) override;
	TextServer::FontAntialiasing font_get_antialiasing(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_antialiasing, RID, TextServer::FontAntialiasing);
	GDVIRTUAL1RC(TextServer::FontAntialiasing, _font_get_antialiasing, RID);

	void font_set_disable_embedded_bitmaps(const RID &p_font_rid, bool p_disable_embedded_bitmaps) override;
	bool font_get_disable_embedded_bitmaps(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_disable_embedded_bitmaps, RID, bool);
	GDVIRTUAL1RC(bool, _font_get_disable_embedded_bitmaps, RID);

	void font_set_generate_mipmaps(const RID &p_font_rid, bool p_generate_mipmaps) override;
	bool font_get_generate_mipmaps(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_generate_mipmaps, RID, bool);
	GDVIRTUAL1RC(bool, _font_get_generate_mipmaps, RID);

	void font_set_multichannel_signed_distance_field(const RID &p_font_rid, bool p_msdf) override;
	bool font_is_multichannel_signed_distance_field(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_multichannel_signed_distance_field, RID, bool);
	GDVIRTUAL1RC(bool, _font_is_multichannel_signed_distance_field, RID);

	void font_set_msdf_pixel_range(const RID &p_font_rid, int64_t p_msdf_pixel_range) override;
	int64_t font_get_msdf_pixel_range(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_msdf_pixel_range, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_msdf_pixel_range, RID);

	void font_set_msdf_size(const RID &p_font_rid, int64_t p_msdf_size) override;
	int64_t font_get_msdf_size(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_msdf_size, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_msdf_size, RID);

	void font_set_fixed_size(const RID &p_font_rid, int64_t p_fixed_size) override;
	int64_t font_get_fixed_size(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_fixed_size, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _font_get_fixed_size, RID);

	void font_set_fixed_size_scale_mode(const RID &p_font_rid, FixedSizeScaleMode p_fixed_size_scale) override;
	FixedSizeScaleMode font_get_fixed_size_scale_mode(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_fixed_size_scale_mode, RID, FixedSizeScaleMode);
	GDVIRTUAL1RC(FixedSizeScaleMode, _font_get_fixed_size_scale_mode, RID);

	void font_set_subpixel_positioning(const RID &p_font_rid, SubpixelPositioning p_subpixel) override;
	SubpixelPositioning font_get_subpixel_positioning(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_subpixel_positioning, RID, SubpixelPositioning);
	GDVIRTUAL1RC(SubpixelPositioning, _font_get_subpixel_positioning, RID);

	void font_set_embolden(const RID &p_font_rid, double p_strength) override;
	double font_get_embolden(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_embolden, RID, double);
	GDVIRTUAL1RC(double, _font_get_embolden, RID);

	void font_set_spacing(const RID &p_font_rid, SpacingType p_spacing, int64_t p_value) override;
	int64_t font_get_spacing(const RID &p_font_rid, SpacingType p_spacing) const override;
	GDVIRTUAL3(_font_set_spacing, const RID &, SpacingType, int64_t);
	GDVIRTUAL2RC(int64_t, _font_get_spacing, const RID &, SpacingType);

	void font_set_baseline_offset(const RID &p_font_rid, double p_baseline_offset) override;
	double font_get_baseline_offset(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_baseline_offset, const RID &, double);
	GDVIRTUAL1RC(double, _font_get_baseline_offset, const RID &);

	void font_set_transform(const RID &p_font_rid, const Transform2D &p_transform) override;
	Transform2D font_get_transform(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_transform, RID, Transform2D);
	GDVIRTUAL1RC(Transform2D, _font_get_transform, RID);

	void font_set_allow_system_fallback(const RID &p_font_rid, bool p_allow_system_fallback) override;
	bool font_is_allow_system_fallback(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_allow_system_fallback, RID, bool);
	GDVIRTUAL1RC(bool, _font_is_allow_system_fallback, RID);

	void font_set_force_autohinter(const RID &p_font_rid, bool p_force_autohinter) override;
	bool font_is_force_autohinter(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_force_autohinter, RID, bool);
	GDVIRTUAL1RC(bool, _font_is_force_autohinter, RID);

	void font_set_hinting(const RID &p_font_rid, Hinting p_hinting) override;
	Hinting font_get_hinting(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_hinting, RID, Hinting);
	GDVIRTUAL1RC(Hinting, _font_get_hinting, RID);

	void font_set_variation_coordinates(const RID &p_font_rid, const Dictionary &p_variation_coordinates) override;
	Dictionary font_get_variation_coordinates(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_variation_coordinates, RID, Dictionary);
	GDVIRTUAL1RC(Dictionary, _font_get_variation_coordinates, RID);

	void font_set_oversampling(const RID &p_font_rid, double p_oversampling) override;
	double font_get_oversampling(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_oversampling, RID, double);
	GDVIRTUAL1RC(double, _font_get_oversampling, RID);

	TypedArray<Vector2i> font_get_size_cache_list(const RID &p_font_rid) const override;
	void font_clear_size_cache(const RID &p_font_rid) override;
	void font_remove_size_cache(const RID &p_font_rid, const Vector2i &p_size) override;
	GDVIRTUAL1RC(TypedArray<Vector2i>, _font_get_size_cache_list, RID);
	GDVIRTUAL1(_font_clear_size_cache, RID);
	GDVIRTUAL2(_font_remove_size_cache, RID, const Vector2i &);

	void font_set_ascent(const RID &p_font_rid, int64_t p_size, double p_ascent) override;
	double font_get_ascent(const RID &p_font_rid, int64_t p_size) const override;
	GDVIRTUAL3(_font_set_ascent, RID, int64_t, double);
	GDVIRTUAL2RC(double, _font_get_ascent, RID, int64_t);

	void font_set_descent(const RID &p_font_rid, int64_t p_size, double p_descent) override;
	double font_get_descent(const RID &p_font_rid, int64_t p_size) const override;
	GDVIRTUAL3(_font_set_descent, RID, int64_t, double);
	GDVIRTUAL2RC(double, _font_get_descent, RID, int64_t);

	void font_set_underline_position(const RID &p_font_rid, int64_t p_size, double p_underline_position) override;
	double font_get_underline_position(const RID &p_font_rid, int64_t p_size) const override;
	GDVIRTUAL3(_font_set_underline_position, RID, int64_t, double);
	GDVIRTUAL2RC(double, _font_get_underline_position, RID, int64_t);

	void font_set_underline_thickness(const RID &p_font_rid, int64_t p_size, double p_underline_thickness) override;
	double font_get_underline_thickness(const RID &p_font_rid, int64_t p_size) const override;
	GDVIRTUAL3(_font_set_underline_thickness, RID, int64_t, double);
	GDVIRTUAL2RC(double, _font_get_underline_thickness, RID, int64_t);

	void font_set_scale(const RID &p_font_rid, int64_t p_size, double p_scale) override;
	double font_get_scale(const RID &p_font_rid, int64_t p_size) const override;
	GDVIRTUAL3(_font_set_scale, RID, int64_t, double);
	GDVIRTUAL2RC(double, _font_get_scale, RID, int64_t);

	int64_t font_get_texture_count(const RID &p_font_rid, const Vector2i &p_size) const override;
	void font_clear_textures(const RID &p_font_rid, const Vector2i &p_size) override;
	void font_remove_texture(const RID &p_font_rid, const Vector2i &p_size, int64_t p_texture_index) override;
	GDVIRTUAL2RC(int64_t, _font_get_texture_count, RID, const Vector2i &);
	GDVIRTUAL2(_font_clear_textures, RID, const Vector2i &);
	GDVIRTUAL3(_font_remove_texture, RID, const Vector2i &, int64_t);

	void font_set_texture_image(const RID &p_font_rid, const Vector2i &p_size, int64_t p_texture_index, const Ref<Image> &p_image) override;
	Ref<Image> font_get_texture_image(const RID &p_font_rid, const Vector2i &p_size, int64_t p_texture_index) const override;
	GDVIRTUAL4(_font_set_texture_image, RID, const Vector2i &, int64_t, const Ref<Image> &);
	GDVIRTUAL3RC(Ref<Image>, _font_get_texture_image, RID, const Vector2i &, int64_t);

	void font_set_texture_offsets(const RID &p_font_rid, const Vector2i &p_size, int64_t p_texture_index, const PackedInt32Array &p_offset) override;
	PackedInt32Array font_get_texture_offsets(const RID &p_font_rid, const Vector2i &p_size, int64_t p_texture_index) const override;
	GDVIRTUAL4(_font_set_texture_offsets, RID, const Vector2i &, int64_t, const PackedInt32Array &);
	GDVIRTUAL3RC(PackedInt32Array, _font_get_texture_offsets, RID, const Vector2i &, int64_t);

	PackedInt32Array font_get_glyph_list(const RID &p_font_rid, const Vector2i &p_size) const override;
	void font_clear_glyphs(const RID &p_font_rid, const Vector2i &p_size) override;
	void font_remove_glyph(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) override;
	GDVIRTUAL2RC(PackedInt32Array, _font_get_glyph_list, RID, const Vector2i &);
	GDVIRTUAL2(_font_clear_glyphs, RID, const Vector2i &);
	GDVIRTUAL3(_font_remove_glyph, RID, const Vector2i &, int64_t);

	Vector2 font_get_glyph_advance(const RID &p_font_rid, int64_t p_size, int64_t p_glyph) const override;
	void font_set_glyph_advance(const RID &p_font_rid, int64_t p_size, int64_t p_glyph, const Vector2 &p_advance) override;
	GDVIRTUAL3RC(Vector2, _font_get_glyph_advance, RID, int64_t, int64_t);
	GDVIRTUAL4(_font_set_glyph_advance, RID, int64_t, int64_t, const Vector2 &);

	Vector2 font_get_glyph_offset(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	void font_set_glyph_offset(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph, const Vector2 &p_offset) override;
	GDVIRTUAL3RC(Vector2, _font_get_glyph_offset, RID, const Vector2i &, int64_t);
	GDVIRTUAL4(_font_set_glyph_offset, RID, const Vector2i &, int64_t, const Vector2 &);

	Vector2 font_get_glyph_size(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	void font_set_glyph_size(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph, const Vector2 &p_gl_size) override;
	GDVIRTUAL3RC(Vector2, _font_get_glyph_size, RID, const Vector2i &, int64_t);
	GDVIRTUAL4(_font_set_glyph_size, RID, const Vector2i &, int64_t, const Vector2 &);

	Rect2 font_get_glyph_uv_rect(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	void font_set_glyph_uv_rect(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph, const Rect2 &p_uv_rect) override;
	GDVIRTUAL3RC(Rect2, _font_get_glyph_uv_rect, RID, const Vector2i &, int64_t);
	GDVIRTUAL4(_font_set_glyph_uv_rect, RID, const Vector2i &, int64_t, const Rect2 &);

	int64_t font_get_glyph_texture_idx(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	void font_set_glyph_texture_idx(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph, int64_t p_texture_idx) override;
	GDVIRTUAL3RC(int64_t, _font_get_glyph_texture_idx, RID, const Vector2i &, int64_t);
	GDVIRTUAL4(_font_set_glyph_texture_idx, RID, const Vector2i &, int64_t, int64_t);

	RID font_get_glyph_texture_rid(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	GDVIRTUAL3RC(RID, _font_get_glyph_texture_rid, RID, const Vector2i &, int64_t);

	Size2 font_get_glyph_texture_size(const RID &p_font_rid, const Vector2i &p_size, int64_t p_glyph) const override;
	GDVIRTUAL3RC(Size2, _font_get_glyph_texture_size, RID, const Vector2i &, int64_t);

	Dictionary font_get_glyph_contours(const RID &p_font, int64_t p_size, int64_t p_index) const override;
	GDVIRTUAL3RC(Dictionary, _font_get_glyph_contours, RID, int64_t, int64_t);

	TypedArray<Vector2i> font_get_kerning_list(const RID &p_font_rid, int64_t p_size) const override;
	void font_clear_kerning_map(const RID &p_font_rid, int64_t p_size) override;
	void font_remove_kerning(const RID &p_font_rid, int64_t p_size, const Vector2i &p_glyph_pair) override;
	GDVIRTUAL2RC(TypedArray<Vector2i>, _font_get_kerning_list, RID, int64_t);
	GDVIRTUAL2(_font_clear_kerning_map, RID, int64_t);
	GDVIRTUAL3(_font_remove_kerning, RID, int64_t, const Vector2i &);

	void font_set_kerning(const RID &p_font_rid, int64_t p_size, const Vector2i &p_glyph_pair, const Vector2 &p_kerning) override;
	Vector2 font_get_kerning(const RID &p_font_rid, int64_t p_size, const Vector2i &p_glyph_pair) const override;
	GDVIRTUAL4(_font_set_kerning, RID, int64_t, const Vector2i &, const Vector2 &);
	GDVIRTUAL3RC(Vector2, _font_get_kerning, RID, int64_t, const Vector2i &);

	int64_t font_get_glyph_index(const RID &p_font_rid, int64_t p_size, int64_t p_char, int64_t p_variation_selector = 0) const override;
	GDVIRTUAL4RC(int64_t, _font_get_glyph_index, RID, int64_t, int64_t, int64_t);

	int64_t font_get_char_from_glyph_index(const RID &p_font_rid, int64_t p_size, int64_t p_glyph_index) const override;
	GDVIRTUAL3RC(int64_t, _font_get_char_from_glyph_index, RID, int64_t, int64_t);

	bool font_has_char(const RID &p_font_rid, int64_t p_char) const override;
	String font_get_supported_chars(const RID &p_font_rid) const override;
	GDVIRTUAL2RC(bool, _font_has_char, RID, int64_t);
	GDVIRTUAL1RC(String, _font_get_supported_chars, RID);

	void font_render_range(const RID &p_font, const Vector2i &p_size, int64_t p_start, int64_t p_end) override;
	void font_render_glyph(const RID &p_font_rid, const Vector2i &p_size, int64_t p_index) override;
	GDVIRTUAL4(_font_render_range, RID, const Vector2i &, int64_t, int64_t);
	GDVIRTUAL3(_font_render_glyph, RID, const Vector2i &, int64_t);

	void font_draw_glyph(const RID &p_font, const RID &p_canvas, int64_t p_size, const Vector2 &p_pos, int64_t p_index, const Color &p_color = Color(1, 1, 1)) const override;
	void font_draw_glyph_outline(const RID &p_font, const RID &p_canvas, int64_t p_size, int64_t p_outline_size, const Vector2 &p_pos, int64_t p_index, const Color &p_color = Color(1, 1, 1)) const override;
	GDVIRTUAL6C(_font_draw_glyph, RID, RID, int64_t, const Vector2 &, int64_t, const Color &);
	GDVIRTUAL7C(_font_draw_glyph_outline, RID, RID, int64_t, int64_t, const Vector2 &, int64_t, const Color &);

	bool font_is_language_supported(const RID &p_font_rid, const String &p_language) const override;
	void font_set_language_support_override(const RID &p_font_rid, const String &p_language, bool p_supported) override;
	bool font_get_language_support_override(const RID &p_font_rid, const String &p_language) override;
	void font_remove_language_support_override(const RID &p_font_rid, const String &p_language) override;
	PackedStringArray font_get_language_support_overrides(const RID &p_font_rid) override;
	GDVIRTUAL2RC(bool, _font_is_language_supported, RID, const String &);
	GDVIRTUAL3(_font_set_language_support_override, RID, const String &, bool);
	GDVIRTUAL2R(bool, _font_get_language_support_override, RID, const String &);
	GDVIRTUAL2(_font_remove_language_support_override, RID, const String &);
	GDVIRTUAL1R(PackedStringArray, _font_get_language_support_overrides, RID);

	bool font_is_script_supported(const RID &p_font_rid, const String &p_script) const override;
	void font_set_script_support_override(const RID &p_font_rid, const String &p_script, bool p_supported) override;
	bool font_get_script_support_override(const RID &p_font_rid, const String &p_script) override;
	void font_remove_script_support_override(const RID &p_font_rid, const String &p_script) override;
	PackedStringArray font_get_script_support_overrides(const RID &p_font_rid) override;
	GDVIRTUAL2RC(bool, _font_is_script_supported, RID, const String &);
	GDVIRTUAL3(_font_set_script_support_override, RID, const String &, bool);
	GDVIRTUAL2R(bool, _font_get_script_support_override, RID, const String &);
	GDVIRTUAL2(_font_remove_script_support_override, RID, const String &);
	GDVIRTUAL1R(PackedStringArray, _font_get_script_support_overrides, RID);

	void font_set_opentype_feature_overrides(const RID &p_font_rid, const Dictionary &p_overrides) override;
	Dictionary font_get_opentype_feature_overrides(const RID &p_font_rid) const override;
	GDVIRTUAL2(_font_set_opentype_feature_overrides, RID, const Dictionary &);
	GDVIRTUAL1RC(Dictionary, _font_get_opentype_feature_overrides, RID);

	Dictionary font_supported_feature_list(const RID &p_font_rid) const override;
	Dictionary font_supported_variation_list(const RID &p_font_rid) const override;
	GDVIRTUAL1RC(Dictionary, _font_supported_feature_list, RID);
	GDVIRTUAL1RC(Dictionary, _font_supported_variation_list, RID);

	double font_get_global_oversampling() const override;
	void font_set_global_oversampling(double p_oversampling) override;
	GDVIRTUAL0RC(double, _font_get_global_oversampling);
	GDVIRTUAL1(_font_set_global_oversampling, double);

	Vector2 get_hex_code_box_size(int64_t p_size, int64_t p_index) const override;
	void draw_hex_code_box(const RID &p_canvas, int64_t p_size, const Vector2 &p_pos, int64_t p_index, const Color &p_color) const override;
	GDVIRTUAL2RC(Vector2, _get_hex_code_box_size, int64_t, int64_t);
	GDVIRTUAL5C(_draw_hex_code_box, RID, int64_t, const Vector2 &, int64_t, const Color &);

	/* Shaped text buffer interface */

	RID create_shaped_text(Direction p_direction = DIRECTION_AUTO, Orientation p_orientation = ORIENTATION_HORIZONTAL) override;
	GDVIRTUAL2R(RID, _create_shaped_text, Direction, Orientation);

	void shaped_text_clear(const RID &p_shaped) override;
	GDVIRTUAL1(_shaped_text_clear, RID);

	void shaped_text_set_direction(const RID &p_shaped, Direction p_direction = DIRECTION_AUTO) override;
	Direction shaped_text_get_direction(const RID &p_shaped) const override;
	Direction shaped_text_get_inferred_direction(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_direction, RID, Direction);
	GDVIRTUAL1RC(Direction, _shaped_text_get_direction, RID);
	GDVIRTUAL1RC(Direction, _shaped_text_get_inferred_direction, RID);

	void shaped_text_set_bidi_override(const RID &p_shaped, const Array &p_override) override;
	GDVIRTUAL2(_shaped_text_set_bidi_override, RID, const Array &);

	void shaped_text_set_custom_punctuation(const RID &p_shaped, const String &p_punct) override;
	String shaped_text_get_custom_punctuation(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_custom_punctuation, RID, String);
	GDVIRTUAL1RC(String, _shaped_text_get_custom_punctuation, RID);

	void shaped_text_set_custom_ellipsis(const RID &p_shaped, int64_t p_char) override;
	int64_t shaped_text_get_custom_ellipsis(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_custom_ellipsis, RID, int64_t);
	GDVIRTUAL1RC(int64_t, _shaped_text_get_custom_ellipsis, RID);

	void shaped_text_set_orientation(const RID &p_shaped, Orientation p_orientation = ORIENTATION_HORIZONTAL) override;
	Orientation shaped_text_get_orientation(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_orientation, RID, Orientation);
	GDVIRTUAL1RC(Orientation, _shaped_text_get_orientation, RID);

	void shaped_text_set_preserve_invalid(const RID &p_shaped, bool p_enabled) override;
	bool shaped_text_get_preserve_invalid(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_preserve_invalid, RID, bool);
	GDVIRTUAL1RC(bool, _shaped_text_get_preserve_invalid, RID);

	void shaped_text_set_preserve_control(const RID &p_shaped, bool p_enabled) override;
	bool shaped_text_get_preserve_control(const RID &p_shaped) const override;
	GDVIRTUAL2(_shaped_text_set_preserve_control, RID, bool);
	GDVIRTUAL1RC(bool, _shaped_text_get_preserve_control, RID);

	void shaped_text_set_spacing(const RID &p_shaped, SpacingType p_spacing, int64_t p_value) override;
	int64_t shaped_text_get_spacing(const RID &p_shaped, SpacingType p_spacing) const override;
	GDVIRTUAL3(_shaped_text_set_spacing, RID, SpacingType, int64_t);
	GDVIRTUAL2RC(int64_t, _shaped_text_get_spacing, RID, SpacingType);

	bool shaped_text_add_string(const RID &p_shaped, const String &p_text, const TypedArray<RID> &p_fonts, int64_t p_size, const Dictionary &p_opentype_features = Dictionary(), const String &p_language = "", const Variant &p_meta = Variant()) override;
	bool shaped_text_add_object(const RID &p_shaped, const Variant &p_key, const Size2 &p_size, InlineAlignment p_inline_align = INLINE_ALIGNMENT_CENTER, int64_t p_length = 1, double p_baseline = 0.0) override;
	bool shaped_text_resize_object(const RID &p_shaped, const Variant &p_key, const Size2 &p_size, InlineAlignment p_inline_align = INLINE_ALIGNMENT_CENTER, double p_baseline = 0.0) override;
	GDVIRTUAL7R(bool, _shaped_text_add_string, RID, const String &, const TypedArray<RID> &, int64_t, const Dictionary &, const String &, const Variant &);
	GDVIRTUAL6R(bool, _shaped_text_add_object, RID, const Variant &, const Size2 &, InlineAlignment, int64_t, double);
	GDVIRTUAL5R(bool, _shaped_text_resize_object, RID, const Variant &, const Size2 &, InlineAlignment, double);

	int64_t shaped_get_span_count(const RID &p_shaped) const override;
	Variant shaped_get_span_meta(const RID &p_shaped, int64_t p_index) const override;
	void shaped_set_span_update_font(const RID &p_shaped, int64_t p_index, const TypedArray<RID> &p_fonts, int64_t p_size, const Dictionary &p_opentype_features = Dictionary()) override;
	GDVIRTUAL1RC(int64_t, _shaped_get_span_count, RID);
	GDVIRTUAL2RC(Variant, _shaped_get_span_meta, RID, int64_t);
	GDVIRTUAL5(_shaped_set_span_update_font, RID, int64_t, const TypedArray<RID> &, int64_t, const Dictionary &);

	RID shaped_text_substr(const RID &p_shaped, int64_t p_start, int64_t p_length) const override;
	RID shaped_text_get_parent(const RID &p_shaped) const override;
	GDVIRTUAL3RC(RID, _shaped_text_substr, RID, int64_t, int64_t);
	GDVIRTUAL1RC(RID, _shaped_text_get_parent, RID);

	double shaped_text_fit_to_width(const RID &p_shaped, double p_width, BitField<TextServer::JustificationFlag> p_jst_flags = JUSTIFICATION_WORD_BOUND | JUSTIFICATION_KASHIDA) override;
	double shaped_text_tab_align(const RID &p_shaped, const PackedFloat32Array &p_tab_stops) override;
	GDVIRTUAL3R(double, _shaped_text_fit_to_width, RID, double, BitField<TextServer::JustificationFlag>);
	GDVIRTUAL2R(double, _shaped_text_tab_align, RID, const PackedFloat32Array &);

	bool shaped_text_shape(const RID &p_shaped) override;
	bool shaped_text_update_breaks(const RID &p_shaped) override;
	bool shaped_text_update_justification_ops(const RID &p_shaped) override;
	GDVIRTUAL1R(bool, _shaped_text_shape, RID);
	GDVIRTUAL1R(bool, _shaped_text_update_breaks, RID);
	GDVIRTUAL1R(bool, _shaped_text_update_justification_ops, RID);

	bool shaped_text_is_ready(const RID &p_shaped) const override;
	GDVIRTUAL1RC(bool, _shaped_text_is_ready, RID);

	const Glyph *shaped_text_get_glyphs(const RID &p_shaped) const override;
	const Glyph *shaped_text_sort_logical(const RID &p_shaped) override;
	int64_t shaped_text_get_glyph_count(const RID &p_shaped) const override;
	GDVIRTUAL1RC(GDExtensionConstPtr<const Glyph>, _shaped_text_get_glyphs, RID);
	GDVIRTUAL1R(GDExtensionConstPtr<const Glyph>, _shaped_text_sort_logical, RID);
	GDVIRTUAL1RC(int64_t, _shaped_text_get_glyph_count, RID);

	Vector2i shaped_text_get_range(const RID &p_shaped) const override;
	GDVIRTUAL1RC(Vector2i, _shaped_text_get_range, RID);

	PackedInt32Array shaped_text_get_line_breaks_adv(const RID &p_shaped, const PackedFloat32Array &p_width, int64_t p_start = 0, bool p_once = true, BitField<TextServer::LineBreakFlag> p_break_flags = BREAK_MANDATORY | BREAK_WORD_BOUND) const override;
	PackedInt32Array shaped_text_get_line_breaks(const RID &p_shaped, double p_width, int64_t p_start = 0, BitField<TextServer::LineBreakFlag> p_break_flags = BREAK_MANDATORY | BREAK_WORD_BOUND) const override;
	PackedInt32Array shaped_text_get_word_breaks(const RID &p_shaped, BitField<TextServer::GraphemeFlag> p_grapheme_flags = GRAPHEME_IS_SPACE | GRAPHEME_IS_PUNCTUATION, BitField<TextServer::GraphemeFlag> p_skip_grapheme_flags = GRAPHEME_IS_VIRTUAL) const override;
	GDVIRTUAL5RC(PackedInt32Array, _shaped_text_get_line_breaks_adv, RID, const PackedFloat32Array &, int64_t, bool, BitField<TextServer::LineBreakFlag>);
	GDVIRTUAL4RC(PackedInt32Array, _shaped_text_get_line_breaks, RID, double, int64_t, BitField<TextServer::LineBreakFlag>);
	GDVIRTUAL3RC(PackedInt32Array, _shaped_text_get_word_breaks, RID, BitField<TextServer::GraphemeFlag>, BitField<TextServer::GraphemeFlag>);

	int64_t shaped_text_get_trim_pos(const RID &p_shaped) const override;
	int64_t shaped_text_get_ellipsis_pos(const RID &p_shaped) const override;
	const Glyph *shaped_text_get_ellipsis_glyphs(const RID &p_shaped) const override;
	int64_t shaped_text_get_ellipsis_glyph_count(const RID &p_shaped) const override;
	GDVIRTUAL1RC(int64_t, _shaped_text_get_trim_pos, RID);
	GDVIRTUAL1RC(int64_t, _shaped_text_get_ellipsis_pos, RID);
	GDVIRTUAL1RC(GDExtensionConstPtr<const Glyph>, _shaped_text_get_ellipsis_glyphs, RID);
	GDVIRTUAL1RC(int64_t, _shaped_text_get_ellipsis_glyph_count, RID);

	void shaped_text_overrun_trim_to_width(const RID &p_shaped, double p_width, BitField<TextServer::TextOverrunFlag> p_trim_flags) override;
	GDVIRTUAL3(_shaped_text_overrun_trim_to_width, RID, double, BitField<TextServer::TextOverrunFlag>);

	Array shaped_text_get_objects(const RID &p_shaped) const override;
	Rect2 shaped_text_get_object_rect(const RID &p_shaped, const Variant &p_key) const override;
	Vector2i shaped_text_get_object_range(const RID &p_shaped, const Variant &p_key) const override;
	int64_t shaped_text_get_object_glyph(const RID &p_shaped, const Variant &p_key) const override;
	GDVIRTUAL1RC(Array, _shaped_text_get_objects, RID);
	GDVIRTUAL2RC(Rect2, _shaped_text_get_object_rect, RID, const Variant &);
	GDVIRTUAL2RC(Vector2i, _shaped_text_get_object_range, RID, const Variant &);
	GDVIRTUAL2RC(int64_t, _shaped_text_get_object_glyph, RID, const Variant &);

	Size2 shaped_text_get_size(const RID &p_shaped) const override;
	double shaped_text_get_ascent(const RID &p_shaped) const override;
	double shaped_text_get_descent(const RID &p_shaped) const override;
	double shaped_text_get_width(const RID &p_shaped) const override;
	double shaped_text_get_underline_position(const RID &p_shaped) const override;
	double shaped_text_get_underline_thickness(const RID &p_shaped) const override;
	GDVIRTUAL1RC(Size2, _shaped_text_get_size, RID);
	GDVIRTUAL1RC(double, _shaped_text_get_ascent, RID);
	GDVIRTUAL1RC(double, _shaped_text_get_descent, RID);
	GDVIRTUAL1RC(double, _shaped_text_get_width, RID);
	GDVIRTUAL1RC(double, _shaped_text_get_underline_position, RID);
	GDVIRTUAL1RC(double, _shaped_text_get_underline_thickness, RID);

	Direction shaped_text_get_dominant_direction_in_range(const RID &p_shaped, int64_t p_start, int64_t p_end) const override;
	GDVIRTUAL3RC(int64_t, _shaped_text_get_dominant_direction_in_range, RID, int64_t, int64_t);

	CaretInfo shaped_text_get_carets(const RID &p_shaped, int64_t p_position) const override;
	Vector<Vector2> shaped_text_get_selection(const RID &p_shaped, int64_t p_start, int64_t p_end) const override;
	GDVIRTUAL3C(_shaped_text_get_carets, RID, int64_t, GDExtensionPtr<CaretInfo>);
	GDVIRTUAL3RC(Vector<Vector2>, _shaped_text_get_selection, RID, int64_t, int64_t);

	int64_t shaped_text_hit_test_grapheme(const RID &p_shaped, double p_coords) const override;
	int64_t shaped_text_hit_test_position(const RID &p_shaped, double p_coords) const override;
	GDVIRTUAL2RC(int64_t, _shaped_text_hit_test_grapheme, RID, double);
	GDVIRTUAL2RC(int64_t, _shaped_text_hit_test_position, RID, double);

	void shaped_text_draw(const RID &p_shaped, const RID &p_canvas, const Vector2 &p_pos, double p_clip_l = -1.0, double p_clip_r = -1.0, const Color &p_color = Color(1, 1, 1)) const override;
	void shaped_text_draw_outline(const RID &p_shaped, const RID &p_canvas, const Vector2 &p_pos, double p_clip_l = -1.0, double p_clip_r = -1.0, int64_t p_outline_size = 1, const Color &p_color = Color(1, 1, 1)) const override;
	GDVIRTUAL6C(_shaped_text_draw, RID, RID, const Vector2 &, double, double, const Color &);
	GDVIRTUAL7C(_shaped_text_draw_outline, RID, RID, const Vector2 &, double, double, int64_t, const Color &);

	Vector2 shaped_text_get_grapheme_bounds(const RID &p_shaped, int64_t p_pos) const override;
	int64_t shaped_text_next_grapheme_pos(const RID &p_shaped, int64_t p_pos) const override;
	int64_t shaped_text_prev_grapheme_pos(const RID &p_shaped, int64_t p_pos) const override;
	GDVIRTUAL2RC(Vector2, _shaped_text_get_grapheme_bounds, RID, int64_t);
	GDVIRTUAL2RC(int64_t, _shaped_text_next_grapheme_pos, RID, int64_t);
	GDVIRTUAL2RC(int64_t, _shaped_text_prev_grapheme_pos, RID, int64_t);

	PackedInt32Array shaped_text_get_character_breaks(const RID &p_shaped) const override;
	int64_t shaped_text_next_character_pos(const RID &p_shaped, int64_t p_pos) const override;
	int64_t shaped_text_prev_character_pos(const RID &p_shaped, int64_t p_pos) const override;
	int64_t shaped_text_closest_character_pos(const RID &p_shaped, int64_t p_pos) const override;
	GDVIRTUAL1RC(PackedInt32Array, _shaped_text_get_character_breaks, RID);
	GDVIRTUAL2RC(int64_t, _shaped_text_next_character_pos, RID, int64_t);
	GDVIRTUAL2RC(int64_t, _shaped_text_prev_character_pos, RID, int64_t);
	GDVIRTUAL2RC(int64_t, _shaped_text_closest_character_pos, RID, int64_t);

	String format_number(const String &p_string, const String &p_language = "") const override;
	String parse_number(const String &p_string, const String &p_language = "") const override;
	String percent_sign(const String &p_language = "") const override;
	GDVIRTUAL2RC(String, _format_number, const String &, const String &);
	GDVIRTUAL2RC(String, _parse_number, const String &, const String &);
	GDVIRTUAL1RC(String, _percent_sign, const String &);

	String strip_diacritics(const String &p_string) const override;
	GDVIRTUAL1RC(String, _strip_diacritics, const String &);

	PackedInt32Array string_get_word_breaks(const String &p_string, const String &p_language = "", int64_t p_chars_per_line = 0) const override;
	GDVIRTUAL3RC(PackedInt32Array, _string_get_word_breaks, const String &, const String &, int64_t);

	PackedInt32Array string_get_character_breaks(const String &p_string, const String &p_language = "") const override;
	GDVIRTUAL2RC(PackedInt32Array, _string_get_character_breaks, const String &, const String &);

	bool is_valid_identifier(const String &p_string) const override;
	GDVIRTUAL1RC(bool, _is_valid_identifier, const String &);
	bool is_valid_letter(uint64_t p_unicode) const override;
	GDVIRTUAL1RC(bool, _is_valid_letter, uint64_t);

	String string_to_upper(const String &p_string, const String &p_language = "") const override;
	String string_to_lower(const String &p_string, const String &p_language = "") const override;
	String string_to_title(const String &p_string, const String &p_language = "") const override;
	GDVIRTUAL2RC(String, _string_to_upper, const String &, const String &);
	GDVIRTUAL2RC(String, _string_to_lower, const String &, const String &);
	GDVIRTUAL2RC(String, _string_to_title, const String &, const String &);

	TypedArray<Vector3i> parse_structured_text(StructuredTextParser p_parser_type, const Array &p_args, const String &p_text) const;
	GDVIRTUAL3RC(TypedArray<Vector3i>, _parse_structured_text, StructuredTextParser, const Array &, const String &);

	int64_t is_confusable(const String &p_string, const PackedStringArray &p_dict) const override;
	bool spoof_check(const String &p_string) const override;
	GDVIRTUAL2RC(int64_t, _is_confusable, const String &, const PackedStringArray &);
	GDVIRTUAL1RC(bool, _spoof_check, const String &);

	void cleanup() override;
	GDVIRTUAL0(_cleanup);

	TextServerExtension();
	~TextServerExtension() override;
};

#endif // TEXT_SERVER_EXTENSION_H
