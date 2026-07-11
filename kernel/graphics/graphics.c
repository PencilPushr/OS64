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
    DisplayDevice* Device = KeDpGetDevice();
    if ( !Device )
        return STATUS_INVALID_ARGUMENT; // Todo: fix this, make a a failed status code when getting driver (bit more generic than graphics related)

    Device->DisplayOps->FillRect( Device, x, y, w, h, Colour);

    return OK;
}

GLOBAL_STATUS
KeGfxFillScreen(
    uint32_t Colour
)
{
    DisplayDevice* Device = KeDpGetDevice();

    if ( !Device )
        return STATUS_INVALID_ARGUMENT;

    GLOBAL_STATUS Status = KeGfxDrawRect(
        0,
        0,
        Device->Width,
        Device->Height,
        Colour
    );

    return Status;
}

//GLOBAL_STATUS
// KeGfxDrawSplash