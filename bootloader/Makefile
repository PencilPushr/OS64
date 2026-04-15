MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRCDIR ?= $(MAKEFILE_DIR)
VPATH  ?= $(SRCDIR)/src

TOPDIR ?= $(abspath $(MAKEFILE_DIR)/../external/gnu-efi)
ARCH   ?= x86_64
BINDIR ?= $(SRCDIR)/bin

include $(TOPDIR)/Make.defaults

INCDIR += -I$(SRCDIR)/include \
          -I$(abspath $(SRCDIR)/../common/include)

EFI_CFLAGS += -ffreestanding \
              -fno-stack-protector \
              -fshort-wchar \
              -Wall -Wextra

CRT0_LIBS = -lgnuefi
CRTOBJS   = $(TOPDIR)/$(ARCH)/gnuefi/crt0-efi-$(ARCH).o
LDSCRIPT  = $(TOPDIR)/gnuefi/elf_$(ARCH)_efi.lds

EFI_LDFLAGS += -L$(TOPDIR)/$(ARCH)/lib \
               -L$(TOPDIR)/$(ARCH)/gnuefi \
               $(CRTOBJS) \
               -pie -Bsymbolic --no-dynamic-linker

LOADLIBES += -T $(LDSCRIPT) -lefi $(CRT0_LIBS) $(LIBGCC)

SUBSYSTEM := 0xa
FORMAT := -O efi-app-$(ARCH)

TARGETS = bootloader.efi

.PHONY: all clean dirs

all: dirs $(TARGETS) $(BINDIR)/bootx64.efi

dirs:
	mkdir -p $(BINDIR)

$(BINDIR)/bootx64.efi: bootloader.efi | dirs
	cp $< $@

clean:
	rm -f *~ *.o *.so *.efi *.efi.debug
	rm -rf $(BINDIR)

include $(TOPDIR)/Make.rules