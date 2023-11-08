/**************************************************************************/
/*  dir_access_windows_registry.cpp                                       */
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

#include "dir_access_windows_registry.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

String DirAccessWindowsRegistry::fix_path(String p_path) const {
	return String();
}

Error DirAccessWindowsRegistry::list_dir_begin() {
	return Error();
}

String DirAccessWindowsRegistry::get_next() {
	return String();
}

bool DirAccessWindowsRegistry::current_is_dir() const {
	return false;
}

bool DirAccessWindowsRegistry::current_is_hidden() const {
	return false;
}

void DirAccessWindowsRegistry::list_dir_end() {
}

int DirAccessWindowsRegistry::get_drive_count() {
	return 0;
}

String DirAccessWindowsRegistry::get_drive(int p_drive) {
	return String();
}

Error DirAccessWindowsRegistry::change_dir(String p_dir) {
	return Error();
}

String DirAccessWindowsRegistry::get_current_dir(bool p_include_drive) const {
	return String();
}

bool DirAccessWindowsRegistry::file_exists(String p_file) {
	return false;
}

bool DirAccessWindowsRegistry::dir_exists(String p_dir) {
	return false;
}

Error DirAccessWindowsRegistry::make_dir(String p_dir) {
	return Error();
}

Error DirAccessWindowsRegistry::rename(String p_path, String p_new_path) {
	return Error();
}

Error DirAccessWindowsRegistry::remove(String p_path) {
	return Error();
}

uint64_t DirAccessWindowsRegistry::get_space_left() {
	return 0;
}

String DirAccessWindowsRegistry::get_filesystem_type() const {
	return String();
}

bool DirAccessWindowsRegistry::is_case_sensitive(const String &p_path) const {
	return false;
}

DirAccessWindowsRegistry::DirAccessWindowsRegistry() {
}

DirAccessWindowsRegistry::~DirAccessWindowsRegistry() {
}
