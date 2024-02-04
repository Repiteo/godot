/**************************************************************************/
/*  error_list.cpp                                                        */
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

#include "error_list.h"

const char *error_names[] = {
	"OK", // OK
	"Failed", // FAILED
	"Unavailable", // UNAVAILABLE
	"Unconfigured", // UNCONFIGURED
	"Unauthorized", // UNAUTHORIZED
	"Parameter out of range", // PARAMETER_RANGE_ERROR
	"Out of memory", // OUT_OF_MEMORY
	"File not found", // FILE_NOT_FOUND
	"File: Bad drive", // FILE_BAD_DRIVE
	"File: Bad path", // FILE_BAD_PATH
	"File: Permission denied", // FILE_NO_PERMISSION
	"File already in use", // FILE_ALREADY_IN_USE
	"Can't open file", // FILE_CANT_OPEN
	"Can't write file", // FILE_CANT_WRITE
	"Can't read file", // FILE_CANT_READ
	"File unrecognized", // FILE_UNRECOGNIZED
	"File corrupt", // FILE_CORRUPT
	"Missing dependencies for file", // FILE_MISSING_DEPENDENCIES
	"End of file", // FILE_EOF
	"Can't open", // CANT_OPEN
	"Can't create", // CANT_CREATE
	"Query failed", // QUERY_FAILED
	"Already in use", // ALREADY_IN_USE
	"Locked", // LOCKED
	"Timeout", // TIMEOUT
	"Can't connect", // CANT_CONNECT
	"Can't resolve", // CANT_RESOLVE
	"Connection error", // CONNECTION_ERROR
	"Can't acquire resource", // CANT_ACQUIRE_RESOURCE
	"Can't fork", // CANT_FORK
	"Invalid data", // INVALID_DATA
	"Invalid parameter", // INVALID_PARAMETER
	"Already exists", // ALREADY_EXISTS
	"Does not exist", // DOES_NOT_EXIST
	"Can't read database", // DATABASE_CANT_READ
	"Can't write database", // DATABASE_CANT_WRITE
	"Compilation failed", // COMPILATION_FAILED
	"Method not found", // METHOD_NOT_FOUND
	"Link failed", // LINK_FAILED
	"Script failed", // SCRIPT_FAILED
	"Cyclic link detected", // CYCLIC_LINK
	"Invalid declaration", // INVALID_DECLARATION
	"Duplicate symbol", // DUPLICATE_SYMBOL
	"Parse error", // PARSE_ERROR
	"Busy", // BUSY
	"Skip", // SKIP
	"Help", // HELP
	"Bug", // BUG
	"Printer on fire", // PRINTER_ON_FIRE
};

static_assert(sizeof(error_names) / sizeof(*error_names) == (int)Error::MAX);
