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
	-drive if=pflash,format=raw,file=$(OUT)/OVMF_VARS_4M.fd \
	-drive format=raw,file=fat:rw:$(OUT) \
	-m 1024M \
	-net none

# --- targets ---

.PHONY: all setup bootloader kernel stage run clean

all: stage

setup:
	$(MAKE) -C $(GNUEFI) ARCH=$(ARCH)

bootloader:
	@test -f $(GNUEFI_LIB)/libefi.a || \
		{ echo "Run 'make setup' first"; exit 1; }
	mkdir -p bootloader/build
	$(MAKE) -C bootloader/build -f ../Makefile \
		ARCH=$(ARCH) \
		GNUEFI_LIB=$(GNUEFI_LIB) \
		GNUEFI_INCLUDE=$(GNUEFI_INCLUDE)

kernel:
	$(MAKE) -C kernel ARCH=$(ARCH)

# Per spec -- https://uefi.org/sites/default/files/resources/UEFI%202_5.pdf#page=587 
# Boot file should be located in /efi/boot/ , while os specific loaders to be located under /efi/
stage: bootloader kernel
	mkdir -p $(EFI_BOOT) $(EFI_OS64)
	cp bootloader/bin/bootx64.efi $(EFI_BOOT)/
	cp kernel/bin/kernel.elf $(EFI_OS64)/

run: stage
	cp $(OVMF_DIR)/OVMF_VARS_4M.fd $(OUT)/
	qemu-system-x86_64 $(QEMU_FLAGS)

clean:
	rm -rf $(OUT) bootloader/build bootloader/bin
	$(MAKE) -C kernel clean