import json
import os
import subprocess

# Determines if build actions should occur after static checks are ran. Broadly speaking, these
#  files changing would result in SCons rebuilding the engine, or are otherwise pertinent to the
#  buildsystem itself.
SOURCE_FILTER = [
    ":(top,glob).github/*.yml",
    ":(top,glob).github/{actions/*,workflows}/*.yml",
    ":(top,glob)**/{SConstruct,SCsub,*.py}",
    ":(top,glob)**/*.{h,hpp,hh,hxx,c,cpp,cc,cxx,m,mm,inc,glsl}",
    ":(top,glob)core/extension/gdextension_interface.json",
    ":(top,glob)misc/extension_api_validation/**",
    ":(top,glob)modules/*/tests/**",
    ":(top,glob)modules/mono/**/*.{cs,csproj,sln,props,targets}",
    ":(top,glob)platform/android/java/{gradle*,**/*.{jar,java,kt,gradle}}",
    ":(top,glob)platform/web/{package{,-lock}.json,js/**/*.js}",
    ":(top,glob)tests/**",
]

# Determines which files are appropriate for running clangd-tidy checks on. This is a subset out
#  of necessity, as we're only evaluating a Linux runner.
CLANGD_FILTER = [
    ":(top,glob,exclude)**/*-so_wrap.{h,c}",
    ":(top,glob,exclude)**/thirdparty/**",
    ":(top,glob,exclude)drivers/{apple*,core*,d3d12,metal,wasapi,windows,winmidi,xaudio2}/**",
    ":(top,glob,exclude)editor/shader/shader_baker/shader_baker_export_plugin_platform_{d3d12,metal}.{h,cpp}",
    ":(top,glob,exclude)modules/camera/camera_{android,macos,win}.{h,cpp}",
    ":(top,glob,exclude)modules/openxr/extensions/platform/openxr_{android,metal}_extension.{h,cpp}",
    ":(top,glob,exclude)platform/{android,ios,macos,visionos,web,windows}/**",
    ":(top,glob)**/*.{h,hpp,hxx,hh,c,cpp,cxx,cc}",
    ":(top,glob)platform/{android,ios,macos,visionos,web,windows}/{api,export}/*.{h,hpp,hxx,hh,c,cpp,cxx,cc}",
]


def main():
    if False:
        with open(os.environ["GITHUB_EVENT_PATH"], encoding="utf-8", newline="\n") as file:
            EVENT_DATA = json.load(file)

        try:
            base_sha = str(EVENT_DATA["before"])
            subprocess.run(["git", "cat-file", "-e", base_sha], capture_output=True, check=True)
        except (KeyError, OSError):
            print("Failed to automatically detect prior SHA; falling back to `HEAD~1`.")
            base_sha = "HEAD~1"

    # CHANGED_FILES = subprocess.run(
    #     ["git", "diff", "--diff-filter=AMR", "--name-only", "-z", "HEAD~10", "HEAD"],
    #     capture_output=True,
    #     encoding="utf-8",
    # ).stdout.split("\0")
    # print(CHANGED_FILES)
    # print()

    # SOURCE_FILES = subprocess.run(
    #     ["git", "diff", "--diff-filter=AMR", "--name-only", "-z", "HEAD~10", "HEAD", "--", *SOURCE_FILTER],
    #     capture_output=True,
    #     encoding="utf-8",
    # ).stdout.split("\0")
    # print(SOURCE_FILES)
    # print()

    # CLANGD_FILES = subprocess.run(
    #     ["git", "diff", "--diff-filter=AMR", "--name-only", "-z", "HEAD~10", "HEAD", "--", *CLANGD_FILTER],
    #     capture_output=True,
    #     encoding="utf-8",
    # ).stdout.split("\0")
    # print(CLANGD_FILES)
    # print()

    ALL_FILES = subprocess.run(["git", "ls-files", "-z"], capture_output=True, encoding="utf-8").stdout.split("\0")
    print(len(ALL_FILES), ALL_FILES)
    print()
    SOURCE_FILES = subprocess.run(
        ["git", "ls-files", "-z", "--", *SOURCE_FILTER], capture_output=True, encoding="utf-8"
    ).stdout.split("\0")
    print(len(SOURCE_FILES), SOURCE_FILES)
    print()
    CLANGD_FILES = subprocess.run(
        ["git", "ls-files", "-z", "--", *CLANGD_FILTER], capture_output=True, encoding="utf-8"
    ).stdout.split("\0")
    print(len(CLANGD_FILES), CLANGD_FILES)

    if False:
        with open(os.environ["GITHUB_OUTPUT"], "a") as file:
            file.write(f"BASE_SHA={base_sha}\n")
            file.write(f"SOURCES_CHANGED={base_sha}\n")
            file.write(f"CLANGD_FILES={base_sha}\n")


if __name__ == "__main__":
    raise SystemExit(main())
