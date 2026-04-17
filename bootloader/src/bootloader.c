#include <bootloader/file.h>

EFI_STATUS
efi_main(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"Hello from OS64 bootloader\r\n");

    EFI_LOADED_IMAGE* LoadedImage = NULL; 
    EFI_FILE_HANDLE RootFileHandle;
    EFI_STATUS Status = EFI_SUCCESS;

    Status = uefi_call_wrapper( BS->HandleProtocol, 3, ImageHandle, &LoadedImageProtocol, (VOID**)&LoadedImage );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Could not get loaded image\n", Status );
    }

    RootFileHandle = LibOpenRoot( LoadedImage->DeviceHandle );
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