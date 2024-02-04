/**************************************************************************/
/*  error_list.h                                                          */
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

#ifndef ERROR_LIST_H
#define ERROR_LIST_H

/** Error List. Please never compare an error against Error::FAILED
 * Either do result != Error::OK , or !result. This way, Error fail
 * values can be more detailed in the future.
 *
 * This is a generic error list, mainly for organizing a language of returning errors.
 *
 * Errors:
 * - Are added to the Error enum in core/error/error_list.h
 * - Have a description added to error_names in core/error/error_list.cpp
 * - Are bound with BIND_CORE_ENUM_CONSTANT() in core/core_constants.cpp
 */

enum class Error {
	OK, // (0)
	FAILED, ///< Generic fail error
	UNAVAILABLE, ///< What is requested is unsupported/unavailable
	UNCONFIGURED, ///< The object being used hasn't been properly set up yet
	UNAUTHORIZED, ///< Missing credentials for requested resource
	PARAMETER_RANGE_ERROR, ///< Parameter given out of range (5)
	OUT_OF_MEMORY, ///< Out of memory
	FILE_NOT_FOUND,
	FILE_BAD_DRIVE,
	FILE_BAD_PATH,
	FILE_NO_PERMISSION, // (10)
	FILE_ALREADY_IN_USE,
	FILE_CANT_OPEN,
	FILE_CANT_WRITE,
	FILE_CANT_READ,
	FILE_UNRECOGNIZED, // (15)
	FILE_CORRUPT,
	FILE_MISSING_DEPENDENCIES,
	FILE_EOF,
	CANT_OPEN, ///< Can't open a resource/socket/file
	CANT_CREATE, // (20)
	QUERY_FAILED,
	ALREADY_IN_USE,
	LOCKED, ///< resource is locked
	TIMEOUT,
	CANT_CONNECT, // (25)
	CANT_RESOLVE,
	CONNECTION_ERROR,
	CANT_ACQUIRE_RESOURCE,
	CANT_FORK,
	INVALID_DATA, ///< Data passed is invalid (30)
	INVALID_PARAMETER, ///< Parameter passed is invalid
	ALREADY_EXISTS, ///< When adding, item already exists
	DOES_NOT_EXIST, ///< When retrieving/erasing, if item does not exist
	DATABASE_CANT_READ, ///< database is full
	DATABASE_CANT_WRITE, ///< database is full (35)
	COMPILATION_FAILED,
	METHOD_NOT_FOUND,
	LINK_FAILED,
	SCRIPT_FAILED,
	CYCLIC_LINK, // (40)
	INVALID_DECLARATION,
	DUPLICATE_SYMBOL,
	PARSE_ERROR,
	BUSY,
	SKIP, // (45)
	HELP, ///< user requested help!!
	BUG, ///< a bug in the software certainly happened, due to a double check failing or unexpected behavior.
	PRINTER_ON_FIRE, /// the parallel port printer is engulfed in flames
	MAX, // Not being returned, value represents the number of errors
};

extern const char *error_names[];

#endif // ERROR_LIST_H
