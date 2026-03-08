OUT_DIR        ?= $(ROOT_DIR)/out/$(ARCH)/$(CONFIG)
ESP_DIR        ?= $(OUT_DIR)/esp
EFI_BOOT_DIR   ?= $(ESP_DIR)/EFI/BOOT
ESP_KERNEL_DIR ?= $(ESP_DIR)/kernel
KERNEL_OUT_DIR ?= $(OUT_DIR)/kernel
BOOT_OUT_DIR   ?= $(OUT_DIR)/bootloader

KERNEL_ELF     ?= $(KERNEL_OUT_DIR)/kernel.elf
BOOT_EFI       ?= $(EFI_BOOT_DIR)/bootx64.efi

MKDIR_P        ?= mkdir -p
RM_RF          ?= rm -rf
CP             ?= cp -f

WARNINGS       := -Wall -Wextra

KERNEL_CFLAGS_COMMON  := -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone $(WARNINGS)
KERNEL_LDFLAGS_COMMON := -nostdlib

EDK2_DIR       ?= $(ROOT_DIR)/external/edk2
LOADER_PKG_DIR ?= $(ROOT_DIR)/bootloader/uefi/loaderpkg

ifeq ($(ARCH),x64)
  EDK2_ARCH := X64
else
  $(error Unsupported ARCH '$(ARCH)')
endif

ifeq ($(CONFIG),debug)
  EDK2_TARGET := DEBUG
else ifeq ($(CONFIG),release)
  EDK2_TARGET := RELEASE
else
  $(error Unsupported CONFIG '$(CONFIG)')
endif