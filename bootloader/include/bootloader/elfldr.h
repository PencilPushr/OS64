#ifndef BOOTLOADER_ELFLDR_H
#define BOOTLOADER_ELFLDR_H

#include "bootloader/boot.h"
#include "common/elfdef.h"

EFI_STATUS
BlElfLoadImage( 
    IN VOID*  ImageFileBuffer,
    IN UINT64 ImageBufferSize 
);

#endif // !BOOTLOADER_ELFLDR_H