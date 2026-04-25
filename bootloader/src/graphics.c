#include "bootloader/graphics.h"

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

    //Status = uefi_call_wrapper( ST->BootServices->LocateProtocol, 3
    //                            &GopGuid, NULL, (VOID **)&Gop );
    Status = ST->BootServices->LocateProtocol(&GraphicsOutputProtocol, NULL, (VOID**)&Gop);
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
    pFrameBuffer->Pitch  = Gop->Mode->Info->PixelsPerScanLine * 4;
    pFrameBuffer->Bpp    = 32;

    Print( L"Framebuffer: " );
    Print( L"%d", pFrameBuffer->Width );
    Print( L"x");
    Print( L"%d", pFrameBuffer->Height );
    Print( L" @ ");
    Print( L"%llx", pFrameBuffer->Base );
    Print( L"\n" );

    return EFI_SUCCESS;
}