# QDT Guest Agent

## Prerequisites

  - SCons build system.
  - Tool chains for cross-compilation of C/C++ for Windows 32-bit
    (e.g. MinGW) and Linux (both x86_64 and i686).

### Ubuntu Linux

#### 18.04

```bash
sudo apt install \
    scons \
    mingw-w64 \
    gcc-i686-linux-gnu g++-i686-linux-gnu binutils-i686-linux-gnu
```

## Installation

There are several ways to edit guest disk file system.
To do it without guest OS launching [use qemu-nbd].
To work with LVM guest partitions (e.g.: Ubuntu 20.04)
see [more complicated manual].

[use qemu-nbd]: https://gist.github.com/shamil/62935d9b456a6f9877b5
[more complicated manual]: https://www.thegeekdiary.com/how-to-mount-guest-qcow2-virtual-disk-image-containing-lvm-on-kvm-host-machine/

### Windows XP, 7 / 32-bit, 64-bit

Copy `build/win32/agent/agent.exe` into "Start" -> "Startup".

### Linux with systemd

Copy `src/agent/qdt-agent.service` (service unit description) into
`/etc/systemd/system`.
Copy `agent/build/linux-[actual arch]/agent` into `/usr/bin`.
Launch guest and run `sudo systemctl enable qdt-agent.service`.

See `man systemd.service`.

#### buildroot

When generating a Linux workload with [buildroot](https://buildroot.org/),
root file system overlay mechanism can be used to setup those files
(look buildroot documentation for `BR2_ROOTFS_OVERLAY`).

Hints...

- Use glibc as `BR2_TOOLCHAIN_BUILDROOT_LIBC`
- Enable `BR2_INIT_SYSTEMD=y`.
- `BR2_ROOTFS_MERGED_USR=y`
- `BR2_TARGET_ROOTFS_EXT2_SIZE` is required to be increased likely.
- `systemctl` command is not required.
