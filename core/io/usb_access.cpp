/**************************************************************************/
/*  usb_access.cpp                                                        */
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

#include "usb_access.h"

#include "core/variant/typed_array.h"

USBAccess::CreateFunc USBAccess::create_func = nullptr;

thread_local Error USBAccess::last_usb_open_error = OK;

Ref<USBAccess> USBAccess::_open(uint16_t p_vendor, uint16_t p_product) {
	Error err = OK;
	Ref<USBAccess> ua = open(p_vendor, p_product, &err);
	last_usb_open_error = err;
	if (err) {
		return Ref<USBAccess>();
	}
	return ua;
}

Ref<USBAccess> USBAccess::open(uint16_t p_vendor, uint16_t p_product, Error *r_error) {
	Ref<USBAccess> ret = create_func();
	ret->vendor_id = p_vendor;
	ret->product_id = p_product;

	Error err = ret->open_internal();

	if (r_error) {
		*r_error = err;
	}
	if (err != OK) {
		ret.unref();
	}

	return ret;
}

TypedArray<Dictionary> USBAccess::get_ports() {
	return TypedArray<Dictionary>();
}

void USBAccess::_bind_methods() {
	ClassDB::bind_static_method("USBAccess", D_METHOD("open", "vendor_id", "product_id"), &USBAccess::_open);
	ClassDB::bind_static_method("USBAccess", D_METHOD("get_open_error"), &USBAccess::get_open_error);

	ClassDB::bind_method(D_METHOD("close"), &USBAccess::close);

	ClassDB::bind_static_method("USBAccess", D_METHOD("get_ports"), &USBAccess::get_ports);

	ClassDB::bind_method(D_METHOD("get_vendor_id"), &USBAccess::get_vendor_id);
	ClassDB::bind_method(D_METHOD("get_product_id"), &USBAccess::get_product_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "vendor_id"), "", "get_vendor_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "product_id"), "", "get_product_id");
}
