#ifndef COMMON_ELFDEF_H
#define COMMON_ELFDEF_H

#include <stdint.h>

/**
 * Snippets taken from the linux source code at https://github.com/torvalds/linux/blob/master/include/uapi/linux/elf.h
 * 
 * See linux license for use
 */

/* These constants define the various ELF target machines */
#define EM_NONE         0
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3
#define EM_68K          4
#define EM_88K          5
#define EM_486          6   /* Perhaps disused */
#define EM_860          7
#define EM_MIPS         8   /* MIPS R3000 (officially, big-endian only) */
                            /* Next two are historical and binaries and
                               modules of these types will be rejected by
                               Linux.  */
#define EM_MIPS_RS3_LE  10  /* MIPS R3000 little-endian */
#define EM_MIPS_RS4_BE  10  /* MIPS R4000 big-endian */
 
#define EM_PARISC       15  /* HPPA */
#define EM_SPARC32PLUS  18  /* Sun's "v8plus" */
#define EM_PPC          20  /* PowerPC */
#define EM_PPC64        21  /* PowerPC64 */
#define EM_S390         22  /* IBM S/390 */
#define EM_SPU          23  /* Cell BE SPU */
#define EM_ARM          40  /* ARM 32 bit */
#define EM_SH           42  /* SuperH */
#define EM_SPARCV9      43  /* SPARC v9 64-bit */
#define EM_H8_300       46  /* Renesas H8/300 */
#define EM_IA_64        50  /* HP/Intel IA-64 */
#define EM_X86_64       62  /* AMD x86-64 */
#define EM_CRIS         76  /* Axis Communications 32-bit embedded processor */
#define EM_M32R         88  /* Renesas M32R */
#define EM_MN10300      89  /* Panasonic/MEI MN10300, AM33 */
#define EM_OPENRISC     92  /* OpenRISC 32-bit embedded processor */
#define EM_ARCOMPACT    93  /* ARCompact processor */
#define EM_XTENSA       94  /* Tensilica Xtensa Architecture */
#define EM_BLACKFIN     106 /* ADI Blackfin Processor */
#define EM_UNICORE      110 /* UniCore-32 */
#define EM_ALTERA_NIOS2 113 /* Altera Nios II soft-core processor */
#define EM_TI_C6000     140 /* TI C6X DSPs */
#define EM_HEXAGON      164 /* QUALCOMM Hexagon */
#define EM_NDS32        167 /* Andes Technology compact code size
                               embedded RISC processor family */
#define EM_AARCH64      183 /* ARM 64 bit */
#define EM_TILEPRO      188 /* Tilera TILEPro */
#define EM_MICROBLAZE   189 /* Xilinx MicroBlaze */
#define EM_TILEGX       191 /* Tilera TILE-Gx */
#define EM_ARCV2        195 /* ARCv2 Cores */
#define EM_RISCV        243 /* RISC-V */
#define EM_BPF          247 /* Linux BPF - in-kernel virtual machine */
#define EM_CSKY         252 /* C-SKY */
#define EM_LOONGARCH    258 /* LoongArch */
#define EM_FRV          0x5441 /* Fujitsu FR-V */


/*
 * This is an interim value that we will use until the committee comes
 * up with a final number.
 */
#define EM_ALPHA	      0x9026

/* Bogus old m32r magic number, used by old tools. */
#define EM_CYGNUS_M32R	  0x9041
/* This is the old interim value for S/390 architecture */
#define EM_S390_OLD	      0xA390
/* Also Panasonic/MEI MN10300, AM33 */
#define EM_CYGNUS_MN10300 0xbeef

/* These constants define the different elf file types */
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOOS   0xfe00
#define ET_HIOS   0xfeff
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* This is the info that is needed to parse the dynamic section of the file */
#define DT_NULL         0
#define DT_NEEDED       1
#define DT_PLTRELSZ     2
#define DT_PLTGOT       3
#define DT_HASH         4
#define DT_STRTAB       5
#define DT_SYMTAB       6
#define DT_RELA         7
#define DT_RELASZ       8
#define DT_RELAENT      9
#define DT_STRSZ        10
#define DT_SYMENT       11
#define DT_INIT         12
#define DT_FINI         13
#define DT_SONAME       14
#define DT_RPATH        15
#define DT_SYMBOLIC     16
#define DT_REL          17
#define DT_RELSZ        18
#define DT_RELENT       19
#define DT_PLTREL       20
#define DT_DEBUG        21
#define DT_TEXTREL      22
#define DT_JMPREL       23
#define DT_BIND_NOW     24
#define DT_INIT_ARRAY   25
#define DT_FINI_ARRAY   26
#define DT_INIT_ARRAYSZ 27
#define DT_FINI_ARRAYSZ 28
#define DT_RUNPATH      29
#define DT_FLAGS        30
#define DT_PREINIT_ARRAY    32
#define DT_PREINIT_ARRAYSZ  33
#define DT_SYMTAB_SHNDX 34
#define DT_RELRSZ       35
#define DT_RELR         36
#define DT_RELRENT      37
#define DT_ENCODING     32
#define OLD_DT_LOOS     0x60000000
#define DT_LOOS         0x6000000d
#define DT_HIOS         0x6ffff000
#define DT_VALRNGLO     0x6ffffd00
#define DT_VALRNGHI     0x6ffffdff
#define DT_ADDRRNGLO    0x6ffffe00
#define DT_GNU_HASH     0x6ffffef5
#define DT_ADDRRNGHI    0x6ffffeff
#define DT_VERSYM       0x6ffffff0
#define DT_RELACOUNT    0x6ffffff9
#define DT_RELCOUNT     0x6ffffffa
#define DT_FLAGS_1      0x6ffffffb
#define DT_VERDEF       0x6ffffffc
#define DT_VERDEFNUM    0x6ffffffd
#define DT_VERNEED      0x6ffffffe
#define DT_VERNEEDNUM   0x6fffffff
#define OLD_DT_HIOS     0x6fffffff
#define DT_LOPROC       0x70000000
#define DT_HIPROC       0x7fffffff
 
/* DT_FLAGS values */
#define DF_ORIGIN       0x00000001
#define DF_SYMBOLIC     0x00000002
#define DF_TEXTREL      0x00000004
#define DF_BIND_NOW     0x00000008
#define DF_STATIC_TLS   0x00000010
 
/* DT_FLAGS_1 values */
#define DF_1_NOW        0x00000001
#define DF_1_GLOBAL     0x00000002
#define DF_1_GROUP      0x00000004
#define DF_1_NODELETE   0x00000008
#define DF_1_LOADFLTR   0x00000010
#define DF_1_INITFIRST  0x00000020
#define DF_1_NOOPEN     0x00000040
#define DF_1_ORIGIN     0x00000080
#define DF_1_DIRECT     0x00000100
#define DF_1_TRANS      0x00000200
#define DF_1_INTERPOSE  0x00000400
#define DF_1_NODEFLIB   0x00000800
#define DF_1_NODUMP     0x00001000
#define DF_1_CONFALT    0x00002000
#define DF_1_ENDFILTEE  0x00004000
#define DF_1_DISPRELDNE 0x00008000
#define DF_1_DISPRELPND 0x00010000
#define DF_1_NODIRECT   0x00020000
#define DF_1_IGNMULDEF  0x00040000
#define DF_1_NOKSYMS    0x00080000
#define DF_1_NOHDR      0x00100000
#define DF_1_EDITED     0x00200000
#define DF_1_NORELOC    0x00400000
#define DF_1_SYMINTPOSE 0x00800000
#define DF_1_GLOBAUDIT  0x01000000
#define DF_1_SINGLETON  0x02000000
#define DF_1_PIE        0x08000000

/* This info is needed when parsing the symbol table */
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2
#define STB_LOOS   10
#define STB_GNU_UNIQUE 10
#define STB_HIOS   12
#define STB_LOPROC 13
#define STB_HIPROC 15
 
#define STN_UNDEF 0
 
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6
#define STT_LOOS    10
#define STT_GNU_IFUNC 10
#define STT_HIOS    12
#define STT_LOPROC  13
#define STT_HIPROC  15
 
/* Symbol visibility (st_other) */
#define STV_DEFAULT   0
#define STV_INTERNAL  1
#define STV_HIDDEN    2
#define STV_PROTECTED 3
 
#define VER_FLG_BASE 0x1
#define VER_FLG_WEAK 0x2
 
#define ELF_ST_BIND(x)       ((x) >> 4)
#define ELF_ST_TYPE(x)       ((x) & 0xf)
#define ELF_ST_INFO(b, t)    (((b) << 4) | ((t) & 0xf))
#define ELF_ST_VISIBILITY(o) ((o) & 0x3)
#define ELF32_ST_BIND(x)     ELF_ST_BIND(x)
#define ELF32_ST_TYPE(x)     ELF_ST_TYPE(x)
#define ELF64_ST_BIND(x)     ELF_ST_BIND(x)
#define ELF64_ST_TYPE(x)     ELF_ST_TYPE(x)

typedef struct _Elf32_Dyn 
{
    int32_t d_tag;
    union 
    {
        int32_t  d_val;
        uint32_t d_ptr;
    } d_un;
} Elf32_Dyn;

typedef struct _Elf64_Dyn
{
    int64_t d_tag; 
    union 
    {
        uint64_t d_val;
        uint64_t d_ptr; 
    } d_un;
} Elf64_Dyn;

/* The following are used with relocations */
#define ELF32_R_SYM(x)         ((x) >> 8)
#define ELF32_R_TYPE(x)        ((x) & 0xff)
#define ELF32_R_INFO(s, t)     (((s) << 8) + ((t) & 0xff))
 
#define ELF64_R_SYM(i)         ((i) >> 32)
#define ELF64_R_TYPE(i)        ((i) & 0xffffffff)
#define ELF64_R_INFO(s, t)     ((((uint64_t)(s)) << 32) + ((t) & 0xffffffff))


typedef struct _Elf32_Rel 
{
    uint32_t r_offset;
    uint32_t r_info;
} Elf32_Rel;

typedef struct _Elf64_Rel
{
    uint64_t r_offset;  // location of action
    uint64_t r_info;    // index and type of relocation
} ELf64_Rel;

typedef struct _Elf32_Rela
{
    uint32_t r_offset;
    uint32_t r_info;
    int32_t  r_addend;
} Elf32_Rela;

typedef struct _Elf64_Rela
{
    uint64_t r_offset;
    uint64_t r_info;
    int64_t  r_addend; // constant addend used to compute value
} Elf64_Rela;

/* RELR — compact relative relocation format (DT_RELR) */
typedef uint32_t Elf32_Relr;
typedef uint64_t Elf64_Relr;

/* --- i386 (EM_386) --- */
#define R_386_NONE          0
#define R_386_32            1
#define R_386_PC32          2
#define R_386_GOT32         3
#define R_386_PLT32         4
#define R_386_COPY          5
#define R_386_GLOB_DAT      6
#define R_386_JMP_SLOT      7
#define R_386_RELATIVE      8
#define R_386_GOTOFF        9
#define R_386_GOTPC         10
#define R_386_32PLT         11
#define R_386_TLS_TPOFF     14
#define R_386_TLS_IE        15
#define R_386_TLS_GOTIE     16
#define R_386_TLS_LE        17
#define R_386_TLS_GD        18
#define R_386_TLS_LDM       19
#define R_386_16            20
#define R_386_PC16          21
#define R_386_8             22
#define R_386_PC8           23
#define R_386_TLS_GD_32     24
#define R_386_TLS_GD_PUSH   25
#define R_386_TLS_GD_CALL   26
#define R_386_TLS_GD_POP    27
#define R_386_TLS_LDM_32    28
#define R_386_TLS_LDM_PUSH  29
#define R_386_TLS_LDM_CALL  30
#define R_386_TLS_LDM_POP   31
#define R_386_TLS_LDO_32    32
#define R_386_TLS_IE_32     33
#define R_386_TLS_LE_32     34
#define R_386_TLS_DTPMOD32  35
#define R_386_TLS_DTPOFF32  36
#define R_386_TLS_TPOFF32   37
#define R_386_SIZE32        38
#define R_386_TLS_GOTDESC   39
#define R_386_TLS_DESC_CALL 40
#define R_386_TLS_DESC      41
#define R_386_IRELATIVE     42
#define R_386_GOT32X        43
 
/* --- x86_64 (EM_X86_64) --- */
#define R_X86_64_NONE             0
#define R_X86_64_64               1
#define R_X86_64_PC32             2
#define R_X86_64_GOT32            3
#define R_X86_64_PLT32            4
#define R_X86_64_COPY             5
#define R_X86_64_GLOB_DAT         6
#define R_X86_64_JUMP_SLOT        7
#define R_X86_64_RELATIVE         8
#define R_X86_64_GOTPCREL         9
#define R_X86_64_32               10
#define R_X86_64_32S              11
#define R_X86_64_16               12
#define R_X86_64_PC16             13
#define R_X86_64_8                14
#define R_X86_64_PC8              15
#define R_X86_64_DTPMOD64         16
#define R_X86_64_DTPOFF64         17
#define R_X86_64_TPOFF64          18
#define R_X86_64_TLSGD            19
#define R_X86_64_TLSLD            20
#define R_X86_64_DTPOFF32         21
#define R_X86_64_GOTTPOFF         22
#define R_X86_64_TPOFF32          23
#define R_X86_64_PC64             24
#define R_X86_64_GOTOFF64         25
#define R_X86_64_GOTPC32          26
#define R_X86_64_GOT64            27
#define R_X86_64_GOTPCREL64       28
#define R_X86_64_GOTPC64          29
#define R_X86_64_GOTPLT64         30
#define R_X86_64_PLTOFF64         31
#define R_X86_64_SIZE32           32
#define R_X86_64_SIZE64           33
#define R_X86_64_GOTPC32_TLSDESC  34
#define R_X86_64_TLSDESC_CALL     35
#define R_X86_64_TLSDESC          36
#define R_X86_64_IRELATIVE        37
#define R_X86_64_RELATIVE64       38
#define R_X86_64_GOTPCRELX        41
#define R_X86_64_REX_GOTPCRELX    42
 
/* --- ARM 32-bit (EM_ARM) --- */
#define R_ARM_NONE              0
#define R_ARM_PC24              1
#define R_ARM_ABS32             2
#define R_ARM_REL32             3
#define R_ARM_LDR_PC_G0         4
#define R_ARM_ABS16             5
#define R_ARM_ABS12             6
#define R_ARM_THM_ABS5          7
#define R_ARM_ABS8              8
#define R_ARM_SBREL32           9
#define R_ARM_THM_CALL          10
#define R_ARM_THM_PC8           11
#define R_ARM_BREL_ADJ          12
#define R_ARM_TLS_DESC          13
#define R_ARM_THM_SWI8          14
#define R_ARM_XPC25             15
#define R_ARM_THM_XPC22         16
#define R_ARM_TLS_DTPMOD32      17
#define R_ARM_TLS_DTPOFF32      18
#define R_ARM_TLS_TPOFF32       19
#define R_ARM_COPY              20
#define R_ARM_GLOB_DAT          21
#define R_ARM_JUMP_SLOT         22
#define R_ARM_RELATIVE          23
#define R_ARM_GOTOFF32          24
#define R_ARM_BASE_PREL         25
#define R_ARM_GOT_BREL          26
#define R_ARM_PLT32             27
#define R_ARM_CALL              28
#define R_ARM_JUMP24            29
#define R_ARM_THM_JUMP24        30
#define R_ARM_BASE_ABS          31
#define R_ARM_TARGET1           38
#define R_ARM_V4BX              40
#define R_ARM_TARGET2           41
#define R_ARM_PREL31            42
#define R_ARM_MOVW_ABS_NC       43
#define R_ARM_MOVT_ABS          44
#define R_ARM_MOVW_PREL_NC      45
#define R_ARM_MOVT_PREL         46
#define R_ARM_THM_MOVW_ABS_NC   47
#define R_ARM_THM_MOVT_ABS      48
#define R_ARM_THM_MOVW_PREL_NC  49
#define R_ARM_THM_MOVT_PREL     50
#define R_ARM_TLS_GD32          104
#define R_ARM_TLS_LDM32         105
#define R_ARM_TLS_LDO32         106
#define R_ARM_TLS_IE32          107
#define R_ARM_TLS_LE32          108
#define R_ARM_TLS_LDO12         109
#define R_ARM_TLS_LE12          110
#define R_ARM_TLS_IE12GP        111
#define R_ARM_IRELATIVE         160
 
/* --- AArch64 (EM_AARCH64) --- */
#define R_AARCH64_NONE                          0
#define R_AARCH64_ABS64                         257
#define R_AARCH64_ABS32                         258
#define R_AARCH64_ABS16                         259
#define R_AARCH64_PREL64                        260
#define R_AARCH64_PREL32                        261
#define R_AARCH64_PREL16                        262
#define R_AARCH64_MOVW_UABS_G0                  263
#define R_AARCH64_MOVW_UABS_G0_NC               264
#define R_AARCH64_MOVW_UABS_G1                  265
#define R_AARCH64_MOVW_UABS_G1_NC               266
#define R_AARCH64_MOVW_UABS_G2                  267
#define R_AARCH64_MOVW_UABS_G2_NC               268
#define R_AARCH64_MOVW_UABS_G3                  269
#define R_AARCH64_MOVW_SABS_G0                  270
#define R_AARCH64_MOVW_SABS_G1                  271
#define R_AARCH64_MOVW_SABS_G2                  272
#define R_AARCH64_LD_PREL_LO19                  273
#define R_AARCH64_ADR_PREL_LO21                 274
#define R_AARCH64_ADR_PREL_PG_HI21              275
#define R_AARCH64_ADR_PREL_PG_HI21_NC           276
#define R_AARCH64_ADD_ABS_LO12_NC               277
#define R_AARCH64_LDST8_ABS_LO12_NC             278
#define R_AARCH64_TSTBR14                       279
#define R_AARCH64_CONDBR19                      280
#define R_AARCH64_JUMP26                        282
#define R_AARCH64_CALL26                        283
#define R_AARCH64_LDST16_ABS_LO12_NC            284
#define R_AARCH64_LDST32_ABS_LO12_NC            285
#define R_AARCH64_LDST64_ABS_LO12_NC            286
#define R_AARCH64_MOVW_PREL_G0                  287
#define R_AARCH64_MOVW_PREL_G0_NC               288
#define R_AARCH64_MOVW_PREL_G1                  289
#define R_AARCH64_MOVW_PREL_G1_NC               290
#define R_AARCH64_MOVW_PREL_G2                  291
#define R_AARCH64_MOVW_PREL_G2_NC               292
#define R_AARCH64_MOVW_PREL_G3                  293
#define R_AARCH64_LDST128_ABS_LO12_NC           299
#define R_AARCH64_MOVW_GOTOFF_G0                300
#define R_AARCH64_MOVW_GOTOFF_G0_NC             301
#define R_AARCH64_MOVW_GOTOFF_G1                302
#define R_AARCH64_MOVW_GOTOFF_G1_NC             303
#define R_AARCH64_MOVW_GOTOFF_G2                304
#define R_AARCH64_MOVW_GOTOFF_G2_NC             305
#define R_AARCH64_MOVW_GOTOFF_G3                306
#define R_AARCH64_GOTREL64                      307
#define R_AARCH64_GOTREL32                      308
#define R_AARCH64_GOT_LD_PREL19                 309
#define R_AARCH64_LD64_GOTOFF_LO15              310
#define R_AARCH64_ADR_GOT_PAGE                  311
#define R_AARCH64_LD64_GOT_LO12_NC              312
#define R_AARCH64_LD64_GOTPAGE_LO15             313
#define R_AARCH64_TLSGD_ADR_PREL21              512
#define R_AARCH64_TLSGD_ADR_PAGE21              513
#define R_AARCH64_TLSGD_ADD_LO12_NC             514
#define R_AARCH64_TLSLD_ADR_PREL21              517
#define R_AARCH64_TLSLD_ADR_PAGE21              518
#define R_AARCH64_TLSLD_ADD_LO12_NC             519
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G1        539
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC     540
#define R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21     541
#define R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC   542
#define R_AARCH64_TLSIE_LD_GOTTPREL_PREL19      543
#define R_AARCH64_TLSLE_MOVW_TPREL_G2           544
#define R_AARCH64_TLSLE_MOVW_TPREL_G1           545
#define R_AARCH64_TLSLE_MOVW_TPREL_G1_NC        546
#define R_AARCH64_TLSLE_MOVW_TPREL_G0           547
#define R_AARCH64_TLSLE_MOVW_TPREL_G0_NC        548
#define R_AARCH64_TLSLE_ADD_TPREL_HI12          549
#define R_AARCH64_TLSLE_ADD_TPREL_LO12          550
#define R_AARCH64_TLSLE_ADD_TPREL_LO12_NC       551
#define R_AARCH64_TLSDESC_LD_PREL19             560
#define R_AARCH64_TLSDESC_ADR_PREL21            561
#define R_AARCH64_TLSDESC_ADR_PAGE21            562
#define R_AARCH64_TLSDESC_LD64_LO12             563
#define R_AARCH64_TLSDESC_ADD_LO12              564
#define R_AARCH64_TLSDESC_OFF_G1                565
#define R_AARCH64_TLSDESC_OFF_G0_NC             566
#define R_AARCH64_TLSDESC_LDR                   567
#define R_AARCH64_TLSDESC_ADD                   568
#define R_AARCH64_TLSDESC_CALL                  569
#define R_AARCH64_COPY                          1024
#define R_AARCH64_GLOB_DAT                      1025
#define R_AARCH64_JUMP_SLOT                     1026
#define R_AARCH64_RELATIVE                      1027
#define R_AARCH64_TLS_DTPMOD                    1028
#define R_AARCH64_TLS_DTPREL                    1029
#define R_AARCH64_TLS_TPREL                     1030
#define R_AARCH64_TLSDESC                       1031
#define R_AARCH64_IRELATIVE                     1032
 
/* --- RISC-V (EM_RISCV) --- */
#define R_RISCV_NONE             0
#define R_RISCV_32               1
#define R_RISCV_64               2
#define R_RISCV_RELATIVE         3
#define R_RISCV_COPY             4
#define R_RISCV_JUMP_SLOT        5
#define R_RISCV_TLS_DTPMOD32     6
#define R_RISCV_TLS_DTPMOD64     7
#define R_RISCV_TLS_DTPREL32     8
#define R_RISCV_TLS_DTPREL64     9
#define R_RISCV_TLS_TPREL32      10
#define R_RISCV_TLS_TPREL64      11
#define R_RISCV_TLSDESC          12
#define R_RISCV_BRANCH           16
#define R_RISCV_JAL              17
#define R_RISCV_CALL             18
#define R_RISCV_CALL_PLT         19
#define R_RISCV_GOT_HI20         20
#define R_RISCV_TLS_GOT_HI20     21
#define R_RISCV_TLS_GD_HI20      22
#define R_RISCV_PCREL_HI20       23
#define R_RISCV_PCREL_LO12_I     24
#define R_RISCV_PCREL_LO12_S     25
#define R_RISCV_HI20             26
#define R_RISCV_LO12_I           27
#define R_RISCV_LO12_S           28
#define R_RISCV_TPREL_HI20       29
#define R_RISCV_TPREL_LO12_I     30
#define R_RISCV_TPREL_LO12_S     31
#define R_RISCV_TPREL_ADD        32
#define R_RISCV_ADD8             33
#define R_RISCV_ADD16            34
#define R_RISCV_ADD32            35
#define R_RISCV_ADD64            36
#define R_RISCV_SUB8             37
#define R_RISCV_SUB16            38
#define R_RISCV_SUB32            39
#define R_RISCV_SUB64            40
#define R_RISCV_GOT32_PCREL      41
#define R_RISCV_ALIGN            43
#define R_RISCV_RVC_BRANCH       44
#define R_RISCV_RVC_JUMP         45
#define R_RISCV_RELAX            51
#define R_RISCV_SUB6             52
#define R_RISCV_SET6             53
#define R_RISCV_SET8             54
#define R_RISCV_SET16            55
#define R_RISCV_SET32            56
#define R_RISCV_32_PCREL         57
#define R_RISCV_IRELATIVE        58
#define R_RISCV_PLT32            59
#define R_RISCV_SET_ULEB128      60
#define R_RISCV_SUB_ULEB128      61
#define R_RISCV_TLSDESC_HI20     62
#define R_RISCV_TLSDESC_LOAD_LO12 63
#define R_RISCV_TLSDESC_ADD_LO12 64
#define R_RISCV_TLSDESC_CALL     65
 
/* --- PowerPC 32-bit (EM_PPC) --- */
#define R_PPC_NONE              0
#define R_PPC_ADDR32            1
#define R_PPC_ADDR24            2
#define R_PPC_ADDR16            3
#define R_PPC_ADDR16_LO         4
#define R_PPC_ADDR16_HI         5
#define R_PPC_ADDR16_HA         6
#define R_PPC_ADDR14            7
#define R_PPC_ADDR14_BRTAKEN    8
#define R_PPC_ADDR14_BRNTAKEN   9
#define R_PPC_REL24             10
#define R_PPC_REL14             11
#define R_PPC_REL14_BRTAKEN     12
#define R_PPC_REL14_BRNTAKEN    13
#define R_PPC_GOT16             14
#define R_PPC_GOT16_LO          15
#define R_PPC_GOT16_HI          16
#define R_PPC_GOT16_HA          17
#define R_PPC_PLTREL24          18
#define R_PPC_COPY              19
#define R_PPC_GLOB_DAT          20
#define R_PPC_JMP_SLOT          21
#define R_PPC_RELATIVE          22
#define R_PPC_LOCAL24PC         23
#define R_PPC_UADDR32           24
#define R_PPC_UADDR16           25
#define R_PPC_REL32             26
#define R_PPC_PLT32             27
#define R_PPC_PLTREL32          28
#define R_PPC_PLT16_LO          29
#define R_PPC_PLT16_HI          30
#define R_PPC_PLT16_HA          31
#define R_PPC_SDAREL16          32
#define R_PPC_SECTOFF           33
#define R_PPC_SECTOFF_LO        34
#define R_PPC_SECTOFF_HI        35
#define R_PPC_SECTOFF_HA        36
#define R_PPC_IRELATIVE         248
 
/* --- PowerPC 64-bit (EM_PPC64) --- */
#define R_PPC64_NONE            0
#define R_PPC64_ADDR32          1
#define R_PPC64_ADDR24          2
#define R_PPC64_ADDR16          3
#define R_PPC64_ADDR16_LO       4
#define R_PPC64_ADDR16_HI       5
#define R_PPC64_ADDR16_HA       6
#define R_PPC64_ADDR14          7
#define R_PPC64_REL24           10
#define R_PPC64_REL14           11
#define R_PPC64_GOT16           14
#define R_PPC64_GOT16_LO        15
#define R_PPC64_GOT16_HI        16
#define R_PPC64_GOT16_HA        17
#define R_PPC64_COPY            19
#define R_PPC64_GLOB_DAT        20
#define R_PPC64_JMP_SLOT        21
#define R_PPC64_RELATIVE        22
#define R_PPC64_UADDR32         24
#define R_PPC64_UADDR16         25
#define R_PPC64_REL32           26
#define R_PPC64_PLT32           27
#define R_PPC64_PLTREL32        28
#define R_PPC64_ADDR64          38
#define R_PPC64_ADDR16_HIGHER   39
#define R_PPC64_ADDR16_HIGHERA  40
#define R_PPC64_ADDR16_HIGHEST  41
#define R_PPC64_ADDR16_HIGHESTA 42
#define R_PPC64_UADDR64         43
#define R_PPC64_REL64           44
#define R_PPC64_PLT64           45
#define R_PPC64_PLTREL64        46
#define R_PPC64_TOC16           47
#define R_PPC64_TOC16_LO        48
#define R_PPC64_TOC16_HI        49
#define R_PPC64_TOC16_HA        50
#define R_PPC64_TOC             51
#define R_PPC64_PLTGOT16        52
#define R_PPC64_PLTGOT16_LO     53
#define R_PPC64_PLTGOT16_HI     54
#define R_PPC64_PLTGOT16_HA     55
#define R_PPC64_TLS             67
#define R_PPC64_DTPMOD64        68
#define R_PPC64_TPREL16         69
#define R_PPC64_TPREL16_LO      70
#define R_PPC64_TPREL16_HI      71
#define R_PPC64_TPREL16_HA      72
#define R_PPC64_TPREL64         73
#define R_PPC64_DTPREL16        74
#define R_PPC64_DTPREL64        78
#define R_PPC64_IRELATIVE       248
 
/* --- MIPS (EM_MIPS) --- */
#define R_MIPS_NONE             0
#define R_MIPS_16               1
#define R_MIPS_32               2
#define R_MIPS_REL32            3
#define R_MIPS_26               4
#define R_MIPS_HI16             5
#define R_MIPS_LO16             6
#define R_MIPS_GPREL16          7
#define R_MIPS_LITERAL          8
#define R_MIPS_GOT16            9
#define R_MIPS_PC16             10
#define R_MIPS_CALL16           11
#define R_MIPS_GPREL32          12
#define R_MIPS_64               18
#define R_MIPS_GOT_DISP         19
#define R_MIPS_GOT_PAGE         20
#define R_MIPS_GOT_OFST         21
#define R_MIPS_GOT_HI16         22
#define R_MIPS_GOT_LO16         23
#define R_MIPS_SUB              24
#define R_MIPS_CALL_HI16        30
#define R_MIPS_CALL_LO16        31
#define R_MIPS_TLS_DTPMOD32     38
#define R_MIPS_TLS_DTPREL32     39
#define R_MIPS_TLS_DTPMOD64     40
#define R_MIPS_TLS_DTPREL64     41
#define R_MIPS_TLS_GD           42
#define R_MIPS_TLS_LDM          43
#define R_MIPS_TLS_DTPREL_HI16  44
#define R_MIPS_TLS_DTPREL_LO16  45
#define R_MIPS_TLS_GOTTPREL     46
#define R_MIPS_TLS_TPREL32      47
#define R_MIPS_TLS_TPREL64      48
#define R_MIPS_TLS_TPREL_HI16   49
#define R_MIPS_TLS_TPREL_LO16   50
#define R_MIPS_COPY             126
#define R_MIPS_JUMP_SLOT        127
#define R_MIPS_RELATIVE         128
 
/* --- LoongArch (EM_LOONGARCH) --- */
#define R_LARCH_NONE                       0
#define R_LARCH_32                         1
#define R_LARCH_64                         2
#define R_LARCH_RELATIVE                   3
#define R_LARCH_COPY                       4
#define R_LARCH_JUMP_SLOT                  5
#define R_LARCH_TLS_DTPMOD32               6
#define R_LARCH_TLS_DTPMOD64               7
#define R_LARCH_TLS_DTPREL32               8
#define R_LARCH_TLS_DTPREL64               9
#define R_LARCH_TLS_TPREL32                10
#define R_LARCH_TLS_TPREL64                11
#define R_LARCH_IRELATIVE                  12
#define R_LARCH_TLS_DESC32                 13
#define R_LARCH_TLS_DESC64                 14
#define R_LARCH_MARK_LA                    20
#define R_LARCH_MARK_PCREL                 21
#define R_LARCH_SOP_PUSH_PCREL             22
#define R_LARCH_SOP_PUSH_ABSOLUTE          23
#define R_LARCH_B16                        64
#define R_LARCH_B21                        65
#define R_LARCH_B26                        66
#define R_LARCH_ABS_HI20                   67
#define R_LARCH_ABS_LO12                   68
#define R_LARCH_ABS64_LO20                 69
#define R_LARCH_ABS64_HI12                 70
#define R_LARCH_PCALA_HI20                 71
#define R_LARCH_PCALA_LO12                 72
#define R_LARCH_PCALA64_LO20               73
#define R_LARCH_PCALA64_HI12               74
#define R_LARCH_GOT_PC_HI20                75
#define R_LARCH_GOT_PC_LO12                76
#define R_LARCH_GOT64_PC_LO20              77
#define R_LARCH_GOT64_PC_HI12              78
#define R_LARCH_CALL36                     110
 
/* --- s390 (EM_S390) --- */
#define R_390_NONE              0
#define R_390_8                 1
#define R_390_12                2
#define R_390_16                3
#define R_390_32                4
#define R_390_PC32              5
#define R_390_GOT12             6
#define R_390_GOT32             7
#define R_390_PLT32             8
#define R_390_COPY              9
#define R_390_GLOB_DAT          10
#define R_390_JMP_SLOT          11
#define R_390_RELATIVE          12
#define R_390_GOTOFF32          13
#define R_390_GOTPC             14
#define R_390_GOT16             15
#define R_390_PC16              16
#define R_390_PC16DBL           17
#define R_390_PLT16DBL          18
#define R_390_PC32DBL           19
#define R_390_PLT32DBL          20
#define R_390_GOTPCDBL          21
#define R_390_64                22
#define R_390_PC64              23
#define R_390_GOT64             24
#define R_390_PLT64             25
#define R_390_GOTENT            26
#define R_390_IRELATIVE         61
 
/* --- SPARC (EM_SPARC, EM_SPARCV9) --- */
#define R_SPARC_NONE            0
#define R_SPARC_8               1
#define R_SPARC_16              2
#define R_SPARC_32              3
#define R_SPARC_DISP8           4
#define R_SPARC_DISP16          5
#define R_SPARC_DISP32          6
#define R_SPARC_WDISP30         7
#define R_SPARC_WDISP22         8
#define R_SPARC_HI22            9
#define R_SPARC_22              10
#define R_SPARC_13              11
#define R_SPARC_LO10            12
#define R_SPARC_GOT10           13
#define R_SPARC_GOT13           14
#define R_SPARC_GOT22           15
#define R_SPARC_PC10            16
#define R_SPARC_PC22            17
#define R_SPARC_WPLT30          18
#define R_SPARC_COPY            19
#define R_SPARC_GLOB_DAT        20
#define R_SPARC_JMP_SLOT        21
#define R_SPARC_RELATIVE        22
#define R_SPARC_UA32            23
#define R_SPARC_64              32
#define R_SPARC_IRELATIVE       249

typedef struct _Elf32_Sym
{
    uint32_t st_name;
    uint32_t st_value;
    uint32_t st_size; 
    uint8_t  st_info;
    uint8_t  st_other;
    uint16_t st_shndx;
} Elf32_Sym;

typedef struct _Elf64_Sym
{
    uint32_t st_name;  // symnbol name, index in string table 
    uint8_t  st_info;  // type and binding attributes
    uint8_t  st_other; // no defined meaning, 0
    uint16_t st_shndx; // assocaited section index
    uint64_t st_value; // value of the symbol
    uint64_t st_size;  // associated symbol size
} Elf64_Sym;

#define EI_NIDENT	16

typedef struct _Elf32_Ehdr
{
    uint8_t  e_ident[ EI_NIDENT ];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf32_Ehdr;

typedef struct _Elf64_Ehdr
{
    uint8_t  e_ident[ EI_NIDENT ]; // ELF 'magic number'
    uint16_t e_type; 
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;  // entry virtual address
    uint64_t e_phoff;  // program header table offset
    uint64_t e_shoff;  // section header table offset
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf64_Ehdr;

/* Sentinel: real value of e_phnum is in section header 0's sh_info.
 * Same trick exists for e_shnum (sh_size of shdr 0) and e_shstrndx
 * (sh_link of shdr 0) when they overflow. */
#define PN_XNUM 0xffff

/* These constants define the permissions on sections in the program
   header, p_flags. */
#define PF_X             0x1
#define PF_W             0x2
#define PF_R             0x4
#define PF_MASKOS        0x0ff00000
#define PF_MASKPROC      0xf0000000

/* These constants define program header p_type values */
#define PT_NULL          0
#define PT_LOAD          1
#define PT_DYNAMIC       2
#define PT_INTERP        3
#define PT_NOTE          4
#define PT_SHLIB         5
#define PT_PHDR          6
#define PT_TLS           7
#define PT_NUM           8
#define PT_LOOS          0x60000000
#define PT_GNU_EH_FRAME  0x6474e550
#define PT_GNU_STACK     0x6474e551
#define PT_GNU_RELRO     0x6474e552
#define PT_GNU_PROPERTY  0x6474e553
#define PT_GNU_SFRAME    0x6474e554
#define PT_HIOS          0x6fffffff
#define PT_LOPROC        0x70000000
#define PT_HIPROC        0x7fffffff

typedef struct _Elf32_Phdr
{
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} Elf32_Phdr;

typedef struct _Elf64_Phdr
{
    uint32_t p_type;   
    uint32_t p_flags;
    uint64_t p_offset; // segment file offset
    uint64_t p_vaddr;  // segment virtual address
    uint64_t p_paddr;  // segment physical address
    uint64_t p_filesz; // segment size in file
    uint64_t p_memsz;  // segment size in memory
    uint64_t p_align;  // segment alignment, files & memory
} Elf64_Phdr;

/* sh_type */
#define SHT_NULL            0
#define SHT_PROGBITS        1
#define SHT_SYMTAB          2
#define SHT_STRTAB          3
#define SHT_RELA            4
#define SHT_HASH            5
#define SHT_DYNAMIC         6
#define SHT_NOTE            7
#define SHT_NOBITS          8
#define SHT_REL             9
#define SHT_SHLIB           10
#define SHT_DYNSYM          11
#define SHT_INIT_ARRAY      14
#define SHT_FINI_ARRAY      15
#define SHT_PREINIT_ARRAY   16
#define SHT_GROUP           17
#define SHT_SYMTAB_SHNDX    18
#define SHT_RELR            19
#define SHT_NUM             20
#define SHT_LOOS            0x60000000
#define SHT_GNU_ATTRIBUTES  0x6ffffff5
#define SHT_GNU_HASH        0x6ffffff6
#define SHT_GNU_LIBLIST     0x6ffffff7
#define SHT_CHECKSUM        0x6ffffff8
#define SHT_LOSUNW          0x6ffffffa
#define SHT_SUNW_move       0x6ffffffa
#define SHT_SUNW_COMDAT     0x6ffffffb
#define SHT_SUNW_syminfo    0x6ffffffc
#define SHT_GNU_verdef      0x6ffffffd
#define SHT_GNU_verneed     0x6ffffffe
#define SHT_GNU_versym      0x6fffffff
#define SHT_HISUNW          0x6fffffff
#define SHT_HIOS            0x6fffffff
#define SHT_LOPROC          0x70000000
#define SHT_HIPROC          0x7fffffff
#define SHT_LOUSER          0x80000000
#define SHT_HIUSER          0xffffffff

/* sh_flags */
#define SHF_WRITE             0x1
#define SHF_ALLOC             0x2
#define SHF_EXECINSTR         0x4
#define SHF_MERGE             0x10
#define SHF_STRINGS           0x20
#define SHF_INFO_LINK         0x40
#define SHF_LINK_ORDER        0x80
#define SHF_OS_NONCONFORMING  0x100
#define SHF_GROUP             0x200
#define SHF_TLS               0x400
#define SHF_COMPRESSED        0x800
#define SHF_RELA_LIVEPATCH    0x00100000
#define SHF_RO_AFTER_INIT     0x00200000
#define SHF_ORDERED           0x04000000
#define SHF_EXCLUDE           0x08000000
#define SHF_MASKOS            0x0ff00000
#define SHF_MASKPROC          0xf0000000

/* Section group flags (in the SHT_GROUP word) */
#define GRP_COMDAT   0x1
#define GRP_MASKOS   0x0ff00000
#define GRP_MASKPROC 0xf0000000

/* special section indexes */
#define SHN_UNDEF       0
#define SHN_LORESERVE   0xff00
#define SHN_LOPROC      0xff00
#define SHN_HIPROC      0xff1f
#define SHN_LOOS        0xff20
#define SHN_LIVEPATCH   0xff20
#define SHN_HIOS        0xff3f
#define SHN_ABS         0xfff1
#define SHN_COMMON      0xfff2
#define SHN_XINDEX      0xffff
#define SHN_HIRESERVE   0xffff

typedef struct _Elf32_Shdr
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint32_t sh_flags;
    uint32_t sh_addr;
    uint32_t sh_offset;
    uint32_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint32_t sh_addralign;
    uint32_t sh_entsize;
} Elf32_Shdr;

typedef struct _Elf64_Shdr
{
    uint32_t sh_name;       // section name, index in string table
    uint32_t sh_type;       // type of section
    uint64_t sh_flags;      // misc section attributes
    uint64_t sh_addr;       // section virtual address at execution
    uint64_t sh_offset;     // section file offset
    uint64_t sh_size;       // size of section in bytes
    uint32_t sh_link;       // index of another section
    uint32_t sh_info;       // additional section information
    uint64_t sh_addralign;  // section alignment
    uint64_t sh_entsize;    // entry size if section holds table
} Elf64_Shdr;

// Values for compression header sections
#define ELFCOMPRESS_ZLIB    1
#define ELFCOMPRESS_ZSTD    2
#define ELFCOMPRESS_LOOS    0x60000000
#define ELFCOMPRESS_HIOS    0x6fffffff
#define ELFCOMPRESS_LOPROC  0x70000000
#define ELFCOMPRESS_HIPROC  0x7fffffff
 
typedef struct _Elf32_Chdr
{
    uint32_t ch_type;
    uint32_t ch_size;
    uint32_t ch_addralign;
} Elf32_Chdr;
 
typedef struct _Elf64_Chdr
{
    uint32_t ch_type;
    uint32_t ch_reserved;
    uint64_t ch_size;
    uint64_t ch_addralign;
} Elf64_Chdr;

#define EI_MAG0         0   /* e_ident[] indexes */
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_OSABI        7
#define EI_ABIVERSION   8
#define EI_PAD          9
 
#define ELFMAG0         0x7f    /* EI_MAG */
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'
#define ELFMAG          "\177ELF"
#define SELFMAG         4
 
#define ELFCLASSNONE    0   /* EI_CLASS */
#define ELFCLASS32      1
#define ELFCLASS64      2
#define ELFCLASSNUM     3
 
#define ELFDATANONE     0   /* e_ident[EI_DATA] */
#define ELFDATA2LSB     1
#define ELFDATA2MSB     2
 
#define EV_NONE         0   /* e_version, EI_VERSION */
#define EV_CURRENT      1
#define EV_NUM          2
 
/* OS ABI identification (EI_OSABI) */
#define ELFOSABI_NONE       0   /* UNIX System V ABI */
#define ELFOSABI_SYSV       0
#define ELFOSABI_HPUX       1
#define ELFOSABI_NETBSD     2
#define ELFOSABI_GNU        3
#define ELFOSABI_LINUX      3   /* alias for GNU */
#define ELFOSABI_SOLARIS    6
#define ELFOSABI_AIX        7
#define ELFOSABI_IRIX       8
#define ELFOSABI_FREEBSD    9
#define ELFOSABI_TRU64      10
#define ELFOSABI_MODESTO    11
#define ELFOSABI_OPENBSD    12
#define ELFOSABI_OPENVMS    13
#define ELFOSABI_NSK        14
#define ELFOSABI_AROS       15
#define ELFOSABI_FENIXOS    16
#define ELFOSABI_CLOUDABI   17
#define ELFOSABI_OPENVOS    18
#define ELFOSABI_ARM_AEABI  64
#define ELFOSABI_ARM        97
#define ELFOSABI_STANDALONE 255
 
#ifndef ELF_OSABI
#define ELF_OSABI ELFOSABI_NONE
#endif

/* Note definitions: NN_ defines names. NT_ defines types. */

#define NN_GNU_PROPERTY_TYPE_0  "GNU"
#define NT_GNU_PROPERTY_TYPE_0  5
 
/* GNU note types found in .note.gnu.* (name == "GNU") */
#define NT_GNU_ABI_TAG          1
#define NT_GNU_HWCAP            2
#define NT_GNU_BUILD_ID         3
#define NT_GNU_GOLD_VERSION     4

/*
 * Notes used in ET_CORE. Architectures export some of the arch register sets
 * using the corresponding note types via the PTRACE_GETREGSET and
 * PTRACE_SETREGSET requests.
 */
#define NN_PRSTATUS	    "CORE"
#define NT_PRSTATUS	    1
#define NN_PRFPREG	    "CORE"
#define NT_PRFPREG	    2
#define NN_PRPSINFO	    "CORE"
#define NT_PRPSINFO	    3
#define NN_TASKSTRUCT	"CORE"
#define NT_TASKSTRUCT	4
#define NN_AUXV		    "CORE"
#define NT_AUXV		    6
/*
 * Note to userspace developers: size of NT_SIGINFO note may increase
 * in the future to accomodate more fields, don't assume it is fixed!
 */
#define NN_SIGINFO      "CORE"
#define NT_SIGINFO      0x53494749
#define NN_FILE         "CORE"
#define NT_FILE         0x46494c45
#define NN_PRXFPREG     "LINUX"
#define NT_PRXFPREG     0x46e62b7f      /* copied from gdb5.1/include/elf/common.h */
#define NN_PPC_VMX	    "LINUX"
#define NT_PPC_VMX	    0x100		/* PowerPC Altivec/VMX registers */
#define NN_PPC_SPE	    "LINUX"
#define NT_PPC_SPE	    0x101		/* PowerPC SPE/EVR registers */
#define NN_PPC_VSX	    "LINUX"
#define NT_PPC_VSX	    0x102		/* PowerPC VSX registers */
#define NN_PPC_TAR	    "LINUX"
#define NT_PPC_TAR	    0x103		/* Target Address Register */
#define NN_PPC_PPR	    "LINUX"
#define NT_PPC_PPR	    0x104		/* Program Priority Register */
#define NN_PPC_DSCR	    "LINUX"
#define NT_PPC_DSCR	    0x105		/* Data Stream Control Register */
#define NN_PPC_EBB	    "LINUX"
#define NT_PPC_EBB	    0x106		/* Event Based Branch Registers */
#define NN_PPC_PMU	    "LINUX"
#define NT_PPC_PMU	    0x107		/* Performance Monitor Registers */
#define NN_PPC_TM_CGPR	"LINUX"
#define NT_PPC_TM_CGPR	0x108		/* TM checkpointed GPR Registers */
#define NN_PPC_TM_CFPR	"LINUX"
#define NT_PPC_TM_CFPR	0x109		/* TM checkpointed FPR Registers */
#define NN_PPC_TM_CVMX	"LINUX"
#define NT_PPC_TM_CVMX	0x10a		/* TM checkpointed VMX Registers */
#define NN_PPC_TM_CVSX	"LINUX"
#define NT_PPC_TM_CVSX	0x10b		/* TM checkpointed VSX Registers */
#define NN_PPC_TM_SPR	"LINUX"
#define NT_PPC_TM_SPR	0x10c		/* TM Special Purpose Registers */
#define NN_PPC_TM_CTAR	"LINUX"
#define NT_PPC_TM_CTAR	0x10d		/* TM checkpointed Target Address Register */
#define NN_PPC_TM_CPPR	"LINUX"
#define NT_PPC_TM_CPPR	0x10e		/* TM checkpointed Program Priority Register */
#define NN_PPC_TM_CDSCR	"LINUX"
#define NT_PPC_TM_CDSCR	0x10f		/* TM checkpointed Data Stream Control Register */
#define NN_PPC_PKEY	    "LINUX"
#define NT_PPC_PKEY	    0x110		/* Memory Protection Keys registers */
#define NN_PPC_DEXCR	"LINUX"
#define NT_PPC_DEXCR	0x111		/* PowerPC DEXCR registers */
#define NN_PPC_HASHKEYR	"LINUX"
#define NT_PPC_HASHKEYR	0x112		/* PowerPC HASHKEYR register */
#define NN_386_TLS	    "LINUX"
#define NT_386_TLS	    0x200		/* i386 TLS slots (struct user_desc) */
#define NN_386_IOPERM	"LINUX"
#define NT_386_IOPERM	0x201		/* x86 io permission bitmap (1=deny) */
#define NN_X86_XSTATE	"LINUX"
#define NT_X86_XSTATE	0x202		/* x86 extended state using xsave */
/* Old binutils treats 0x203 as a CET state */
#define NN_X86_SHSTK	"LINUX"
#define NT_X86_SHSTK	0x204		/* x86 SHSTK state */
#define NN_X86_XSAVE_LAYOUT	"LINUX"
#define NT_X86_XSAVE_LAYOUT	0x205	/* XSAVE layout description */
#define NN_S390_HIGH_GPRS	"LINUX"
#define NT_S390_HIGH_GPRS	0x300	/* s390 upper register halves */
#define NN_S390_TIMER	"LINUX"
#define NT_S390_TIMER	0x301		/* s390 timer register */
#define NN_S390_TODCMP	"LINUX"
#define NT_S390_TODCMP	0x302		/* s390 TOD clock comparator register */
#define NN_S390_TODPREG	"LINUX"
#define NT_S390_TODPREG	0x303		/* s390 TOD programmable register */
#define NN_S390_CTRS	"LINUX"
#define NT_S390_CTRS	0x304		/* s390 control registers */
#define NN_S390_PREFIX	"LINUX"
#define NT_S390_PREFIX	0x305		/* s390 prefix register */
#define NN_S390_LAST_BREAK	"LINUX"
#define NT_S390_LAST_BREAK	0x306	/* s390 breaking event address */
#define NN_S390_SYSTEM_CALL	"LINUX"
#define NT_S390_SYSTEM_CALL	0x307	/* s390 system call restart data */
#define NN_S390_TDB	"LINUX"
#define NT_S390_TDB	0x308		/* s390 transaction diagnostic block */
#define NN_S390_VXRS_LOW	"LINUX"
#define NT_S390_VXRS_LOW	0x309	/* s390 vector registers 0-15 upper half */
#define NN_S390_VXRS_HIGH	"LINUX"
#define NT_S390_VXRS_HIGH	0x30a	/* s390 vector registers 16-31 */
#define NN_S390_GS_CB	"LINUX"
#define NT_S390_GS_CB	0x30b		/* s390 guarded storage registers */
#define NN_S390_GS_BC	"LINUX"
#define NT_S390_GS_BC	0x30c		/* s390 guarded storage broadcast control block */
#define NN_S390_RI_CB	"LINUX"
#define NT_S390_RI_CB	0x30d		/* s390 runtime instrumentation */
#define NN_S390_PV_CPU_DATA	"LINUX"
#define NT_S390_PV_CPU_DATA	0x30e	/* s390 protvirt cpu dump data */
#define NN_ARM_VFP	"LINUX"
#define NT_ARM_VFP	0x400		/* ARM VFP/NEON registers */
#define NN_ARM_TLS	"LINUX"
#define NT_ARM_TLS	0x401		/* ARM TLS register */
#define NN_ARM_HW_BREAK	"LINUX"
#define NT_ARM_HW_BREAK	0x402		/* ARM hardware breakpoint registers */
#define NN_ARM_HW_WATCH	"LINUX"
#define NT_ARM_HW_WATCH	0x403		/* ARM hardware watchpoint registers */
#define NN_ARM_SYSTEM_CALL	"LINUX"
#define NT_ARM_SYSTEM_CALL	0x404	/* ARM system call number */
#define NN_ARM_SVE	"LINUX"
#define NT_ARM_SVE	0x405		/* ARM Scalable Vector Extension registers */
#define NN_ARM_PAC_MASK		"LINUX"
#define NT_ARM_PAC_MASK		0x406	/* ARM pointer authentication code masks */
#define NN_ARM_PACA_KEYS	"LINUX"
#define NT_ARM_PACA_KEYS	0x407	/* ARM pointer authentication address keys */
#define NN_ARM_PACG_KEYS	"LINUX"
#define NT_ARM_PACG_KEYS	0x408	/* ARM pointer authentication generic key */
#define NN_ARM_TAGGED_ADDR_CTRL	"LINUX"
#define NT_ARM_TAGGED_ADDR_CTRL	0x409	/* arm64 tagged address control (prctl()) */
#define NN_ARM_PAC_ENABLED_KEYS	"LINUX"
#define NT_ARM_PAC_ENABLED_KEYS	0x40a	/* arm64 ptr auth enabled keys (prctl()) */
#define NN_ARM_SSVE	"LINUX"
#define NT_ARM_SSVE	0x40b		/* ARM Streaming SVE registers */
#define NN_ARM_ZA	"LINUX"
#define NT_ARM_ZA	0x40c		/* ARM SME ZA registers */
#define NN_ARM_ZT	"LINUX"
#define NT_ARM_ZT	0x40d		/* ARM SME ZT registers */
#define NN_ARM_FPMR	"LINUX"
#define NT_ARM_FPMR	0x40e		/* ARM floating point mode register */
#define NN_ARM_POE	"LINUX"
#define NT_ARM_POE	0x40f		/* ARM POE registers */
#define NN_ARM_GCS	"LINUX"
#define NT_ARM_GCS	0x410		/* ARM GCS state */
#define NN_ARC_V2	"LINUX"
#define NT_ARC_V2	0x600		/* ARCv2 accumulator/extra registers */
#define NN_VMCOREDD	"LINUX"
#define NT_VMCOREDD	0x700		/* Vmcore Device Dump Note */
#define NN_MIPS_DSP	"LINUX"
#define NT_MIPS_DSP	0x800		/* MIPS DSP ASE registers */
#define NN_MIPS_FP_MODE	"LINUX"
#define NT_MIPS_FP_MODE	0x801		/* MIPS floating-point mode */
#define NN_MIPS_MSA	"LINUX"
#define NT_MIPS_MSA	0x802		/* MIPS SIMD registers */
#define NN_RISCV_CSR	"LINUX"
#define NT_RISCV_CSR	0x900		/* RISC-V Control and Status Registers */
#define NN_RISCV_VECTOR	"LINUX"
#define NT_RISCV_VECTOR	0x901		/* RISC-V vector registers */
#define NN_RISCV_TAGGED_ADDR_CTRL "LINUX"
#define NT_RISCV_TAGGED_ADDR_CTRL 0x902	/* RISC-V tagged address control (prctl()) */
#define NN_RISCV_USER_CFI	"LINUX"
#define NT_RISCV_USER_CFI	0x903		/* RISC-V shadow stack state */
#define NN_LOONGARCH_CPUCFG	"LINUX"
#define NT_LOONGARCH_CPUCFG	0xa00	/* LoongArch CPU config registers */
#define NN_LOONGARCH_CSR	"LINUX"
#define NT_LOONGARCH_CSR	0xa01	/* LoongArch control and status registers */
#define NN_LOONGARCH_LSX	"LINUX"
#define NT_LOONGARCH_LSX	0xa02	/* LoongArch Loongson SIMD Extension registers */
#define NN_LOONGARCH_LASX	"LINUX"
#define NT_LOONGARCH_LASX	0xa03	/* LoongArch Loongson Advanced SIMD Extension registers */
#define NN_LOONGARCH_LBT	"LINUX"
#define NT_LOONGARCH_LBT	0xa04	/* LoongArch Loongson Binary Translation registers */
#define NN_LOONGARCH_HW_BREAK	"LINUX"
#define NT_LOONGARCH_HW_BREAK	0xa05   /* LoongArch hardware breakpoint registers */
#define NN_LOONGARCH_HW_WATCH	"LINUX"
#define NT_LOONGARCH_HW_WATCH	0xa06   /* LoongArch hardware watchpoint registers */

// Note head in a PT_NOTE section
typedef struct _Elf32_Nhdr 
{
    uint32_t n_namesz;  // name size
    uint32_t n_descsz;  // content size
    uint32_t n_type;    // content type
} Elf32_Nhdr;

// Note head in a PT_NOTE section
typedef struct _Elf64_Nhdr
{
    uint32_t n_namesz;  // name size
    uint32_t n_descsz;  // content size
    uint32_t n_type;    // content type
} Elf64_Nhdr;

/* .note.gnu.property types for EM_AARCH64: */
#define GNU_PROPERTY_AARCH64_FEATURE_1_AND  0xc0000000
 
/* Bits for GNU_PROPERTY_AARCH64_FEATURE_1_BTI */
#define GNU_PROPERTY_AARCH64_FEATURE_1_BTI  (1U << 0)
#define GNU_PROPERTY_AARCH64_FEATURE_1_PAC  (1U << 1)
 
/* .note.gnu.property types for EM_X86_64 / EM_386: */
#define GNU_PROPERTY_X86_FEATURE_1_AND      0xc0000002
#define GNU_PROPERTY_X86_FEATURE_1_IBT      (1U << 0)
#define GNU_PROPERTY_X86_FEATURE_1_SHSTK    (1U << 1)

// values for auxiliary vector
#define AT_NULL          0
#define AT_IGNORE        1
#define AT_EXECFD        2
#define AT_PHDR          3
#define AT_PHENT         4
#define AT_PHNUM         5
#define AT_PAGESZ        6
#define AT_BASE          7
#define AT_FLAGS         8
#define AT_ENTRY         9
#define AT_NOTELF        10
#define AT_UID           11
#define AT_EUID          12
#define AT_GID           13
#define AT_EGID          14
#define AT_PLATFORM      15
#define AT_HWCAP         16
#define AT_CLKTCK        17
#define AT_SECURE        23
#define AT_BASE_PLATFORM 24
#define AT_RANDOM        25
#define AT_HWCAP2        26
#define AT_RSEQ_FEATURE_SIZE 27
#define AT_RSEQ_ALIGN    28
#define AT_HWCAP3        29
#define AT_HWCAP4        30
#define AT_EXECFN        31
#define AT_SYSINFO       32
#define AT_SYSINFO_EHDR  33
#define AT_MINSIGSTKSZ   51
 
typedef struct _Elf32_auxv_t
{
    uint32_t a_type;
    union
    {
        uint32_t a_val;
    } a_un;
} Elf32_auxv_t;
 
typedef struct _Elf64_auxv_t
{
    uint64_t a_type;
    union
    {
        uint64_t a_val;
    } a_un;
} Elf64_auxv_t;

// Versym values 
#define VER_NDX_LOCAL     0
#define VER_NDX_GLOBAL    1
#define VER_NDX_LORESERVE 0xff00
#define VER_NDX_ELIMINATE 0xff01
#define VER_NDX_HIDDEN    0x8000     // high bit = hidden symbol 
#define VER_NDX_VERSION   0x7fff
 
// Verdef revision values 
#define VER_DEF_NONE     0
#define VER_DEF_CURRENT  1
#define VER_DEF_NUM      2
 
// Verneed revision values
#define VER_NEED_NONE    0
#define VER_NEED_CURRENT 1
#define VER_NEED_NUM     2
 
typedef uint16_t Elf32_Versym;
typedef uint16_t Elf64_Versym;

typedef struct _Elf32_Verdef
{
    uint16_t vd_version;
    uint16_t vd_flags;
    uint16_t vd_ndx;
    uint16_t vd_cnt;
    uint32_t vd_hash;
    uint32_t vd_aux;
    uint32_t vd_next;
} Elf32_Verdef;
 
typedef struct _Elf64_Verdef
{
    uint16_t vd_version;
    uint16_t vd_flags;
    uint16_t vd_ndx;
    uint16_t vd_cnt;
    uint32_t vd_hash;
    uint32_t vd_aux;
    uint32_t vd_next;
} Elf64_Verdef;
 
typedef struct _Elf32_Verdaux
{
    uint32_t vda_name;
    uint32_t vda_next;
} Elf32_Verdaux;
 
typedef struct _Elf64_Verdaux
{
    uint32_t vda_name;
    uint32_t vda_next;
} Elf64_Verdaux;
 
typedef struct _Elf32_Verneed
{
    uint16_t vn_version;
    uint16_t vn_cnt;
    uint32_t vn_file;
    uint32_t vn_aux;
    uint32_t vn_next;
} Elf32_Verneed;
 
typedef struct _Elf64_Verneed
{
    uint16_t vn_version;
    uint16_t vn_cnt;
    uint32_t vn_file;
    uint32_t vn_aux;
    uint32_t vn_next;
} Elf64_Verneed;
 
typedef struct _Elf32_Vernaux
{
    uint32_t vna_hash;
    uint16_t vna_flags;
    uint16_t vna_other;
    uint32_t vna_name;
    uint32_t vna_next;
} Elf32_Vernaux;
 
typedef struct _Elf64_Vernaux
{
    uint32_t vna_hash;
    uint16_t vna_flags;
    uint16_t vna_other;
    uint32_t vna_name;
    uint32_t vna_next;
} Elf64_Vernaux;

#define ELF_R_SYM(i, is64)  ((is64) ? ELF64_R_SYM(i)  : ELF32_R_SYM(i))
#define ELF_R_TYPE(i, is64) ((is64) ? ELF64_R_TYPE(i) : ELF32_R_TYPE(i))

#endif // !COMMON_ELFDEF_H