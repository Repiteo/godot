import os
import sys
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables, BoolVariable, EnumVariable


def exists(env: SConsEnvironment) -> bool:
    return os.name == "posix" and sys.platform != "darwin"

    # pkgconf_error = os.system("pkg-config --version > /dev/null")
    # if pkgconf_error:
    #     print("Error: pkg-config not found. Aborting.")
    #     return False


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    opts.AddVariables(
        EnumVariable("linker", "Linker program", "default", ("default", "bfd", "gold", "lld", "mold")),
        BoolVariable("use_llvm", "Use the LLVM compiler", False),
        BoolVariable("use_static_cpp", "Link libgcc and libstdc++ statically for better portability", True),
        BoolVariable("use_coverage", "Test Godot coverage", False),
        BoolVariable("use_ubsan", "Use LLVM/GCC compiler undefined behavior sanitizer (UBSAN)", False),
        BoolVariable("use_asan", "Use LLVM/GCC compiler address sanitizer (ASAN)", False),
        BoolVariable("use_lsan", "Use LLVM/GCC compiler leak sanitizer (LSAN)", False),
        BoolVariable("use_tsan", "Use LLVM/GCC compiler thread sanitizer (TSAN)", False),
        BoolVariable("use_msan", "Use LLVM compiler memory sanitizer (MSAN)", False),
        BoolVariable("use_sowrap", "Dynamically load system libraries", True),
        BoolVariable("alsa", "Use ALSA", True),
        BoolVariable("pulseaudio", "Use PulseAudio", True),
        BoolVariable("dbus", "Use D-Bus to handle screensaver and portal desktop settings", True),
        BoolVariable("speechd", "Use Speech Dispatcher for Text-to-Speech support", True),
        BoolVariable("fontconfig", "Use fontconfig for system fonts support", True),
        BoolVariable("udev", "Use udev for gamepad connection callbacks", True),
        BoolVariable("x11", "Enable X11 display", True),
        BoolVariable("wayland", "Enable Wayland display", True),
        BoolVariable("libdecor", "Enable libdecor support", True),
        BoolVariable("touch", "Enable touch events", True),
        BoolVariable("execinfo", "Use libexecinfo on systems where glibc is not available", None),
    )
