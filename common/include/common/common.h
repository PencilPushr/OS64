#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

// Stops GCC crying about unreferenced paramters...
#define UNREFERENCED_PARAMETER( P ) ((void)(P))

// packs bytes into desired size with little endianess
#define PACK_UNSIGNED_WORD( a, b )                    ( ( (uint16_t)(a) ) | ( (uint16_t)(b) << 8 ) )
#define PACK_UNSIGNED_DWORD( a, b, c, d )             ( ( (uint32_t)PACK_UNSIGNED_WORD( a, b ) ) | ( (uint32_t)PACK_UNSIGNED_WORD( c, d ) << 16 ) )
#define PACK_UNSIGNED_QWORD( a, b, c, d, e, f, g, h ) ( ( (uint64_t)PACK_UNSIGNED_DWORD( a, b, c, d ) ) | ( (uint64_t)PACK_UNSIGNED_DWORD( e, f, g, h ) << 32 ) )

// to retrieve low/high sets
#define LOW_BYTE(a)        ((uint8_t)((uint16_t)(a) & 0xFFu))
#define HIGH_BYTE(a)       ((uint8_t)(((uint16_t)(a) >> 8) & 0xFFu))
    
#define LOW_WORD(a)        ((uint16_t)((uint32_t)(a) & 0xFFFFu))
#define HIGH_WORD(a)       ((uint16_t)(((uint32_t)(a) >> 16) & 0xFFFFu))
    
#define LOW_DWORD(a)       ((uint32_t)((uint64_t)(a) & 0xFFFFFFFFull))
#define HIGH_DWORD(a)      ((uint32_t)(((uint64_t)(a) >> 32) & 0xFFFFFFFFull))

#define LOW_QWORD128(a)   ((uint64_t)((__uint128_t)(a) & 0xFFFFFFFFFFFFFFFFull))
#define HIGH_QWORD128(a)  ((uint64_t)(((__uint128_t)(a) >> 64) & 0xFFFFFFFFFFFFFFFFull))

#ifndef _In_
#define _In_
#endif
#ifndef _In_opt_
#define _In_opt_
#endif
#ifndef _Inout_
#define _Inout_
#endif
#ifndef _Inout_opt_
#define _Inout_opt_
#endif
#ifndef _Out_
#define _Out_
#endif
#ifndef _Out_opt_
#define _Out_opt_
#endif

#ifndef static_assert
#define static_assert _Static_assert
#endif


#endif // !COMMON_COMMON_H