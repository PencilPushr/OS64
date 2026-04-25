#include "bootloader/common.h"

EFI_STATUS
BlEfiInitialiseLoadedImage(
    IN OUT BOOTLOADER_CONTEXT* pContext
)
{
    if( pContext == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    if ( pContext->ImageHandle == NULL )
    {
        return EFI_NOT_READY;
    }

    return uefi_call_wrapper(
        BS->OpenProtocol,
        6,
        pContext->ImageHandle,
        &LoadedImageProtocol,
        (VOID**)&pContext->LoadedImage,
        pContext->ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
    );
}