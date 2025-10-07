from __future__ import annotations

if __name__ != "__main__":
    raise SystemExit(f'Utility script "{__file__}" should not be used as a module!')

import sys

try:
    sys.path.insert(0, "./")
    from misc.utility.color import print_error
except ImportError:
    raise SystemExit(f'Utility script "{__file__}" must be ran from repository root!')

import argparse
import subprocess
from collections.abc import Generator

EXECUTABLE_VALUES = frozenset(("1", "3", "5", "7"))


def git_ls_files(paths: list[str]) -> Generator[tuple[str, str]]:
    out = subprocess.run(["git", "ls-files", "--stage", "--"] + paths, capture_output=True, text=True)
    for item in out.stdout:
        metadata, filename = item.split("\t")
        mode, _, _ = metadata.split()
        yield mode, filename


def check_executables(paths: list[str]) -> int:
    ret = 0
    for mode, file in git_ls_files(paths):
        if any(bit in EXECUTABLE_VALUES for bit in mode[-3:]):
            print_error(f'File "{file}" should not be marked as executable!')
            ret += 1

    return ret


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("filenames", nargs="+")
    args = parser.parse_args()

    return check_executables(args.filenames)


try:
    raise SystemExit(main())
except KeyboardInterrupt:
    import os
    import signal

    signal.signal(signal.SIGINT, signal.SIG_DFL)
    os.kill(os.getpid(), signal.SIGINT)
