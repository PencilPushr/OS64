#ifndef COMMON_STATUS_FACILITY_H
#define COMMON_STATUS_FACILITY_H
// common/

/*
 * SCOPE  — the subsystem that produced the status.
 * CODE   — the specific condition within that scope.
 *
 * Together with a severity they form a GLOBAL_STATUS via MAKE_STATUS().
 *
 * Convention: generic codes live in the low range (0x0000 – 0x00FF).
 *             Scope-specific codes start at 0x0100 and are grouped by
 *             their owning scope in the comments below.
 */


typedef enum _SCOPE
{
    SCOPE_GENERAL = 0,
    SCOPE_ARCH,
    SCOPE_KRNL,
    SCOPE_MM,
    SCOPE_MSR,
    SCOPE_PMU,
    SCOPE_BL,
    SCOPE_GFX,
    SCOPE_FS,
    SCOPE_EFI
} SCOPE;

typedef enum _CODE
{
    /* ---- Generic (usable with any scope) 0x0000 – 0x00FF ---- */
    CODE_SUCCESS          = 0x0000,
    CODE_UNSUPPORTED      = 0x0001,
    CODE_INVALID_PARAM    = 0x0002,
    CODE_NO_MEMORY        = 0x0003,
    CODE_NOT_FOUND        = 0x0004,
    CODE_ALREADY_EXISTS   = 0x0005,
    CODE_TIMEOUT          = 0x0006,
    CODE_UNKNOWN_ERROR    = 0x0007,
 
    /* ---- SCOPE_GFX / Font  0x0100 – 0x01FF ---- */
    CODE_INVALID_MAGIC    = 0x0100,
    CODE_INVALID_HEADER   = 0x0101,
    CODE_BAD_VERSION      = 0x0102,
    CODE_BAD_GLYPH_DATA   = 0x0103,
    CODE_OVERFLOW         = 0x0104,
 
    /* ---- SCOPE_FS          0x0200 – 0x02FF ---- */
    CODE_FILE_NOT_FOUND   = 0x0200,
    CODE_READ_ERROR       = 0x0201,
    CODE_WRITE_ERROR      = 0x0202,
 
    /* ---- SCOPE_MM          0x0300 – 0x03FF ---- */
    /* (CODE_NO_MEMORY from generic range covers the common case) */
 
} CODE;



#endif