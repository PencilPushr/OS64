#include "bootloader/graphics.h"

EFI_STATUS
BlGfxInitialiseFrameBuffer(
    IN EFI_SYSTEM_TABLE* ST,
    IN OUT FramebufferInfo* pFramebuffer
)
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GUID GopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_STATUS Status;

    //Status = uefi_call_wrapper( ST->BootServices->LocateProtocol, 3
    //                            &GopGuid, NULL, (VOID **)&Gop );
    Status = ST->BootServices->LocateProtocol(&GopGuid, NULL, (VOID **)&Gop);
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
            pFramebuffer->RedMask = 0x000000FF;
            pFramebuffer->GreenMask = 0x0000FF00;
            pFramebuffer->BlueMask  = 0x00FF0000;
            pFramebuffer->RSVDMask  = 0xFF000000;
            //Print(L"RGB\n");
            break;
        }
        case PixelBlueGreenRedReserved8BitPerColor:
        {
            pFramebuffer->BlueMask  = 0x000000FF;
            pFramebuffer->GreenMask = 0x0000FF00;
            pFramebuffer->RedMask   = 0x00FF0000;
            pFramebuffer->RSVDMask  = 0xFF000000;
            //Print(L"BGR\n");
            break;
        }
        case PixelBitMask:
        {
            pFramebuffer->RedMask   = Gop->Mode->Info->PixelInformation.RedMask;
            pFramebuffer->GreenMask = Gop->Mode->Info->PixelInformation.GreenMask;
            pFramebuffer->BlueMask  = Gop->Mode->Info->PixelInformation.BlueMask;
            pFramebuffer->RSVDMask = Gop->Mode->Info->PixelInformation.ReservedMask;
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
    pFramebuffer->Base   = Gop->Mode->FrameBufferBase;
    pFramebuffer->Width  = Gop->Mode->Info->HorizontalResolution;
    pFramebuffer->Height = Gop->Mode->Info->VerticalResolution;
    pFramebuffer->Pitch  = Gop->Mode->Info->PixelsPerScanLine * 4;
    pFramebuffer->Bpp    = 32;

    Print( L"Framebuffer: " );
    Print( L"%d", pFramebuffer->Width );
    Print( L"x");
    Print( L"%d", pFramebuffer->Height );
    Print( L" @ ");
    Print( L"%d", pFramebuffer->Base );
    Print( L"\n" );

    return EFI_SUCCESS;

}