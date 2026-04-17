#include <bootloader/common.h>

STATIC EFI_LOADED_IMAGE* g_LoadedImage = NULL;
STATIC EFI_HANDLE        g_ImageHandle = NULL;

EFI_STATUS
BlEfiInitialiseLoadedImage(
    IN EFI_HANDLE ImageHandle,
    OUT EFI_LOADED_IMAGE* LoadedImage OPTIONAL
)
{
    if ( ImageHandle == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    EFI_STATUS Status = EFI_SUCCESS;

    if ( g_ImageHandle == NULL )
    {
        g_ImageHandle = ImageHandle;
    }

    Status = uefi_call_wrapper( BS->HandleProtocol, 3, ImageHandle, &LoadedImageProtocol, (VOID*)&g_LoadedImage );
    if ( EFI_ERROR( Status ) || g_LoadedImage == NULL )
    {
        return Status;
    }

    if ( LoadedImage != NULL )   
    {
        LoadedImage = g_LoadedImage;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
BlEfiGetImageHandle( 
    OUT EFI_HANDLE ImageHandle
)
{
    if ( g_ImageHandle == NULL )
    {
        return EFI_NOT_READY;
    }

    ImageHandle = g_ImageHandle;

    return EFI_SUCCESS;
}

EFI_STATUS
BlEfiGetLoadedImage(
    OUT EFI_LOADED_IMAGE* LoadedImage
)
{
    if ( g_LoadedImage == NULL )
    {
        if ( g_ImageHandle == NULL )
        {
            return EFI_NOT_READY;
        }

        return BlEfiInitialiseLoadedImage( g_ImageHandle, LoadedImage );
    }

    LoadedImage = g_LoadedImage;

    return EFI_SUCCESS;
}
