#include <efi.h>
#include <efilib.h>

EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{

    InitializeLib( ImageHandle, SystemTable );

    Print( (const CHAR16*)"Hello bootloader\n" );

    for( ;; );

    return EFI_SUCCESS;
}