#include "bootloader/elfldr.h"

/*
 * Minimal ELF64 definitions used by the OS64 bootloader - different from the implementation written by Mat.
 * 
 * Unfortunately the better implementation by Mat needs a little more setup. Working with a basic version now.
 *
 *                                  TODO: When merging with main, discard this file (.h/.c) !!!!!!!!!
 *
 * We intentionally keep the loader dependent only on the pieces of ELF that
 * it actually needs: the ELF header and PT_LOAD program headers.  Section
 * headers are linker/debugging metadata and are not required to load the
 * kernel for execution.
 */

#define ELF_NIDENT      16

#define EI_MAG0         0
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6

#define ELFMAG0         0x7f
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'

#define ELFCLASS64      2
#define ELFDATA2LSB     1
#define EV_CURRENT      1

#define ET_EXEC         2
#define EM_X86_64       62

#define PT_LOAD         1

#define PAGE_SIZE       0x1000ULL
#define PAGE_MASK       ( PAGE_SIZE - 1ULL )
#define PAGE_ALIGN_DOWN(Value) ( (UINT64)(Value) & ~PAGE_MASK )
#define PAGE_ALIGN_UP(Value)   ( ( (UINT64)(Value) + PAGE_MASK ) & ~PAGE_MASK )

typedef struct _ELF64_HEADER
{
    UINT8  Ident[ELF_NIDENT];
    UINT16 Type;
    UINT16 Machine;
    UINT32 Version;
    UINT64 Entry;
    UINT64 ProgramHeaderOffset;
    UINT64 SectionHeaderOffset;
    UINT32 Flags;
    UINT16 HeaderSize;
    UINT16 ProgramHeaderEntrySize;
    UINT16 ProgramHeaderCount;
    UINT16 SectionHeaderEntrySize;
    UINT16 SectionHeaderCount;
    UINT16 SectionNameStringTableIndex;

} ELF64_HEADER;

typedef struct _ELF64_PROGRAM_HEADER
{
    UINT32 Type;
    UINT32 Flags;
    UINT64 Offset;
    UINT64 VirtualAddress;
    UINT64 PhysicalAddress;
    UINT64 FileSize;
    UINT64 MemorySize;
    UINT64 Alignment;

} ELF64_PROGRAM_HEADER;

static BOOLEAN
BlElfRangeIsInsideFile(
    IN UINT64 Offset,
    IN UINT64 Size,
    IN UINT64 FileSize
)
{
    /*
     * Written this way rather than checking Offset + Size <= FileSize so an
     * overflowing addition cannot accidentally pass validation.
     */
    if( Offset > FileSize )
    {
        return FALSE;
    }

    return Size <= ( FileSize - Offset );
}

static EFI_STATUS
BlElfValidateHeader(
    IN const ELF64_HEADER* Header,
    IN UINT64              ImageBufferSize
)
{
    if( Header == NULL )
    {
        return EFI_INVALID_PARAMETER;
    }

    if( ImageBufferSize < sizeof( ELF64_HEADER ) )
    {
        return EFI_LOAD_ERROR;
    }

    if(
        Header->Ident[EI_MAG0] != ELFMAG0 ||
        Header->Ident[EI_MAG1] != ELFMAG1 ||
        Header->Ident[EI_MAG2] != ELFMAG2 ||
        Header->Ident[EI_MAG3] != ELFMAG3
    )
    {
        return EFI_LOAD_ERROR;
    }

    if(
        Header->Ident[EI_CLASS]   != ELFCLASS64  ||
        Header->Ident[EI_DATA]    != ELFDATA2LSB ||
        Header->Ident[EI_VERSION] != EV_CURRENT
    )
    {
        return EFI_UNSUPPORTED;
    }

    if(
        Header->Type    != ET_EXEC   ||
        Header->Machine != EM_X86_64 ||
        Header->Version != EV_CURRENT
    )
    {
        return EFI_UNSUPPORTED;
    }

    if(
        Header->HeaderSize != sizeof( ELF64_HEADER ) ||
        Header->ProgramHeaderEntrySize != sizeof( ELF64_PROGRAM_HEADER ) ||
        Header->ProgramHeaderCount == 0
    )
    {
        return EFI_LOAD_ERROR;
    }

    UINT64 ProgramHeaderTableSize =
        (UINT64)Header->ProgramHeaderCount * Header->ProgramHeaderEntrySize;

    if(
        !BlElfRangeIsInsideFile(
            Header->ProgramHeaderOffset,
            ProgramHeaderTableSize,
            ImageBufferSize
        )
    )
    {
        return EFI_LOAD_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
BlElfLoadImage(
    IN  VOID*   ImageFileBuffer,
    IN  UINT64  ImageBufferSize,
    OUT UINT64* EntryPoint
)
{
    if(
        ImageFileBuffer == NULL ||
        EntryPoint       == NULL
    )
    {
        return EFI_INVALID_PARAMETER;
    }

    *EntryPoint = 0;

    if( ImageBufferSize < sizeof( ELF64_HEADER ) )
    {
        return EFI_LOAD_ERROR;
    }

    UINT8* ImageBase = (UINT8*)ImageFileBuffer;
    ELF64_HEADER* Header = (ELF64_HEADER*)ImageBase;

    EFI_STATUS Status = BlElfValidateHeader( Header, ImageBufferSize );
    if( EFI_ERROR( Status ) )
    {
        return Status;
    }

    ELF64_PROGRAM_HEADER* ProgramHeaders =
        (ELF64_PROGRAM_HEADER*)( ImageBase + Header->ProgramHeaderOffset );

    /*
     * Find one page-aligned physical range covering every PT_LOAD segment.
     *
     * Allocating the whole image in one operation avoids the bug in the old
     * main-branch loader where independently page-aligning adjacent segments
     * could make two AllocateAddress calls request overlapping pages.
     *
     * OS64 currently links the kernel as ET_EXEC with p_vaddr == p_paddr, so
     * those linked addresses are also the physical load addresses.
     */
    UINT64 ImageStart = ~0ULL;
    UINT64 ImageEnd   = 0;
    BOOLEAN FoundLoadSegment = FALSE;

    for( UINT16 Index = 0; Index < Header->ProgramHeaderCount; ++Index )
    {
        ELF64_PROGRAM_HEADER* Segment = &ProgramHeaders[Index];

        if( Segment->Type != PT_LOAD )
        {
            continue;
        }

        FoundLoadSegment = TRUE;

        if( Segment->FileSize > Segment->MemorySize )
        {
            return EFI_LOAD_ERROR;
        }

        if(
            !BlElfRangeIsInsideFile(
                Segment->Offset,
                Segment->FileSize,
                ImageBufferSize
            )
        )
        {
            return EFI_LOAD_ERROR;
        }

        if( Segment->MemorySize == 0 )
        {
            continue;
        }

        UINT64 SegmentStart = PAGE_ALIGN_DOWN( Segment->PhysicalAddress );

        if( Segment->PhysicalAddress > ~0ULL - Segment->MemorySize )
        {
            return EFI_LOAD_ERROR;
        }

        UINT64 SegmentEnd = PAGE_ALIGN_UP(
            Segment->PhysicalAddress + Segment->MemorySize
        );

        if( SegmentStart < ImageStart )
        {
            ImageStart = SegmentStart;
        }

        if( SegmentEnd > ImageEnd )
        {
            ImageEnd = SegmentEnd;
        }
    }

    if(
        !FoundLoadSegment ||
        ImageStart == ~0ULL ||
        ImageEnd <= ImageStart
    )
    {
        return EFI_LOAD_ERROR;
    }

    EFI_PHYSICAL_ADDRESS AllocationAddress =
        (EFI_PHYSICAL_ADDRESS)ImageStart;

    UINT64 AllocationSize = ImageEnd - ImageStart;
    UINTN  PageCount      = EFI_SIZE_TO_PAGES( AllocationSize );

    Status = uefi_call_wrapper(
        BS->AllocatePages,
        4,
        AllocateAddress,
        EfiLoaderData,
        PageCount,
        &AllocationAddress
    );
    if( EFI_ERROR( Status ) )
    {
        return Status;
    }

    if( (UINT64)AllocationAddress != ImageStart )
    {
        return EFI_LOAD_ERROR;
    }

    /*
     * Clear the complete allocated image first.  This naturally establishes
     * zero-filled .bss / NOBITS storage and deterministic bytes in gaps
     * between loadable segments.
     */
    SetMem( (VOID*)(UINTN)ImageStart, AllocationSize, 0 );

    for( UINT16 Index = 0; Index < Header->ProgramHeaderCount; ++Index )
    {
        ELF64_PROGRAM_HEADER* Segment = &ProgramHeaders[Index];

        if( Segment->Type != PT_LOAD || Segment->MemorySize == 0 )
        {
            continue;
        }

        /*
         * For the current identity-mapped ET_EXEC kernel, p_paddr is where
         * firmware memory is reserved and where the segment is copied.
         */
        VOID* Destination = (VOID*)(UINTN)Segment->PhysicalAddress;
        VOID* Source      = (VOID*)( ImageBase + Segment->Offset );

        CopyMem( Destination, Source, Segment->FileSize );
    }

    /*
     * The kernel is linked identity-mapped, therefore e_entry is a
     * directly callable address after the load above.
     */
    if( Header->Entry < ImageStart || Header->Entry >= ImageEnd )
    {
        return EFI_LOAD_ERROR;
    }

    *EntryPoint = Header->Entry;
    return EFI_SUCCESS;
}
