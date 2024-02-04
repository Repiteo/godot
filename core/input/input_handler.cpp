/**************************************************************************/
/*  input_handler.cpp                                                     */
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

#include "input_handler.h"

#include "core/input/input.h"
#include "core/string/ustring.h"

Input *input = Input::get_singleton();

void InputHandler::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_name"), &InputHandler::get_name);
	ClassDB::bind_method(D_METHOD("claim_device"), &InputHandler::claim_device);
	ClassDB::bind_method(D_METHOD("release_device", "device"), &InputHandler::release_device);
	ClassDB::bind_method(D_METHOD("set_device_button", "device", "button", "pressed"), &InputHandler::set_device_button);
	ClassDB::bind_method(D_METHOD("set_device_axis", "device", "axis", "value"), &InputHandler::set_device_axis);

	GDVIRTUAL_BIND(_get_name);
}

String InputHandler::get_name() const {
	String ret = "Unknown";
	GDVIRTUAL_REQUIRED_CALL(_get_name, ret);
	return ret;
}

int InputHandler::claim_device() {
	return input->_claim_device(this->get_instance_id());
}

void InputHandler::release_device(int p_device) {
	input->_release_device(this->get_instance_id(), p_device);
}

void InputHandler::set_device_button(int p_device, JoyButton p_button, bool p_pressed) {
	input->_set_device_button(this->get_instance_id(), p_device, p_button, p_pressed);
}

void InputHandler::set_device_axis(int p_device, JoyAxis p_axis, float p_value) {
	input->_set_device_axis(this->get_instance_id(), p_device, p_axis, p_value);
}

void InputHandler::set_device_hat(int p_device, BitField<HatMask> p_val) {
	input->_set_device_hat(this->get_instance_id(), p_device, p_val);
}

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}
