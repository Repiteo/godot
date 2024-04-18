import os
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables, BoolVariable


def exists(env: SConsEnvironment) -> bool:
    return os.path.exists(get_env_android_sdk_root())


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    opts.AddVariables(
        ("ANDROID_HOME", "Path to the Android SDK", get_env_android_sdk_root()),
        (
            "ndk_platform",
            'Target platform (android-<api>, e.g. "android-' + str(get_min_target_api()) + '")',
            "android-" + str(get_min_target_api()),
        ),
        BoolVariable("store_release", "Editor build for Google Play Store (for official builds only)", False),
        BoolVariable("generate_apk", "Generate an APK/AAB after building Android library by calling Gradle", False),
    )


# Return the ANDROID_HOME environment variable.
def get_env_android_sdk_root() -> str:
    return os.environ.get("ANDROID_HOME", os.environ.get("ANDROID_SDK_ROOT", ""))


# This is kept in sync with the value in 'platform/android/java/app/config.gradle'.
def get_min_target_api() -> int:
    return 21
