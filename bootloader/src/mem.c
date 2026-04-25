#include "bootloader/mem.h"


EFI_STATUS
BlMmGetMemoryMap( 
    OUT UINT64*                 pMemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR** pMemoryMap,
    OUT UINT64*                 pMapKey,
    OUT UINT64*                 pDescriptorSize,
    OUT UINT32*                 pDescriptorVersion
)
{
    if( 
        pMemoryMapSize     == NULL || 
        pMemoryMap         == NULL || 
        pMapKey            == NULL || 
        pDescriptorSize    == NULL || 
        pDescriptorVersion == NULL 
    )
    {
        return EFI_INVALID_PARAMETER;
    }

    EFI_STATUS Status          = EFI_SUCCESS;
    UINT64     MemoryMapSize   = 0;
    EFI_MEMORY_DESCRIPTOR* Map = NULL;

    // On first call we get the size of the memory map, but per the docs
    // the memory map will be bigger than memory map size. So we just multiply it by 1.5.
    // Realistcally we should put this in a loop to ensure we allocate enough memory.

    Status = uefi_call_wrapper(
        BS->GetMemoryMap, 
        5,
        &MemoryMapSize,
        NULL,
        pMapKey,
        pDescriptorSize,
        pDescriptorVersion
    );

    MemoryMapSize *= 1.5;

    if( Status == EFI_BUFFER_TOO_SMALL )
    {
        Map = (EFI_MEMORY_DESCRIPTOR*)AllocatePool( MemoryMapSize );
        if( Map == NULL )
        {
            return EFI_OUT_OF_RESOURCES;
        }

        Status = uefi_call_wrapper(
            BS->GetMemoryMap, 
            5,
            &MemoryMapSize,
            Map,
            pMapKey,
            pDescriptorSize,
            pDescriptorVersion
        );
        if( EFI_ERROR( Status ) )
        {
            FreePool( Map );
            return Status;
        }
    }

    if( EFI_ERROR( Status ) )
    {
        return Status;
    }

    *pMemoryMap     = Map;
    *pMemoryMapSize = MemoryMapSize;

    return EFI_SUCCESS;
}