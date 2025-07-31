#!/usr/bin/env python3
from __future__ import annotations

import json
import os
import re

ANSI = r"\x1b\[[=\?]?[;\d]*[a-zA-Z]"  # A single ANSI codepoint.
BREAK = rf"(?:\s|{ANSI})*"  # Non-matching collection of spaces and/or ANSI codepoints; can be empty.
RE_GROUP = re.compile(r"\?P<[a-zA-Z]+>")  # Regex to strip group identifiers.


def format_breaks(breaks: list[str]) -> str:
    return f"^{BREAK}{BREAK.join(breaks)}{BREAK}$"


def build_problem_matcher(owner: str, *regexps: list[str]) -> dict[str, str | list[dict[str, str | int]]]:
    patterns = []
    for regexp in regexps:
        pattern: dict[str, str | int] = {}
        compile = re.compile(format_breaks(regexp))
        pattern["regexp"] = RE_GROUP.sub("", compile.pattern)  # Problem matcher can't parse group identifiers.
        for name, idx in compile.groupindex.items():
            pattern[name] = idx
        patterns.append(pattern)
    return {"owner": owner, "pattern": patterns}


CLANG = build_problem_matcher(
    "clang",
    [
        r"(?P<file>.*?)(?::|\(|\s\+)(?P<line>\d+)(?:[,:](?P<column>\d+))?[,:\d\-]*\)?:",
        r"(?:(?:fatal|runtime)\s)?(?P<severity>error|warning):",
        r"(?P<message>.*?)(?:\[(?P<code>.*)\])?",
    ],
)
MSVC = build_problem_matcher(
    "msvc",
    [
        r"(?P<file>.*?)\((?P<line>\d+)(?:,(?P<column>\d+))?[,\d\-]*\):",
        r"(?:(?:fatal|runtime)\s)?(?P<severity>error|warning)\s(?P<code>[a-zA-Z]{1,2}\d+):",
        r"(?P<message>.*?)",
    ],
)
GODOT = build_problem_matcher(
    "godot",
    [
        r"(?:(?:SCRIPT|SHADER|UNKNOWN)\s)?(?P<severity>ERROR|WARNING):"
        r"(?P<message>.*)"
    ],
    [
        r"at:\s\w+",
        r"\((?P<file>.*):(?P<line>\d+)\)",
    ],
)


def main():
    problem_matchers = [CLANG, MSVC, GODOT]
    with open(
        os.path.join(os.path.dirname(__file__), "../utility/problem-matchers.json"), "w", encoding="utf-8", newline="\n"
    ) as file:
        file.write(json.dumps({"problemMatcher": problem_matchers}, indent=4).replace("    ", "\t") + "\n")


try:
    raise SystemExit(main())
except KeyboardInterrupt:
    import signal

    signal.signal(signal.SIGINT, signal.SIG_DFL)
    os.kill(os.getpid(), signal.SIGINT)
