#ifndef COMMON_STATUS_H
#define COMMON_STATUS_H

#include <stdint.h>

/*
 * Status code layout (32-bit):
 *
 *   [31..30]  Severity  (2 bits)   — OK / WARN / ERROR / FATAL
 *   [29..16]  Scope     (14 bits)  — subsystem (GFX, FS, MM …)
 *   [15.. 0]  Code      (16 bits)  — specific error within that scope
 *
 * Usage:  MAKE_STATUS( SEVERITY_xxx, SCOPE_xxx, CODE_xxx )
 *
 * The future idea is to be able to OR the result of multiple error
 * categories for more verbose logging.  For now this is effectively
 * equivalent to errno() / GetLastError().
 */
typedef uint32_t GLOBAL_STATUS;

extern uint32_t g_GlobalError;

#define SEVERITY_SHIFT 30u
#define SCOPE_SHIFT  16u

#define SEVERITY_MASK   0xC0000000u   /* bits [31..30] */
#define SCOPE_MASK      0x3FFF0000u   /* bits [29..16] */
#define CODE_MASK       0x0000FFFFu   /* bits [15.. 0] */

#define SEVERITY_OK     0u
#define SEVERITY_WARN   1u
#define SEVERITY_ERROR  2u
#define SEVERITY_FATAL  3u

#define MAKE_STATUS( Severity, Scope, Code )                      \
    ( ( ( (GLOBAL_STATUS)( Severity ) & 0x3    )  << SEVERITY_SHIFT )    | \
      ( ( (GLOBAL_STATUS)( Scope )    & 0x3FFF )  << SCOPE_SHIFT )       | \
        ( (GLOBAL_STATUS)( Code )     & 0xFFFF ) )

/*
 *    Convenience wrappers
 */
#define SEVERITY_FROM_STATUS( Status ) ( ( ( (GLOBAL_STATUS)( Status ) ) >> SEVERITY_SHIFT ) & 0x3u )
#define SCOPE_FROM_STATUS( Status )    ( ( ( (GLOBAL_STATUS)( Status ) ) >> SCOPE_SHIFT ) & 0x3FFFu )
#define CODE_FROM_STATUS( Status )         ( (GLOBAL_STATUS)( Status ) & 0xFFFFu )

/*
 *    Convenience wrappers
 */
#define OK                  ( MAKE_STATUS( SEVERITY_OK, 0, 0 ) )
#define FAILED( Status )    ( SEVERITY_FROM_STATUS( Status ) >= SEVERITY_ERROR )
#define SUCCEEDED( Status ) ( !FAILED( Status ) )


#endif // !COMMON_STATUS_H