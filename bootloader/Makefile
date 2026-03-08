include $(ROOT_DIR)/build/common.mk
include $(ROOT_DIR)/build/$(HOST).mk

UEFI_BUILD_FILES := \
	$(LOADER_PKG_DIR)/loaderpkg.dec \
	$(LOADER_PKG_DIR)/loaderpkg.dsc \
	$(LOADER_PKG_DIR)/loader.inf \
	$(LOADER_PKG_DIR)/loader.c

EDK2_OUTPUT_ROOT := $(ROOT_DIR)/build/loaderpkg
EDK2_OUTPUT_EFI  := $(EDK2_OUTPUT_ROOT)/$(EDK2_TARGET)_CLANGPDB/$(EDK2_ARCH)/loader.efi

.PHONY: all clean

all: $(BOOT_EFI)

$(BOOT_OUT_DIR):
	$(MKDIR_P) "$(BOOT_OUT_DIR)"

$(EFI_BOOT_DIR):
	$(MKDIR_P) "$(EFI_BOOT_DIR)"

$(ESP_KERNEL_DIR):
	$(MKDIR_P) "$(ESP_KERNEL_DIR)"

ifeq ($(HOST),windows)
define EDK2_BUILD_CMD
MSYS2_ARG_CONV_EXCL='*' MSYS_NO_PATHCONV=1 \
ROOT_DIR_WIN="$(ROOT_DIR_WIN)" \
EDK2_DIR_WIN="$(EDK2_DIR_WIN)" \
LLVM_BIN_WIN="$(LLVM_BIN_WIN)" \
PYTHON_COMMAND_WIN="$(PYTHON_COMMAND_WIN)" \
PYTHON_HOME_WIN="$(PYTHON_HOME_WIN)" \
EDK2_ARCH="$(EDK2_ARCH)" \
EDK2_TARGET="$(EDK2_TARGET)" \
cmd.exe /C "$(EDK2_BUILD_SCRIPT_WIN)"
endef
else
define EDK2_BUILD_CMD
bash -lc 'cd "$(ROOT_DIR)" && \
  export WORKSPACE="$(ROOT_DIR)" && \
  export PACKAGES_PATH="$(EDK2_DIR)" && \
  export EDK_TOOLS_PATH="$(EDK2_DIR)/BaseTools" && \
  export CLANG_BIN="$(CLANG_BIN)" && \
  make -C "$(EDK2_DIR)/BaseTools" && \
  . "$(EDK2_DIR)/edksetup.sh" BaseTools && \
  build -p bootloader/uefi/loaderpkg/loaderpkg.dsc -a $(EDK2_ARCH) -b $(EDK2_TARGET) -t CLANGPDB'
endef
endif

$(BOOT_OUT_DIR)/loader.efi: $(UEFI_BUILD_FILES) | $(BOOT_OUT_DIR)
	$(EDK2_BUILD_CMD)
	$(CP) "$(EDK2_OUTPUT_EFI)" "$@"

$(BOOT_EFI): $(BOOT_OUT_DIR)/loader.efi $(KERNEL_ELF) | $(EFI_BOOT_DIR) $(ESP_KERNEL_DIR)
	$(CP) "$(BOOT_OUT_DIR)/loader.efi" "$@"
	$(CP) "$(KERNEL_ELF)" "$(ESP_KERNEL_DIR)/kernel.elf"

clean:
	$(RM_RF) "$(BOOT_OUT_DIR)"
	$(RM_RF) "$(ESP_DIR)"
	$(RM_RF) "$(EDK2_OUTPUT_ROOT)"