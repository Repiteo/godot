/**************************************************************************/
/*  native_menu_windows.h                                                 */
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

#ifndef NATIVE_MENU_WINDOWS_H
#define NATIVE_MENU_WINDOWS_H

#include "core/templates/hash_map.h"
#include "core/templates/rid_owner.h"
#include "servers/display/native_menu.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class NativeMenuWindows : public NativeMenu {
	GDCLASS(NativeMenuWindows, NativeMenu)

	enum GlobalMenuCheckType {
		CHECKABLE_TYPE_NONE,
		CHECKABLE_TYPE_CHECK_BOX,
		CHECKABLE_TYPE_RADIO_BUTTON,
	};

	struct MenuItemData {
		Callable callback;
		Variant meta;
		GlobalMenuCheckType checkable_type;
		int max_states = 0;
		int state = 0;
		Ref<Image> img;
		HBITMAP bmp = 0;
	};

	struct MenuData {
		HMENU menu = 0;
		bool is_rtl = false;
	};

	mutable RID_PtrOwner<MenuData> menus;
	HashMap<HMENU, RID> menu_lookup;

	HBITMAP _make_bitmap(const Ref<Image> &p_img) const;

public:
	void _menu_activate(HMENU p_menu, int p_index) const;

	bool has_feature(Feature p_feature) const override;

	bool has_system_menu(SystemMenus p_menu_id) const override;
	RID get_system_menu(SystemMenus p_menu_id) const override;

	RID create_menu() override;
	bool has_menu(const RID &p_rid) const override;
	void free_menu(const RID &p_rid) override;

	Size2 get_size(const RID &p_rid) const override;
	void popup(const RID &p_rid, const Vector2i &p_position) override;

	void set_interface_direction(const RID &p_rid, bool p_is_rtl) override;
	void set_popup_open_callback(const RID &p_rid, const Callable &p_callback) override;
	Callable get_popup_open_callback(const RID &p_rid) const override;
	void set_popup_close_callback(const RID &p_rid, const Callable &p_callback) override;
	Callable get_popup_close_callback(const RID &p_rid) const override;
	void set_minimum_width(const RID &p_rid, float p_width) override;
	float get_minimum_width(const RID &p_rid) const override;

	bool is_opened(const RID &p_rid) const override;

	int add_submenu_item(const RID &p_rid, const String &p_label, const RID &p_submenu_rid, const Variant &p_tag = Variant(), int p_index = -1) override;
	int add_item(const RID &p_rid, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_check_item(const RID &p_rid, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_icon_item(const RID &p_rid, const Ref<Texture2D> &p_icon, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_icon_check_item(const RID &p_rid, const Ref<Texture2D> &p_icon, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_radio_check_item(const RID &p_rid, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_icon_radio_check_item(const RID &p_rid, const Ref<Texture2D> &p_icon, const String &p_label, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_multistate_item(const RID &p_rid, const String &p_label, int p_max_states, int p_default_state, const Callable &p_callback = Callable(), const Callable &p_key_callback = Callable(), const Variant &p_tag = Variant(), Key p_accel = Key::NONE, int p_index = -1) override;
	int add_separator(const RID &p_rid, int p_index = -1) override;

	int find_item_index_with_text(const RID &p_rid, const String &p_text) const override;
	int find_item_index_with_tag(const RID &p_rid, const Variant &p_tag) const override;

	bool is_item_checked(const RID &p_rid, int p_idx) const override;
	bool is_item_checkable(const RID &p_rid, int p_idx) const override;
	bool is_item_radio_checkable(const RID &p_rid, int p_idx) const override;
	Callable get_item_callback(const RID &p_rid, int p_idx) const override;
	Callable get_item_key_callback(const RID &p_rid, int p_idx) const override;
	Variant get_item_tag(const RID &p_rid, int p_idx) const override;
	String get_item_text(const RID &p_rid, int p_idx) const override;
	RID get_item_submenu(const RID &p_rid, int p_idx) const override;
	Key get_item_accelerator(const RID &p_rid, int p_idx) const override;
	bool is_item_disabled(const RID &p_rid, int p_idx) const override;
	bool is_item_hidden(const RID &p_rid, int p_idx) const override;
	String get_item_tooltip(const RID &p_rid, int p_idx) const override;
	int get_item_state(const RID &p_rid, int p_idx) const override;
	int get_item_max_states(const RID &p_rid, int p_idx) const override;
	Ref<Texture2D> get_item_icon(const RID &p_rid, int p_idx) const override;
	int get_item_indentation_level(const RID &p_rid, int p_idx) const override;

	void set_item_checked(const RID &p_rid, int p_idx, bool p_checked) override;
	void set_item_checkable(const RID &p_rid, int p_idx, bool p_checkable) override;
	void set_item_radio_checkable(const RID &p_rid, int p_idx, bool p_checkable) override;
	void set_item_callback(const RID &p_rid, int p_idx, const Callable &p_callback) override;
	void set_item_key_callback(const RID &p_rid, int p_idx, const Callable &p_key_callback) override;
	void set_item_hover_callbacks(const RID &p_rid, int p_idx, const Callable &p_callback) override;
	void set_item_tag(const RID &p_rid, int p_idx, const Variant &p_tag) override;
	void set_item_text(const RID &p_rid, int p_idx, const String &p_text) override;
	void set_item_submenu(const RID &p_rid, int p_idx, const RID &p_submenu_rid) override;
	void set_item_accelerator(const RID &p_rid, int p_idx, Key p_keycode) override;
	void set_item_disabled(const RID &p_rid, int p_idx, bool p_disabled) override;
	void set_item_hidden(const RID &p_rid, int p_idx, bool p_hidden) override;
	void set_item_tooltip(const RID &p_rid, int p_idx, const String &p_tooltip) override;
	void set_item_state(const RID &p_rid, int p_idx, int p_state) override;
	void set_item_max_states(const RID &p_rid, int p_idx, int p_max_states) override;
	void set_item_icon(const RID &p_rid, int p_idx, const Ref<Texture2D> &p_icon) override;
	void set_item_indentation_level(const RID &p_rid, int p_idx, int p_level) override;

	int get_item_count(const RID &p_rid) const override;
	bool is_system_menu(const RID &p_rid) const override;

	void remove_item(const RID &p_rid, int p_idx) override;
	void clear(const RID &p_rid) override;

	NativeMenuWindows();
	~NativeMenuWindows() override;
};

#endif // NATIVE_MENU_WINDOWS_H
