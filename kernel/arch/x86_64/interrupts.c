#include "kernel/interrupts.h"
#include "arch_x86_64/idt.h"



extern void load_idt( __uint128_t* idt );

GLOBAL_STATUS  
InitialiseInterrupts(
    void
)
{
    return STATUS_OK;
}
