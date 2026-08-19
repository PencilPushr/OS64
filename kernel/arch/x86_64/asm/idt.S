// arch_x86_64 
// routines for interfacing with interrupts

.intel_syntax noprefix
.section .text
.code64

.extern InterruptServiceRoutineHandler

.macro _push_general_registers
    push r15   
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rsi
    push rdi
    push rbp
    push rdx
    push rcx
    push rbx
    push rax
.endm

.macro _pop_general_registers
    pop rax
    pop rbx
    pop rcx 
    pop rdx 
    pop rbp
    pop rdi 
    pop rsi 
    pop r8
    pop r9
    pop r10 
    pop r11 
    pop r12 
    pop r13 
    pop r14 
    pop r15
.endm

.macro _push_segement_registers
    // cannot push ds and es onto stack as is it throws #UD fault...
    mov ax, ds 
    push rax
    mov ax, es 
    push rax
    push fs 
    push gs
.endm

.macro _pop_segment_registers
    pop gs 
    pop fs
    pop rax 
    mov es, ax 
    pop rax 
    mov ds, ax
.endm

.macro _interrupt_service_routine_e vector
    .global _interrupt_service_routine\vector
    _interrupt_service_routine\vector:

        // error code for interrupt implicitly pushed onto stack 
        push \vector

        _push_general_registers
        _push_segement_registers

        mov rdi, rsp // pass stack space to isr handler 
        cld 
        call InterruptServiceRoutineHandler

        _pop_segment_registers
        _pop_general_registers

        // clean error code and vector from stack
        add rsp, 16 

        // iretq instruction used to switch back to interrupting process
        // similar to a ret but restores EFLAGS state
        iretq 
.endm

.macro _interrupt_service_routine_ne vector
    .global _interrupt_service_routine\vector
    _interrupt_service_routine\vector:
        
        push 0
        push \vector

        _push_general_registers
        _push_segement_registers

        mov rdi, rsp // pass stack space to isr handler 
        cld 
        call InterruptServiceRoutineHandler

        _pop_segment_registers
        _pop_general_registers

        // clean error code and vector from stack
        add rsp, 16 

        // iretq instruction used to switch back to interrupting process
        // similar to a ret but restores EFLAGS state
        iretq
.endm

_interrupt_service_routine_ne 0
_interrupt_service_routine_ne 1
_interrupt_service_routine_ne 2
_interrupt_service_routine_ne 3
_interrupt_service_routine_ne 4
_interrupt_service_routine_ne 5
_interrupt_service_routine_ne 6
_interrupt_service_routine_ne 7
_interrupt_service_routine_e 8
_interrupt_service_routine_ne 9
_interrupt_service_routine_e 10
_interrupt_service_routine_e 11
_interrupt_service_routine_e 12
_interrupt_service_routine_e 13
_interrupt_service_routine_e 14
_interrupt_service_routine_ne 15
_interrupt_service_routine_ne 16
_interrupt_service_routine_e 17
_interrupt_service_routine_ne 18
_interrupt_service_routine_ne 19
_interrupt_service_routine_ne 20
_interrupt_service_routine_e 21
_interrupt_service_routine_ne 22
_interrupt_service_routine_ne 23
_interrupt_service_routine_ne 24
_interrupt_service_routine_ne 25
_interrupt_service_routine_ne 26
_interrupt_service_routine_ne 27
_interrupt_service_routine_ne 28
_interrupt_service_routine_ne 29
_interrupt_service_routine_ne 30
_interrupt_service_routine_ne 31

// 
// Wrapper around lidt instruction for setting the IDT
// void load_idt( __uint128_t* idt )
// Paramters: 
//  rdi - a pointer to the idt descriptor to be used
//

.global _load_idt
.type _load_idt, @function
_load_idt:
    lidt [rdi]
    ret
.size _load_idt, . - _load_idt


