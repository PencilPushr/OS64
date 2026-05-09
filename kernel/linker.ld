/* kernel/linker.ld */
/* Load kernel at 1MB (0x100000) */
ENTRY(kmain)

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