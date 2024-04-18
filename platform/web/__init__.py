from SCons.Util import WhereIs
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables, BoolVariable


def exists(env: SConsEnvironment) -> bool:
    return WhereIs("emcc") is not None


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    opts.AddVariables(
        ("initial_memory", "Initial WASM memory (in MiB)", 32),
        # Matches default values from before Emscripten 3.1.27. New defaults are too low for Godot.
        ("stack_size", "WASM stack size (in KiB)", 5120),
        ("default_pthread_stack_size", "WASM pthread default stack size (in KiB)", 2048),
        BoolVariable("use_assertions", "Use Emscripten runtime assertions", False),
        BoolVariable("use_ubsan", "Use Emscripten undefined behavior sanitizer (UBSAN)", False),
        BoolVariable("use_asan", "Use Emscripten address sanitizer (ASAN)", False),
        BoolVariable("use_lsan", "Use Emscripten leak sanitizer (LSAN)", False),
        BoolVariable("use_safe_heap", "Use Emscripten SAFE_HEAP sanitizer", False),
        # eval() can be a security concern, so it can be disabled.
        BoolVariable("javascript_eval", "Enable JavaScript eval interface", True),
        BoolVariable(
            "dlink_enabled", "Enable WebAssembly dynamic linking (GDExtension support). Produces bigger binaries", False
        ),
        BoolVariable("use_closure_compiler", "Use closure compiler to minimize JavaScript code", False),
        BoolVariable(
            "proxy_to_pthread",
            "Use Emscripten PROXY_TO_PTHREAD option to run the main application code to a separate thread",
            False,
        ),
    )
