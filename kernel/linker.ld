/* kernel/linker.ld */
/* Load kernel at 1MB (0x100000) */
ENTRY(kmain)

/* May need to shift it to a 2mib position if we fail to allocate the kernel at that range - fine for now */
SECTIONS {
    . = 0x100000;

    .text : {
        /* Realised that kmain is never guarenteed to come first */
        *(.text.kernel_main)
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
    }
}