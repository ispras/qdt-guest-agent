from os import (
    environ,
)

base_env = DefaultEnvironment().Clone(
    LINKFLAGS = ["-static-libgcc", "-static-libstdc++"]
)
base_env.Append(ENV = dict(
    PATH = environ["PATH"],
))

def target(arch, name, **kw):
    global env

    prefix = arch + "-"

    env = base_env.Clone(
        CC = prefix + "gcc",
        CXX = prefix + "g++",
        LD = prefix + "ld",
        AR = prefix + "ar",
        STRIP = prefix +"strip",
        **kw
    )

    SConscript(
        variant_dir = "build/" + name,
        duplicate = False,
        exports = ["env"],
        dirs = [
            "src",
        ]
    )

target("x86_64-linux-gnu", "linux64")

target("i686-w64-mingw32", "win32",
    PROGSUFFIX = ".exe"
)
