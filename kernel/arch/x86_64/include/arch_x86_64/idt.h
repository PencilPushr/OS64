#ifndef ARCH_X64_INTERRUPTS_H
#define ARCH_X64_INTERRUPTS_H

#include <stdint.h>

// 
// Based on intel sdm Vol.3A Chapter 7 
//

#define IDT_MAX_VECTORS 255

//
// Intel Sdm Vol.3A Chapter 7.14.1
// In 64-bit bit long mode each trap gate is 16 bytes in length and provides a 64-bit offset for RIP. 
//
typedef struct _IDT_INTERRUPT_TRAP_GATE
{
    uint16_t LowOffet;          // [15:0]   
    uint16_t SegmentSelector;   // [31:16]
    uint8_t  IstOffset;         // [39:32]     Interrupt stack table offset ( when clear dont switch )
    uint8_t  Attributes;        // [47:40]
    uint16_t MiOffset;          // [63:48]

    uint32_t HiOffset;          // [31:0]
    uint32_t _Reserved;         // [63:32]

} __attribute__((packed)) IDT_INTERRUPT_TRAP_GATE;


#endif // ! ARCH_X64_INTERRUPTS_H