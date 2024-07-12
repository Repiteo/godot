/**************************************************************************/
/*  input_handler.h                                                       */
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

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "core/object/gdvirtual.gen.inc"
#include "core/object/ref_counted.h"

class InputHandler : public RefCounted {
	GDCLASS(InputHandler, RefCounted);

protected:
	static void _bind_methods();

	GDVIRTUAL0RC(String, _get_name);

public:
	virtual String get_name() const;

	[[nodiscard]] int claim_device();
	void release_device(int p_device);

	void set_device_button(int p_device, JoyButton p_button, bool p_pressed);
	void set_device_axis(int p_device, JoyAxis p_axis, float p_value);
	void set_device_hat(int p_device, BitField<HatMask> p_val);

	InputHandler();
	~InputHandler();
};

#endif // INPUT_HANDLER_H
