#include "kernel/graphics.h"

GLOBAL_STATUS
DrawRect(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN uint32_t x,
    IN uint32_t y,
    IN uint32_t w,
    IN uint32_t h,
    IN uint32_t Colour
)
{
    if ( !pFrameBufferDesc )
        return STATUS_FRAMEBUFFER_WAS_NULL;
    
    uint32_t* Pixels = (uint32_t *)pFrameBufferDesc->Base;
    int PixelsPerScanLine = pFrameBufferDesc->Pitch / 4;

    for( uint32_t Row = y; Row < y + h && Row < pFrameBufferDesc->Height; Row++ )
    {
        for( uint32_t Col = x; Col < x + w && Col < pFrameBufferDesc->Width; Col++ )
        {
            Pixels[ Row * PixelsPerScanLine + Col ] = Colour;
        }
    }

    return OK;
}

GLOBAL_STATUS
FillScreen(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN uint32_t Colour
)
{
    GLOBAL_STATUS Status = DrawRect(
        pFrameBufferDesc,
        0,
        0,
        pFrameBufferDesc->Width,
        pFrameBufferDesc->Height,
        Colour
    );

    return Status;
}

GLOBAL