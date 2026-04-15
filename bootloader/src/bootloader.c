#include <efi.h>
#include <efilib.h>

#include <bootloader/file.h>

EFI_STATUS
efi_main(
    IN EFI_HANDLE Image, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitializeLib(Image, SystemTable);
    Print(L"Hello from OS64 bootloader\r\n");

    EFI_FILE_HANDLE RootFileHandle = LibOpenRoot(Image);

    if ( RootFileHandle == NULL )
    {
        Print( L"Failed to find root file handle\n" );
    }


    while( 1 )
    {
        continue;
    }

    return EFI_SUCCESS;
}