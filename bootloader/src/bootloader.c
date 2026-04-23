#include "bootloader/file.h"
#include "bootloader/common.h"

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
        return Status;
    }

    Status = BlFsInitialiseFileSystem( &BootloaderContext );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get root volume handle\n", Status );
        return Status;
    }

    while( 1 )
    {
        continue;
    }

    return EFI_SUCCESS;
}