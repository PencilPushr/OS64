#include "kernel/interrupts.h"
#include "common/bootinfo.h"
#include "common/status_codes.h"
#include "common/common.h"
#include "arch_x86_64/serial.h"

KMAIN_ENTRY( kmain, BootInfo )
{
    if( BootInfo == NULL )
    {
        return STATUS_INVALID_BOOT_INFO;
    }

    GLOBAL_STATUS Status = STATUS_ERROR;
    InitialiseInterrupts();


    char WriteToPort[] = "init\0";
    SerialWriteEx( 0xE9, ARRAY_LENGTH( WriteToPort ), (uint8_t*)WriteToPort );

    *(volatile uint8_t*)0x7FFFFFFF = 0;

    char p[] = "faulted?\0";
    SerialWriteEx( 0xE9, ARRAY_LENGTH( p ), (uint8_t*)p );

    return 0xC1A;
}