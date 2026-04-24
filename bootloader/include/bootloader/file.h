#ifndef BOOTLOADER_FILE_H
#define BOOTLOADER_FILE_H

#include <bootloader/common.h>

/**
 * Uses loaded image handle to open a protocol to get the root file handle. 
 * 
 * @param Context  The bootloader context to hold commonly used information such as handles/objects.
 * 
 * @return EFI_SUPPORTED If loaded device handle does not support file system protocol.
 *  
 * Further status codes returned - 
 * https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html?highlight=openprotocol#efi-boot-services-openprotocol    
 */
EFI_STATUS  
BlFsInitialiseFileSystem (
    IN OUT BOOTLOADER_CONTEXT* Context
);

/**
 * Opens file based on given string which can include the path i.e. L"\efi\os64\kernel.elf"
 * See spec for more information on file open -
 * https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-open
 * 
 * @param Directory      File handle holding pointer to the root directory of file.  
 * @param Path           Null-terminated string of file to be opened, can include '.', ',', '..', and '\'.
 * @param OpenMode       Only valid combinations to open file are: Read, Read/Write or Create/Read/Write. 
 * @param OpenAttributes Only valid when using 'Create' mode to set file attributes.
 * @param FileHandle     Handle to the opened file. 
 * 
 * @return EFI_NOT_FOUND       Specified file could not be found.
 * 
 *         EFI_MEDIA_CHANGED   Media may have changed or issue with the medium. 
 * 
 *         EFI_WRITE_PROTOCTED Tried opening file when medium is write-protected.
 * 
 *         See spec for further status codes.
 */
EFI_STATUS
BlFsOpenFile(
    IN  EFI_FILE_HANDLE  Directory,
    IN  CHAR16*          Path,
    IN  UINT64           OpenMode,
    IN  UINT64           OpenAttributes,
    OUT EFI_FILE_HANDLE* FileHandle
);


/**
 * Closes specified file handle. Will wait for I/O request to complete before closing.
 * 
 * @param FileHandle The handle to close. 
 * 
 * @return EFI_SUCCESS If the file was closed.  
 */
EFI_STATUS 
BlFsCloseFile(
    IN EFI_FILE_HANDLE FileHandle 
);

/**
 * 
 */
EFI_STATUS
BlFsReadFile( 
    IN     EFI_FILE_HANDLE FileHandle,
    IN OUT UINT64*         BufferSize,
    OUT    VOID*           Buffer
);

/**
 * 
 */
EFI_STATUS 
BlFsReadFullFile( 
    IN  EFI_FILE_HANDLE FileHandle,
    OUT VOID**          FileBuffer,
    OUT UINT64*         FileSize
);

/**
 * 
 */
EFI_STATUS
BlFsGetFileInfo(
    IN  EFI_FILE_HANDLE File, 
    OUT EFI_FILE_INFO**  FileInfo
);

/**
 * 
 */
EFI_STATUS
BlFsGetFileSystemInfo(
    IN  EFI_FILE_HANDLE         File,
    OUT EFI_FILE_SYSTEM_INFO**  FileSysInfo
);

// TODO: Implement

//EFI_STATUS 
//BlFsFindAndOpenFile( 
//    VOID
//);
//
//EFI_STATUS
//BlFsFindFilePath(
//    VOID
//);

#endif // !BOOTLOADER_FILE_H