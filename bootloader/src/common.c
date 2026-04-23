#include "bootloader/common.h"

EFI_STATUS
BlEfiInitialiseLoadedImage(
    IN OUT BOOTLOADER_CONTEXT* Context
)
{
    if( Context == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    if ( Context->ImageHandle == NULL )
    {
        return EFI_NOT_READY;
    }

    return uefi_call_wrapper(
        BS->OpenProtocol,
        6,
        Context->ImageHandle,
        &LoadedImageProtocol,
        (VOID**)&Context->LoadedImage,
        Context->ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
    );
}