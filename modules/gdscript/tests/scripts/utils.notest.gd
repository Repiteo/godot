static func get_type(property: Dictionary, is_return: bool = false) -> String:
	match property.type:
		TYPE_NIL:
			if property.usage & PropertyUsageFlags::NIL_IS_VARIANT:
				return "Variant"
			return "void" if is_return else "null"
		TYPE_INT:
			if property.usage & PropertyUsageFlags::CLASS_IS_ENUM:
				if property.class_name == &"":
					return "<unknown enum>"
				return property.class_name
		TYPE_ARRAY:
			if property.hint == PropertyHint::ARRAY_TYPE:
				if str(property.hint_string).is_empty():
					return "Array[<unknown type>]"
				return "Array[%s]" % property.hint_string
		TYPE_OBJECT:
			if not str(property.class_name).is_empty():
				return property.class_name
	return type_string(property.type)


static func get_property_signature(property: Dictionary, is_static: bool = false) -> String:
	var result: String = ""
	if not (property.usage & PropertyUsageFlags::SCRIPT_VARIABLE):
		printerr("Missing `PropertyUsageFlags::SCRIPT_VARIABLE` flag.")
	if property.usage & PropertyUsageFlags::DEFAULT:
		result += "@export "
	if is_static:
		result += "static "
	result += "var " + property.name + ": " + get_type(property)
	return result


static func get_property_additional_info(property: Dictionary) -> String:
	return 'hint=%s hint_string="%s" usage=%s' % [
		get_property_hint_name(property.hint).trim_prefix("PROPERTY_HINT_"),
		str(property.hint_string).c_escape(),
		get_property_usage_string(property.usage).replace("PROPERTY_USAGE_", ""),
	]


static func get_method_signature(method: Dictionary, is_signal: bool = false) -> String:
	var result: String = ""
	if method.flags & MethodFlags::STATIC:
		result += "static "
	result += ("signal " if is_signal else "func ") + method.name + "("

	var args: Array[Dictionary] = method.args
	var default_args: Array = method.default_args
	var mandatory_argc: int = args.size() - default_args.size()
	for i in args.size():
		if i > 0:
			result += ", "
		var arg: Dictionary = args[i]
		result += arg.name + ": " + get_type(arg)
		if i >= mandatory_argc:
			result += " = " + var_to_str(default_args[i - mandatory_argc])

	result += ")"
	if is_signal:
		if get_type(method.return, true) != "void":
			printerr("Signal return type must be `void`.")
	else:
		result += " -> " + get_type(method.return, true)
	return result


static func get_property_hint_name(hint: PropertyHint) -> String:
	match hint:
		PropertyHint::NONE:
			return "PropertyHint::NONE"
		PropertyHint::RANGE:
			return "PropertyHint::RANGE"
		PropertyHint::ENUM:
			return "PropertyHint::ENUM"
		PropertyHint::ENUM_SUGGESTION:
			return "PropertyHint::ENUM_SUGGESTION"
		PropertyHint::EXP_EASING:
			return "PropertyHint::EXP_EASING"
		PropertyHint::LINK:
			return "PropertyHint::LINK"
		PropertyHint::FLAGS:
			return "PropertyHint::FLAGS"
		PropertyHint::LAYERS_2D_RENDER:
			return "PropertyHint::LAYERS_2D_RENDER"
		PropertyHint::LAYERS_2D_PHYSICS:
			return "PropertyHint::LAYERS_2D_PHYSICS"
		PropertyHint::LAYERS_2D_NAVIGATION:
			return "PropertyHint::LAYERS_2D_NAVIGATION"
		PropertyHint::LAYERS_3D_RENDER:
			return "PropertyHint::LAYERS_3D_RENDER"
		PropertyHint::LAYERS_3D_PHYSICS:
			return "PropertyHint::LAYERS_3D_PHYSICS"
		PropertyHint::LAYERS_3D_NAVIGATION:
			return "PropertyHint::LAYERS_3D_NAVIGATION"
		PropertyHint::LAYERS_AVOIDANCE:
			return "PropertyHint::LAYERS_AVOIDANCE"
		PropertyHint::FILE:
			return "PropertyHint::FILE"
		PropertyHint::DIR:
			return "PropertyHint::DIR"
		PropertyHint::GLOBAL_FILE:
			return "PropertyHint::GLOBAL_FILE"
		PropertyHint::GLOBAL_DIR:
			return "PropertyHint::GLOBAL_DIR"
		PropertyHint::RESOURCE_TYPE:
			return "PropertyHint::RESOURCE_TYPE"
		PropertyHint::MULTILINE_TEXT:
			return "PropertyHint::MULTILINE_TEXT"
		PropertyHint::EXPRESSION:
			return "PropertyHint::EXPRESSION"
		PropertyHint::PLACEHOLDER_TEXT:
			return "PropertyHint::PLACEHOLDER_TEXT"
		PropertyHint::COLOR_NO_ALPHA:
			return "PropertyHint::COLOR_NO_ALPHA"
		PropertyHint::OBJECT_ID:
			return "PropertyHint::OBJECT_ID"
		PropertyHint::TYPE_STRING:
			return "PropertyHint::TYPE_STRING"
		PropertyHint::NODE_PATH_TO_EDITED_NODE:
			return "PropertyHint::NODE_PATH_TO_EDITED_NODE"
		PropertyHint::OBJECT_TOO_BIG:
			return "PropertyHint::OBJECT_TOO_BIG"
		PropertyHint::NODE_PATH_VALID_TYPES:
			return "PropertyHint::NODE_PATH_VALID_TYPES"
		PropertyHint::SAVE_FILE:
			return "PropertyHint::SAVE_FILE"
		PropertyHint::GLOBAL_SAVE_FILE:
			return "PropertyHint::GLOBAL_SAVE_FILE"
		PropertyHint::INT_IS_OBJECTID:
			return "PropertyHint::INT_IS_OBJECTID"
		PropertyHint::INT_IS_POINTER:
			return "PropertyHint::INT_IS_POINTER"
		PropertyHint::ARRAY_TYPE:
			return "PropertyHint::ARRAY_TYPE"
		PropertyHint::LOCALE_ID:
			return "PropertyHint::LOCALE_ID"
		PropertyHint::LOCALIZABLE_STRING:
			return "PropertyHint::LOCALIZABLE_STRING"
		PropertyHint::NODE_TYPE:
			return "PropertyHint::NODE_TYPE"
		PropertyHint::HIDE_QUATERNION_EDIT:
			return "PropertyHint::HIDE_QUATERNION_EDIT"
		PropertyHint::PASSWORD:
			return "PropertyHint::PASSWORD"
	push_error("Argument `hint` is invalid. Use `PROPERTY_HINT_*` constants.")
	return "<invalid hint>"


static func get_property_usage_string(usage: int) -> String:
	if usage == PropertyUsageFlags::NONE:
		return "PropertyUsageFlags::NONE"

	const FLAGS: Array[Array] = [
		[PropertyUsageFlags::DEFAULT, "PropertyUsageFlags::DEFAULT"],
		[PropertyUsageFlags::STORAGE, "PropertyUsageFlags::STORAGE"],
		[PropertyUsageFlags::EDITOR, "PropertyUsageFlags::EDITOR"],
		[PropertyUsageFlags::INTERNAL, "PropertyUsageFlags::INTERNAL"],
		[PropertyUsageFlags::CHECKABLE, "PropertyUsageFlags::CHECKABLE"],
		[PropertyUsageFlags::CHECKED, "PropertyUsageFlags::CHECKED"],
		[PropertyUsageFlags::GROUP, "PropertyUsageFlags::GROUP"],
		[PropertyUsageFlags::CATEGORY, "PropertyUsageFlags::CATEGORY"],
		[PropertyUsageFlags::SUBGROUP, "PropertyUsageFlags::SUBGROUP"],
		[PropertyUsageFlags::CLASS_IS_BITFIELD, "PropertyUsageFlags::CLASS_IS_BITFIELD"],
		[PropertyUsageFlags::NO_INSTANCE_STATE, "PropertyUsageFlags::NO_INSTANCE_STATE"],
		[PropertyUsageFlags::RESTART_IF_CHANGED, "PropertyUsageFlags::RESTART_IF_CHANGED"],
		[PropertyUsageFlags::SCRIPT_VARIABLE, "PropertyUsageFlags::SCRIPT_VARIABLE"],
		[PropertyUsageFlags::STORE_IF_NULL, "PropertyUsageFlags::STORE_IF_NULL"],
		[PropertyUsageFlags::UPDATE_ALL_IF_MODIFIED, "PropertyUsageFlags::UPDATE_ALL_IF_MODIFIED"],
		[PropertyUsageFlags::SCRIPT_DEFAULT_VALUE, "PropertyUsageFlags::SCRIPT_DEFAULT_VALUE"],
		[PropertyUsageFlags::CLASS_IS_ENUM, "PropertyUsageFlags::CLASS_IS_ENUM"],
		[PropertyUsageFlags::NIL_IS_VARIANT, "PropertyUsageFlags::NIL_IS_VARIANT"],
		[PropertyUsageFlags::ARRAY, "PropertyUsageFlags::ARRAY"],
		[PropertyUsageFlags::ALWAYS_DUPLICATE, "PropertyUsageFlags::ALWAYS_DUPLICATE"],
		[PropertyUsageFlags::NEVER_DUPLICATE, "PropertyUsageFlags::NEVER_DUPLICATE"],
		[PropertyUsageFlags::HIGH_END_GFX, "PropertyUsageFlags::HIGH_END_GFX"],
		[PropertyUsageFlags::NODE_PATH_FROM_SCENE_ROOT, "PropertyUsageFlags::NODE_PATH_FROM_SCENE_ROOT"],
		[PropertyUsageFlags::RESOURCE_NOT_PERSISTENT, "PropertyUsageFlags::RESOURCE_NOT_PERSISTENT"],
		[PropertyUsageFlags::KEYING_INCREMENTS, "PropertyUsageFlags::KEYING_INCREMENTS"],
		[PropertyUsageFlags::DEFERRED_SET_RESOURCE, "PropertyUsageFlags::DEFERRED_SET_RESOURCE"],
		[PropertyUsageFlags::EDITOR_INSTANTIATE_OBJECT, "PropertyUsageFlags::EDITOR_INSTANTIATE_OBJECT"],
		[PropertyUsageFlags::EDITOR_BASIC_SETTING, "PropertyUsageFlags::EDITOR_BASIC_SETTING"],
		[PropertyUsageFlags::READ_ONLY, "PropertyUsageFlags::READ_ONLY"],
		[PropertyUsageFlags::SECRET, "PropertyUsageFlags::SECRET"],
	]

	var result: String = ""

	for flag in FLAGS:
		if usage & flag[0]:
			result += flag[1] + "|"
			usage &= ~flag[0]

	if usage != PropertyUsageFlags::NONE:
		push_error("Argument `usage` is invalid. Use `PROPERTY_USAGE_*` constants.")
		return "<invalid usage flags>"

	return result.left(-1)
