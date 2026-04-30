#ifndef COMMON_STATUS_H
#define COMMON_STATUS_H

#include <stdint.h>

/*
* The future idea for this is to be able to OR the result of multiple error categories, for example Graphics and others
* To give more verbose logging functionality.
* For now this is effecitively equivalent to errno() and GetLastError()
*/
uint32_t g_GlobalError = 0;

typedef uint32_t GLOBAL_STATUS

#define SEVERITY_SHIFT 30u
#define FACILITY_SHIFT 16u

#define SEVERITY_MASK(x) (x & ~0x3FFF_FFFF)

#define SEVERITY_OK     0u
#define SEVERITY_WARN   1u
#define SEVERITY_ERROR  2u
#define SEVERITY_FATAL  3u

#define MAKE_STATUS( Severity, Scope, Code )                      \
    ( ( ( (GLOBAL_STATUS)( Severity ) & 0x3 ) << SEVERITY_SHIFT )    | \
      ( ( (GLOBAL_STATUS)( Scope ) & 0x3FFF ) << SCOPE_SHIFT )       | \
        ( (GLOBAL_STATUS)( Code ) & 0xFFFF ) )

#define SEVERITY_FROM_STATUS( Status ) ( ( ( (GLOBAL_STATUS)( Status ) ) >> SEVERITY_SHIFT ) & 0x3 )
#define SCOPE_FROM_STATUS( Status )    ( ( ( (GLOBAL_STATUS)( Status ) ) >> SCOPE_SHIFT ) & 0x3FFF )
#define CODE_FROM_STATUS( Status )         ( (GLOBAL_STATUS)( Status ) & 0xFFFF )

#define OK                  ( MAKE_STATUS( SEVERITY_OK, 0, 0 ) )
#define FAILED( Status )    ( SEVERITY_FROM_STATUS( Status ) >= SEVERITY_ERROR )
#define SUCCEEDED( Status ) ( !FAILED( Status ) )


#endif // !COMMON_STATUS_H