#!/usr/bin/env python3
from __future__ import annotations

ANSI = r"\x1b\[\d+(;\d+)*m"
ANSI_OR_SPACE = "(?:\s|" + ANSI + ")"


ERROR_NAMES = r"(?:(fatal|runtime)\s+)(error|warning|info)"


def main() -> int:
    print(ERROR_NAMES)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
