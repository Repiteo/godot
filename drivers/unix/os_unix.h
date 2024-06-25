/**************************************************************************/
/*  os_unix.h                                                             */
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

#ifndef OS_UNIX_H
#define OS_UNIX_H

#ifdef UNIX_ENABLED

#include "core/os/os.h"
#include "drivers/unix/ip_unix.h"

class OS_Unix : public OS {
	struct ProcessInfo {
		mutable bool is_running = true;
		mutable int exit_code = -1;
	};
	HashMap<ProcessID, ProcessInfo> *process_map = nullptr;
	Mutex process_map_mutex;

protected:
	// UNIX only handles the core functions.
	// inheriting platforms under unix (eg. X11) should handle the rest

	virtual void initialize_core();
	virtual int unix_initialize_audio(int p_audio_driver);

	void finalize_core() override;

public:
	OS_Unix();

	Vector<String> get_video_adapter_driver_info() const override;

	String get_stdin_string() override;

	Error get_entropy(uint8_t *r_buffer, int p_bytes) override;

	Error open_dynamic_library(const String &p_path, void *&p_library_handle, GDExtensionData *p_data = nullptr) override;
	Error close_dynamic_library(void *p_library_handle) override;
	Error get_dynamic_library_symbol_handle(void *p_library_handle, const String &p_name, void *&p_symbol_handle, bool p_optional = false) override;

	Error set_cwd(const String &p_cwd) override;

	String get_name() const override;
	String get_distribution_name() const override;
	String get_version() const override;

	DateTime get_datetime(bool p_utc) const override;
	TimeZoneInfo get_time_zone_info() const override;

	double get_unix_time() const override;

	void delay_usec(uint32_t p_usec) const override;
	uint64_t get_ticks_usec() const override;

	Dictionary get_memory_info() const override;

	Error execute(const String &p_path, const List<String> &p_arguments, String *r_pipe = nullptr, int *r_exitcode = nullptr, bool read_stderr = false, Mutex *p_pipe_mutex = nullptr, bool p_open_console = false) override;
	Dictionary execute_with_pipe(const String &p_path, const List<String> &p_arguments) override;
	Error create_process(const String &p_path, const List<String> &p_arguments, ProcessID *r_child_id = nullptr, bool p_open_console = false) override;
	Error kill(const ProcessID &p_pid) override;
	int get_process_id() const override;
	bool is_process_running(const ProcessID &p_pid) const override;
	int get_process_exit_code(const ProcessID &p_pid) const override;

	bool has_environment(const String &p_var) const override;
	String get_environment(const String &p_var) const override;
	void set_environment(const String &p_var, const String &p_value) const override;
	void unset_environment(const String &p_var) const override;

	String get_locale() const override;

	void initialize_debugging() override;

	String get_executable_path() const override;
	String get_user_data_dir() const override;
};

class UnixTerminalLogger : public StdLogger {
public:
	void log_error(const char *p_function, const char *p_file, int p_line, const char *p_code, const char *p_rationale, bool p_editor_notify = false, ErrorType p_type = ERR_ERROR) override;
	~UnixTerminalLogger() override;
};

#endif // UNIX_ENABLED

#endif // OS_UNIX_H
