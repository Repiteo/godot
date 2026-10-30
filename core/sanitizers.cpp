/**************************************************************************/
/*  sanitizers.cpp                                                        */
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

#include "core/typedefs.h"

#if defined(ASAN_ENABLED)

#include <sanitizer/asan_interface.h>

extern "C" const char *__asan_default_options() {
	return "color=always:"
		   "print_suppressions=1:"
		   "alloc_dealloc_mismatch=0";
}

extern "C" const char *__asan_default_suppressions() {
	// Supported suppression types are:
	// - interceptor_name
	// - interceptor_via_fun
	// - interceptor_via_lib
	// - odr_violation

	return "";
}

#endif // defined(ASAN_ENABLED)

#if defined(LSAN_ENABLED)

#include <sanitizer/lsan_interface.h>

extern "C" const char *__lsan_default_options() {
	return "color=always:"
		   "print_suppressions=1";
}

extern "C" const char *__lsan_default_suppressions() {
	// Supported suppression types are:
	// - leak

	return "";
}

#endif // defined(LSAN_ENABLED)

#if defined(MSAN_ENABLED)

#include <sanitizer/msan_interface.h>

extern "C" const char *__msan_default_options() {
	return "color=always:"
		   "print_suppressions=1";
}

// `__msan_default_suppressions()` does not exist.

#endif // defined(MSAN_ENABLED)

#if defined(TSAN_ENABLED)

#include <sanitizer/tsan_interface.h>

extern "C" const char *__tsan_default_options() {
	return "color=always:"
		   "print_suppressions=1";
}

extern "C" const char *__tsan_default_suppressions() {
	// See the below link for an explanation of this file's format.
	// https://github.com/google/sanitizers/wiki/ThreadSanitizerSuppressions

	return "deadlock:modules/text_server_adv/text_server_adv.cpp\n"
		   "deadlock:modules/text_server_fb/text_server_fb.cpp\n"
		   "deadlock:tests/core/templates/test_command_queue.cpp\n"
		   "race:modules/navigation_2d/nav_map_2d.cpp\n"
		   "race:modules/navigation_3d/nav_map_3d.cpp\n"
		   "race:thirdparty/thorvg/src/loaders/external_jpg/tvgJpgLoader.cpp\n";
}

#endif // defined(TSAN_ENABLED)

#if defined(UBSAN_ENABLED)

#include <sanitizer/ubsan_interface.h>

extern "C" const char *__tsan_default_options() {
	return "color=always:"
		   "print_suppressions=1";
}

extern "C" const char *__tsan_default_suppressions() {
	// See the below link for an explanation of this file's format.
	// https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#available-checks

	return "bounds:thirdparty/harfbuzz/src/hb-open-type.hh\n"
		   "bounds:thirdparty/harfbuzz/src/OT/Layout/GPOS/../../../hb-ot-layout-gsubgpos.hh\n"
		   "bounds:thirdparty/harfbuzz/src/OT/Layout/GSUB/LigatureSet.hh\n"
		   "bounds:thirdparty/harfbuzz/src/OT/name/../../hb-open-type.hh\n"
		   "bounds:thirdparty/icu4c/common/rbbi.cpp\n"
		   "enum:thirdparty/glslang/SPIRV/spirv.hpp\n"
		   "float-divide-by-zero:thirdparty/amd-fsr2/ffx_fsr2.cpp\n"
		   "float-divide-by-zero:thirdparty/misc/ok_color.h\n"
		   "float-divide-by-zero:thirdparty/rvo2/rvo2_2d/Agent2d.cpp\n"
		   "float-divide-by-zero:thirdparty/thorvg/src/renderer/cpu_engine/tvgSwFill.cpp\n"
		   "float-divide-by-zero:thirdparty/thorvg/src/renderer/tvgText.h\n"
		   "function:thirdparty/embree/common/sys/thread.cpp\n"
		   "function:thirdparty/embree/kernels/common/accel.h\n"
		   "function:thirdparty/xatlas/xatlas.cpp\n"
		   "implicit-integer-sign-change:MachineIndependent/glslang.y\n"
		   "implicit-integer-sign-change:thirdparty/basis_universal/encoder/jpgd.cpp\n"
		   "implicit-integer-sign-change:thirdparty/basis_universal/transcoder/basisu_astc_helpers.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/common/lexers/../sys/ref.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/common/lexers/tokenstream.cpp\n"
		   "implicit-integer-sign-change:thirdparty/embree/common/sys/sysinfo.cpp\n"
		   "implicit-integer-sign-change:thirdparty/embree/common/tasking/taskschedulerinternal.cpp\n"
		   "implicit-integer-sign-change:thirdparty/embree/common/tasking/taskschedulerinternal.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/kernels/bvh/../common/../../common/sys/../math/../simd/vfloat4_sse2.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/kernels/bvh/../common/../../common/sys/../math/../simd/vuint4_sse2.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/kernels/bvh/../common/../builders/primref.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/kernels/bvh/../common/vector.h\n"
		   "implicit-integer-sign-change:thirdparty/embree/kernels/bvh/../geometry/triangle.h\n"
		   "implicit-integer-sign-change:thirdparty/etcpak/ProcessDxtc.cpp\n"
		   "implicit-integer-sign-change:thirdparty/glslang/glslang/MachineIndependent/ParseHelper.cpp\n"
		   "implicit-integer-sign-change:thirdparty/glslang/glslang/MachineIndependent/preprocessor/PpScanner.cpp\n"
		   "implicit-integer-sign-change:thirdparty/glslang/glslang/MachineIndependent/preprocessor/PpTokens.cpp\n"
		   "implicit-integer-sign-change:thirdparty/glslang/glslang/MachineIndependent/Versions.cpp\n"
		   "implicit-integer-sign-change:thirdparty/glslang/SPIRV/hex_float.h\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-algs.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-buffer.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-cache.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-face.cc\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-face.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/hb-ot-layout-gsubgpos.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/OT/Layout/GDEF/../../../hb-cache.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/OT/Layout/GPOS/../../../hb-ot-layout-gsubgpos.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/OT/Layout/GPOS/../../../OT/Layout/GDEF/../../../hb-cache.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/OT/Layout/GSUB/../../../hb-ot-layout-gsubgpos.hh\n"
		   "implicit-integer-sign-change:thirdparty/harfbuzz/src/OT/name/name.hh\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/bmpset.cpp\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/ubidiln.cpp\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/unicode/unistr.h\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/unistr.cpp\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/uresbund.cpp\n"
		   "implicit-integer-sign-change:thirdparty/icu4c/common/ustrtrns.cpp\n"
		   "implicit-integer-sign-change:thirdparty/libjpeg-turbo/src/jcdctmgr.c\n"
		   "implicit-integer-sign-change:thirdparty/libjpeg-turbo/src/jdarith.c\n"
		   "implicit-integer-sign-change:thirdparty/libjpeg-turbo/src/jdhuff.c\n"
		   "implicit-integer-sign-change:thirdparty/libogg/bitwise.c\n"
		   "implicit-integer-sign-change:thirdparty/libvorbis/info.c\n"
		   "implicit-integer-sign-change:thirdparty/libvorbis/sharedbook.c\n"
		   "implicit-integer-sign-change:thirdparty/manifold/src/impl.h\n"
		   "implicit-integer-sign-change:thirdparty/mbedtls/library/base64.c\n"
		   "implicit-integer-sign-change:thirdparty/misc/smolv.cpp\n"
		   "implicit-integer-sign-change:thirdparty/recastnavigation/Recast/Include/Recast.h\n"
		   "implicit-integer-sign-change:thirdparty/recastnavigation/Recast/Source/RecastMesh.cpp\n"
		   "implicit-integer-sign-change:thirdparty/sdl/SDL_guid.c\n"
		   "implicit-integer-sign-change:thirdparty/spirv-reflect/spirv_reflect.c\n"
		   "implicit-integer-sign-change:thirdparty/thorvg/src/common/tvgCompressor.cpp\n"
		   "implicit-integer-sign-change:thirdparty/thorvg/src/renderer/cpu_engine/tvgSwRaster.cpp\n"
		   "implicit-integer-sign-change:thirdparty/tinyexr/tinyexr.h\n"
		   "implicit-integer-sign-change:thirdparty/vulkan/vk_mem_alloc.h\n"
		   "implicit-integer-sign-change:thirdparty/xatlas/xatlas.cpp\n"
		   "implicit-integer-sign-change:thirdparty/zlib/trees.c\n"
		   "implicit-integer-sign-change:thirdparty/zstd/compress/zstd_cwksp.h\n"
		   "nonnull-attribute:thirdparty/spirv-reflect/spirv_reflect.c\n"
		   "pointer-overflow:thirdparty/libogg/framing.c\n"
		   "shift-base:thirdparty/libogg/bitwise.c\n"
		   "shift-base:thirdparty/libvorbis/sharedbook.c\n"
		   "shift-base:thirdparty/misc/FastNoiseLite.h\n"
		   "shift-base:thirdparty/tinyexr/tinyexr.h\n"
		   "signed-integer-overflow:thirdparty/misc/FastNoiseLite.h\n";
}

#endif // defined(UBSAN_ENABLED)
