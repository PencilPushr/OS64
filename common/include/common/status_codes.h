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
 * Reads like C++ scope resolution — each field narrows the meaning.
 */
 
/* 
 * General
 */
#define STATUS_INVALID_ARGUMENT                                           \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GENERAL, CODE_INVALID_PARAM)
 
#define STATUS_NOT_IMPLEMENTED                                            \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_GENERAL, CODE_UNSUPPORTED)
 
/* 
 * Memory 
 */
#define STATUS_OUT_OF_MEMORY                                              \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_MM, CODE_NO_MEMORY)
 
/* 
 * File system 
 */
#define STATUS_NOT_FOUND                                                  \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_FS, CODE_FILE_NOT_FOUND)
 
#define STATUS_READ_ERROR                                                 \
    MAKE_STATUS(SEVERITY_ERROR, SCOPE_FS, CODE_READ_ERROR)
 
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
 

#endif