// kernel/displays/display_lfb.c

#include "kernel/graphics/display.h"
#include <stdint.h>
#include "display_lfb.h"

typedef struct LFBData_t
{
    volatile uint32_t * pFrameBuffer;

    uint32_t Width;
    uint32_t Height;
    
    // Copy of DisplayDevice internals
    uint32_t PitchBytes; // pixels per scanline ( pitch / 4 )
    uint32_t PixelsPerScanLine; 
    uint32_t Bpp;

    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;

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
    if (Mask == 0) 
        return 0;

    uint8_t Shift = 0;

    while ((Mask & 1u) == 0) 
    {
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
    uint32t_t XRGBFormat
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
    uint32_t HWFormat
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
KeDpLfbPutPixel(
    DisplayDevice * Device,
    uint32_t x,
    uint32_t y,
    uint32_t Colour
)
{
    LFBData * pDriver = Device->DriverSpecific;

    // Bounds check - Can't write beyond framebuffer and shouldn't...
    if ( x >= pDriver->Width || y >= pDriver->Height ) // TODO: Return global status? this seems alarming that you are attempting to write beyond what's available.
        return;

    uint32_t HwColour = ConvertMaskToHwColour( pDriver, Colour );

    pDriver->pFrameBuffer[ y * pDriver->PixelsPerScanLine  + x ] = HwColour;

}

static void
KeDpLfbFillRect(
    DisplayDevice* Device,
    uint32_t x,
    uint32_t y,
    uint32_t w,
    uint32_t h,
    uint32_t Colour
)
{
    LFBData * pDriver = Device->DriverSpecific;

    if ( w == 0 || h == 0 )
        return;

    // No clipping check for up and left bounds:
    //
    //          v
    //          ____
    //     >   |                but             |  <
    //         |                            ____|
    //                  
    //                                         ^
    //  Left and Up are impossible to clip unless overflowed due to unsigned: x or y != < 0
    //  But right and bottom are possible to overflow and write into nothingness/overflow. 
    //  So we just clamp it.


    if ( w > pDriver->Width - x )
        w = pDriver->Width - x;

    if ( h > pDriver->Height - y )
        h = pDriver->Height - y;

    uint32_t HwColour = ConvertMaskToHwColour( pDriver, Colour );

    for( uint32_t row = 0; row < h; row++ )
    {
        volatile uint32_t* Dst = pDriver->pFrameBuffer + ( y + row ) * pDriver->PixelsPerScanLine + x;

        for( uint32_t col = 0; col < w; col++ )
        {
            Dst[ col ] = HwColour;
        }
    }
}

static void
KeDpLfbDrawRect(
    uint32_t x,
    uint32_t y,
    uint32_t w,
    uint32_t h,
    uint32_t Thickness,
    uint32_t Colour
)
{
    if ( w == 0 || h == 0 || Thickness == 0 )

    if ( Thickness * 2 > w )
        Thickness = ( w + 1 ) / 2;
        
    if ( Thickness * 2 > h )
        Thickness = ( w + 1 ) / 2;

    // Draw top, bottom, left and right with FillRect

    // KeDpLfbFillRect( DisplayDevice, x, y, w, Thickness, Colour );
    // KeDpLfbFillRect( DisplayDevice, x, y + h - Thickness, w, Thickness, Colour ); // Move down by height and up by thickness amount (remember we draw top left to bottom right )
    // KeDpLfbFillRect( DisplayDevice, x, y + thickness, )
}

// Todo: Forward declare the functions so they can go on the top. Then move g_LFBOps just below.
static const IDisplayOps g_LFBOps =
{
    .PutPixel = KeDpLfbPutPixel,
    .GetPixel = KeDpLfbGetPixel,
    .FillRect = KeDpLfbFillRect,
};

#define BPP_HARD32

GLOBAL_STATUS
KeDpInitLFB(
    IN GOP_FRAMEBUFFER_DESCRIPTOR * FrameBufferDesc
)
{
    if ( FrameBufferDesc == NULL )
        return GLOBAL_STATUS_INVALID_PARAMETER;

        if (FrameBufferDesc->Base == 0)
        return GLOBAL_STATUS_INVALID_PARAMETER;

#ifdef BPP_HARD32 // This only exists because for now we only support 32 bit pixels format - change when we want to support 24 or 16

    if (FrameBufferDesc->Bpp != 32)
        return GLOBAL_STATUS_UNSUPPORTED;

#endif

    g_LFBData.pFrameBuffer = (volatile uint32_t *)(uintptr_t)FrameBufferDesc->Base;

    g_LFBData.Width  = FrameBufferDesc->Width;
    g_LFBData.Height = FrameBufferDesc->Height;
    g_LFBData.Bpp    = FrameBufferDesc->Bpp;

    g_LFBData.PitchBytes = FrameBufferDesc->PitchBytes;
    g_LFBData.PixelsPerScanLine = FrameBufferDesc->PixelsPerScanLine;

    g_LFBData.RedMask   = FrameBufferDesc->RedMask;
    g_LFBData.GreenMask = FrameBufferDesc->GreenMask;
    g_LFBData.BlueMask  = FrameBufferDesc->BlueMask;

    g_LFBData.RedShift   = MaskToShift(FrameBufferDesc->RedMask);
    g_LFBData.GreenShift = MaskToShift(FrameBufferDesc->GreenMask);
    g_LFBData.BlueShift  = MaskToShift(FrameBufferDesc->BlueMask);

    g_LFBDisplayDevice.Name = "lfb";

    g_LFBDisplayDevice.DisplayOps = &g_LFBOps;

    g_LFBDisplayDevice.Width  = FrameBufferDesc->Width;
    g_LFBDisplayDevice.Height = FrameBufferDesc->Height;
    g_LFBDisplayDevice.Bpp    = FrameBufferDesc->Bpp;

    g_LFBDisplayDevice.PitchBytes = FrameBufferDesc->PitchBytes;
    g_LFBDisplayDevice.PixelsPerScanLine = FrameBufferDesc->PixelsPerScanLine;

    g_LFBDisplayDevice.DriverSpecific = &g_LFBData;

    KeDpSetDevice(&g_LFBDisplayDevice);

    return GLOBAL_STATUS_SUCCESS;

}