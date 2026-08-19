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

#define INTERRUPT_ERROR_EXTERNAL_EVENT( ErrorCode )      ( (uint64_t)ErrorCode & 0ull )
#define INTERRUPT_ERROR_DESCIRPTOR_LOCATION( ErrorCode ) ( ((uint64_t)ErrorCode >> 1) & 0ull )
#define INTERRUPT_ERROR_DESCRIPTOR_TABLE( ErrorCode )    ( ((uint64_t)ErrorCode >> 2) & 0ull )
#define INTERRPT_ERROR_SEGMENT_SELECTOR( ErrorCode )     ( ((uint32_t)ErrorCode << 16) >> 19 )

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
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;

    uint64_t InterruptVector;
    uint64_t ErrorCode;

    // Extra data pushed for iretq implicitly 
    uint64_t IretRip;
    uint64_t IretCs;
    uint64_t IretRFlags;
    uint64_t IretRsp;
    uint64_t IretSs;

} __attribute__((packed)) INTERRUPT_STACK_STATE;

extern void _interrupt_service_routine0();
extern void _interrupt_service_routine1();
extern void _interrupt_service_routine2();
extern void _interrupt_service_routine3();
extern void _interrupt_service_routine4();
extern void _interrupt_service_routine5();
extern void _interrupt_service_routine6();
extern void _interrupt_service_routine7();
extern void _interrupt_service_routine8();
extern void _interrupt_service_routine9();
extern void _interrupt_service_routine10();
extern void _interrupt_service_routine11();
extern void _interrupt_service_routine12();
extern void _interrupt_service_routine13();
extern void _interrupt_service_routine14();
extern void _interrupt_service_routine15();
extern void _interrupt_service_routine16();
extern void _interrupt_service_routine17();
extern void _interrupt_service_routine18();
extern void _interrupt_service_routine19();
extern void _interrupt_service_routine20();
extern void _interrupt_service_routine21();
extern void _interrupt_service_routine22();
extern void _interrupt_service_routine23();
extern void _interrupt_service_routine24();
extern void _interrupt_service_routine25();
extern void _interrupt_service_routine26();
extern void _interrupt_service_routine27();
extern void _interrupt_service_routine28();
extern void _interrupt_service_routine29();
extern void _interrupt_service_routine30();
extern void _interrupt_service_routine31();

#endif // ! ARCH_X64_INTERRUPTS_H