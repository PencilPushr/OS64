#include "../include/filesystem.h"

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTable
)
{
    Print(L"Hello from OS64 loader\r\n");

    BlEfiInitFileSystem();
    BlListAllFiles();

    for( ;; )
    {
        asm ( "hlt" );
    }
    return EFI_SUCCESS;
}