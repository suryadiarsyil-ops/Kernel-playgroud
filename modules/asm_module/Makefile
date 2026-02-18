obj-m += asm_module.o

ARCH          ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
KDIR          ?= /lib/modules/$(shell uname -r)/build
PWD           := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) clean
