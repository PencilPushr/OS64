#ifndef COMMON_BOOTINFO_H
#define COMMON_BOOTINFO_H

#include <stdint.h>

typedef struct GOP_FRAMEBUFFER_DESCRIPTOR
{
    uint64_t Base;
    uint32_t Width;
    uint32_t Height;
    uint32_t Pitch;
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t RSVDMask;
    uint8_t  Bpp;
    uint8_t  _pad[3];

} GOP_FRAMEBUFFER_DESCRIPTOR;

typedef struct _MEMORY_MAP_DESCRIPTOR
{
    uint32_t Type;
    uint32_t Pad;
    uint64_t PhysicalStart;
    uint64_t VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;

} MEMORY_MAP_DESCRIPTOR;

typedef struct _MEMORY_MAP 
{
    MEMORY_MAP_DESCRIPTOR* Descriptor;
    uint64_t MapSize;
    uint64_t Key;
    uint64_t DescriptorSize;
    uint32_t Version;

} MEMORY_MAP;

typedef struct _BOOT_INFO
{
    GOP_FRAMEBUFFER_DESCRIPTOR FrameBufferDescriptor;
    MEMORY_MAP                 MemoryMap; 
    
} BOOT_INFO;

#endif // !COMMON_BOOTINFO_H
