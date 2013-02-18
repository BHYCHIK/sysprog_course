KERNELVERSION = `uname -r`
# KERNELVERSION = 2.6.26-test
KERNELDIR = /lib/modules/$(KERNELVERSION)/build
PWD = `pwd`
EXTRA_CFLAGS = -Wall -Werror

ifneq ($(KERNELRELEASE),)
	obj-m += stackwatch.o
	stackwatch-objs := main.o
else
all:
	$(MAKE) -C $(KERNELDIR) M="$(PWD)" modules
clean:
	rm -rf *.o *.order *mod.c *.symvers
endif
	