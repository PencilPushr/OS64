#ifndef BOOTLOADER_COMMON_H
#define BOOTLOADER_COMMON_H

#include <bootloader/boot.h>

/**
 *  Holds the booted from volume handles/protocols.
 */
typedef struct _FILE_VOLUME
{
    EFI_HANDLE                       DeviceHandle;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
    EFI_FILE_HANDLE                  RootDirectory;

} FILE_VOLUME;

/**
 * Used to hold commonly used handles/objects inplace of globals.
 */
typedef struct _BOOTLOADER_CONTEXT
{
    EFI_HANDLE        ImageHandle;
    EFI_LOADED_IMAGE* LoadedImage; 

    FILE_VOLUME       BootVolume;

} BOOTLOADER_CONTEXT;

/***
 * Retrieves the loaded image descriptor through the image handle.
 * 
 * @param ImageHandle      A handle to the executing uefi image.
 * @param LoadedImage      An optional pointer to retrieved image descriptor.
 * 
 * @return EFI_SUCCESS     On successfully retrieving the loaded image. 
 *         EFI_UNSUPPROTED Returned by handle protocol if protocol is not supported.
 */
EFI_STATUS
BlEfiInitialiseLoadedImage(
    IN OUT BOOTLOADER_CONTEXT* Context
);

#endif // !BOOTLOADER_COMMON_H