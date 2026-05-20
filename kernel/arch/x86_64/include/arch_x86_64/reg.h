#ifndef ARCH_X64_REG_H
#define ARCH_X64_REG_H

#include <stdint.h>

typedef union _CPUID_REGISTERS
{
    __uint128_t Value;

    struct 
    {
        uint32_t Eax;
        uint32_t Ebx;
        
    };
} CPUID_REGSTERS;


#endif // ! ARCH_X64_REG_h