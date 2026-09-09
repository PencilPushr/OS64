#include "graphics/graphics.h"

GLOBAL_STATUS
KeGfxDrawRect(
    uint32_t x,
    uint32_t y,
    uint32_t w,
    uint32_t h,
    uint32_t Colour
)
{
    DisplayDevice *Device = KeDpGetDevice();

    if ( Device == NULL ||
         Device->DisplayOps == NULL ||
         Device->DisplayOps->FillRect == NULL )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    Device->DisplayOps->FillRect( Device, x, y, w, h, Colour );

    return OK;
}

GLOBAL_STATUS
KeGfxFillScreen(
    uint32_t Colour
)
{
    DisplayDevice *Device = KeDpGetDevice();

    if ( Device == NULL )
        return STATUS_INVALID_ARGUMENT;

    return KeGfxDrawRect(
        0,
        0,
        Device->Width,
        Device->Height,
        Colour
    );
}

GLOBAL_STATUS
KeGfxDrawGlyph(
    const Font *pFont,
    uint32_t Codepoint,
    uint32_t x,
    uint32_t y,
    uint32_t FgColour,
    uint32_t BgColour
)
{
    if ( pFont == NULL ||
         pFont->GlyphData == NULL ||
         pFont->Width == 0 ||
         pFont->Height == 0 ||
         pFont->BytesPerRow == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    DisplayDevice *Device = KeDpGetDevice();

    if ( Device == NULL ||
         Device->DisplayOps == NULL ||
         Device->DisplayOps->PutPixel == NULL )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    const uint8_t *Glyph = FontGetGlyph( pFont, Codepoint );

    if ( Glyph == NULL )
        return STATUS_INVALID_ARGUMENT;

    for ( uint32_t Row = 0; Row < pFont->Height; ++Row )
    {
        const uint8_t *GlyphRow = Glyph + Row * pFont->BytesPerRow;

        for ( uint32_t Col = 0; Col < pFont->Width; ++Col )
        {
            const uint32_t ByteIndex = Col / 8u;
            const uint32_t BitIndex  = Col % 8u;
            const uint8_t  Mask      = (uint8_t)( 0x80u >> BitIndex );

            const uint32_t Colour =
                ( GlyphRow[ ByteIndex ] & Mask ) ? FgColour : BgColour;

            Device->DisplayOps->PutPixel(
                Device,
                x + Col,
                y + Row,
                Colour
            );
        }
    }

    return OK;
}
