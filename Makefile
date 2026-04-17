ARCH ?= x86_64

OUT_DIR := out
OUT_EFI_BOOT := $(OUT_DIR)/efi/boot
OUT_OS64 := $(OUT_DIR)/efi/os64

BOOTLOADER_BUILD_DIR := bootloader/build

OVMF_CODE := $(abspath external/ovmf/OVMF_CODE_4M.fd)
OVMF_VARS := $(abspath external/ovmf/OVMF_VARS_4M.fd)

GNUEFI_DIR = $(abspath external/gnu-efi)

.PHONY: all bootloader kernel stage run clean setup

all: clean stage

setup:
	$(MAKE) -C $(GNUEFI_DIR) ARCH=$(ARCH)

bootloader: 
	@test -f $(GNUEFI_DIR)/$(ARCH)/lib/libefi.a || \
		{ echo "Run 'make setup' first to build gnu-efi"; exit 1; }
	mkdir -p $(BOOTLOADER_BUILD_DIR)
	$(MAKE) -C $(BOOTLOADER_BUILD_DIR) \
		-f ../Makefile \
		ARCH=$(ARCH) \
		BINDIR=../bin
		GNUEFI_DIR=$(GNUEFI_DIR)

kernel:
	$(MAKE) -C kernel

# Per spec -- https://uefi.org/sites/default/files/resources/UEFI%202_5.pdf#page=587 
# Boot file should be located in /efi/boot/ , while os specific loaders to be located under /efi/
stage: bootloader kernel
	mkdir -p $(OUT_EFI_BOOT)
	mkdir -p $(OUT_OS64)
	cp bootloader/bin/bootx64.efi $(OUT_EFI_BOOT)/
	cp kernel/bin/kernel.elf $(OUT_OS64)/

run: stage
	cp $(OVMF_VARS) $(OUT_DIR)/OVMF_VARS_4M.fd
	qemu-system-x86_64 \
		-drive if=pflash,format=raw,readonly=on,file=$(OVMF_CODE) \
		-drive if=pflash,format=raw,file=$(OUT_DIR)/OVMF_VARS_4M.fd \
		-drive format=raw,file=fat:rw:$(OUT_DIR) \
		-m 1024M \
		-net none

clean:
	rm -rf $(OUT_DIR)
	rm -rf bootloader/build bootloader/bin
	$(MAKE) -C kernel clean
