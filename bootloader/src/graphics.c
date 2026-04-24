#include "include/bootloader/graphics.h"

BlGfxInitialiseFrameBuffer(
    IN EFI_SYSTEM_TABLE* ST
    IN OUT FramebufferInfo* pFramebuffer
)
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_STATUS status;

    status = uefi_call_wrapper( ST->BootServices->LocateProtocol, 3
                                &gop_guid, NULL, (VOID **)&gop );
    if ( EFI_ERROR( status ) )
    {
        Print("ERROR: Failed to locate GOP\n");
        return status;
    }

    // Setup the masks
    switch( UefiGop->Mode->Info->PixelFormat )
    {
        case PixelRedGreenBlueReserved8BitPerColor:
        {
            pFramebuffer->RedMask = 0x000000FF;
            pFramebuffer->GreenMask = 0x0000FF00;
            pFramebuffer->BlueMask  = 0x00FF0000;
            pFramebuffer->RSVDMaskMask  = 0xFF000000;
            //Print(L"RGB\n");
            break;
        }
        case PixelBlueGreenRedReserved8BitPerColor:
        {
            pFramebuffer->BlueMask  = 0x000000FF;
            pFramebuffer->GreenMask = 0x0000FF00;
            pFramebuffer->RedMask   = 0x00FF0000;
            pFramebuffer->RSVDMaskMask  = 0xFF000000;
            //Print(L"BGR\n");
            break;
        }
        case PixelBitMask:
        {
            pFramebuffer->RedMask   = UefiGop->Mode->Info->PixelInformation.RedMask;
            pFramebuffer->GreenMask = UefiGop->Mode->Info->PixelInformation.GreenMask;
            pFramebuffer->BlueMask  = UefiGop->Mode->Info->PixelInformation.BlueMask;
            pFramebuffer->RSVDMaskMask  = UefiGop->Mode->Info->PixelInformation.ReservedMask;
            //Print(L"BitMask\n");
            break;
        }
        default:
        {
            //Print(L"UNSUPPORTED?!\n");
            return SC_UNSUPPORTED;
        }
    }

    // Store framebuffer info
    pFramebuffer.Base   = gop->Mode->FrameBufferBase;
    pFramebuffer.Width  = gop->Mode->Info->HorizontalResolution;
    pFramebuffer.Height = gop->Mode->Info->VerticalResolution;
    pFramebuffer.Pitch  = gop->Mode->Info->PixelsPerScanLine * 4;
    pFramebuffer.Bpp    = 32;

    print("Framebuffer: ");
    print(pFrameBuffer.Width);
    print("x");
    print(pFrameBuffer.Height);
    print(" @ ");
    print(pFrameBuffer.Base);
    print("\n");

    return EFI_SUCCESS;

}