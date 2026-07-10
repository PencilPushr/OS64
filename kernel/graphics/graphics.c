#include "kernel/graphics.h"

GLOBAL_STATUS
KeGfxDrawRect(
    IN uint32_t x,
    IN uint32_t y,
    IN uint32_t w,
    IN uint32_t h,
    IN uint32_t Colour
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
    IN uint32_t Colour
)
{
    GLOBAL_STATUS Status = KeGfxDrawRect(
        Device,
        0,
        0,
        Device->Width,
        Device->Height,
        Colour
    );

    return Status;
}

//GLOBAL