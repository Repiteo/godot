/**************************************************************************/
/*  dir_access_unix.h                                                     */
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

#ifndef DIR_ACCESS_UNIX_H
#define DIR_ACCESS_UNIX_H

#if defined(UNIX_ENABLED)

#include "core/io/dir_access.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class DirAccessUnix : public DirAccess {
	DIR *dir_stream = nullptr;

	bool _cisdir = false;
	bool _cishidden = false;

protected:
	String current_dir;
	virtual String fix_unicode_name(const char *p_name) const { return String::utf8(p_name); }
	virtual bool is_hidden(const String &p_name);

public:
	Error list_dir_begin() override; ///< This starts dir listing
	String get_next() override;
	bool current_is_dir() const override;
	bool current_is_hidden() const override;

	void list_dir_end() override; ///<

	int get_drive_count() override;
	String get_drive(int p_drive) override;
	int get_current_drive() override;
	bool drives_are_shortcuts() override;

	Error change_dir(String p_dir) override; ///< can be relative or absolute, return false on success
	String get_current_dir(bool p_include_drive = true) const override; ///< return current dir location
	Error make_dir(String p_dir) override;

	bool file_exists(String p_file) override;
	bool dir_exists(String p_dir) override;
	bool is_readable(String p_dir) override;
	bool is_writable(String p_dir) override;

	virtual uint64_t get_modified_time(String p_file);

	Error rename(String p_path, String p_new_path) override;
	Error remove(String p_path) override;

	bool is_link(String p_file) override;
	String read_link(String p_file) override;
	Error create_link(String p_source, String p_target) override;

	bool is_case_sensitive(const String &p_path) const override;

	uint64_t get_space_left() override;

	String get_filesystem_type() const override;

	DirAccessUnix();
	~DirAccessUnix() override;
};

#endif // UNIX_ENABLED

#endif // DIR_ACCESS_UNIX_H
