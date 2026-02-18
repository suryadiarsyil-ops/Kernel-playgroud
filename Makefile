# ============================================================
# Top-level Makefile — Kernel Playground
# Target: ARM64 / Android Common Kernel GKI 5.10
# ============================================================

ARCH          ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-
KDIR          ?= $(PWD)/linux-src
MODULES_DIR   := modules
SUBDIRS       := hello chardev asm_module

.PHONY: all clean load unload

all:
	@for dir in $(SUBDIRS); do \
		echo "==> Building modules/$$dir (ARM64)"; \
		$(MAKE) -C $(MODULES_DIR)/$$dir \
			ARCH=$(ARCH) \
			CROSS_COMPILE=$(CROSS_COMPILE) \
			KDIR=$(KDIR); \
	done

clean:
	@for dir in $(SUBDIRS); do \
		echo "==> Cleaning modules/$$dir"; \
		$(MAKE) -C $(MODULES_DIR)/$$dir \
			ARCH=$(ARCH) \
			CROSS_COMPILE=$(CROSS_COMPILE) \
			KDIR=$(KDIR) clean; \
	done

# load/unload only makes sense on ARM64 device or emulator
load:
	@echo "Loading all modules (requires ARM64 target)..."
	@sudo insmod $(MODULES_DIR)/hello/hello.ko
	@sudo insmod $(MODULES_DIR)/chardev/chardev.ko
	@sudo insmod $(MODULES_DIR)/asm_module/asm_module.ko

unload:
	@echo "Unloading all modules..."
	@sudo rmmod asm_module || true
	@sudo rmmod chardev    || true
	@sudo rmmod hello      || true
