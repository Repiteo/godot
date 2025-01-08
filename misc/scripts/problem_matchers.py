#!/usr/bin/env python3
from __future__ import annotations

if __name__ != "__main__":
    raise ImportError(f"{__name__} should not be used as a module.")

ANSI = r"\x1b\[[=\?]?[;\d]+[a-zA-Z]"
ANSI_OR_SPACE = "(?:\s|" + ANSI + ")*"

ERROR_NAMES = r"(?:(fatal|runtime)\s+)(error|warning|info)"


def main() -> int:
    print(ERROR_NAMES)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
