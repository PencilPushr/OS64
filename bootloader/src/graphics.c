#include "include/bootloader/graphics.h"

BlGfxInitialiseFrameBuffer(
    IN EFI_SYSTEM_TABLE* ST
    IN OUT FramebufferInfo* pFramebuffer
)
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GUID GopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_Status Status;

    Status = uefi_call_wrapper( ST->BootServices->LocateProtocol, 3
                                &GopGuid, NULL, (VOID **)&Gop );
    if ( EFI_ERROR( Status ) )
    {
        Print("ERROR: Failed to locate GOP\n");
        return Status;
    }

    // Setup the masks
    switch( GopGuid->Mode->Info->PixelFormat )
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
            pFramebuffer->RedMask   = GopGuid->Mode->Info->PixelInformation.RedMask;
            pFramebuffer->GreenMask = GopGuid->Mode->Info->PixelInformation.GreenMask;
            pFramebuffer->BlueMask  = GopGuid->Mode->Info->PixelInformation.BlueMask;
            pFramebuffer->RSVDMask = GopGuid->Mode->Info->PixelInformation.ReservedMask;
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
    pFramebuffer->Base   = Gop->Mode->FrameBufferBase;
    pFramebuffer->Width  = Gop->Mode->Info->HorizontalResolution;
    pFramebuffer->Height = Gop->Mode->Info->VerticalResolution;
    pFramebuffer->Pitch  = Gop->Mode->Info->PixelsPerScanLine * 4;
    pFramebuffer->Bpp    = 32;

    Print("Framebuffer: ");
    Print(pFrameBuffer->Width);
    Print("x");
    Print(pFrameBuffer->Height);
    Print(" @ ");
    Print(pFrameBuffer->Base);
    Print("\n");

    return EFI_SUCCESS;

}