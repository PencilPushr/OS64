CC := gcc
OBJCOPY := objcopy

SRCDIR := src
INCDIR := include

BUILD_DIR := build
BIN_DIR := bin

CFLAGS := -ffreestanding \
          -fno-stack-protector \
          -mno-red-zone \
          -nostdlib \
          -Wall -Wextra \
          -I$(INCDIR) \
          -I../common/include

LDFLAGS := -T linker.ld -nostdlib -Wl,--build-id=none

.PHONY: all clean

all: $(BIN_DIR)/kernel.elf $(BIN_DIR)/kernel.bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/kmain.o: $(SRCDIR)/kmain.c ../common/include/common/bootinfo.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/kernel.elf: $(BUILD_DIR)/kmain.o linker.ld | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(BUILD_DIR)/kmain.o -o $@

$(BIN_DIR)/kernel.bin: $(BIN_DIR)/kernel.elf | $(BIN_DIR)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)