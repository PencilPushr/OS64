#include "string.h"

int
memcmp(
    const void* Str1,
    const void* Str2,
    size_t Count
)
{
    register const uint8_t* S1 = ( const uint8_t * ) Str1;
    register const uint8_t* S2 = ( const uint8_t * ) Str2;

    while (Count-- > 0)
    {
        if (*S1++ != *S2++)
            return S1[-1] < S2[-1] ? -1 : 1;
    }

    return 0;
}

/* Courtesy of Godbolt - gcc 16.1 -O1 produces: 
"memcmp":
        mov     eax, 0
.L2:
        cmp     rdx, rax
        je      .L7
        movzx   r8d, BYTE PTR [rdi+rax]
        add     rax, 1
        movzx   ecx, BYTE PTR [rsi-1+rax]
        cmp     r8b, cl
        je      .L2
        sbb     eax, eax
        or      eax, 1
        ret
.L7:
        mov     eax, 0
        ret
*/

void
memcpy(
    void* Src,
    void* Dst,
    size_t Size
)
{
    if ( Src > Dst ) // In front of Dst -> copy forwards
    {
        const uint8_t * S = ( const uint8_t * ) Src;
        uint8_t * D = ( uint8_t * ) Dst;
        
        while ( Size-- )
        {
            *D++ = *S++;
        }
        
    }
    else
    {
        const uint8_t * Sback = ( const uint8_t * ) Src + ( Size - 1 );
        uint8_t * Dback = ( uint8_t * ) Dst + ( Size - 1);

        while ( Size-- )
        {
            *Dback-- = *Sback--;
        }
    }
}