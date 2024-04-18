import os
import sys
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables, BoolVariable


def exists(env: SConsEnvironment) -> bool:
    return sys.platform == "darwin" or "OSXCROSS_IOS" in os.environ


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    opts.AddVariables(
        ("vulkan_sdk_path", "Path to the Vulkan SDK", ""),
        (
            "IOS_TOOLCHAIN_PATH",
            "Path to iOS toolchain",
            "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain",
        ),
        ("IOS_SDK_PATH", "Path to the iOS SDK", ""),
        BoolVariable("ios_simulator", "Build for iOS Simulator", False),
        ("ios_triple", "Triple for ios toolchain", ""),
        BoolVariable("generate_bundle", "Generate an APP bundle after building iOS/macOS binaries", False),
    )
