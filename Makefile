
# Define output module
obj-m += gigachad_kernel_module.o

# Build module
all:
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) modules

# Clean built modules
clean:
	make -C /lib/modules/$$(uname -r)/build M=$$(pwd) clean
