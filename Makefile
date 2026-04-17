# Top-level Makefile

ARCH ?= x86_64

# --- toolchain ---

GNUEFI         := $(abspath external/gnu-efi)
GNUEFI_LIB     := $(GNUEFI)/$(ARCH)/lib
GNUEFI_INCLUDE := $(GNUEFI)/inc

OVMF_DIR := $(abspath external/ovmf)

# --- output paths ---

OUT      := out
EFI_BOOT := $(OUT)/efi/boot
EFI_OS64 := $(OUT)/efi/os64

# --- qemu ---

QEMU_FLAGS := \
	-drive if=pflash,format=raw,readonly=on,file=$(OVMF_DIR)/OVMF_CODE_4M.fd \
	-drive if=pflash,format=raw,file=$(OVMF_DIR)/OVMF_VARS_4M.fd \
	-drive format=raw,file=fat:rw:$(OUT) \
	-drive file=$(OVMF_DIR)/UefiShell.iso,format=raw \
	-m 2048M \
	-net none \
	-d int \
	-D $(OVMF_DIR)/dbg.log 

# --- targets ---

.PHONY: all setup bootloader kernel stage run clean

all: stage

setup:
	$(MAKE) -C $(GNUEFI) ARCH=$(ARCH)

bootloader:
	@test -f $(GNUEFI_LIB)/libefi.a || \
		{ echo "Run 'make setup' first"; exit 1; }
	$(MAKE) -C bootloader \
	    ARCH=$(ARCH) \
	    TOPDIR=$(GNUEFI)
		
kernel:
	$(MAKE) -C kernel ARCH=$(ARCH)

# Per spec -- https://uefi.org/sites/default/files/resources/UEFI%202_5.pdf#page=587 
# Boot file should be located in /efi/boot/ , while os specific loaders to be located under /efi/
stage: bootloader kernel
	mkdir -p $(EFI_BOOT) $(EFI_OS64)
	cp bootloader/bin/bootx64.efi $(EFI_BOOT)/
	cp kernel/bin/kernel.elf $(EFI_OS64)/


run: stage
	mkdir -p $(OUT)
	cp -f $(OVMF_DIR)/OVMF_VARS_4M.fd $(OUT)/OVMF_VARS_4M.fd
	qemu-system-x86_64 $(QEMU_FLAGS)

clean:
	rm -rf $(OUT) bootloader/build bootloader/bin
	$(MAKE) -C kernel clean

cclean: clean
	$(MAKE) -C $(GNUEFI) ARCH=$(ARCH) clean