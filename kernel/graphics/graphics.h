#ifndef KERNEL_GRAPHICS_H
#define KERNEL_GRAPHICS_H

#include "display.h"

GLOBAL_STATUS
KeGfxDrawRect(
    IN DisplayDevice* Device,
    IN uint32_t x,
    IN uint32_t y,
    IN uint32_t w,
    IN uint32_t h,
    IN uint32_t Colour
);

GLOBAL_STATUS
KeGfxFillScreen(
    IN DisplayDevice* Device,
    IN uint32_t Colour
);



#endif // KERNEL_GRAPHICS_H