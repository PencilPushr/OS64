#include "kernel/interrupts.h"
#include "arch_x86_64/idt.h"
#include "arch_x86_64/serial.h"

__attribute__((aligned(0x10)))
static IDT_INTERRUPT_TRAP_GATE g_IDT[ IDT_MAX_VECTORS ];
static IDT_DESCRIPTOR g_IDTDescriptor;

void IDTPageFaultHandler( void )
{
    char WriteToPort[] = "page fault\0";
    SerialWriteEx( 0xE9, ARRAY_LENGTH( WriteToPort ), (uint8_t*)WriteToPort );
    __asm__ volatile( "iretq" );
}


void IDTServiceHandler( void )
{
    char WriteToPort[] = "service fault\0";
    SerialWriteEx( 0xE9, ARRAY_LENGTH( WriteToPort ), (uint8_t*)WriteToPort );
    __asm__ volatile( "iretq" );
}


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
    IdtEntry->SegmentSelector = 0x0; // Kernel code segment selector
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
    g_IDTDescriptor.Limit = (uint16_t)sizeof( IDT_INTERRUPT_TRAP_GATE ) * IDT_MAX_VECTORS - 1;
    g_IDTDescriptor.Base = (uint64_t)&g_IDT[0];

    SetIDTEntry( 0xE, IDTPageFaultHandler, 0x8E ); // Page fault handler
    SetIDTEntry( 0x20, IDTServiceHandler, 0x8E ); // Service handler

    LoadIDT( &g_IDTDescriptor );
     __asm__ volatile ("sti");
    return STATUS_OK;
}
