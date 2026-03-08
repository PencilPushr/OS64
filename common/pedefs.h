#ifndef COMMON_PEDEFS_H
#define COMMON_PEDEFS_H

//
// defines for basic PE64 architecture
//

// #include "stddefs.h"
// #include "stdtypes.h"
typedef char 				CHAR;

typedef unsigned char  		UINT8;
typedef unsigned short 		UINT16;
typedef unsigned int   		UINT32;
typedef unsigned long long  UINT64;

typedef unsigned short 		WORD;
typedef unsigned int 		ULONG32;
typedef unsigned long long  ULONGLONG;

#define IMAGE_FILE_MACHINE_I386            0x014c
#define IMAGE_FILE_MACHINE_IA64            0x0200
#define IMAGE_FILE_MACHINE_EBC             0x0EBC
#define IMAGE_FILE_MACHINE_X64             0x8664
#define IMAGE_FILE_MACHINE_ARMTHUMB_MIXED  0x01c2
#define IMAGE_FILE_MACHINE_ARM64           0xAA64
#define IMAGE_FILE_MACHINE_RISCV32         0x5032
#define IMAGE_FILE_MACHINE_RISCV64         0x5064
#define IMAGE_FILE_MACHINE_RISCV128        0x5128
#define IMAGE_FILE_MACHINE_LOONGARCH32     0x6232
#define IMAGE_FILE_MACHINE_LOONGARCH64     0x6264

#define IMAGE_DOS_SIGNATURE      0x5A4D    
#define IMAGE_OS2_SIGNATURE      0x454E    
#define IMAGE_OS2_SIGNATURE_LE   0x454C    
#define IMAGE_VXD_SIGNATURE      0x454C    
#define IMAGE_NT_SIGNATURE       0x00004550

typedef struct _IMAGE_DOS_HEADER
{
	UINT16 e_magic;      ///< Magic number.
	UINT16 e_cblp;       ///< Bytes on last page of file.
	UINT16 e_cp;         ///< Pages in file.
	UINT16 e_crlc;       ///< Relocations.
	UINT16 e_cparhdr;    ///< Size of header in paragraphs.
	UINT16 e_minalloc;   ///< Minimum extra paragraphs needed.
	UINT16 e_maxalloc;   ///< Maximum extra paragraphs needed.
	UINT16 e_ss;         ///< Initial (relative) SS value.
	UINT16 e_sp;         ///< Initial SP value.
	UINT16 e_csum;       ///< Checksum.
	UINT16 e_ip;         ///< Initial IP value.
	UINT16 e_cs;         ///< Initial (relative) CS value.
	UINT16 e_lfarlc;     ///< File address of relocation table.
	UINT16 e_ovno;       ///< Overlay number.
	UINT16 e_res[ 4 ];   ///< Reserved words.
	UINT16 e_oemid;      ///< OEM identifier (for e_oeminfo).
	UINT16 e_oeminfo;    ///< OEM information; e_oemid specific.
	UINT16 e_res2[ 10 ]; ///< Reserved words.
	UINT32 e_lfanew;     ///< File address of new exe header.

} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER
{
	UINT16 Machine;
	UINT16 NumberOfSections;
	UINT32 TimeDateStamp;
	UINT32 PointerToSymbolTable;
	UINT32 NumberOfSymbols;
	UINT16 SizeOfOptionalHeader;
	UINT16 Characteristics;

} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

#define IMAGE_SIZEOF_FILE_HEADER  20

#define IMAGE_FILE_RELOCS_STRIPPED      ( 1 << 0  ) ///< 0x0001  Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE     ( 1 << 1  ) ///< 0x0002  File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED   ( 1 << 2  ) ///< 0x0004  Line numbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED  ( 1 << 3  ) ///< 0x0008  Local symbols stripped from file.
#define IMAGE_FILE_LARGE_ADDRESS_AWARE  ( 1 << 5  ) ///< 0x0020  Supports addresses > 2-GB
#define IMAGE_FILE_BYTES_REVERSED_LO    ( 1 << 7  ) ///< 0x0080  Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE        ( 1 << 8  ) ///< 0x0100  32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED       ( 1 << 9  ) ///< 0x0200  Debugging info stripped from file in .DBG file.
#define IMAGE_FILE_SYSTEM               ( 1 << 12 ) ///< 0x1000  System File.
#define IMAGE_FILE_DLL                  ( 1 << 13 ) ///< 0x2000  File is a DLL.
#define IMAGE_FILE_BYTES_REVERSED_HI    ( 1 << 15 ) ///< 0x8000  Bytes of machine word are reversed.

typedef struct _IMAGE_DATA_DIRECTORY
{
	UINT32 VirtualAddress;
	UINT32 Size;

} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_DIRECTORY_ENTRY_EXPORT       0
#define IMAGE_DIRECTORY_ENTRY_IMPORT       1
#define IMAGE_DIRECTORY_ENTRY_RESOURCE     2
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION    3
#define IMAGE_DIRECTORY_ENTRY_SECURITY     4
#define IMAGE_DIRECTORY_ENTRY_BASERELOC    5
#define IMAGE_DIRECTORY_ENTRY_DEBUG        6
#define IMAGE_DIRECTORY_ENTRY_COPYRIGHT    7
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR    8
#define IMAGE_DIRECTORY_ENTRY_TLS          9
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG  10

#define IMAGE_NUMBER_OF_DIRECTORY_ENTRIES  16

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC  0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC  0x20b

typedef struct _IMAGE_OPTIONAL_HEADER
{
	//
	// Standard fields.
	//
	UINT16                      Magic;
	UINT8                       MajorLinkerVersion;
	UINT8                       MinorLinkerVersion;
	UINT32                      SizeOfCode;
	UINT32                      SizeOfInitializedData;
	UINT32                      SizeOfUninitializedData;
	UINT32                      AddressOfEntryPoint;
	UINT32                      BaseOfCode;

	//
	// Optional Header Windows-Specific Fields.
	//
	UINT64                      ImageBase;
	UINT32                      SectionAlignment;
	UINT32                      FileAlignment;
	UINT16                      MajorOperatingSystemVersion;
	UINT16                      MinorOperatingSystemVersion;
	UINT16                      MajorImageVersion;
	UINT16                      MinorImageVersion;
	UINT16                      MajorSubsystemVersion;
	UINT16                      MinorSubsystemVersion;
	UINT32                      Win32VersionValue;
	UINT32                      SizeOfImage;
	UINT32                      SizeOfHeaders;
	UINT32                      CheckSum;
	UINT16                      Subsystem;
	UINT16                      DllCharacteristics;
	UINT64                      SizeOfStackReserve;
	UINT64                      SizeOfStackCommit;
	UINT64                      SizeOfHeapReserve;
	UINT64                      SizeOfHeapCommit;
	UINT32                      LoaderFlags;
	UINT32                      NumberOfRvaAndSizes;

	IMAGE_DATA_DIRECTORY    DataDirectory[ IMAGE_NUMBER_OF_DIRECTORY_ENTRIES ];

} IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_NT_HEADERS
{
	UINT32                     Signature;
	IMAGE_FILE_HEADER          FileHeader;
	IMAGE_OPTIONAL_HEADER      OptionalHeader;

} IMAGE_NT_HEADERS, *PIMAGE_NT_HEADERS;

#define IMAGE_SIZEOF_SHORT_NAME  8

typedef struct _IMAGE_SECTION_HEADER
{
	UINT8     Name[ IMAGE_SIZEOF_SHORT_NAME ];

	union
	{
		UINT32    PhysicalAddress;
		UINT32    VirtualSize;
	} Misc;

	UINT32    VirtualAddress;
	UINT32    SizeOfRawData;
	UINT32    PointerToRawData;
	UINT32    PointerToRelocations;
	UINT32    PointerToLinenumbers;
	UINT16    NumberOfRelocations;
	UINT16    NumberOfLinenumbers;
	UINT32    Characteristics;

} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

#define IMAGE_SIZEOF_SECTION_HEADER  40

//
// Section Flags Values
//
#define IMAGE_SCN_TYPE_NO_PAD             0x00000008  ///< Reserved.
#define IMAGE_SCN_CNT_CODE                0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA    0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA  0x00000080

#define IMAGE_SCN_LNK_OTHER               0x00000100  ///< Reserved.
#define IMAGE_SCN_LNK_INFO                0x00000200  ///< Section contains comments or some other type of information.
#define IMAGE_SCN_LNK_REMOVE              0x00000800  ///< Section contents will not become part of image.
#define IMAGE_SCN_LNK_COMDAT              0x00001000

#define IMAGE_SCN_ALIGN_1BYTES            0x00100000
#define IMAGE_SCN_ALIGN_2BYTES            0x00200000
#define IMAGE_SCN_ALIGN_4BYTES            0x00300000
#define IMAGE_SCN_ALIGN_8BYTES            0x00400000
#define IMAGE_SCN_ALIGN_16BYTES           0x00500000
#define IMAGE_SCN_ALIGN_32BYTES           0x00600000
#define IMAGE_SCN_ALIGN_64BYTES           0x00700000

#define IMAGE_SCN_MEM_DISCARDABLE         0x02000000
#define IMAGE_SCN_MEM_NOT_CACHED          0x04000000
#define IMAGE_SCN_MEM_NOT_PAGED           0x08000000
#define IMAGE_SCN_MEM_SHARED              0x10000000
#define IMAGE_SCN_MEM_EXECUTE             0x20000000
#define IMAGE_SCN_MEM_READ                0x40000000
#define IMAGE_SCN_MEM_WRITE               0x80000000

typedef struct _IMAGE_BASE_RELOCATION
{
	UINT32    VirtualAddress;
	UINT32    SizeOfBlock;
} IMAGE_BASE_RELOCATION, *PIMAGE_BASE_RELOCATION;

#define IMAGE_SIZEOF_BASE_RELOCATION  8

//
// Based relocation types.
//
#define IMAGE_REL_BASED_ABSOLUTE        0
#define IMAGE_REL_BASED_HIGH            1
#define IMAGE_REL_BASED_LOW             2
#define IMAGE_REL_BASED_HIGHLOW         3
#define IMAGE_REL_BASED_HIGHADJ         4
#define IMAGE_REL_BASED_MIPS_JMPADDR    5
#define IMAGE_REL_BASED_ARM_MOV32A      5
#define IMAGE_REL_BASED_ARM_MOV32T      7
#define IMAGE_REL_BASED_IA64_IMM64      9
#define IMAGE_REL_BASED_MIPS_JMPADDR16  9
#define IMAGE_REL_BASED_DIR64           10

typedef struct _IMAGE_EXPORT_DIRECTORY
{
    ULONG32 Characteristics;
    ULONG32 TimeDateStamp;
    WORD  MajorVersion;
    WORD  MinorVersion;
    ULONG32 Name;
    ULONG32 Base;
    ULONG32 NumberOfFunctions;
    ULONG32 NumberOfNames;
    ULONG32 AddressOfFunctions;     // RVA from base of image
    ULONG32 AddressOfNames;         // RVA from base of image
    ULONG32 AddressOfNameOrdinals;  // RVA from base of image

} IMAGE_EXPORT_DIRECTORY, * PIMAGE_EXPORT_DIRECTORY;

typedef struct _IMAGE_IMPORT_BY_NAME
{
    WORD Hint;
    CHAR Name[ 1 ];

} IMAGE_IMPORT_BY_NAME, * PIMAGE_IMPORT_BY_NAME;

typedef union _IMAGE_THUNK_DATA
{
    ULONGLONG ForwarderString;  // PBYTE 
    ULONGLONG Function;         // PDWORD
    ULONGLONG Ordinal;
    ULONGLONG AddressOfData;    // PIMAGE_IMPORT_BY_NAME

} IMAGE_THUNK_DATA, *PIMAGE_THUNK_DATA;

typedef struct _IMAGE_IMPORT_DESCRIPTOR
{
    union
    {
        ULONG32   Characteristics;            // 0 for terminating null import descriptor
        ULONG32   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    } DUMMYUNIONNAME;
    ULONG32   TimeDateStamp;                  // 0 if not bound,
    // -1 if bound, and real date\time stamp
    //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
    // O.W. date/time stamp of DLL bound to (Old BIND)

    ULONG32   ForwarderChain;                 // -1 if no forwarders
    ULONG32   Name;
    ULONG32   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)

} IMAGE_IMPORT_DESCRIPTOR, *PIMAGE_IMPORT_DESCRIPTOR;

#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((ULONG64)(ntheader) +                                            \
     offsetof( IMAGE_NT_HEADERS, OptionalHeader ) +                 \
     ((ntheader))->FileHeader.SizeOfOptionalHeader   \
    ))


#endif // !COMMON_PEDEFS_H