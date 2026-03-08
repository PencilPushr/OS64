#ifndef BL_EFI_FILESYSTEM_H
#define BL_EFI_FILESYSTEM_H

#include "boot.h"

EFI_STATUS
BlEfiInitFileSystem(
    VOID 
);

EFI_STATUS
BlGetLastFileError(
    VOID
);


EFI_STATUS
BlGetRootDirectory(
    OUT OPTIONAL EFI_FILE_PROTOCOL** Directory
);

EFI_STATUS
BlListAllFiles(
    VOID
);

#endif 