#include "bootloader/elfldr.h"

EFI_STATUS
BlElfLoadImage( 
    IN VOID*  ImageFileBuffer,
    IN UINT64 ImageBufferSize 
)
{
    UNREFERENCED_PARAMETER( ImageBufferSize );

    Elf64_Ehdr* Elf64Header = (Elf64_Ehdr*)AllocatePool( sizeof( Elf64_Ehdr ) );

    Elf64Header = (Elf64_Ehdr*)ImageFileBuffer;

    UINT32 MagicLow = *(UINT32*)(&Elf64Header->e_ident[0]); // not really safe should memcpy
    UINT8 Class     = (Elf64Header->e_ident[4]);
    UINT8 Endianess = (Elf64Header->e_ident[5]);
    UINT8 Version   = (Elf64Header->e_ident[6]);
    UINT8 OsAbi     = (Elf64Header->e_ident[7]);
    UINT8 AbiVer    = (Elf64Header->e_ident[8]);

    UINT32 MagicBytes = PACK_UNSIGNED_DWORD( 0x7F, 'E', 'L', 'F' ); // header ident should be this ! 

    Print( L"Kernel elf header: \n  Magic Low %lx, class %d, endianess %d, version %d, osabi %d, abiver %d\n\n", MagicLow, Class, Endianess, Version, OsAbi, AbiVer );

    if( MagicBytes == MagicLow )
    {
        Print( L"KernelFileBuffer seems uncorrupted, Magic Bytes %lx\n", MagicBytes );
    }

    return EFI_SUCCESS;
}