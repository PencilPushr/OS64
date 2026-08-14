#ifndef ARCH_X64_INTERRUPTS_H
#define ARCH_X64_INTERRUPTS_H

#include <stdint.h>

//
// Interrupt vector froms 0 to 31 are reserved for predefined exceptions and interrupts.
// Each IDT entry (or gate) holds base address, access flags and segment selector for the interrupt handler.
// Address holds the virtual address of the interrupt service function, ISR, and is what the processor calls for the specific interrupt. 
// 

// 
// Based on intel sdm Vol.3A Chapter 7 
//

#define IDT_MAX_VECTORS 256

//
// Intel Sdm Vol.3A Chapter 7.14.1
// In 64-bit bit long mode each trap gate is 16 bytes in length and provides a 64-bit offset for RIP. 
//
typedef struct _IDT_INTERRUPT_TRAP_GATE
{
    uint16_t LowOffset;         // [15:0]   
    uint16_t SegmentSelector;   // [31:16]
    uint8_t  IstOffset;         // [39:32]     Interrupt stack table offset ( when clear dont switch )
    uint8_t  Attributes;        // [47:40]
    uint16_t MidOffset;         // [63:48]

    uint32_t HiOffset;          // [31:0]
    uint32_t _Reserved;         // [63:32]

} __attribute__((packed)) IDT_INTERRUPT_TRAP_GATE;

static_assert(sizeof(IDT_INTERRUPT_TRAP_GATE) == 16, "IDT_INTERRUPT_TRAP_GATE size is not 16 bytes");

typedef struct _IDT_DESCRIPTOR
{
    uint16_t Limit;             // [15:0]   Size of the IDT in bytes - 1  (should be aligned to 8 bytes - 1)
    uint64_t Base;              // [63:0]   Base address of the IDT

} __attribute__((packed)) IDT_DESCRIPTOR;

static_assert(sizeof(IDT_DESCRIPTOR) == 10, "IDT_DESCRIPTOR size is not 10 bytes");

extern void _load_idt( IDT_DESCRIPTOR* IdtDescriptor );
#define LoadIDT( IdtDescriptor ) (_load_idt( IdtDescriptor ))

// idea i stole from https://forum.osdev.org/viewtopic.php?t=58001 where he pushes saved registers on the stack (and error codes/iret but thats implicit) and passes rsp to
// function that is handling the interrupt :)
typedef struct _INTERRUPT_STACK_STATE
{
    // Segment registers
    uint64_t Gs;
    uint64_t Fs;
    uint64_t Es;
    uint64_t Ds;

     // General purpose registers
    uint64_t Rax;
    uint64_t Rbx;
    uint64_t Rcx;
    uint64_t Rdx;
    uint64_t Rbp;
    uint64_t Rdi;
    uint64_t Rsi;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;

    uint64_t InterruptVector;
    uint64_t ErrorCode;

    // Extra data pushed for iret implicitly 
    uint64_t IretRip;
    uint64_t IretCs;
    uint64_t IretRFlags;
    uint64_t IretRsp;
    uint64_t IrsetRsp;

} __attribute__((packed)) INTERRUPT_STACK_STATE;

#endif // ! ARCH_X64_INTERRUPTS_H