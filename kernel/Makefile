# Kernel Makefile

# --- toolchain ---

CC := gcc
LD := gcc
OBJCOPY := objcopy

ARCH ?= x86_64

# --- generic flags ---

CFLAGS := -ffreestanding        \
          -fno-stack-protector  \
          -mno-red-zone         \
          -nostdlib             \
          -Wall -Wextra         \
          -I../common/include   \
          -Iinclude

ASFLAGS := -ffreestanding       \
           -mno-red-zone        \
           -I../common/include  \
           -Iinclude

LDFLAGS := -T linker.ld -nostdlib -Wl,--build-id=none

# --- architecture selection ---

ifeq ($(ARCH),x86_64)

ARCH_DIR := arch/x86_64

CFLAGS += -I$(ARCH_DIR)/include
ASFLAGS += -I$(ARCH_DIR)/include

ARCH_C_SRCS := \
	$(wildcard $(ARCH_DIR)/*.c)

ARCH_ASM_SRCS := \
	$(ARCH_DIR)/asm/idt.s

else
$(error Unsupported ARCH '$(ARCH)')
endif

# --- sources ---

C_SRCS := \
	src/kmain.c \
	$(ARCH_C_SRCS)

ASM_SRCS := \
	$(ARCH_ASM_SRCS)

C_OBJS := $(patsubst %.c,build/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst %.s,build/%.o,$(ASM_SRCS))

OBJS := $(C_OBJS) $(ASM_OBJS)

# --- targets ---

.PHONY: all clean

all: bin/kernel.elf bin/kernel.bin

bin:
	mkdir -p bin

build:
	mkdir -p build

# Compile C files
build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble GAS .s files
build/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

# Link kernel ELF
bin/kernel.elf: $(OBJS) linker.ld | bin
	$(LD) $(LDFLAGS) $(OBJS) -o $@

# Flat binary
bin/kernel.bin: bin/kernel.elf | bin
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf build bin