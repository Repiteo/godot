#!/usr/bin/env python3

if __name__ != "__main__":
    raise SystemExit(f'Utility script "{__file__}" should not be used as a module!')

import os
from pathlib import Path

if Path(os.getcwd()).as_posix() != Path(__file__).parent.parent.parent.as_posix():
    raise RuntimeError(f'Utility script "{__file__}" must be ran from the repository root!')

import argparse
import asyncio
import itertools
import multiprocessing
import re
import sys
from collections.abc import Awaitable, Callable
from time import time


async def run_clangd_tidy(file: str, color: str, verbose: bool, log: bool) -> int:
    if verbose:
        print(f'Starting "{file}".')

    try:
        process = await asyncio.create_subprocess_exec(
            *["clangd-tidy", "--allow-extensions", "c,h,cpp,hpp,cc,hh,cxx,hxx,m,mm,java", file, "--color", color],
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE,
        )
        start = time()
        stdout, stderr = (out.strip() for out in await process.communicate())
        end = time()
    except asyncio.CancelledError:
        process.terminate()
        await process.wait()
        raise

    if verbose:
        print(f'Finished "{file}". [{end - start:.2f}s]')

    if stdout or stderr:
        output = b"\n".join(itertools.chain(stdout.splitlines(), stderr.splitlines())).decode()
        print(output, sys.stderr, flush=True)
        if log:
            # TODO: Replace with non-blocking equivalent.
            with open(
                f"bin/clangd_tidy_logs/{file.replace('/', '-')}.log", "w", encoding="utf-8", newline="\n"
            ) as log_file:
                RE_ANSI_STRIP = re.compile(r"\x1b(?:\[[=\?]?[;\d]+[a-zA-Z]|\]8;(?:[^;]=[^;]:?)*;.*?\x1b\\)")
                log_file.write(RE_ANSI_STRIP.sub("", output) + "\n")  # Logged files always have ANSI stripped.
        return 1

    return 0


async def run_with_semaphore(
    semaphore: asyncio.Semaphore,
    callable: Callable[[str, str, bool, bool], Awaitable[int]],
    file: str,
    color: str,
    verbose: bool,
    log: bool,
) -> int:
    async with semaphore:
        return await callable(file, color, verbose, log)


async def main() -> int:
    RE_INCLUDE = re.compile(r".*\.(c|h|cpp|hpp|cc|hh|cxx|hxx|m|mm|java)$")
    RE_EXCLUDE = re.compile(
        "|".join([
            r".*thirdparty/.*",
            r".*-(dll|dylib|so)_wrap\.[ch]",
            r"platform/android/java/editor/src/main/java/com/android/.*",
            r"platform/android/java/lib/src/main/java/com/google/.*",
        ])
    )

    parser = argparse.ArgumentParser(description="Runs clangd-tidy on passed files (if compiledb present)")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("-f", "--files", nargs="*", help="List of files/globs to parse and pass to `clangd-tidy`")
    group.add_argument("-a", "--all-files", action="store_true", help="Pass all valid files with `clangd-tidy`")
    parser.add_argument("-c", "--color", action=argparse.BooleanOptionalAction, help="Override color output detection")
    parser.add_argument("-v", "--verbose", action="store_true", help="Expanded output to the command line")
    parser.add_argument("-l", "--log", action="store_true", help="Store outputs to a dedicated logging directory")

    if not Path("compile_commands.json").exists():
        parser.print_help()
        parser.exit(message="No compilation database detected; skipping hook!")

    args = parser.parse_args()
    color = "auto" if args.files is None else "always" if args.files else "never"
    verbose = args.verbose
    log = args.log

    if log:
        os.makedirs("bin/clangd_tidy_logs", exist_ok=True)

    files: list[str] = []
    if args.all_files:
        try:
            process = await asyncio.create_subprocess_exec(
                "git", "ls-files", stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE
            )
            stdout, _ = await process.communicate()
            files = stdout.decode().splitlines()
        except asyncio.CancelledError:
            process.terminate()
            await process.wait()
            raise
    else:
        for file in args.files:
            files += [item.as_posix() for item in Path(".").glob(file)]

    files = [file for file in files if RE_INCLUDE.match(file) and not RE_EXCLUDE.match(file)]
    semaphore = asyncio.Semaphore(multiprocessing.cpu_count())
    tasks = [
        asyncio.create_task(run_with_semaphore(semaphore, run_clangd_tidy, file, color, verbose, log)) for file in files
    ]

    ret = 0

    for task in asyncio.as_completed(tasks):
        ret += await task

    return ret


try:
    raise SystemExit(asyncio.run(main()))
except KeyboardInterrupt:
    import signal

    signal.signal(signal.SIGINT, signal.SIG_DFL)
    os.kill(os.getpid(), signal.SIGINT)
