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

    EFI_FILE_SYSTEM_INFO* FileSysInfo = { 0 };
    Status = BlFsGetFileSystemInfo( BootloaderContext.BootVolume.RootDirectory, &FileSysInfo );
    if( EFI_ERROR( Status ) && FileSysInfo == NULL )
    {
        Print( L"[%r] Failed to get volume information\n", Status );
        FreePool( FileSysInfo);
        goto spinlock;
    }

    Print( 
        L"Volume Information:\n  Size: %llx\n  ReadOnly: %s\n  VolumeSize: %llx\n  FreeSpace: %llx\n  BlockSize: %lx\n  VolumeLabel: %s\n", 
        FileSysInfo->Size,
        FileSysInfo->ReadOnly ? L"TRUE" : L"FALSE",
        FileSysInfo->VolumeSize,
        FileSysInfo->FreeSpace, 
        FileSysInfo->BlockSize, 
        FileSysInfo->VolumeLabel 
    );

spinlock: 
    while( 1 )
    {
        continue;
    }

    return EFI_SUCCESS;
}