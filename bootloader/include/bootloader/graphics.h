#ifndef BOOTLOADER_GRAPHICS_H 
#define BOOTLOADER_GRAPHICS_H

#include "boot.h"
#include "stdint.h"



typedef struct FramebufferInfo 
{
    uint64_t Base;
    uint32_t Width;
    uint32_t Height;
    uint32_t Pitch;
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t Bluemask;
    uint32_t RSVDMask;
    uint8_t  Bpp;
    uint8_t  _pad[3];
} FramebufferInfo;

EFI_STATUS
BlGfxInitialiseFrameBuffer(
    IN EFI_SYSTEM_TABLE* ST
    IN OUT FramebufferInfo* pFramebuffer
);

#endif // BOOTLOADER_GRAPHICS_H