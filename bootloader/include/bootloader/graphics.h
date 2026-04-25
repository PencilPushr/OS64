#ifndef BOOTLOADER_GRAPHICS_H 
#define BOOTLOADER_GRAPHICS_H

#include "boot.h"

/**
 * 
 * @
 */
EFI_STATUS
BlGfxInitialiseFrameBuffer(
    IN OUT GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBuffer
);

#endif // !BOOTLOADER_GRAPHICS_H