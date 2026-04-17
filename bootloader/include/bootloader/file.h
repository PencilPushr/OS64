#ifndef BOOTLOADER_FILE_H
#define BOOTLOADER_FILE_H

#include <bootloader/boot.h>

EFI_STATUS  
BlFsInitialiseFileSystem (
    IN  EFI_HANDLE         EfiImageHandle,
    OUT EFI_LOADED_IMAGE*  LoadedImage
);

EFI_STATUS 
BlFsOpenFile (
    IN  EFI_FILE_HANDLE VolumeHandle,
    OUT EFI_FILE_HANDLE FileHandle,
    IN  UINT64          OpenMode,
    OUT EFI_STATUS*     ErrorReason OPTIONAL
);

#endif // !BOOTLOADER_FILE_H