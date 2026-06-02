#ifndef KERNEL_DISPLAY_H
#define KERNEL_DISPLAY_H

// Forward declare - the actual struct data is either display.c or a driver file
struct DisplayDevice;

// Interface
typedef struct DisplayModeOps_t
{
    int         ( *GetMode )( struct DisplayDevice * Device, struct DisplayMode * Mode );
    int         ( *SetMode )( struct DisplayDevice * Device, )
} IDisplayModeOps;

// Interface - display backend must provide this
typedef struct DisplayOps_t
{
    void        ( *PutPixel )( struct DisplayDevice * Device, uint32_t x, uint32_t y, uint32_t Colour );
    uint32_t    ( *GetPixel )( struct DisplayDevice * Device, uint32_t x, uint32_t y );
    void        ( *DrawRect )( struct DisplayDevice * Device, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t Colour );
} IDisplayOps;

typedef struct DisplayDevice_t
{
    const char * Name; // "efifb", "vgafb", "gpu0"

    const IDisplayModeOps * ModeOps;
    const IDisplayOps *DisplayOps;

    uint32_t Width;
    uint32_t Height;
    uint32_t Pitch;
    uin32_t bpp;

    void* DriverSpecific;
} DisplayDevice;

// Methods
// The system should only have one display device at the time (Not sure about later on, but we are basically efifb right now)

// Register the active display device. Should be called by driver during init.
// Warning: Calling this again with an already active input will replace it.
void
KeDpSetDevice( 
    IN OUT DisplayDevice * Device 
);

// Gets the active display device. NULL if no device.
DisplayDevice* 
KeDpGetDevice( 
    void 
);

void
KeDpInitDisplayOpsDefaults(
    void
);


#endif // KERNEL_DISPLAY_H