#ifndef KERNEL_GRAPHICS_H
#define KERNEL_GRAPHICS_H

#include "display.h"
#include "common/status_codes.h"

GLOBAL_STATUS
KeGfxDrawRect(
    uint32_t x,
    uint32_t y,
    uint32_t w,
    uint32_t h,
    uint32_t Colour
);

GLOBAL_STATUS
KeGfxFillScreen(
    uint32_t Colour
);

#endif // KERNEL_GRAPHICS_H