\# OS64 - Custom UEFI Bootloader \& Kernel



A minimal operating system with custom UEFI headers written from the UEFI specification.



\## What This Is



This project demonstrates:

\- Custom UEFI type definitions and protocol structures (currently no EDK2 dependency, working towards also introducing Legacy BIOS bootloader)

\- A UEFI bootloader that loads a kernel and passes boot information

\- A minimal kernel that draws to the framebuffer



We could approach Legacy BIOS by either performing compile time operations or detecting whether EFI could be supported or not:

i.e. 
Opli:	

&nbsp;	"...we can have a fallback thats the 512byte word sector

&nbsp;	so if it doesnt automatically load our boot.efi

&nbsp;	then we assume efi is not supported"



\## Project Structure



```

myos/

├── efi/                    # Custom UEFI headers (written from spec)

│   ├── types.h             # Basic types, EFIAPI macro, status codes

│   ├── tables.h            # System table, boot services

│   ├── protocols/

│   │   ├── text.h          # Console output protocol

│   │   ├── graphics.h      # GOP (framebuffer) protocol

│   │   └── file.h          # File system protocol

│   └── efi.h               # Main include file

├── common/

│   └── bootinfo.h          # Shared bootloader-kernel interface

├── bootloader/

│   ├── main.c              # Full bootloader (loads kernel, exits boot services)

│   ├── test.c              # Minimal test (draws rectangle)

│   └── Makefile

├── kernel/

│   ├── main.c              # Simple graphics demo

│   ├── linker.ld           # Load kernel at 1MB

│   └── Makefile

└── Makefile                # Top-level build

```



\## Building (Linux/WSL2)



```bash

\# Install dependencies:

# Ubuntu

sudo apt install build-essential gnu-efi qemu-system-x86 ovmf



\# Arch

sudo pacman -S base-devel gnu-efi qemu-system-x86 edk2-ovmf



\# Build

make



\# Run in QEMU

make run

```

### If you are ever stuck and need to find the right package for a file/dependency.

```bash
# Arch: Search which package provides a file

pacman -F crt0-efi-x86\_64.o



\# Ubuntu/Debian: Search which package provides a file

apt-file search crt0-efi-x86\_64.o
```



\## Building on Windows



Cross-compile from WSL2, then run with Windows QEMU:



```powershell

\# In WSL2: make

\# Then in Windows PowerShell:

qemu-system-x86\_64.exe -bios "C:\\path\\to\\OVMF.fd" -drive format=raw,file=fat:rw:esp -m 256M

```



Get OVMF from: https://retrage.github.io/edk2-nightly/



\## Key Technical Details



\### Why gnu-efi's crt0 and libgnuefi?



We use three things from gnu-efi:

1\. `crt0-efi-x86\_64.o` - Entry point that handles PE setup and calls `efi\_main`

2\. `elf\_x86\_64\_efi.lds` - Linker script for PE32+ EFI format

3\. `libgnuefi.a` - Contains `\_relocate` function for PE relocation fixups



Everything else (types, tables, protocols) is our own code.



\### CRITICAL: Calling Convention



\- `efi\_main()` must use \*\*System V ABI\*\* (default) - NO EFIAPI attribute!

\- UEFI protocol function pointers must use \*\*MS ABI\*\* (EFIAPI attribute)



The calling chain:

```

UEFI Firmware → \_start (MS ABI)

&nbsp;                  ↓

&nbsp;              crt0 converts

&nbsp;                  ↓

&nbsp;           efi\_main (System V ABI)  ← Your code starts here

&nbsp;                  ↓

&nbsp;           UEFI functions (MS ABI)  ← These need EFIAPI on typedefs

```



\### Boot Process



1\. UEFI loads `BOOTX64.EFI` from `EFI/BOOT/` on FAT partition

2\. Bootloader initializes GOP (graphics), finds ACPI RSDP, loads kernel

3\. Bootloader gets memory map and exits boot services

4\. Bootloader jumps to kernel, passing `BootInfo` structure

5\. Kernel draws to framebuffer and halts



\## Next Steps



After this foundation, typical OS development continues with:

\- GDT (Global Descriptor Table) setup

\- IDT (Interrupt Descriptor Table) and interrupt handlers

\- Physical memory allocator

\- Virtual memory / paging

\- Keyboard/mouse input

\- Process scheduler

\- System calls

\- File system



\## Resources



\- UEFI Specification: https://uefi.org/specifications

\- OSDev Wiki: https://wiki.osdev.org/UEFI

\- gnu-efi: https://sourceforge.net/projects/gnu-efi/



