
EXTRA_CFLAGS += -mfpu=neon
#EXTRA_CFLAGS += -D__KERNEL__ -DKERNEL -DCONFIG_KEXEC -DCONFIG_KEXEC_JUMP -march=armv7-a -mtune=cortex-a9
EXTRA_CFLAGS += -D__KERNEL__ -DKERNEL -DCONFIG_KEXEC -march=armv7-a -mtune=cortex-a9

# Make this match the optimisation values of the kernel you're
# loading this into. Should work without changes, but it seems to
# crash on the Nexus One and Droid Pro. If you're compiling on an 
# Evo 4g, set this value to 1 and change the EXTRA_CFLAGS value to
# something appropriate to your phone
# EXTRA_CFLAGS += -O0

ARCH		= arm
KERNEL ?= /home/basel/my_mifi_mod/krnl/E5573Cs/kernel
####CONFIG = ford_cyanogenmod_defconfig
CROSS_COMPILE ?= /home/basel/my_mifi_mod/gcc-4.6/bin/arm-eabi-

CPPFLAGS	=  -I$(KERNEL)/

obj-m += kexec_load.o
kexec_load-objs := kexec_mod.o \
	arch/arm/kernel/machine_kexec.o \
	arch/arm/kernel/relocate_kernel.o \
	kernel/kexec.o \
	kernel/ksysfs.o \
	kernel/sys.o \
	kernel/printk.o

all: module

module:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out M=$(PWD) modules

clean:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out M=$(PWD) clean
	rm -f *.order

prepare:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out $(CONFIG)
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out modules_prepare

kernel_clean:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out mrproper
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) make -C $(KERNEL)/ O=out clean
