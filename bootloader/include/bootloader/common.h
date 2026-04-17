#ifndef BOOTLOADER_COMMON_H
#define BOOTLOADER_COMMON_H

#include <bootloader/boot.h>

/***
 * Retrieves the loaded image descriptor through the image handle.
 * 
 * @param ImageHandle      A handle to the executing uefi image.
 * @param LoadedImage      An optional pointer to retrieved image descriptor.
 * 
 * @return EFI_SUCCESS     On successfully retrieving the loaded image. 
 *         EFI_UNSUPPROTED Returned by handle protocol if protocol is not supported 
 */
EFI_STATUS
BlEfiInitialiseLoadedImage(
    IN EFI_HANDLE ImageHandle,
    OUT EFI_LOADED_IMAGE* LoadedImage OPTIONAL
);

EFI_STATUS
BlEfiGetImageHandle( 
    OUT EFI_HANDLE ImageHandle
);

EFI_STATUS
BlEfiGetLoadedImage(
    OUT EFI_LOADED_IMAGE* LoadedImage
);

#endif // !BOOTLOADER_COMMON_H