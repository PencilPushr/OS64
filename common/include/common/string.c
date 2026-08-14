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

    while ( Count-- > 0 )
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

void *
memcpy(
    void * restrict Dst,
    const void * restrict Src,
    size_t Size
)
{
    uint8_t* D = ( uint8_t * ) Dst;
    const uint8_t* S = ( const uint8_t * ) Src;

    while ( Size-- )
    {
        *D++ = *S++;
    }

    return Dst;

}

void *
memmove(
    void *Dst,
    const void *Src,
    size_t Size
)
{
    uint8_t* D = ( uint8_t * ) Dst;
    const uint8_t* S = ( const uint8_t * ) Src;

    if ( D == S || Size == 0 )
        return Dst;

    if ( S > D )    // Src ahead of Dst -> writes trail reads -> forward is safe
    {
        while ( Size-- )
        {
            *D++ = *S++;
        }
    }
    else            // Dst ahead of Src -> forward would write to unread Src -> backward
    {
        D += Size - 1;
        S += Size - 1;

        while ( Size-- )
        {
            *D-- = *S--;
        }
    }

    return Dst;
}

void *
memset(
    void *Dst,
    int Value,
    size_t Size
)
{
    uint8_t* D      = ( uint8_t * ) Dst;
    const uint8_t V = ( uint8_t ) Value;

    while ( Size-- )
    {
        *D++ = V;
    }

    return Dst;
}