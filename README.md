# Gigachad Kernel module

This is a simple Linux Kernel module. Try it inside a VM. Don't use on your install (unless you are a Gigachad).

![Gigachad loading his own Kernel module](https://i.imgflip.com/6c7jl7.png)

All code is free to use. **Modifications in editors besides Vim / Neovim are not allowed.**

## Prerequisites

On Debian-based distros Install:

```shell
apt install linux-headers-$(uname -r) gcc make build-essential libncurses-dev exuberant-ctags
```

Whereas, if you are on Arch, you probably don't even need to install anything because Arch is a Gigachad-teir distro by default.

*I use Arch btw.*

## Building

```shell
make
```

### Loading the module into your Kernel

To load the the module, you must install the `.ko` file. You can do so with the following make command:

```shell
sudo make install
```

### Unloading module from your Kernel

To unload the module from your kernel run:

```shell
sudo make uninstall
```

### Testing if the module was loaded

To test whether the module run `dmesg` command to check if the follwing message are present:

```shell
[ 3433.692029] Gigachad Kernel Module loaded!
[ 3442.597728] Gigachad Kernel Module unloaded!
```

#### BTF generation error

In case you get a similar error when running `make`:

```
Skipping BTF generation for /home/user/linux_mod/gigachad_kernel_module.ko due to unavailability of vmlinux
```

This is due to unavailability of vmlinux on your system. To remedy this, try installing the following package:

```shell
apt install dwarves
```

Then, check if the vmlinux file is located in `/sys/kernel/btf` by running:

```shell
ls /sys/kernel/btf
```

If the vmlinux file is present, copy it to the appropriate directory using the following command:

```shell
cp /sys/kernel/btf/vmlinux /usr/lib/modules/$(uname -r)/build/
```

If after runing `make` once again you continue getting the error:

```
/bin/sh: 1: ./tools/bpf/resolve_btfids/resolve_btfids: not found
```

See the [following solution](https://github.com/aircrack-ng/rtl8188eus/issues/263).

### Cleaning

```shell
make clean
```

## Other info

- [*The Linux Kernel Module Programming Guide*](https://github.com/sysprog21/lkmpg)
