#ifndef BOOTLOADER_ELFLDR_H
#define BOOTLOADER_ELFLDR_H

#include "bootloader/boot.h"

EFI_STATUS
BlElfLoadImage(
    IN  VOID*   ImageFileBuffer,
    IN  UINT64  ImageBufferSize,
    OUT UINT64* EntryPoint
);

#endif // !BOOTLOADER_ELFLDR_H
