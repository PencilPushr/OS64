#ifndef KERNEL_DISPLAY_H
#define KERNEL_DISPLAY_H

// Forward declare - the actual struct data is either display.c or a driver file
struct DisplayDevice;

// Interface - display backend must provide this
typedef struct DisplayOps_t
{
    void        ( *PutPixel )( struct DisplayDevice * Device, uint32_t x, uint32_t y, uint32_t Colour );
    uint32_t    ( *GetPixel )( struct DisplayDevice * Device, uint32_t x, uint32_t y );
    void        ( *DrawRect )( struct DisplayDevice * Device, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t Colour );
} IDisplayOps;

typedef struct DisplayDevice_t
{
    const struct DisplayOps *ops;
    uint32_t Width;
    uint32_t Height;
    uint32_t Pitch;
    uin32t_ bpp
} DisplayDevice;

#endif // KERNEL_DISPLAY_H