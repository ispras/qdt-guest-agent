from os import (
    environ,
)

env = DefaultEnvironment()

SConscript(
    variant_dir = 'build/host',
    duplicate = False,
    exports = ["env"],
    dirs = [
        "src",
    ]
)

win32_prefix = "i686-w64-mingw32-"

env = Environment(
    CC = win32_prefix + "gcc",
    CXX = win32_prefix + "g++",
    LD = win32_prefix + "ld",
    AR = win32_prefix + "ar",
    STRIP = win32_prefix +"strip",
    PROGSUFFIX = ".exe",
)
env.Append(ENV = {"PATH" : environ["PATH"]})

SConscript(
    variant_dir = 'build/win32',
    duplicate = False,
    exports = ["env"],
    dirs = [
        "src",
    ]
)