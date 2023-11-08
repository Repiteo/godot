/**************************************************************************/
/*  file_access_windows_registry.cpp                                      */
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

#include "file_access_windows_registry.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

String FileAccessWindowsRegistry::fix_path(const String &p_path) const {
	return String();
}

Error FileAccessWindowsRegistry::open_internal(const String &p_path, int p_mode_flags) {
	return Error();
}

bool FileAccessWindowsRegistry::is_open() const {
	return false;
}

String FileAccessWindowsRegistry::get_path() const {
	return String();
}

String FileAccessWindowsRegistry::get_path_absolute() const {
	return String();
}

void FileAccessWindowsRegistry::seek(uint64_t p_position) {
}

void FileAccessWindowsRegistry::seek_end(int64_t p_position) {
}

uint64_t FileAccessWindowsRegistry::get_position() const {
	return 0;
}

uint64_t FileAccessWindowsRegistry::get_length() const {
	return 0;
}

bool FileAccessWindowsRegistry::eof_reached() const {
	return false;
}

uint8_t FileAccessWindowsRegistry::get_8() const {
	return 0;
}

uint64_t FileAccessWindowsRegistry::get_buffer(uint8_t *p_dst, uint64_t p_length) const {
	return 0;
}

Error FileAccessWindowsRegistry::get_error() const {
	return Error();
}

void FileAccessWindowsRegistry::flush() {
}

void FileAccessWindowsRegistry::store_8(uint8_t p_dest) {
}

void FileAccessWindowsRegistry::store_buffer(const uint8_t *p_src, uint64_t p_length) {
}

bool FileAccessWindowsRegistry::file_exists(const String &p_name) {
	return false;
}

uint64_t FileAccessWindowsRegistry::_get_modified_time(const String &p_file) {
	return 0;
}

BitField<FileAccess::UnixPermissionFlags> FileAccessWindowsRegistry::_get_unix_permissions(const String &p_file) {
	return BitField<FileAccess::UnixPermissionFlags>();
}

Error FileAccessWindowsRegistry::_set_unix_permissions(const String &p_file, BitField<FileAccess::UnixPermissionFlags> p_permissions) {
	return Error();
}

bool FileAccessWindowsRegistry::_get_hidden_attribute(const String &p_file) {
	return false;
}

Error FileAccessWindowsRegistry::_set_hidden_attribute(const String &p_file, bool p_hidden) {
	return Error();
}

bool FileAccessWindowsRegistry::_get_read_only_attribute(const String &p_file) {
	return false;
}

Error FileAccessWindowsRegistry::_set_read_only_attribute(const String &p_file, bool p_ro) {
	return Error();
}

void FileAccessWindowsRegistry::_close() {
}

void FileAccessWindowsRegistry::close() {
	_close();
}

FileAccessWindowsRegistry::~FileAccessWindowsRegistry() {
	_close();
}
