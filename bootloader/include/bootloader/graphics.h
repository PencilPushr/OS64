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

// Implemented a clear screen function that just wraps static DrawRect - but I don't want to expose either
// Leaving it as extern for intent that unless strictly necessary - don't use it.
/*

EFI_STATUS
BlGfxClearScreen(
    IN FrameBufferInfo_t FrameBufferIno
)

*/

#endif // !BOOTLOADER_GRAPHICS_H