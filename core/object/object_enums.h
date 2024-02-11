/**************************************************************************/
/*  object_enums.h                                                        */
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

#ifndef OBJECT_ENUMS_H
#define OBJECT_ENUMS_H

enum class PropertyHint {
	NONE, ///< no hint provided.
	RANGE, ///< hint_text = "min,max[,step][,or_greater][,or_less][,hide_slider][,radians_as_degrees][,degrees][,exp][,suffix:<keyword>] range.
	ENUM, ///< hint_text= "val1,val2,val3,etc"
	ENUM_SUGGESTION, ///< hint_text= "val1,val2,val3,etc"
	EXP_EASING, /// exponential easing function (Math::ease) use "attenuation" hint string to revert (flip h), "positive_only" to exclude in-out and out-in. (ie: "attenuation,positive_only")
	LINK,
	FLAGS, ///< hint_text= "flag1,flag2,etc" (as bit flags)
	LAYERS_2D_RENDER,
	LAYERS_2D_PHYSICS,
	LAYERS_2D_NAVIGATION,
	LAYERS_3D_RENDER,
	LAYERS_3D_PHYSICS,
	LAYERS_3D_NAVIGATION,
	FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	DIR, ///< a directory path must be passed
	GLOBAL_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	GLOBAL_DIR, ///< a directory path must be passed
	RESOURCE_TYPE, ///< a resource object type
	MULTILINE_TEXT, ///< used for string properties that can contain multiple lines
	EXPRESSION, ///< used for string properties that can contain multiple lines
	PLACEHOLDER_TEXT, ///< used to set a placeholder text for string properties
	COLOR_NO_ALPHA, ///< used for ignoring alpha component when editing a color
	OBJECT_ID,
	TYPE_STRING, ///< a type string, the hint is the base type to choose
	NODE_PATH_TO_EDITED_NODE, // Deprecated.
	OBJECT_TOO_BIG, ///< object is too big to send
	NODE_PATH_VALID_TYPES,
	SAVE_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,". This opens a save dialog
	GLOBAL_SAVE_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,". This opens a save dialog
	INT_IS_OBJECTID, // Deprecated.
	INT_IS_POINTER,
	ARRAY_TYPE,
	LOCALE_ID,
	LOCALIZABLE_STRING,
	NODE_TYPE, ///< a node object type
	HIDE_QUATERNION_EDIT, /// Only Node3D::transform should hide the quaternion editor.
	PASSWORD,
	LAYERS_AVOIDANCE,
	MAX,
};

enum class PropertyUsageFlags {
	NONE = 0,
	STORAGE = 1 << 1,
	EDITOR = 1 << 2,
	INTERNAL = 1 << 3,
	CHECKABLE = 1 << 4, // Used for editing global variables.
	CHECKED = 1 << 5, // Used for editing global variables.
	GROUP = 1 << 6, // Used for grouping props in the editor.
	CATEGORY = 1 << 7,
	SUBGROUP = 1 << 8,
	CLASS_IS_BITFIELD = 1 << 9,
	NO_INSTANCE_STATE = 1 << 10,
	RESTART_IF_CHANGED = 1 << 11,
	SCRIPT_VARIABLE = 1 << 12,
	STORE_IF_NULL = 1 << 13,
	UPDATE_ALL_IF_MODIFIED = 1 << 14,
	SCRIPT_DEFAULT_VALUE = 1 << 15, // Deprecated.
	CLASS_IS_ENUM = 1 << 16,
	NIL_IS_VARIANT = 1 << 17,
	ARRAY = 1 << 18, // Used in the inspector to group properties as elements of an array.
	ALWAYS_DUPLICATE = 1 << 19, // When duplicating a resource, always duplicate, even with subresource duplication disabled.
	NEVER_DUPLICATE = 1 << 20, // When duplicating a resource, never duplicate, even with subresource duplication enabled.
	HIGH_END_GFX = 1 << 21,
	NODE_PATH_FROM_SCENE_ROOT = 1 << 22,
	RESOURCE_NOT_PERSISTENT = 1 << 23,
	KEYING_INCREMENTS = 1 << 24, // Used in inspector to increment property when keyed in animation player.
	DEFERRED_SET_RESOURCE = 1 << 25, // Deprecated.
	EDITOR_INSTANTIATE_OBJECT = 1 << 26, // For Object properties, instantiate them when creating in editor.
	EDITOR_BASIC_SETTING = 1 << 27, //for project or editor settings, show when basic settings are selected.
	READ_ONLY = 1 << 28, // Mark a property as read-only in the inspector.
	SECRET = 1 << 29, // Export preset credentials that should be stored separately from the rest of the export config.

	DEFAULT = STORAGE | EDITOR,
	NO_EDITOR = STORAGE,
};

enum class MethodFlags {
	NORMAL = 1,
	EDITOR = 2,
	CONST = 4,
	VIRTUAL = 8,
	VARARG = 16,
	STATIC = 32,
	OBJECT_CORE = 64,
	DEFAULT = NORMAL,
};

#endif // OBJECT_ENUMS_H
