ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello.o
else
# normal makefile
KDIR ?= /lib/modules/‘uname -r‘/build

default:
$(MAKE) -C $(KDIR) M=$$PWD
 cp ./hello.ko ~/build/repos/busybox/_install/root/out/
 clean:
 $(MAKE) -C $(KDIR) M=$$PWD clean
 endif
