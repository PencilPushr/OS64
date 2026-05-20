#include "arch_x86_64/serial.h"

uint8_t _SEEN_PORTS[ MAX_SERIAL_PORTS ] = { 0 };

static 
inline
void
outb( 
    uint16_t Port, 
    uint8_t  Data 
)
{
    __asm__ volatile ("outb %0, %1" : : "a"(Data), "Nd"(Port));
}

static 
inline 
uint8_t
inb( 
    uint16_t Port
)
{
    uint8_t Value;
    __asm__ volatile ("inb %1, %0" : "=a"(Value) : "Nd"(Port));
    return Value;
}

GLOBAL_STATUS 
SerialWrite(
    uint16_t Port,
    uint8_t  Data
)
{
    return STATUS_NOT_IMPLEMENTED;
};

GLOBAL_STATUS 
SerialWriteEx(
    uint16_t Port,
    uint64_t Size,
    uint8_t* Data
)
{
    if( Data == NULL || Size == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    for( uint64_t Index = 0; Index < Size; Index++ )
    {
        outb( Port, Data[Index] );
    }

    return STATUS_OK;
};

GLOBAL_STATUS 
SerialRead(
    uint16_t Port,
    uint8_t* Data
)
{
    return STATUS_NOT_IMPLEMENTED;
};

GLOBAL_STATUS 
SerialReadEx(
    uint16_t Port,
    uint64_t Size,
    uint8_t* Data
)
{
    return STATUS_NOT_IMPLEMENTED;
};
