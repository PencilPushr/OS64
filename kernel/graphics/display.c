// kernel/display.c

#include "display.h"

// Display device management
//
// This is intentionally minimal — just the active device pointer.
// All real work happens in the driver files (display_lfb.c, etc.)
// and in the graphics layer (graphics.c).

static DisplayDevice * g_pDisplayDevice = 0;

void 
KeDpSetDevice( 
    IN OUT DisplayDevice *Device 
) 
{
    g_pDisplayDevice = Device;
}

DisplayDevice 
KeDpGetDevice( 
    void 
)
{
    return g_pDisplayDevice;
}