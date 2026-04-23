#include <bootloader/file.h>

EFI_STATUS 
BlFsInitialiseFileSystem (
    IN OUT BOOTLOADER_CONTEXT* Context
)
{
    if( Context == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    if ( Context->LoadedImage == NULL )
    {
        return EFI_NOT_READY;
    }

    EFI_STATUS             Status = EFI_SUCCESS;
    EFI_FILE_IO_INTERFACE* Volume = NULL;

    Context->BootVolume.DeviceHandle = Context->LoadedImage->DeviceHandle;

    // Per spec -- https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html?highlight=handleprotocol#efi-boot-services-handleprotocol
    // File the file system interface to the device, through the newer 'OpenProtocol'. 'HandleProtocol' is depreciated.

    // Status = uefi_call_wrapper( BS->HandleProtocol, 3, LoadedImage->DeviceHandle, &FileSystemProtocol, (VOID*)&Volume );
    Status = uefi_call_wrapper( 
        BS->OpenProtocol, 
        6, 
        Context->BootVolume.DeviceHandle, 
        &FileSystemProtocol, 
        (VOID**)&Volume, 
        Context->ImageHandle, 
        NULL, 
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 
    );
    if( EFI_ERROR( Status ) || Volume == NULL )
    {
        return Status;
    }

    // Open the root directory of the volume 

    Status = uefi_call_wrapper( 
        Volume->OpenVolume, 
        2, 
        Volume, 
        (VOID**)&Context->BootVolume.RootDirectory 
    );
    if( EFI_ERROR( Status ) || Context->BootVolume.RootDirectory  == NULL )
    {
        return Status;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
BlFsOpenFile(
    IN  EFI_FILE_HANDLE  Directory,
    IN  CHAR16*          Path,
    IN  UINT64           OpenMode,
    IN  UINT64           OpenAttributes,
    OUT EFI_FILE_HANDLE* FileHandle
)
{
    if ( Directory == NULL || Path == NULL || FileHandle == NULL ) 
    {
        return EFI_INVALID_PARAMETER;
    }

    return uefi_call_wrapper(
        Directory->Open,
        5,
        Directory,
        FileHandle,
        Path,
        OpenMode,
        OpenAttributes
    );
}