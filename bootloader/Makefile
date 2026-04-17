# Bootloader Makefile

ARCH   ?= x86_64

# --- toolchain ---

TOPDIR ?= $(abspath external/gnu-efi)

CC      ?= gcc 
LD      ?= ld 
OBJCOPY ?= objcopy

GNU_EFI_INCLUDE :=          \
	-I$(TOPDIR)/inc         \
	-I$(TOPDIR)/inc/$(ARCH) \
	-I$(TOPDIR)/inc/protocol

LOCAL_INCLUDE :=  \
	-I include    \
	-I ../common/include

CFLAGS :=                      \
          $(LOCAL_INCLUDE)     \
          $(GNU_EFI_INCLUDE)   \
	      -ffreestanding       \
	      -fno-stack-protector \
	      -fpic                \
	      -fshort-wchar        \
	      -mno-red-zone        \
	      -Wall                \
	      -Wextra 

CRTOBJS   := $(TOPDIR)/$(ARCH)/gnuefi/crt0-efi-$(ARCH).o
LDSCRIPT  := $(TOPDIR)/gnuefi/elf_$(ARCH)_efi.lds
LIBDIR    := $(TOPDIR)/$(ARCH)/gnuefi

LDFLAGS := -nostdlib     \
	      -shared        \
	      -Bsymbolic     \
	      -T $(LDSCRIPT) \
	      $(CRTOBJS)     \
	      -L$(LIBDIR)    \
	      -lgnuefi

OBJS := build/bootloader.o

# --- targets ---

.PHONY: all clean

all: bin/bootx64.efi

build bin:
	mkdir -p $@

build/bootloader.o: src/bootloader.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/bootloader.so: $(OBJS) | build
	$(LD) $(LDFLAGS) $(OBJS) -o $@

bin/bootx64.efi: build/bootloader.so | bin
	$(OBJCOPY) \
		-j .text \
		-j .sdata \
		-j .data \
		-j .dynamic \
		-j .dynsym \
		-j .rel \
		-j .rela \
		-j .reloc \
		--target=efi-app-$(ARCH) \
		$< $@

clean: 
	rm -f build bin




