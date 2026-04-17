MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SRCDIR       := $(MAKEFILE_DIR)

TOPDIR ?= $(abspath $(MAKEFILE_DIR)/../external/gnu-efi)
ARCH   ?= x86_64

include $(TOPDIR)/Make.defaults

INCDIR += -I$(SRCDIR)/include \
          -I$(abspath $(SRCDIR)/../common/include)

override CFLAGS += -fcf-protection=none -mno-shstk

CRTOBJS  := $(TOPDIR)/$(ARCH)/gnuefi/crt0-efi-$(ARCH).o
LDSCRIPT := $(TOPDIR)/gnuefi/elf_$(ARCH)_efi.lds

LIBEFI_A    := $(TOPDIR)/$(ARCH)/lib/libefi.a
LIBGNUEFI_A := $(TOPDIR)/$(ARCH)/gnuefi/libgnuefi.a

override LDFLAGS += -T $(LDSCRIPT) \
                    -shared \
                    -Bsymbolic

LOADLIBES := $(CRTOBJS) $(LIBEFI_A) $(LIBGNUEFI_A) $(LIBGCC)

.PHONY: all clean dirs

all: dirs bin/bootx64.efi

dirs:
	mkdir -p build bin

build/bootloader.o: $(SRCDIR)/src/bootloader.c | dirs
	$(CC) $(INCDIR) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/bootloader.so: build/bootloader.o | dirs
	$(LD) $(LDFLAGS) $< -o $@ $(LOADLIBES)

build/bootloader.efi: build/bootloader.so | dirs
	$(OBJCOPY) -O efi-app-$(ARCH) $< $@

bin/bootx64.efi: build/bootloader.efi | dirs
	cp $< $@

clean:
	rm -rf build bin