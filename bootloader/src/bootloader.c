#include "bootloader/file.h"
#include "bootloader/file.h"

EFI_STATUS
efi_main(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitializeLib( ImageHandle, SystemTable );

    Print(L"Hello from OS64 bootloader\r\n");

    // When working in less-forgiving enviroments always zero-intialise, 
    // this avoids issues of accidentally overwriting valid memory/values and causing issues.

    EFI_STATUS         Status = EFI_SUCCESS;
    BOOTLOADER_CONTEXT BootloaderContext = { .ImageHandle = ImageHandle };

    Status = BlEfiInitialiseLoadedImage( &BootloaderContext );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get loaded image.\n", Status );
        goto spinlock;
    }

    Status = BlFsInitialiseFileSystem( &BootloaderContext );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get root volume handle\n", Status );
        goto spinlock;
    }

    EFI_FILE_HANDLE KernelFileHandle = NULL;

    Status = BlFsOpenFile( 
        BootloaderContext.BootVolume.RootDirectory, 
        L"\\efi\\os64\\kernel.elf",
        EFI_FILE_MODE_READ,
        0,
        &KernelFileHandle
    );

    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to open file\n", Status );
        goto spinlock;
    }

    EFI_FILE_INFO* FileInfo = NULL;

    Status = BlFsGetFileInfo( KernelFileHandle, &FileInfo );
    if (EFI_ERROR(Status) || FileInfo == NULL)
    {
        Print(L"[%r] Failed to get kernel file information\n", Status);
        goto spinlock;
    }

    CHAR16 KernelCreateTime[64] = { 0 };
    CHAR16 KernelLastAccessTime[64] = { 0 };
    CHAR16 KernelLastModificationTime[64] = { 0 };

    TimeToString( KernelCreateTime, &FileInfo->CreateTime );
    TimeToString( KernelLastAccessTime, &FileInfo->LastAccessTime );
    TimeToString( KernelLastModificationTime, &FileInfo->ModificationTime );

    Print( 
        L"Kernel file information:\n  Size: %llx\n  FileSize: %llx\n  PhysicalSize: %llx\n  CreateTime: %s\n  LastAccessTime: %s\n  ModificationTime: %s\n  Attribute: %d\n  FileName: %s\n", 
        FileInfo->Size,
        FileInfo->FileSize,
        FileInfo->PhysicalSize,
        KernelCreateTime, 
        KernelLastAccessTime,
        KernelLastModificationTime,
        FileInfo->Attribute,
        FileInfo->FileName
    );

    VOID*  KernelFileBuffer = NULL;
    UINT64 KernelFileBufferSize; 
    Status = BlFsReadFullFile( KernelFileHandle, &KernelFileBuffer, &KernelFileBufferSize );
    if( EFI_ERROR( Status ) ) 
    {
        Print( L"[%r] Failed to read kernel file\n", Status );
        goto spinlock;
    }

    Print( L"Read kernel.elf [%lx]\n", KernelFileBufferSize );

spinlock: 
    Print( L"Made it to spinlock\n" );
    while( 1 )
    {
        continue;
    }

    return EFI_SUCCESS;
}