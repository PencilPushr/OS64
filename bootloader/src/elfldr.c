#include "bootloader/elfldr.h"

EFI_STATUS
BlElf64LoadProgramSegment(
    IN UINT8* ImageBase,
    IN Elf64_Phdr* ElfProgramHeader
)
{
    if( ImageBase == NULL || ElfProgramHeader == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    // TODO: Map program segment with correct permissions. 

    return EFI_SUCCESS;
}

EFI_STATUS
BlElfLoadImage( 
    IN VOID*  ImageFileBuffer,
    IN UINT64 ImageBufferSize 
)
{
    UNREFERENCED_PARAMETER( ImageBufferSize );

    UINT8* ImageBase        = (UINT8*)ImageFileBuffer;
    Elf64_Ehdr* Elf64Header = NULL;

    Elf64Header = (Elf64_Ehdr*)ImageBase;

    UINT32 MagicLow = *(UINT32*)(&Elf64Header->e_ident[EI_MAG0]); // not really safe should memcpy
    UINT8 Class     = (Elf64Header->e_ident[EI_CLASS]);
    UINT8 Endianess = (Elf64Header->e_ident[EI_DATA]);
    UINT8 Version   = (Elf64Header->e_ident[EI_VERSION]);
    UINT8 OsAbi     = (Elf64Header->e_ident[EI_OSABI]);
    UINT8 AbiVer    = (Elf64Header->e_ident[EI_ABIVERSION]);

    UINT32 MagicBytes = PACK_UNSIGNED_DWORD( 0x7F, 'E', 'L', 'F' ); // header ident should be this ! 

    Print( L"Kernel elf header: \n  Magic Low %lx, class %d, endianess %d, version %d, osabi %d, abiver %d\n\n", MagicLow, Class, Endianess, Version, OsAbi, AbiVer );

    if( MagicBytes == MagicLow )
    {
        Print( L"KernelFileBuffer seems uncorrupted, Magic Bytes %lx\n", MagicBytes );
    }

    if( Elf64Header->e_type != ET_EXEC )
    {
        Print( L"Kernel is not an executable, %d\n", Elf64Header->e_type );
        return EFI_INCOMPATIBLE_VERSION;
    }

    if ( Elf64Header->e_machine != EM_X86_64 || Class != ELFCLASS64 )
    {
        Print( L"Kernel format is not x86-64, %d\n", Elf64Header->e_machine );
        return EFI_INCOMPATIBLE_VERSION;
    }

    Print( L"Program headers: off %llx, size %llx, number %llx\n", Elf64Header->e_phoff, Elf64Header->e_phentsize, Elf64Header->e_phnum );
    Print( L"Section headers: off %llx, size %llx, number %llx\n", Elf64Header->e_shoff, Elf64Header->e_shentsize, Elf64Header->e_shnum );

    Elf64_Shdr* Elf64SectionHeader = (Elf64_Shdr*)(ImageBase + Elf64Header->e_shoff );

    Elf64_Shdr* SectionNameStringTableHeader = &Elf64SectionHeader[Elf64Header->e_shstrndx];
    CHAR8*      SectionNameStringTable = (CHAR8*)(ImageBase + SectionNameStringTableHeader->sh_offset);

    for( UINT32 SectionIndex = 0; SectionIndex < Elf64Header->e_shnum; SectionIndex++ )
    {
        Elf64_Shdr* Section = &Elf64SectionHeader[SectionIndex];
        Print(
            L"Section %u: name %a, type %u, addr %llx, offset %llx, size %llx\n",
            SectionIndex,
            SectionNameStringTable + Section->sh_name,
            Section->sh_type,
            Section->sh_addr,
            Section->sh_offset,
            Section->sh_size
        );
    }

    Elf64_Phdr* Elf64ProgramHeader = (Elf64_Phdr*)( ImageBase + Elf64Header->e_phoff );

    for ( uint32_t ProgramIndex = 0; ProgramIndex < Elf64Header->e_phnum; ++ProgramIndex )
    {
        Elf64_Phdr* ProgramHeader = &Elf64ProgramHeader[ProgramIndex];
        if ( ProgramHeader->p_type == PT_LOAD )
        {
            Print(
                L"Loading program segment %u: type %u, offset %llx, vaddr %llx, paddr %llx, filesz %llx, memsz %llx, flags %u\n",
                ProgramIndex,
                ProgramHeader->p_type,
                ProgramHeader->p_offset,
                ProgramHeader->p_vaddr,
                ProgramHeader->p_paddr,
                ProgramHeader->p_filesz,
                ProgramHeader->p_memsz,
                ProgramHeader->p_flags
            );

            EFI_STATUS Status = BlElf64LoadProgramSegment( ImageBase, ProgramHeader );
            if ( EFI_ERROR( Status ) )
            {
                Print( L"Failed to load segment %u, status %r\n", ProgramIndex, Status );
                return Status;
            }
        }
    }

    return EFI_SUCCESS;
}