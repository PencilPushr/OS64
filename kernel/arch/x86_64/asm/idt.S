// arch_x86_64 
// routines for interfacing with interrupts

.section .text
.code64

[extern InterruptServiceRoutineHandler]

%macro _push_general_registers 0
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
%endmacro

%macro _push_segement_registers 0
    ; cannot push ds and es onto stack as is it throws undefined opcode fault...
    mov rax, ds 
    push rax
    mov rax, es 
    push rax
    push fs 
    push gs
%endmacro

%macro _interrupt_service_routine_e 1
    [global _interrupt_service_routine_e%1]
    _interrupt_service_routine_e%1:
        
        ; error code for interrupt implicitly pushed onto stack 
        push %1

        _push_general_registers
        _push_segement_registers

        mov rdi, rsp ; pass stack space to isr handler 
        cld 
        call InterruptServiceRoutineHandler




    


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


