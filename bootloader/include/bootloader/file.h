#ifndef BOOTLOADER_FILE_H
#define BOOTLOADER_FILE_H

#include "bootloader/common.h"

EFI_STATUS  
BlFsInitialiseFileSystem (
    IN OUT BOOTLOADER_CONTEXT* Context
);

EFI_STATUS
BlFsOpenFile(
    IN  EFI_FILE_HANDLE  Directory,
    IN  CHAR16*          Path,
    IN  UINT64           OpenMode,
    IN  UINT64           OpenAttributes,
    OUT EFI_FILE_HANDLE* FileHandle
);

// TODO: Implement

EFI_STATUS 
BlFsFindAndOpenFile( 
    VOID
);

EFI_STATUS
BlFsFindFilePath(
    VOID
);

#endif // !BOOTLOADER_FILE_H