#ifndef BOOTLOADER_MEM_H
#define BOOTLOADER_MEM_H

#include "bootloader/boot.h"

/**
 * https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-getmemorymap
 * 
 * 
 * Returns copy of the current memory map. Map is an array of descriptors, each describinng a block
 * of memory. Only memory present in system is described, such as some MMIO ranges. Regions not meant to
 * be accessed by the OS must be returned as 'EfiReservedMemoryType'.
 * 
 * When exiting bootservice, map key must be given which changes on every change to memory map. This should
 * be called right before exiting boot services to gurantee a correct memory map. 
 * 
 * Descriptors describe each block, and its size is used to offset to the next descriptor similar to a linked
 * list. 
 * 
 * @param pMemoryMapSize     A pointer, in bytes, of MemoryMap buffer. 
 * @param pMemoryMap         Pointer to the array of memory descriptors, should be freed after use. 
 * @param pMapKey            Key for the most recent memory map. Changes whenever memory map is modified.
 * @param pDescriptorSize    Size of each individual element in the memory map of descriptors.
 * @param pDescriptorVersion Version number of the descriptors.
 * 
 * @return EFI_INVALID_PARAMTER When MemoryMapSize or MemoryMap is NULL.
 */
EFI_STATUS
BlMmGetMemoryMap( 
    OUT UINT64*                 pMemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR** pMemoryMap,
    OUT UINT64*                 pMapKey,
    OUT UINT64*                 pDescriptorSize,
    OUT UINT32*                 pDescriptorVersion
);

#endif // !BOOTLOADER_MEM_H