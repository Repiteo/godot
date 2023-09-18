/**************************************************************************/
/*  usb_access.h                                                          */
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

#ifndef USB_ACCESS_H
#define USB_ACCESS_H

#include "core/object/ref_counted.h"

template <typename T>
class TypedArray;

/**
 * Multi-Platform abstraction for accessing usb devices.
 */

class USBAccess : public RefCounted {
	GDCLASS(USBAccess, RefCounted);

	uint16_t vendor_id;
	uint16_t product_id;

public:
	typedef Ref<USBAccess> (*CreateFunc)();

protected:
	static void _bind_methods();

private:
	static CreateFunc create_func; /** default file access creation function for a platform */
	template <class T>
	static Ref<USBAccess> _create_builtin() {
		return memnew(T);
	}

	thread_local static Error last_usb_open_error;
	static Ref<USBAccess> _open(uint16_t p_vendor_id, uint16_t p_product_id);

public:
	static Ref<USBAccess> open(uint16_t p_vendor_id, uint16_t p_product_id, Error *r_error = nullptr); /// Create a usb access (for the current platform) this is the only portable way of accessing usbs.
	static Error get_open_error() { return last_usb_open_error; }

	virtual Error open_internal() = 0;
	virtual void close() = 0;

	uint16_t get_vendor_id() const { return vendor_id; }
	uint16_t get_product_id() const { return product_id; }

	static TypedArray<Dictionary> get_ports();

	template <class T>
	static void make_default() {
		create_func = _create_builtin<T>;
	}

	USBAccess() {}
	virtual ~USBAccess() {}
};

#endif // USB_ACCESS_H
