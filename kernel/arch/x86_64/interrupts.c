#include "kernel/interrupts.h"
#include "arch_x86_64/idt.h"
#include "arch_x86_64/serial.h"

__attribute__((aligned(0x10)))
static IDT_INTERRUPT_TRAP_GATE g_IDT[ IDT_MAX_VECTORS ];
static IDT_DESCRIPTOR g_IDTDescriptor;

void 
SetIDTEntry( 
    uint8_t Vector, 
    void*   InterruptHandler,
    uint8_t Flags
)
{
    IDT_INTERRUPT_TRAP_GATE* IdtEntry = &g_IDT[ Vector ];

    uint64_t HandlerAddress = (uint64_t)InterruptHandler;

    IdtEntry->LowOffset       = (uint16_t)(HandlerAddress & 0xFFFF);
    IdtEntry->SegmentSelector = 0x38; // Kernel code segment selector...for now qemu shows it as 0x38
    IdtEntry->IstOffset       = 0x0; // No IST
    IdtEntry->Attributes      = Flags;
    IdtEntry->MidOffset       = (uint16_t)((HandlerAddress >> 16) & 0xFFFF); 
    IdtEntry->HiOffset        = (uint32_t)((HandlerAddress >> 32) & 0xFFFFFFFF);
    IdtEntry->_Reserved       = 0;
}

GLOBAL_STATUS  
InitialiseInterrupts(
    void
)
{
    // limit to specify how many interrupt vectors we have (we do all 255 for now)
    g_IDTDescriptor.Limit = (uint16_t)sizeof( IDT_INTERRUPT_TRAP_GATE ) * IDT_MAX_VECTORS - 1;
    g_IDTDescriptor.Base = (uint64_t)&g_IDT[0];

    SetIDTEntry( 0 , _interrupt_service_routine0 , 0x8E );
    SetIDTEntry( 1 , _interrupt_service_routine1 , 0x8E );
    SetIDTEntry( 2 , _interrupt_service_routine2 , 0x8E );
    SetIDTEntry( 3 , _interrupt_service_routine3 , 0x8E );
    SetIDTEntry( 4 , _interrupt_service_routine4 , 0x8E );
    SetIDTEntry( 5 , _interrupt_service_routine5 , 0x8E );
    SetIDTEntry( 6 , _interrupt_service_routine6 , 0x8E );
    SetIDTEntry( 7 , _interrupt_service_routine7 , 0x8E );
    SetIDTEntry( 8 , _interrupt_service_routine8 , 0x8E );
    SetIDTEntry( 9 , _interrupt_service_routine9 , 0x8E );
    SetIDTEntry( 10, _interrupt_service_routine10, 0x8E );
    SetIDTEntry( 11, _interrupt_service_routine11, 0x8E );
    SetIDTEntry( 12, _interrupt_service_routine12, 0x8E );
    SetIDTEntry( 13, _interrupt_service_routine13, 0x8E );
    SetIDTEntry( 14, _interrupt_service_routine14, 0x8E );
    SetIDTEntry( 15, _interrupt_service_routine15, 0x8E );
    SetIDTEntry( 16, _interrupt_service_routine16, 0x8E );
    SetIDTEntry( 17, _interrupt_service_routine17, 0x8E );
    SetIDTEntry( 18, _interrupt_service_routine18, 0x8E );
    SetIDTEntry( 19, _interrupt_service_routine19, 0x8E );
    SetIDTEntry( 20, _interrupt_service_routine20, 0x8E );
    SetIDTEntry( 21, _interrupt_service_routine21, 0x8E );
    SetIDTEntry( 22, _interrupt_service_routine22, 0x8E );
    SetIDTEntry( 23, _interrupt_service_routine23, 0x8E );
    SetIDTEntry( 24, _interrupt_service_routine24, 0x8E );
    SetIDTEntry( 25, _interrupt_service_routine25, 0x8E );
    SetIDTEntry( 26, _interrupt_service_routine26, 0x8E );
    SetIDTEntry( 27, _interrupt_service_routine27, 0x8E );
    SetIDTEntry( 28, _interrupt_service_routine28, 0x8E );
    SetIDTEntry( 29, _interrupt_service_routine29, 0x8E );
    SetIDTEntry( 30, _interrupt_service_routine30, 0x8E );
    SetIDTEntry( 31, _interrupt_service_routine31, 0x8E );

    LoadIDT( &g_IDTDescriptor );
    // don't handle external interrupts until we can resolve them (apic)
    // __asm__ volatile ("sti");
    return STATUS_OK;
}


void 
InterruptServiceRoutineHandler( 
    INTERRUPT_STACK_STATE* rsp 
)
{
    char WriteToPort[] = "interrupt service handler\0";
    SerialWriteEx( 0xE9, ARRAY_LENGTH( WriteToPort ), (uint8_t*)WriteToPort );
}