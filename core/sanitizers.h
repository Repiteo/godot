/**************************************************************************/
/*  sanitizers.h                                                          */
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

#pragma once

#include "core/typedefs.h"

#if !defined(_WIN32)
#define GD_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
#else
#define GD_VISIBILITY_HIDDEN
#endif

namespace Sanitizers {
GD_VISIBILITY_HIDDEN void persist_sanitizers();
} // namespace Sanitizers

#if defined(_WIN32)
#define GD_CDECL __cdecl
#else
#define GD_CDECL
#endif

#if defined(_MSC_VER) || defined(__MINGW32__)
#define GD_PERSIST __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
#define GD_PERSIST __attribute__((visibility("default")))
#else
#define GD_PERSIST
#endif

#if defined(ASAN_ENABLED)

extern "C" GD_CDECL GD_PERSIST const char *__asan_default_options();
extern "C" GD_CDECL GD_PERSIST const char *__asan_default_suppressions();

#endif // defined(ASAN_ENABLED)

#if defined(LSAN_ENABLED)

extern "C" GD_CDECL GD_PERSIST const char *__lsan_default_options();
extern "C" GD_CDECL GD_PERSIST const char *__lsan_default_suppressions();

#endif // defined(LSAN_ENABLED)

#if defined(MSAN_ENABLED)

extern "C" GD_CDECL GD_PERSIST const char *__msan_default_options();
// `__msan_default_suppressions()` does not exist.

#endif // defined(MSAN_ENABLED)

#if defined(TSAN_ENABLED)

extern "C" GD_CDECL GD_PERSIST const char *__tsan_default_options();
extern "C" GD_CDECL GD_PERSIST const char *__tsan_default_suppressions();

#endif // defined(TSAN_ENABLED)

#if defined(UBSAN_ENABLED)

extern "C" GD_CDECL GD_PERSIST const char *__ubsan_default_options();
extern "C" GD_CDECL GD_PERSIST const char *__ubsan_default_suppressions();

#endif // defined(UBSAN_ENABLED)
