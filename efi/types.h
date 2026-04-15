// efi/types.h
// Fundamental UEFI types from UEFI Specification 2.10, Section 2.3
// Written from scratch based on the spec
#pragma once

#include <stdint.h>

//=============================================================================
// Basic Types (UEFI Spec 2.3.1)
//=============================================================================

typedef uint8_t   UINT8;
typedef uint16_t  UINT16;
typedef uint32_t  UINT32;
typedef uint64_t  UINT64;
typedef int8_t    INT8;
typedef int16_t   INT16;
typedef int32_t   INT32;
typedef int64_t   INT64;

typedef UINT8     BOOLEAN;
typedef UINT16    CHAR16;     // UCS-2 character
typedef void      VOID;

// Native width types (64-bit on x64)
typedef UINT64    UINTN;
typedef INT64     INTN;

// Pointer and handle types
typedef VOID     *EFI_HANDLE;
typedef VOID     *EFI_EVENT;
typedef UINT64    EFI_STATUS;
typedef UINT64    EFI_TPL;
typedef UINT64    EFI_LBA;
typedef UINT64    EFI_PHYSICAL_ADDRESS;
typedef UINT64    EFI_VIRTUAL_ADDRESS;

#define TRUE  1
#define FALSE 0

// Despite how this seems redundant - The UEFI spec defines it, so I thought it was worth implementing.
#ifndef NULL
    #define NULL  ((void *)0)
#endif

//=============================================================================
// Status Codes (UEFI Spec Appendix D)
//=============================================================================

/*
    In progress - Don't quite understand how to implement this at the moment
*/

#define EFI_SUCCESS 0ULL;

// Error codes have the high bit set

#define EFI_ERROR_BIT ( 1ULL << 63 )
#define EFI_ERROR(status)     ( (status) & EFI_ERROR_BIT )

// Other errors ... "In progress"

//=============================================================================
// GUID Structure (UEFI Spec 2.3.1)
//=============================================================================
