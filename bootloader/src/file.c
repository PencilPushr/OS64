#include <bootloader/file.h>

inline
VOID 
BlSetErrorReason ( 
    IN OUT EFI_STATUS* Status,
    IN     EFI_STATUS  Reason
)
{
    if( Status != NULL )
    {
        *Status = Reason;
    }
}

BOOLEAN 
BlEfiInitialiseFileSystem (
    IN  EFI_HANDLE         ImageHandle,
    OUT EFI_LOADED_IMAGE*  LoadedImage,
    OUT EFI_FILE_HANDLE    VolumeHandle,
    OUT EFI_STATUS*        ErrorReason OPTIONAL
)
{
    if ( ImageHandle == NULL || LoadedImage == NULL )
    {
        BlSetErrorReason( ErrorReason, EFI_INVALID_PARAMETER );
    }

    EFI_STATUS             Status = EFI_SUCCESS;
    EFI_FILE_IO_INTERFACE* Volume = NULL;

    //
    // Per spec -- 
    // Perform a call to locate the loaded image handle, required for extras such as file handles
    //

    Status = uefi_call_wrapper( BS->HandleProtocol, 3, ImageHandle, &LoadedImageProtocol, (VOID**)&LoadedImage );
    if ( EFI_ERROR( Status ) || LoadedImage == NULL )
    {
        BlSetErrorReason( ErrorReason, Status );
        return FALSE;
    }

    //
    // File the file system interface to the device
    //

    Status = uefi_call_wrapper( BS->HandleProtocol, 3, LoadedImage->DeviceHandle, &FileSystemProtocol, (VOID*)&Volume );
    if( EFI_ERROR( Status ) || Volume == NULL )
    {
        BlSetErrorReason( ErrorReason, Status );
        return FALSE;
    }

    //
    // Open the root directory of the volume 
    //

    Status = uefi_call_wrapper( Volume->OpenVolume, 2, Volume, &VolumeHandle );
    if( EFI_ERROR( Status ) || VolumeHandle == NULL )
    {
        BlSetErrorReason( ErrorReason, Status );
        return FALSE;
    }

    return TRUE;
}

BOOLEAN
BlEfiOpenFile(
    IN  EFI_FILE_HANDLE VolumeHandle,
    OUT EFI_FILE_HANDLE FileHandle,
    IN  UINT64          OpenMode,
    IN  UINT64          OpenAttributes,
    OUT EFI_STATUS*     ErrorReason OPTIONAL
)
{
    if( VolumeHandle == NULL || !OpenMode )
    {
        *ErrorReason = EFI_INVALID_PARAMETER;
        return FALSE;
    }

    EFI_STATUS Status = EFI_SUCCESS;


    return TRUE;
}