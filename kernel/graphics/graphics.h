#ifndef KERNEL_GRAPHICS_H
#define KERNEL_GRAPHICS_H

#include <stdint.h>

#include "display.h"
#include "common/font.h"
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

/*
 * Draw one bitmap glyph at a framebuffer pixel position.
 *
 * Font rows are stored MSB-first.  The renderer deliberately goes through
 * DisplayOps rather than knowing anything about an LFB, GOP, pitch, masks,
 * or framebuffer layout.
 */
GLOBAL_STATUS
KeGfxDrawGlyph(
    const Font *pFont,
    uint32_t Codepoint,
    uint32_t x,
    uint32_t y,
    uint32_t FgColour,
    uint32_t BgColour
);

#endif // KERNEL_GRAPHICS_H
