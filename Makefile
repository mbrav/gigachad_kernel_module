# For Kbuild to include header files 
# https://unix.stackexchange.com/questions/18143/how-to-include-local-header-files-in-linux-kernel-module
# EXTRA_CFLAGS := -I$(src)/src/inc

# Define output module
obj-m += virgin_kernel_module.o
obj-m += normie_kernel_module.o
obj-m += gigachad_kernel_module.o

PWD := $(CURDIR)

# Build modules
all:
	@echo "====== BUILD MODULES BEGIN ====="
	@make -C /lib/modules/$$(uname -r)/build M=$(PWD) modules
	@echo "======= BUILD MODULES END ======"

# Install built modules with sudo
install:
	@echo "====== LOAD MODULES BEGIN ====="
	cat /proc/modules | grep virgin_kernel_module || sudo insmod virgin_kernel_module.ko
	cat /proc/modules | grep normie_kernel_module || sudo insmod normie_kernel_module.ko
	cat /proc/modules | grep gigachad_kernel_module || sudo insmod gigachad_kernel_module.ko
	@echo "======= LOAD MODULES END ======"
	@echo "====== LOADED MODULES SHOW BEGIN ====="
	@cat /proc/kallsyms | grep --color -E "(virgin|normie|gigachad)_kernel_module"
	@echo "======= LOADED MODULES SHOW END ======"

# Uninstall modules with sudo
uninstall:
	@echo "====== UNLOAD MODULES BEGIN ====="
	cat /proc/modules | grep virgin_kernel_module && sudo rmmod virgin_kernel_module.ko
	cat /proc/modules | grep normie_kernel_module && sudo rmmod normie_kernel_module.ko
	cat /proc/modules | grep gigachad_kernel_module && sudo rmmod gigachad_kernel_module.ko
	@echo "======= UNLOAD MODULES END ======"

# Clean built modules
clean:
	@echo "====== CLEAN BEGIN ====="
	@make -C /lib/modules/$$(uname -r)/build M=$(PWD) clean
	@echo "======= CLEAN END ======"
