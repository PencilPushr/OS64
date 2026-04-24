#include "bootloader/file.h"

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
        (VOID*)&Context->BootVolume.RootDirectory 
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

EFI_STATUS 
BlFsCloseFile(
    IN EFI_FILE_HANDLE FileHandle 
)
{
    if( FileHandle == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    return uefi_call_wrapper( 
        FileHandle->Close,
        1,
        FileHandle
    );
}

EFI_STATUS 
BlFsReadFile( 
    IN     EFI_FILE_HANDLE FileHandle,
    IN OUT UINTN*          BufferSize,
    OUT    VOID*           Buffer
)
{
    if (FileHandle == NULL || BufferSize == NULL || Buffer == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    return uefi_call_wrapper(
        FileHandle->Read,
        3,
        FileHandle,
        BufferSize,
        Buffer
    );
}

EFI_STATUS 
BlFsReadFullFile( 
    IN  EFI_FILE_HANDLE FileHandle,
    OUT VOID**          FileBuffer,
    OUT UINT64*         FileSize
)
{
    if (FileHandle == NULL || FileBuffer == NULL || FileSize == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    *FileBuffer = NULL;
    *FileSize = 0;

    EFI_STATUS Status;
    EFI_FILE_INFO* FileInfo = NULL;

    Status = BlFsGetFileInfo(FileHandle, &FileInfo);
    if (EFI_ERROR(Status))
    {
        return Status;
    }

    if (FileInfo->FileSize == 0)
    {
        FreePool(FileInfo);
        return EFI_LOAD_ERROR;
    }

    if ( FileInfo->FileSize > UINT64_MAX )
    {
        FreePool(FileInfo);
        return EFI_BAD_BUFFER_SIZE;
    }

    VOID* Buffer = AllocatePool( FileInfo->FileSize );
    if (Buffer == NULL)
    {
        FreePool(FileInfo);
        return EFI_OUT_OF_RESOURCES;
    }

    // Make sure we read from the start of the file.

    Status = uefi_call_wrapper(
        FileHandle->SetPosition,
        2,
        FileHandle,
        0
    );
    if ( EFI_ERROR( Status ) )
    {
        FreePool( Buffer );
        FreePool( FileInfo );
        return Status;
    }

    UINT64 BytesToRead = FileInfo->FileSize;
    Status = uefi_call_wrapper(
        FileHandle->Read,
        3,
        FileHandle,
        &BytesToRead,
        Buffer
    );
    if ( EFI_ERROR( Status ) )
    {
        FreePool( Buffer );
        FreePool( FileInfo );
        return Status;
    }

    if ( BytesToRead != FileInfo->FileSize )
    {
        FreePool(Buffer);
        FreePool(FileInfo);
        return EFI_LOAD_ERROR;
    }

    *FileBuffer = Buffer;
    *FileSize   = FileInfo->FileSize;

    FreePool( FileInfo );
    return EFI_SUCCESS;
}

EFI_STATUS
BlFsGetFileInfo(
    IN     EFI_FILE_HANDLE File, 
    OUT    EFI_FILE_INFO** FileInfo
)
{
    if( File == NULL ||  FileInfo == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    // Per documentation EFI_FIELD_OFFSET should be used to get the correct size
    // for file info structures. The define uses EFI_FIELD_OFFSET internally.

    EFI_STATUS     Status = EFI_SUCCESS;
    UINT64         Size   = SIZE_OF_EFI_FILE_INFO;
    EFI_FILE_INFO* FsInfo = NULL;

    FsInfo = AllocatePool( Size );
    if( FsInfo == NULL )
    {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = uefi_call_wrapper( 
        File->GetInfo, 
        4,
        File,   
        &GenericFileInfo,
        &Size,
        FsInfo
    );

    if (Status == EFI_BUFFER_TOO_SMALL)
    {
        FreePool( FsInfo );

        FsInfo = AllocatePool( Size );
        if( FsInfo == NULL )
        {
            return EFI_OUT_OF_RESOURCES;
        }

        Status = uefi_call_wrapper(
            File->GetInfo,
            4,
            File,
            &GenericFileInfo,
            &Size,
            FsInfo
        );
    }

    if (EFI_ERROR(Status))
    {
        FreePool( FsInfo );
        return Status;
    }

    *FileInfo = FsInfo;
    return EFI_SUCCESS;
}

EFI_STATUS
BlFsGetFileSystemInfo(
    IN  EFI_FILE_HANDLE         File,
    OUT EFI_FILE_SYSTEM_INFO**  FileSysInfo
)
{
    if (File == NULL || FileSysInfo == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    *FileSysInfo = NULL;

    // Per documentation EFI_FIELD_OFFSET should be used to get the correct size
    // for file info structures. The define uses EFI_FIELD_OFFSET internally.

    EFI_STATUS Status;
    UINTN Size = SIZE_OF_EFI_FILE_SYSTEM_INFO;
    EFI_FILE_SYSTEM_INFO* FsInfo = NULL;

    FsInfo = AllocatePool( Size );
    if( FsInfo == NULL )
    {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = uefi_call_wrapper(
        File->GetInfo,
        4,
        File,
        &gEfiFileSystemInfoGuid,
        &Size,
        FsInfo
    );

    if (Status == EFI_BUFFER_TOO_SMALL)
    {
        FreePool( FsInfo );

        FsInfo = AllocatePool( Size );
        if( FsInfo == NULL )
        {
            return EFI_OUT_OF_RESOURCES;
        }

        Status = uefi_call_wrapper(
            File->GetInfo,
            4,
            File,
            &gEfiFileSystemInfoGuid,
            &Size,
            FsInfo
        );
    }

    if (EFI_ERROR(Status))
    {
        FreePool( FsInfo );
        return Status;
    }

    *FileSysInfo = FsInfo;
    return EFI_SUCCESS;
}


// TODO: Implement

//EFI_STATUS 
//BlFsFindAndOpenFile( 
//    VOID
//);
//
//EFI_STATUS
//BlFsFindFilePath(
//    VOID
//);