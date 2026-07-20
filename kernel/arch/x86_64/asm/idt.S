// arch_x86_64 
// routines for interfacing with interrupts

.section .text
.code64

// 
// Wrapper around lidt instruction for setting the IDT
// void load_idt( __uint128_t* idt )
// Paramters: 
//  rdi - a pointer to the idt descriptor to be used
//

.global _load_idt
.type _load_idt, @function
_load_idt:
    lidt (%rdi)
    ret
.size _load_idt, . - _load_idt


