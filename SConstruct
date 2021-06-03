from os import (
    environ,
)

base_env = DefaultEnvironment().Clone(
    LINKFLAGS = ["-static-libgcc", "-static-libstdc++"]
)
base_env.Append(ENV = dict(
    PATH = environ["PATH"],
))

env = base_env.Clone()

SConscript(
    variant_dir = 'build/host',
    duplicate = False,
    exports = ["env"],
    dirs = [
        "src",
    ]
)

win32_prefix = "i686-w64-mingw32-"

env = base_env.Clone(
    CC = win32_prefix + "gcc",
    CXX = win32_prefix + "g++",
    LD = win32_prefix + "ld",
    AR = win32_prefix + "ar",
    STRIP = win32_prefix +"strip",
    PROGSUFFIX = ".exe",
)

SConscript(
    variant_dir = 'build/win32',
    duplicate = False,
    exports = ["env"],
    dirs = [
        "src",
    ]
)
