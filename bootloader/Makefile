# Bootloader makefile

MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
TOPDIR ?= $(abspath $(MAKEFILE_DIR)/../external/gnu-efi)
ARCH   ?= x86_64

include $(TOPDIR)/Make.defaults

SRCDIR := $(MAKEFILE_DIR)/src

INCDIR += -I$(MAKEFILE_DIR)/include \
          -I$(abspath $(MAKEFILE_DIR)/../common/include)

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,build/%.o,$(SRCS))

CRTOBJS     := $(TOPDIR)/$(ARCH)/gnuefi/crt0-efi-$(ARCH).o
LDSCRIPT    := $(TOPDIR)/gnuefi/elf_$(ARCH)_efi.lds
LIBEFI_A    := $(TOPDIR)/$(ARCH)/lib/libefi.a
LIBGNUEFI_A := $(TOPDIR)/$(ARCH)/gnuefi/libgnuefi.a

override CFLAGS += -fcf-protection=none -mno-shstk -fshort-wchar
override LDFLAGS += -nostdlib -znocombreloc -T $(LDSCRIPT) -shared -Bsymbolic

LOADLIBES := $(CRTOBJS) $(LIBEFI_A) $(LIBGNUEFI_A) $(LIBGCC)

.PHONY: all clean dirs

all: dirs bin/bootx64.efi

dirs:
    mkdir -p build bin

build/%.o: $(SRCDIR)/%.c | dirs
    $(CC) $(INCDIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/bootloader.so: $(OBJS) | dirs
    $(LD) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES)

build/bootloader.efi: build/bootloader.so | dirs
    $(OBJCOPY) \
        -j .text \
        -j .text.* \
        -j .sdata \
        -j .sdata.* \
        -j .data \
        -j .data.* \
        -j .rodata \
        -j .rodata.* \
        -j .dynamic \
        -j .dynsym \
        -j .dynstr \
        -j .rel \
        -j .rel.* \
        -j .rela \
        -j .rela.* \
        -j .reloc \
        --target=efi-app-$(ARCH) \
        $< $@

bin/bootx64.efi: build/bootloader.efi | dirs
    cp $< $@

clean:
    rm -rf build bin