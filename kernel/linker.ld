/* kernel/linker.ld */
/* Load kernel at 2MB (0x200000;) */
ENTRY(kmain)

SECTIONS {
    . = 0x200000;

    .text : ALIGN(0x1000)
    {
        *(.text*)
    }

    .rodata :  ALIGN(0x1000)
    {
        *(.rodata*)
    }

    .data : ALIGN(0x1000)
    {
        *(.data*)
    }

    .bss : ALIGN(0x1000)
    {
        *(.bss*)
        *(COMMON)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
    }
}