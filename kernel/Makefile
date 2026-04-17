CC := gcc
OBJCOPY := objcopy

CFLAGS := -ffreestanding 	   \
          -fno-stack-protector \
          -mno-red-zone 	   \
          -nostdlib 	       \
          -Wall -Wextra 	   \
          -I$(INCDIR) 		   \
          -I../common/include

LDFLAGS := -T linker.ld -nostdlib -Wl,--build-id=none

.PHONY: all clean

all: bin/kernel.elf bin/kernel.bin

build: 
	mkdir -p build

bin:
	mkdir -p bin

build/kmain.o: \
	src/kmain.c ../common/include/common/bootinfo.h | build
	$(CC) $(CFLAGS) -c $< -o $@

bin/kernel.elf: \
	build/kmain.o linker.ld | bin
	$(CC) $(LDFLAGS) build/kmain.o -o $@

bin/kernel.bin: \
	bin/kernel.elf | bin
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf build bin