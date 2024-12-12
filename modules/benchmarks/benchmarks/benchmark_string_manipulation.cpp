/**************************************************************************/
/*  benchmark_string_manipulation.cpp                                     */
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

#include "benchmark_string_manipulation.h"

#ifdef GODOT_MODULE
#include "core/object/class_db.h"
#include "core/variant/variant_utility.h"

#define TO_STR VariantUtilityFunctions::var_to_str
#else
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#define TO_STR UtilityFunctions::str

using namespace godot;
#endif // GODOT_MODULE

void BenchmarkStringManipulation::_bind_methods() {
	ClassDB::bind_method(D_METHOD("benchmark_begins_with"), &BenchmarkStringManipulation::benchmark_begins_with);
	ClassDB::bind_method(D_METHOD("benchmark_ends_with"), &BenchmarkStringManipulation::benchmark_ends_with);
	ClassDB::bind_method(D_METHOD("benchmark_count"), &BenchmarkStringManipulation::benchmark_count);
	ClassDB::bind_method(D_METHOD("benchmark_countn"), &BenchmarkStringManipulation::benchmark_countn);
	ClassDB::bind_method(D_METHOD("benchmark_contains"), &BenchmarkStringManipulation::benchmark_contains);
	ClassDB::bind_method(D_METHOD("benchmark_find"), &BenchmarkStringManipulation::benchmark_find);
	ClassDB::bind_method(D_METHOD("benchmark_findn"), &BenchmarkStringManipulation::benchmark_findn);
	ClassDB::bind_method(D_METHOD("benchmark_rfind"), &BenchmarkStringManipulation::benchmark_rfind);
	ClassDB::bind_method(D_METHOD("benchmark_rfindn"), &BenchmarkStringManipulation::benchmark_rfindn);
	ClassDB::bind_method(D_METHOD("benchmark_substr"), &BenchmarkStringManipulation::benchmark_substr);
	ClassDB::bind_method(D_METHOD("benchmark_insert"), &BenchmarkStringManipulation::benchmark_insert);
	ClassDB::bind_method(D_METHOD("benchmark_get_slice"), &BenchmarkStringManipulation::benchmark_get_slice);
	ClassDB::bind_method(D_METHOD("benchmark_get_slice_count"), &BenchmarkStringManipulation::benchmark_get_slice_count);
	ClassDB::bind_method(D_METHOD("benchmark_bigrams"), &BenchmarkStringManipulation::benchmark_bigrams);
	ClassDB::bind_method(D_METHOD("benchmark_split"), &BenchmarkStringManipulation::benchmark_split);
	ClassDB::bind_method(D_METHOD("benchmark_rsplit"), &BenchmarkStringManipulation::benchmark_rsplit);
	ClassDB::bind_method(D_METHOD("benchmark_split_floats"), &BenchmarkStringManipulation::benchmark_split_floats);
	ClassDB::bind_method(D_METHOD("benchmark_pad_zeros_pre_constructed"), &BenchmarkStringManipulation::benchmark_pad_zeros_pre_constructed);
	ClassDB::bind_method(D_METHOD("benchmark_pad_zeros"), &BenchmarkStringManipulation::benchmark_pad_zeros);
	ClassDB::bind_method(D_METHOD("benchmark_pad_decimals_pre_constructed"), &BenchmarkStringManipulation::benchmark_pad_decimals_pre_constructed);
	ClassDB::bind_method(D_METHOD("benchmark_pad_decimals"), &BenchmarkStringManipulation::benchmark_pad_decimals);
	ClassDB::bind_method(D_METHOD("benchmark_lpad"), &BenchmarkStringManipulation::benchmark_lpad);
	ClassDB::bind_method(D_METHOD("benchmark_rpad"), &BenchmarkStringManipulation::benchmark_rpad);
	ClassDB::bind_method(D_METHOD("benchmark_similarity"), &BenchmarkStringManipulation::benchmark_similarity);
	ClassDB::bind_method(D_METHOD("benchmark_simplify_path"), &BenchmarkStringManipulation::benchmark_simplify_path);
	ClassDB::bind_method(D_METHOD("benchmark_capitalize"), &BenchmarkStringManipulation::benchmark_capitalize);
	ClassDB::bind_method(D_METHOD("benchmark_to_snake_case"), &BenchmarkStringManipulation::benchmark_to_snake_case);
	ClassDB::bind_method(D_METHOD("benchmark_to_camel_case"), &BenchmarkStringManipulation::benchmark_to_camel_case);
	ClassDB::bind_method(D_METHOD("benchmark_to_pascal_case"), &BenchmarkStringManipulation::benchmark_to_pascal_case);
	ClassDB::bind_method(D_METHOD("benchmark_to_lower"), &BenchmarkStringManipulation::benchmark_to_lower);
	ClassDB::bind_method(D_METHOD("benchmark_uri_decode"), &BenchmarkStringManipulation::benchmark_uri_decode);
	ClassDB::bind_method(D_METHOD("benchmark_uri_encode"), &BenchmarkStringManipulation::benchmark_uri_encode);
	ClassDB::bind_method(D_METHOD("benchmark_xml_escape"), &BenchmarkStringManipulation::benchmark_xml_escape);
	ClassDB::bind_method(D_METHOD("benchmark_xml_unescape"), &BenchmarkStringManipulation::benchmark_xml_unescape);
	ClassDB::bind_method(D_METHOD("benchmark_humanize_size"), &BenchmarkStringManipulation::benchmark_humanize_size);
	ClassDB::bind_method(D_METHOD("benchmark_is_valid_filename"), &BenchmarkStringManipulation::benchmark_is_valid_filename);
	ClassDB::bind_method(D_METHOD("benchmark_validate_filename"), &BenchmarkStringManipulation::benchmark_validate_filename);
	ClassDB::bind_method(D_METHOD("benchmark_validate_node_name"), &BenchmarkStringManipulation::benchmark_validate_node_name);
	ClassDB::bind_method(D_METHOD("benchmark_casecmp_to"), &BenchmarkStringManipulation::benchmark_casecmp_to);
	ClassDB::bind_method(D_METHOD("benchmark_nocasecmp_to"), &BenchmarkStringManipulation::benchmark_nocasecmp_to);
	ClassDB::bind_method(D_METHOD("benchmark_naturalnocasecmp_to"), &BenchmarkStringManipulation::benchmark_naturalnocasecmp_to);
	ClassDB::bind_method(D_METHOD("benchmark_to_utf8_buffer"), &BenchmarkStringManipulation::benchmark_to_utf8_buffer);
	ClassDB::bind_method(D_METHOD("benchmark_to_utf16_buffer"), &BenchmarkStringManipulation::benchmark_to_utf16_buffer);
	ClassDB::bind_method(D_METHOD("benchmark_to_utf32_buffer"), &BenchmarkStringManipulation::benchmark_to_utf32_buffer);
	ClassDB::bind_method(D_METHOD("benchmark_to_wchar_buffer"), &BenchmarkStringManipulation::benchmark_to_wchar_buffer);
}

void BenchmarkStringManipulation::benchmark_begins_with() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").begins_with("Godot"); // true
	}
}

void BenchmarkStringManipulation::benchmark_ends_with() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").ends_with("Engine"); // true
	}
}

void BenchmarkStringManipulation::benchmark_count() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").count("o"); // 2
	}
}

void BenchmarkStringManipulation::benchmark_countn() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").countn("o"); // 2
	}
}

void BenchmarkStringManipulation::benchmark_contains() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").contains("o"); // tr
	}
}

void BenchmarkStringManipulation::benchmark_find() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").find("o"); // 1
	}
}

void BenchmarkStringManipulation::benchmark_findn() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").findn("o"); // 1
	}
}

void BenchmarkStringManipulation::benchmark_rfind() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").rfind("o"); // 3
	}
}

void BenchmarkStringManipulation::benchmark_rfindn() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").rfindn("o"); // 3
	}
}

void BenchmarkStringManipulation::benchmark_substr() {
	for (int i = 0; i < iterations; i++) {
		String("Hello Godot!").substr(6, 5); // "Godot"
	}
}

void BenchmarkStringManipulation::benchmark_insert() {
	for (int i = 0; i < iterations; i++) {
		String("Hello !").insert(6, "Godot"); // "Hello Godot!"
	}
}

void BenchmarkStringManipulation::benchmark_get_slice() {
	for (int i = 0; i < iterations; i++) {
		String("1234,5678,90.12").get_slice(",", 1); // "5678"
	}
}

void BenchmarkStringManipulation::benchmark_get_slice_count() {
	for (int i = 0; i < iterations; i++) {
		String("1234,5678,90.12").get_slice_count(","); // 3
	}
}

void BenchmarkStringManipulation::benchmark_bigrams() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").bigrams(); // ["Go", "od", "do", "ot", "t ", " E", "En", "ng", "gi", "in", "ne"]
	}
}

void BenchmarkStringManipulation::benchmark_split() {
	for (int i = 0; i < iterations; i++) {
		String("1234,5678,90.12").split(","); //  ["1234", "5678", "90.12"]
	}
}

void BenchmarkStringManipulation::benchmark_rsplit() {
	for (int i = 0; i < iterations; i++) {
		String("1234,5678,90.12").rsplit(","); //  ["1234", "5678", "90.12"]
	}
}

void BenchmarkStringManipulation::benchmark_split_floats() {
	for (int i = 0; i < iterations; i++) {
		String("1234,5678,90.12").split_floats(","); //  [1234.0, 5678.0, 90.12]
	}
}

void BenchmarkStringManipulation::benchmark_pad_zeros_pre_constructed() {
	for (int i = 0; i < iterations; i++) {
		String("12345").pad_zeros(7); // "0012345"
	}
}

void BenchmarkStringManipulation::benchmark_pad_zeros() {
	for (int i = 0; i < iterations; i++) {
		TO_STR(12345).pad_zeros(7); // "0012345"
	}
}

void BenchmarkStringManipulation::benchmark_pad_decimals_pre_constructed() {
	for (int i = 0; i < iterations; i++) {
		String("1234.5678").pad_decimals(2); // "1234.56"
	}
}

void BenchmarkStringManipulation::benchmark_pad_decimals() {
	for (int i = 0; i < iterations; i++) {
		TO_STR(1234.5678).pad_decimals(2); // "1234.56"
	}
}

void BenchmarkStringManipulation::benchmark_lpad() {
	for (int i = 0; i < iterations; i++) {
		String("Godot").lpad(7, "+"); // "++Godot"
	}
}

void BenchmarkStringManipulation::benchmark_rpad() {
	for (int i = 0; i < iterations; i++) {
		String("Godot").rpad(7, "+"); // "Godot++"
	}
}

void BenchmarkStringManipulation::benchmark_similarity() {
	for (int i = 0; i < iterations; i++) {
		String("Godot").similarity("Engine");
	}
}

void BenchmarkStringManipulation::benchmark_simplify_path() {
	for (int i = 0; i < iterations; i++) {
		String("./path/to///../file").simplify_path(); // "path/file"
	}
}

void BenchmarkStringManipulation::benchmark_capitalize() {
	for (int i = 0; i < iterations; i++) {
		String("godot_engine_demo").capitalize(); // "Godot Engine Demo"
	}
}

void BenchmarkStringManipulation::benchmark_to_snake_case() {
	for (int i = 0; i < iterations; i++) {
		String("GodotEngineDemo").to_snake_case(); // "godot_engine_demo"
	}
}

void BenchmarkStringManipulation::benchmark_to_camel_case() {
	for (int i = 0; i < iterations; i++) {
		String("godot_engine_demo").to_snake_case(); // "godotEngineDemo"
	}
}

void BenchmarkStringManipulation::benchmark_to_pascal_case() {
	for (int i = 0; i < iterations; i++) {
		String("godot_engine_demo").to_pascal_case(); // "GodotEngineDemo"
	}
}

void BenchmarkStringManipulation::benchmark_to_lower() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine Demo").to_lower(); // "godot engine demo"
	}
}

void BenchmarkStringManipulation::benchmark_uri_decode() {
	for (int i = 0; i < iterations; i++) {
		String("Godot%20Engine%3Adocs").uri_decode(); // "Godot Engine:docs"
	}
}

void BenchmarkStringManipulation::benchmark_uri_encode() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine:docs").uri_encode(); // "Godot%20Engine%3Adocs"
	}
}

void BenchmarkStringManipulation::benchmark_xml_escape() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine <&>").xml_escape(); // "Godot Engine &lt;&amp;&gt;"
	}
}

void BenchmarkStringManipulation::benchmark_xml_unescape() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine &lt;&amp;&gt;").xml_unescape(); // "Godot Engine <&>"
	}
}

void BenchmarkStringManipulation::benchmark_humanize_size() {
	for (int i = 0; i < iterations; i++) {
		String::humanize_size(123456); // 120.5 KB
	}
}

void BenchmarkStringManipulation::benchmark_is_valid_filename() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine: Demo.exe").is_valid_filename(); // false
	}
}

void BenchmarkStringManipulation::benchmark_validate_filename() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine: Demo.exe").validate_filename(); // "Godot Engine_ Demo.exe"
	}
}

void BenchmarkStringManipulation::benchmark_validate_node_name() {
	for (int i = 0; i < iterations; i++) {
		String("TestNode:123456").validate_node_name(); // "TestNode123456"
	}
}

void BenchmarkStringManipulation::benchmark_casecmp_to() {
	for (int i = 0; i < iterations; i++) {
		String("2 Example").casecmp_to("10 Example"); // 1
	}
}

void BenchmarkStringManipulation::benchmark_nocasecmp_to() {
	for (int i = 0; i < iterations; i++) {
		String("2 Example").nocasecmp_to("10 Example"); // 1
	}
}

void BenchmarkStringManipulation::benchmark_naturalnocasecmp_to() {
	for (int i = 0; i < iterations; i++) {
		String("2 Example").naturalnocasecmp_to("10 Example"); // -1
	}
}

void BenchmarkStringManipulation::benchmark_to_utf8_buffer() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").to_utf8_buffer();
	}
}

void BenchmarkStringManipulation::benchmark_to_utf16_buffer() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").to_utf16_buffer();
	}
}

void BenchmarkStringManipulation::benchmark_to_utf32_buffer() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").to_utf32_buffer();
	}
}

void BenchmarkStringManipulation::benchmark_to_wchar_buffer() {
	for (int i = 0; i < iterations; i++) {
		String("Godot Engine").to_wchar_buffer();
	}
}

BenchmarkStringManipulation::BenchmarkStringManipulation() {}

BenchmarkStringManipulation::~BenchmarkStringManipulation() {}
