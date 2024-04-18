import os
import sys
from SCons.Script.SConscript import SConsEnvironment
from SCons.Variables import Variables


def exists(env: SConsEnvironment) -> bool:
    return sys.platform == "darwin" or "OSXCROSS_ROOT" in os.environ


def generate(env: SConsEnvironment) -> None:
    pass


def options(opts: Variables) -> None:
    pass
