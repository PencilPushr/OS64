// kernel/displays/display_lfb.c

#include "kernel/graphics/display.h"
#include <cstdint>
#include "display_lfb.h"

typedef struct LFBData_t
{
    uint32_t * pFrameBuffer;
    
    // Copy of DisplayDevice internals
    uint32_t Pitch; // pixels per scanline ( pitch / 4 )

    // XRGB format conversion <-> hardware format
    uint8_t RedShift;
    uint8_t GreenShift;
    uint8_t BlueShift;

} LFBData;

static LFBData g_LFBData;
static DisplayDevice g_LFBDisplayDevice;

// Straight copy from bootloader/graphics.c
/**
 * @brief Returns bit pos where a colour mask starts:
 *        Example: 0x00FF0000 -> Shift 16 ( R in XRGB )
 *                 0x000000FF -> Shift 0 ( R in RGB )
 * 
 * @param Mask Hardware agnostic format used ( We prefer XRGB ) - you must check GOP_FRAMEBUFFER_DESCRIPTOR for RedMask, GreenMask and BlueMask
 * @return uint8_t Integer amount needed to convert to hardware format
 */
static uint8_t
MaskToShift(
    IN uint32_t Mask
)
{
    if (Mask == 0) return 0;
    uint8_t Shift = 0;
    while ((Mask & 1) == 0) {
        Mask >>= 1;
        Shift++;
    }
    return Shift;
}

// Useful for putting pixels
static 
inline
uint32_t 
ConvertMaskToHwColour(
    LFBData* pLinearFrameBuffer,
    uin32_t XRGBFormat
)
{
    uint8_t R = ( XRGBFormat >> 16) & 0xFF;
    uint8_t G = ( XRGBFormat >>  8) & 0xFF;
    uint8_t B = ( XRGBFormat      ) & 0xFF;
 
    return ( ( uint32_t ) R << pLinearFrameBuffer->RedShift   ) |
           ( ( uint32_t ) G << pLinearFrameBuffer->GreenShift ) |
           ( ( uint32_t ) B << pLinearFrameBuffer->BlueShift  );

}

// Useful for getting pixels
static
inline
uint32_t
ConvertHwColourToMask(
    LFBData* pLinearFrameBuffer,
    uin32_t HWFormat
)
{
    uint8_t R = ( HWFormat >> pLinearFrameBuffer->RedShift   ) & 0xFF;
    uint8_t G = ( HWFormat >> pLinearFrameBuffer->GreenShift ) & 0xFF;
    uint8_t B = ( HWFormat >> pLinearFrameBuffer->BlueShift  ) & 0xFF;

    return  ( ( uint32_t ) R << 16 ) |
            ( ( uint32_t ) G << 8  ) |
            ( ( uint32_t ) B       );
}


//
// Operations
//

static void
KeDpPutPixel(
    DisplayDevice * Device,
    uint32_t x,
    uint32_t y
    uint32_t Colour
)
{
    LFBData * pDriver = Device->Private;

    // Bounds check - Can't write beyond framebuffer and shouldn't...
    if ( x >= pDriver->Width || y >= pDriver->Height ) return; // TODO: Return global status? this seems alarming that you are attempting to write beyond what's available.

    pDriver->pFrameBuffer[ y * pDriver->PixelsPerScanLine  + x ] = ConvertMaskToHwColour( pDriver->pFrameBuffer, Colour );

}