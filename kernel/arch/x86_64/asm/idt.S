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

.global load_idt
.type load_idt, @function
load_idt:
    lidt (%rdi)
    ret
.size load_idt, . - load_idt



