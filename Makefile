# For Kbuild to include header files 
# https://unix.stackexchange.com/questions/18143/how-to-include-local-header-files-in-linux-kernel-module
# EXTRA_CFLAGS := -I$(src)/src/inc

# Define output module
obj-m += gigachad_kernel_module.o
obj-m += virgin_kernel_module.o

PWD := $(CURDIR)

# Build module
all:
	make -C /lib/modules/$$(uname -r)/build M=$(PWD) modules

# Clean built modules
clean:
	make -C /lib/modules/$$(uname -r)/build M=$(PWD) clean
