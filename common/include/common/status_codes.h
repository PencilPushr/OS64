#ifndef COMMON_STATUS_CODES_H
#define COMMON_STATUS_CODES_H

#include "status.h"
#include "status_facility.h"

/*
 * Pre-built status codes.
 *
 * Pattern:  MAKE_STATUS( SEVERITY_xxx,  SCOPE_xxx,  CODE_xxx )
 *                         ^^^^^^^^^^^   ^^^^^^^^^   ^^^^^^^^
 *                         how bad?      where?      what?
 *
 * Reads like C++ scope resolution - each field narrows the meaning.
 */

/* 
 * General
 */
#define STATUS_INVALID_ARGUMENT                                           \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GENERAL, CODE_INVALID_PARAM)
 
#define STATUS_NOT_IMPLEMENTED                                            \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GENERAL, CODE_UNSUPPORTED)

#define STATUS_ERROR                                                      \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GENERAL, CODE_GENERIC_ERROR)

/* 
 * Memory 
 */
#define STATUS_OUT_OF_MEMORY                                              \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_MM, CODE_NO_MEMORY)
 
/* 
 * Graphics / Fonts 
 */
#define STATUS_INVALID_PSF2_MAGIC                                         \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_INVALID_MAGIC)
 
#define STATUS_INVALID_PSF2_HEADER                                        \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_INVALID_HEADER)
 
#define STATUS_UNSUPPORTED_PSF2_VERSION                                   \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_BAD_VERSION)
 
#define STATUS_BAD_PSF2_GLYPH_DATA                                        \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_BAD_GLYPH_DATA)
 
#define STATUS_PSF2_OVERFLOW                                              \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_OVERFLOW)
 

#define STATUS_FRAMEBUFFER_WAS_NULL                                       \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GFX, CODE_NULL_FRAMEBUFF)


// krnl 
#define STATUS_INVALID_BOOT_INFO \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_KRNL, CODE_INVALID_PARAM)

#endif