import os
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables, BoolVariable, EnumVariable


def exists(env: SConsEnvironment) -> bool:
    return os.name == "nt"


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    mingw = os.getenv("MINGW_PREFIX", "")

    # Direct3D 12 SDK dependencies folder.
    d3d12_deps_folder = os.getenv("LOCALAPPDATA")
    if d3d12_deps_folder:
        d3d12_deps_folder = os.path.join(d3d12_deps_folder, "Godot", "build_deps")
    else:
        # Cross-compiling, the deps install script puts things in `bin`.
        # Getting an absolute path to it is a bit hacky in Python.
        try:
            import inspect

            caller_frame = inspect.stack()[1]
            caller_script_dir = os.path.dirname(os.path.abspath(caller_frame[1]))
            d3d12_deps_folder = os.path.join(caller_script_dir, "bin", "build_deps")
        except Exception:  # Give up.
            d3d12_deps_folder = ""

    opts.AddVariables(
        ("mingw_prefix", "MinGW prefix", mingw),
        # Targeted Windows version: 7 (and later), minimum supported version
        # XP support dropped after EOL due to missing API for IPv6 and other issues
        # Vista support dropped after EOL due to GH-10243
        (
            "target_win_version",
            "Targeted Windows version, >= 0x0601 (Windows 7)",
            "0x0601",
        ),
        EnumVariable("windows_subsystem", "Windows subsystem", "gui", ("gui", "console")),
        (
            "msvc_version",
            "MSVC version to use. Ignored if VCINSTALLDIR is set in shell env.",
            None,
        ),
        BoolVariable("use_mingw", "Use the Mingw compiler, even if MSVC is installed.", False),
        BoolVariable("use_llvm", "Use the LLVM compiler", False),
        BoolVariable("use_static_cpp", "Link MinGW/MSVC C++ runtime libraries statically", True),
        BoolVariable("use_asan", "Use address sanitizer (ASAN)", False),
        BoolVariable("debug_crt", "Compile with MSVC's debug CRT (/MDd)", False),
        BoolVariable("incremental_link", "Use MSVC incremental linking. May increase or decrease build times.", False),
        BoolVariable("silence_msvc", "Silence MSVC's cl/link stdout bloat, redirecting any errors to stderr.", True),
        ("angle_libs", "Path to the ANGLE static libraries", ""),
        # Direct3D 12 support.
        (
            "mesa_libs",
            "Path to the MESA/NIR static libraries (required for D3D12)",
            os.path.join(d3d12_deps_folder, "mesa"),
        ),
        (
            "dxc_path",
            "Path to the DirectX Shader Compiler distribution (required for D3D12)",
            os.path.join(d3d12_deps_folder, "dxc"),
        ),
        (
            "agility_sdk_path",
            "Path to the Agility SDK distribution (optional for D3D12)",
            os.path.join(d3d12_deps_folder, "agility_sdk"),
        ),
        BoolVariable(
            "agility_sdk_multiarch",
            "Whether the Agility SDK DLLs will be stored in arch-specific subdirectories",
            False,
        ),
        BoolVariable("use_pix", "Use PIX (Performance tuning and debugging for DirectX 12) runtime", False),
        (
            "pix_path",
            "Path to the PIX runtime distribution (optional for D3D12)",
            os.path.join(d3d12_deps_folder, "pix"),
        ),
    )
