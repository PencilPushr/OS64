#include <bootloader/file.h>


EFI_STATUS 
BlFsInitialiseFileSystem (
    IN  EFI_HANDLE        ImageHandle,
    IN  EFI_LOADED_IMAGE* LoadedImage,
    OUT EFI_FILE_HANDLE   VolumeHandle
)
{
    if ( LoadedImage == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    EFI_STATUS             Status = EFI_SUCCESS;
    EFI_FILE_IO_INTERFACE* Volume = NULL;

    // Per spec -- https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html?highlight=handleprotocol#efi-boot-services-handleprotocol
    // File the file system interface to the device, through the newer 'OpenProtocol'. 'HandleProtocol' is depreciated.

    // Status = uefi_call_wrapper( BS->HandleProtocol, 3, LoadedImage->DeviceHandle, &FileSystemProtocol, (VOID*)&Volume );
    Status = uefi_call_wrapper( BS->OpenProtocol, 6, 
        LoadedImage->DeviceHandle, &FileSystemProtocol, (VOID*)&Volume, ImageHandle, NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 
    );
    if( EFI_ERROR( Status ) || Volume == NULL )
    {
        return Status;
    }

    // Open the root directory of the volume 

    Status = uefi_call_wrapper( Volume->OpenVolume, 2, Volume, &VolumeHandle );
    if( EFI_ERROR( Status ) || VolumeHandle == NULL )
    {
        return Status;
    }

    return EFI_SUCCESS;
}

BOOLEAN
BlFsOpenFile(
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