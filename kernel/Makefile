# Kernel Makefile

# --- toolchain ---

CC      := gcc
OBJCOPY := objcopy

CFLAGS := -ffreestanding       \
          -fno-stack-protector \
          -fno-pie             \
          -fno-pic             \
          -mno-red-zone        \
          -Wall                \
          -Wextra              \
          -I.                  \
          -I../common/include

LDFLAGS := -T linker.ld          \
           -nostdlib             \
           -no-pie               \
           -Wl,--build-id=none

# --- objects ---

OBJECTS := \
    build/kmain.o \
    build/display.o \
    build/graphics.o \
    build/kconsole.o \
    build/display_lfb.o \
    build/font.o \
    build/status.o \
	build/string.o

# --- targets ---

.PHONY: all clean

all: bin/kernel.elf bin/kernel.bin

build:
	mkdir -p build

bin:
	mkdir -p bin

build/kmain.o: \
	src/kmain.c ../common/include/common/bootinfo.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/display.o: \
	graphics/display.c
	$(CC) $(CFLAGS) -c $< -o $@

build/display_lfb.o: \
	graphics/displays/display_lfb.c
	$(CC) $(CFLAGS) -c $< -o $@

build/graphics.o: \
	graphics/graphics.c
	$(CC) $(CFLAGS) -c $< -o $@

build/kconsole.o: \
	graphics/kconsole.c
	$(CC) $(CFLAGS) -c $< -o $@

build/font.o: \
	../common/include/common/font.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/status.o: \
	../common/include/common/status.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/string.o: \
	../common/include/common/string.c | build
	$(CC) $(CFLAGS) -c $< -o $@

bin/kernel.elf: \
	$(OBJECTS) linker.ld | bin
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

bin/kernel.bin: \
	bin/kernel.elf | bin
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf build bin