#include "bootloader/graphics.h"
#include "common/status_codes.h"

EFI_STATUS
BlGfxInitialiseFrameBuffer(
    IN OUT GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBuffer
)
{
    if( pFrameBuffer == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_STATUS Status;

    Status = uefi_call_wrapper( ST->BootServices->LocateProtocol, 3,
                                &GraphicsOutputProtocol, NULL, (VOID **)&Gop);
    if ( EFI_ERROR( Status ) )
    {
        Print(L"ERROR: Failed to locate GOP\n");
        return Status;
    }

    // Setup the masks
    switch( Gop->Mode->Info->PixelFormat )
    {
        case PixelRedGreenBlueReserved8BitPerColor:
        {
            pFrameBuffer->RedMask   = 0x000000FF;
            pFrameBuffer->GreenMask = 0x0000FF00;
            pFrameBuffer->BlueMask  = 0x00FF0000;
            pFrameBuffer->RSVDMask  = 0xFF000000;
            //Print(L"RGB\n");
            break;
        }
        case PixelBlueGreenRedReserved8BitPerColor:
        {
            pFrameBuffer->BlueMask  = 0x000000FF;
            pFrameBuffer->GreenMask = 0x0000FF00;
            pFrameBuffer->RedMask   = 0x00FF0000;
            pFrameBuffer->RSVDMask  = 0xFF000000;
            //Print(L"BGR\n");
            break;
        }
        case PixelBitMask:
        {
            pFrameBuffer->RedMask   = Gop->Mode->Info->PixelInformation.RedMask;
            pFrameBuffer->GreenMask = Gop->Mode->Info->PixelInformation.GreenMask;
            pFrameBuffer->BlueMask  = Gop->Mode->Info->PixelInformation.BlueMask;
            pFrameBuffer->RSVDMask  = Gop->Mode->Info->PixelInformation.ReservedMask;
            //Print(L"BitMask\n");
            break;
        }
        default:
        {
            //Print(L"UNSUPPORTED?!\n");
            return EFI_UNSUPPORTED;
        }
    }

    // Store framebuffer info
    pFrameBuffer->Base   = Gop->Mode->FrameBufferBase;
    pFrameBuffer->Width  = Gop->Mode->Info->HorizontalResolution;
    pFrameBuffer->Height = Gop->Mode->Info->VerticalResolution;
    pFrameBuffer->Bpp    = 32;

    pFrameBuffer->PixelsPerScanLine = Gop->Mode->Info->PixelsPerScanLine;
    pFrameBuffer->PitchBytes        = Gop->Mode->Info->PixelsPerScanLine * 4;

    Print( L"Framebuffer: " );
    Print( L"%d", pFrameBuffer->Width );
    Print( L"x");
    Print( L"%d", pFrameBuffer->Height );
    Print( L" @ ");
    Print( L"%llx", pFrameBuffer->Base );
    Print( L"\n" );

    return EFI_SUCCESS;
}

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

static uint32_t
ConvertColour(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN uint32_t Xrgb
)
{
    uint8_t r = (Xrgb >> 16) & 0xFF;
    uint8_t g = (Xrgb >>  8) & 0xFF;
    uint8_t b = (Xrgb      ) & 0xFF;

    return ((uint32_t)r << MaskToShift(pFrameBufferDesc->RedMask))   |
           ((uint32_t)g << MaskToShift(pFrameBufferDesc->GreenMask)) |
           ((uint32_t)b << MaskToShift(pFrameBufferDesc->BlueMask));
}

static GLOBAL_STATUS
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

    // 21/05/2026 - Colour fix: note this is inefficient - MaskToShift walks bits everytime ConvertColour is called
    //                          Ideally - compute the shifts once during init and store them in a variable. 
    //                                     One variable for each shift: ( rshift, gshift, bshift )
    // This is acceptable for now as we just want to init the boot services and then get out. Dump/Print if something has gone wrong
    uint32_t HwColour = ConvertColour(pFrameBufferDesc, Colour);

    for( uint32_t Row = y; Row < y + h && Row < pFrameBufferDesc->Height; Row++ )
    {
        for( uint32_t Col = x; Col < x + w && Col < pFrameBufferDesc->Width; Col++ )
        {
            Pixels[ Row * PixelsPerScanLine + Col ] = HwColour;
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

