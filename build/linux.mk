KERNEL_CC            ?= x86_64-elf-gcc
KERNEL_LD            ?= x86_64-elf-ld
KERNEL_CFLAGS_HOST   ?=
KERNEL_LDFLAGS_HOST  ?=

EDK2_TOOLCHAIN       ?= CLANGPDB
CLANG_BIN            ?= /usr/bin/

QEMU ?= qemu-system-x86_64
OVMF ?= /usr/share/OVMF/OVMF.fd

QEMU_FLAGS ?= \
	-name OS64 \
	-bios "$(OVMF)" \
	-drive format=raw,file=fat:rw:"$(ESP_DIR)" \
	-m 2048M